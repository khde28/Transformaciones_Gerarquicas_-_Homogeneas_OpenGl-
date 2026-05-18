#include <GL/glut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float angulo = 0.0f;

void matTraslacion(float tx, float ty, float tz, float m[16]) {
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[0] = m[5] = m[10] = m[15] = 1.0f;
    m[12] = tx;
    m[13] = ty;
    m[14] = tz;
}

void matRotacionY(float grados, float m[16]) {
    float rad = grados * (float)PI / 180.0f;
    float c = cosf(rad), s = sinf(rad);
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[15] = 1.0f;
    m[0] =  c;  m[8]  = s;
    m[1] =  0;  m[5]  = 1;  m[9]  = 0;
    m[2] = -s;  m[10] = c;
    m[4] =  0;
    m[6] =  0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    float mT[16], mR[16];

    glPushMatrix();
        matTraslacion(-2.5f, 0.0f, 0.0f, mT);
        glMultMatrixf(mT);

        matRotacionY(angulo, mR);
        glMultMatrixf(mR);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidTeapot(0.6);

        matTraslacion(1.8f, 0.0f, 0.0f, mT);
        glMultMatrixf(mT);
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidTeapot(0.6);
    glPopMatrix();

    glPushMatrix();
        matTraslacion(2.5f, 0.0f, 0.0f, mT);
        glMultMatrixf(mT);

        glPushMatrix();
            matRotacionY(angulo, mR);
            glMultMatrixf(mR);
            glColor3f(1.0f, 0.5f, 0.5f);
            glutSolidTeapot(0.6);
        glPopMatrix();

        glPushMatrix();
            matTraslacion(1.8f, 0.0f, 0.0f, mT);
            glMultMatrixf(mT);
            glColor3f(0.5f, 1.0f, 0.5f);
            glutSolidTeapot(0.6);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    angulo += 0.03f;
    if (angulo > 360.0f) angulo -= 360.0f;
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_pos[] = {2.0f, 2.0f, 3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Homogenea P1: SIN push/pop (izq) vs CON push/pop (der)");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
