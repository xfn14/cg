#include "main.h"

string filename;
World world;

int startX, startY, tracking = 0;
Camera camera;
Point pos,
      center,
      up;

float camX,camY,camZ;
int alpha = 0, beta = 0, r;

int tempo;
int degree = 0, axisOnOff = 1;

void changeSize(int w, int h) {
    if (h == 0) h = 1;
    float ratio = w * 1.0f / h;
    //Camera camera = world.getCamera();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(camera.getFov(), ratio, camera.getNear(), camera.getFar());
    glMatrixMode(GL_MODELVIEW);
}

//void setCamera() {
//    Camera camera = world.getCamera();
//    Point pos = camera.getPosition(),
//          center = camera.getLookAt(),
//          up = camera.getUp();
//
//    gluLookAt(
//        camX, camY, camZ,
//        center.getX(), center.getY(), center.getZ(),
//        up.getX(), up.getY(), up.getZ()
//    );
//}

void renderAxis() {
    if(axisOnOff) {
        glBegin(GL_LINES);

        // X Axis
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);

        // Y Axis
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);

        // Z Axis
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    
        glEnd();
    }
}

void transformacoes(Group group){
    vector<Rotate> rotates = group.getRotate();
    if(!rotates.empty())
        for(Rotate rotate : rotates) {
            if(rotate.getTime() != -1) {
                int t = floor((float) tempo / (float) 1000 / rotate.getTime());
                float p = ((float) tempo / (float) 1000 - t * rotate.getTime()) / rotate.getTime();
                rotate.setAngle(p * 360);
            }
            glRotatef(rotate.getAngle(), rotate.getX(), rotate.getY(), rotate.getZ());
        }

    vector<Translate> translates = group.getTranslate();
    if(!translates.empty())
        for(Translate translate : translates) {
            if (translate.getX() != -1)
                glTranslatef(translate.getX(), translate.getY(), translate.getZ());
            else if(translate.getTime() != -1) {
                float pos[3], deriv[3];
                translate.drawCatmullRomCurve();
                int t = floor((float) tempo / (float) 1000 / translate.getTime());
                float p = ((float) tempo / (float) 1000 - t * translate.getTime()) / translate.getTime();
                translate.getGlobalCatmullRomPoint(p, pos, deriv);
                // cout << "pos: " << pos[0] << " " << pos[1] << " " << pos[2] << endl;
                glTranslatef(pos[0], pos[1], pos[2]);
                float x[3] = {deriv[0], deriv[1], deriv[2]};
                normalize(x);
                float z[3];
                float y_0[3] = {0,1,0};
                cross(x,y_0,z);
                normalize(z);
                float y[3];
                cross(z,x,y);
                normalize(y);
                float m[16];
                buildRotMatrix(x,y,z,m);
                glMultMatrixf(m);
            }
        }

    vector<Scale> scales = group.getScale();
    if(!scales.empty())
        for(Scale scale : scales)
            glScalef(scale.getX(), scale.getY(), scale.getZ());
}

void Translate::getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float *pos, float *deriv) {
	float m[4][4] = 
        {
            {-0.5f,  1.5f, -1.5f,  0.5f},
            { 1.0f, -2.5f,  2.0f, -0.5f},
            {-0.5f,  0.0f,  0.5f,  0.0f},
            { 0.0f,  1.0f,  0.0f,  0.0f}
        };

    for(int i=0; i < 3; i++){
        float a[4], p[4] =
            {
                i == 0 ? p0.getX() : i == 1 ? p0.getY() : p0.getZ(),
                i == 0 ? p1.getX() : i == 1 ? p1.getY() : p1.getZ(),
                i == 0 ? p2.getX() : i == 1 ? p2.getY() : p2.getZ(),
                i == 0 ? p3.getX() : i == 1 ? p3.getY() : p3.getZ()
            };
        multMatrixVector(*m, p, a);
        pos[i] = pow(t,3.0) * a[0] + pow(t,2.0) * a[1] + t * a[2] + a[3];
        deriv[i] = 3 * powf(t,2.0) * a[0] + 2 * t * a[1] + a[2];
    }
}

