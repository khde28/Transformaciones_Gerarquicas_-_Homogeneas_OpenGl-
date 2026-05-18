#include <GL/glut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float angulo = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
        glTranslatef(-2.5f, 0.0f, 0.0f);

        glRotatef(angulo, 0.0f, 1.0f, 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glutSolidTeapot(0.6);

        glTranslatef(1.8f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glutSolidTeapot(0.6);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2.5f, 0.0f, 0.0f);

        glPushMatrix();
            glRotatef(angulo, 0.0f, 1.0f, 0.0f);
            glColor3f(1.0f, 0.5f, 0.5f);
            glutSolidTeapot(0.6);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(1.8f, 0.0f, 0.0f);
            glColor3f(0.5f, 1.0f, 0.5f);
            glutSolidTeapot(0.6);
        glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    angulo += 0.03f;
    if(angulo > 360.0f) angulo -= 360.0f;
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
    glutCreateWindow("Comparativa: SIN push/pop (izq) vs CON push/pop (der)");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.6, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
