#include "main.h"

World world;

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

void renderModels(Group group) {
    glPushMatrix();
    vector<Translate> translates = group.getTranslate();
    if(translates.size() > 0 )
        for(Translate translate : translates)
            glTranslatef(translate.getX(), translate.getY(), translate.getZ());

    vector<Rotate> rotates = group.getRotate();
    if(rotates.size() > 0 )
        for(Rotate rotate : rotates)
            glRotatef(rotate.getAngle(), rotate.getX(), rotate.getY(), rotate.getZ());
    
    vector<Scale> scale = group.getScale();
    if(scale.size() > 0)
        for(Scale scale : scale)
            glScalef(scale.getX(), scale.getY(), scale.getZ());
    
    vector<Model> models = group.getModels();
    
    if(models.size() > 0)
        for(Model model : models)
            model.drawModel();

    vector<Group> subGroups = group.getGroups();
    if(subGroups.size() > 0)
        for(Group g : subGroups)
            renderModels(g);
    
    glPopMatrix();
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    setCamera();
    renderAxis();
    renderModels(*world.getGroup());

    glutSwapBuffers();
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

    // Handlers
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);
    glutDisplayFunc(printInfo);

    // Settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Initialize window
    glutMainLoop();

    return 1;
}