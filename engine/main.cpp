#include "main.h"

double g_time = 0.f, scale = 0.f, frequency = 1.f;

void changeSize(int w, int h) {
    if (h == 0) h = 1;
    float ratio = w * 1.0f / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(
        0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f
    );

    scale = sin(frequency * 2.0 * M_PI * g_time) * 0.5 + 1.0;
    glutWireTeapot(scale);
    
    glutSwapBuffers();
}

void printInfo() {
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
}

int main(int argc, char** argv) {
    if(argc != 3) {
        cout << "./engine <path> <xml_file>" << endl;
        return 0;
    }

    string path = argv[1];
    string xmlFile = argv[2];
    
    World world;
    world.parseXML(path + xmlFile);
    Camera camera = world.getCamera();
    cout << camera.getPosition().getY() << endl;

    // Window settings
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@GRUPO??@21/22");

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