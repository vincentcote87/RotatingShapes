#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int windowWidth = 800;
int windowHeight = 800;
int windowX = 100;
int windowY = 100;
float pyrAngle = 0.0;
float cubeAngle = 0.0;
float sphereAngle = 0.0;
float eyeX = 0.0;
float eyeY = 0.0;

// 1 for spin, 0 for no spin
// order is pyramid, cube, spere
int spin[] = {1,1,1};

float spinIt(float angle) {
    if (angle > 360.0)
        return 0.0;
    else
        return angle += 1.0;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(eyeX, eyeY, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Pyramid
    glPushMatrix();
    glTranslatef(0.0, 0.0, -1.0);
    if (spin[0])
        pyrAngle = spinIt(pyrAngle);
    glRotatef(pyrAngle, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    // front face
        glColor3f(0.75, 0.4, .35);
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.0, 1.5, 0.0);
        glVertex3f(-0.5, 0.0, 0.5);

    // back face
        glColor3f(0.45, 0.6, .39);
        glVertex3f(-0.5, 0.0, -0.5);
        glVertex3f(0.0, 1.5, 0.0);
        glVertex3f(0.5, 0.0, -0.5);

    // right face
        glColor3f(0.15, 0.6, .79);
        glVertex3f(0.5, 0.0, -0.5);
        glVertex3f(0.0, 1.5, 0.0);
        glVertex3f(0.5, 0.0, 0.5);

    // left face
        glColor3f(0.15, 1.0, 0.79);
        glVertex3f(-0.5, 0.0, 0.5);
        glVertex3f(0.0, 1.5, 0.0);
        glVertex3f(-0.5, 0.0, -0.5);

    glEnd();
    glPopMatrix();

    // Cube
    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    if (spin[1])
        cubeAngle = spinIt(cubeAngle);
    glRotatef(cubeAngle, 0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    // front face
        glColor3f(0.0, 0.5, 0.75);
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 1.0, 0.5);
        glVertex3f(-0.5, 1.0, 0.5);
        glVertex3f(-0.5, 0.0, 0.5);

    // left face
        glColor3f(0.0, 0.75, 0.50);
        glVertex3f(0.5, 0.0, -0.5);
        glVertex3f(0.5, 1.0, -0.5);
        glVertex3f(0.5, 1.0, 0.5);
        glVertex3f(0.5, 0.0, 0.5);

    // back face
        glColor3f(0.75, 0.0, 0.50);
        glVertex3f(-0.5, 0.0, -0.5);
        glVertex3f(-0.5, 1.0, -0.5);
        glVertex3f(0.5, 1.0, -0.5);
        glVertex3f(0.5, 0.0, -0.5);

    // right face
        glColor3f(0.25, 0.10, 0.70);
        glVertex3f(-0.5, 0.0, 0.5);
        glVertex3f(-0.5, 1.0, 0.5);
        glVertex3f(-0.5, 1.0, -0.5);
        glVertex3f(-0.5, 0.0, -0.5);

    // Top face
        glColor3f(0.25, 0.30, 0.50);
        glVertex3f(0.5, 1.0, 0.5);
        glVertex3f(0.5, 1.0, -0.5);
        glVertex3f(-0.5, 1.0, -0.5);
        glVertex3f(-0.5, 1.0, 0.5);

    // Bottom face
        glColor3f(0.95, 0.40, 0.60);
        glVertex3f(0.5, 0.0, -0.5);
        glVertex3f(-0.5, 0.0, -0.5);
        glVertex3f(-0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.5);

    glEnd();
    glPopMatrix();

    // Sphere
    glTranslatef(3.0, -1.0, -3.5);
    if (spin[2])
        sphereAngle = spinIt(sphereAngle);
    glRotatef(sphereAngle, 0.0, 0.0, 1.0);
    glColor3f(0.5, 0.8, .35);
    glutSolidSphere(0.5, 20, 20);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20);
    glMatrixMode(GL_MODELVIEW);
    windowWidth = w;
    windowHeight = h;
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_FRONT);
}

void changeEye(float x, float y) {
    eyeX = x;
    eyeY = y;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON :
            if (state == GLUT_DOWN)
                changeEye(-5.0,5.0);
            if (state == GLUT_UP)
                changeEye(0.0,0.0);
            break;
        case GLUT_MIDDLE_BUTTON :
        case GLUT_RIGHT_BUTTON :
            if (state == GLUT_DOWN)
                changeEye(5.0,5.0);
            if (state == GLUT_UP)
                changeEye(0.0,0.0);
            break;
        default:
            break;
   }
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 32 : //space bar
            spin[0] = 1;
            spin[1] = 1;
            spin[2] = 1;
            break;
        case 97 : // a
            spin[0] = 1;
            spin[1] = 0;
            spin[2] = 1;
            break;
        case 113 : // q
            spin[0] = 0;
            spin[1] = 0;
            spin[2] = 0;
            break;
        case 122 : // z
            spin[0] = 0;
            spin[1] = 1;
            spin[2] = 1;
            break;
        default :
            printf ("KP: No action for %d.\n", key);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(windowX, windowY);
    glutCreateWindow (argv[0]);
    init();
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