void Translate::getGlobalCatmullRomPoint(float gt, float *point, float *deriv) {
    float t = gt * path.size();
    int index = floor(t);
    t = t - index;

    int p0, p1, p2, p3, size = path.size();
    p0 = (index + size - 1) % size;
	p1 = (p0 + 1) % size;
	p2 = (p1 + 1) % size; 
	p3 = (p2 + 1) % size;

    getCatmullRomPoint(t, path[p0], path[p1], path[p2], path[p3], point, deriv);
}

void Translate::drawCatmullRomCurve() {
    float gt = 0, pos[3], deriv[3];

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        getGlobalCatmullRomPoint(gt, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
        gt += 0.01;
    }
    glEnd();
}

void renderModels(Group group) {
    glPushMatrix();

    transformacoes(group);

    vector<Model> models = group.getModels();
    if (!models.empty())
        for (Model model: models) {
             //if(model.getVbo() == 0)
             //    model.initVbo();
            model.drawModel(group.getColor());
        }

    vector<Group> subGroups = group.getGroups();
    if (!subGroups.empty())
        for (Group g: subGroups)
            renderModels(g);
            
    glPopMatrix();
}

void Light::render() {
    GLfloat ambiente [4] = {0.2,0.2,0.2,1.0};
    GLfloat diff     [4] = {1.0,1.0,1.0,0.0};
    GLfloat spec     [4] = {1.0,1.0,1.0,1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);

    if(type == POINT || type == DIRECTIONAL) {
        float pose[4] = {pos.getX(), pos.getY(), pos.getZ(), type == POINT ? 1.0f : 0.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, pose);
    } else if(type == SPOTLIGHT) {
        float dire[3] = {dir.getX(), dir.getY(), dir.getZ()};
        float pose[4] = {pos.getX(), pos.getY(), pos.getZ(), 1};
        glLightfv(GL_LIGHT0, GL_POSITION, pose);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dire);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
    }
}

void renderScene(void) {
    tempo = glutGet(GLUT_ELAPSED_TIME);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    // cout << camera.getPosition().getX() << " " << camera.getPosition().getY() << " " << camera.getPosition().getZ() << endl;

    gluLookAt(
            camX, camY, camZ,
            center.getX(), center.getY(), center.getZ(),
            up.getX(), up.getY(), up.getZ()
    );

    renderAxis();
    
    //glRotatef(degree, 0, 1, 0);
    for(Light light : world.getLights())
        light.render();

    renderModels(*world.getGroup());

    glutSwapBuffers();
}

void keyboard(unsigned char key, int xmouse, int ymouse) {
    switch (key) {
        case 'f': // Eixos
            axisOnOff = !axisOnOff;
            break;
        case 'w':
            world.addPositionCamera(1, 0, 0);
            break;
        case 's':
            world.addPositionCamera(-1, 0, 0);
            break;
        case 'a':
            world.addPositionCamera(0, 1, 0);
            break;
        case 'd':
            world.addPositionCamera(0, -1, 0);
            break;
        case 'q':
            world.addPositionCamera(0, 0, 1);
            break;
        case 'e':
            world.addPositionCamera(0, 0, -1);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void keyboard_special(int key, int a, int b){
    // Rotações
    switch (key) {
        case GLUT_KEY_LEFT:
            ++degree;
            break;
        case GLUT_KEY_RIGHT:
            --degree;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN)  {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}


void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {
        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {
        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
    // world.addPositionCamera(camX,camY,camZ);
}

void printInfo() {
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}

void initGL() {

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glClearColor(0, 0, 0, 0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_TEXTURE_2D);

}

int main(int argc, char** argv) {
    // Initialize the World
    if(argc != 3) {
        cout << "./engine <path> <xml_file>" << endl;
        return 0;
    }
    string path = argv[1];
    string xmlFile = argv[2];

    // Window settings
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@GRUPO39@21/22");
    printInfo();

    // Handlers
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);

    //glutSpecialFunc(keyboard_special);
    //glutKeyboardFunc(keyboard);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

    // Settings
    glewInit();
    initGL();
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_RESCALE_NORMAL);

    world.parseXML(path, xmlFile);
    
    camera = world.getCamera();
    pos = camera.getPosition(); center = camera.getLookAt(); up = camera.getUp();
    camX = pos.getX(); camY = pos.getY(); camZ = pos.getZ();
    r = sqrt(pow(camX, 2) + pow(camY, 2) + pow(camZ, 2));

    // Initialize window
    glutMainLoop();

    return 1;
}