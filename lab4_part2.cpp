#include <GL/glut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float angulo = 0.0f;

void circulo(float x, float y, float radio, int segmentos) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segmentos; i++) {
        float theta = 2.0f * PI * i / segmentos;
        glVertex3f(x + radio * cos(theta), y + radio * sin(theta), 0.0f);
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

    glPushMatrix();
    float x = 4.0f * cos(angulo * PI / 180.0f);
    float y = 4.0f * sin(angulo * PI / 180.0f);
    glTranslatef(x, y, 0.0f);

    glRotatef(0, 0.0f, 0.0f, 1.0f);

    glColor3f(0.9f, 0.6f, 0.2f);
    glutSolidTeapot(0.7);
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    angulo += 0.005f;
    if (angulo > 360.0f) {
        angulo -= 360.0f;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Tetera en Orbita - Orientacion Fija");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
