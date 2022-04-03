#include "main.h"

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
    Camera camera = world.getCamera();
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
        for(Translate translate : translates)
            glTranslatef(translate.getX(), translate.getY(), translate.getZ());

    vector<Scale> scales = group.getScale();
    if(!scales.empty())
        for(Scale scale : scales)
            glScalef(scale.getX(), scale.getY(), scale.getZ());
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    setCamera();
    renderAxis();
    glRotatef(degree,0,1,0);

    renderModels(*world.getGroup());

    glutSwapBuffers();
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
    // Initialize the World
    if(argc != 3) {
        cout << "./engine <path> <xml_file>" << endl;
        return 0;
    }
    string path = argv[1];
    string xmlFile = argv[2];
    world.parseXML(path, xmlFile);

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
    glutSpecialFunc(keyboard_special);
    glutKeyboardFunc(keyboard);

    // Settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialize window
    glutMainLoop();

    return 1;
}