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

void matRotacionZ(float grados, float m[16]) {
    float rad = grados * (float)PI / 180.0f;
    float c = cosf(rad), s = sinf(rad);
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[15] = 1.0f;
    m[0] =  c;  m[4] = -s;
    m[1] =  s;  m[5] =  c;
    m[10] = 1.0f;
}

void circulo(float x, float y, float radio, int segmentos) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segmentos; i++) {
        float theta = 2.0f * (float)PI * i / segmentos;
        glVertex3f(x + radio * cosf(theta), y + radio * sinf(theta), 0.0f);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glDisable(GL_LIGHTING);
    glColor3f(0.5f, 0.8f, 1.0f);
    circulo(0.0f, 0.0f, 4.0f, 100);
    circulo(0.0f, 0.0f, 0.3f, 50);
    glEnable(GL_LIGHTING);

    float mRz[16], mRzInv[16], mT[16];
    matRotacionZ(angulo,  mRz);
    matRotacionZ(-angulo, mRzInv);
    matTraslacion(4.0f, 0.0f, 0.0f, mT);

    glPushMatrix();
        glMultMatrixf(mRz);
        glMultMatrixf(mT);
        glMultMatrixf(mRzInv);
        glColor3f(0.9f, 0.6f, 0.2f);
        glutSolidTeapot(0.7);
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    angulo += 0.005f;
    if (angulo > 360.0f) angulo -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Homogenea P2: Tetera en Orbita - Orientacion Fija");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
