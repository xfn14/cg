#include "main.h"

string filename;
World world;
int degree = 0, axisOnOff = 1;

void changeSize(int w, int h) {
    if (h == 0) h = 1;
    float ratio = w * 1.0f / h;
    Camera camera = world.getCamera();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.getFov(), ratio, camera.getNear(), camera.getFar());
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void setCamera() {
    Camera camera = *(new Camera());
    // Camera camera = world.getCamera();
    Point pos = camera.getPosition(),
          center = camera.getLookAt(),
          up = camera.getUp();
    gluLookAt(
        pos.getX(), pos.getY(), pos.getZ(),
        center.getX(), center.getY(), center.getZ(),
        up.getX(), up.getY(), up.getZ()
    );
}

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
        for(Rotate rotate : rotates)
            glRotatef(rotate.getAngle(), rotate.getX(), rotate.getY(), rotate.getZ());

    vector<Translate> translates = group.getTranslate();
    if(!translates.empty())
        for(Translate translate : translates) {
            if (translate.getX() != -1 && translate.getY() != -1 && translate.getZ() != -1)
                glTranslatef(translate.getX(), translate.getY(), translate.getZ());
            else if(translate.getTime() != -1) {

                if(translate.getAlign()) {
                    glTranslatef(0.0f, 0.0f, translate.getTime());
                } else {
                    glTranslatef(0.0f, translate.getTime(), 0.0f);
                }
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
        for (Model model: models)
            model.drawModel(group.getColor());

    vector<Group> subGroups = group.getGroups();
    if (!subGroups.empty())
        for (Group g: subGroups)
            renderModels(g);

    glPopMatrix();
}

void renderScene(void) {
    static float t = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    setCamera();

    renderAxis();
    
    glRotatef(degree, 0, 1, 0);

    Model model;
    model.readModelPatch(filename);
    model.drawModel(*(new Color(255, 0, 0)));
    // renderModels(*world.getGroup());

    glutSwapBuffers();

    t += 0.01;
}

void keyboard(unsigned char key, int xmouse, int ymouse) {
    switch (key) {
        case 'f': // Eixos
            axisOnOff = !axisOnOff;
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

void printInfo() {
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}

int main(int argc, char** argv) {
    filename = argv[1];
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
    glutSpecialFunc(keyboard_special);
    glutKeyboardFunc(keyboard);

    // Settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialize window
    glutMainLoop();
    // Initialize the World
    // if(argc != 3) {
    //     cout << "./engine <path> <xml_file>" << endl;
    //     return 0;
    // }
    // string path = argv[1];
    // string xmlFile = argv[2];
    // world.parseXML(path, xmlFile);

    // Window settings
    // glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    // glutInitWindowPosition(100, 100);
    // glutInitWindowSize(800, 800);
    // glutCreateWindow("CG@GRUPO39@21/22");
    // printInfo();

    // // Handlers
    // glutReshapeFunc(changeSize);
    // glutIdleFunc(renderScene);
    // glutDisplayFunc(renderScene);
    // glutSpecialFunc(keyboard_special);
    // glutKeyboardFunc(keyboard);

    // // Settings
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // // Initialize window
    // glutMainLoop();

    return 1;
}