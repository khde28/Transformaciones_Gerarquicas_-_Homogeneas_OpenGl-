#include <GL/glut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float angulo = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glDisable(GL_LIGHTING);

    glPushMatrix();

    glColor3f(0.7f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-2.0f, -4.0f);
        glVertex2f( 2.0f, -4.0f);
        glVertex2f( 2.0f, -3.0f);
        glVertex2f(-2.0f, -3.0f);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-2.0f, -4.0f);
        glVertex2f( 2.0f, -4.0f);
        glVertex2f( 2.0f, -3.0f);
        glVertex2f(-2.0f, -3.0f);
    glEnd();

    glTranslatef(0.0f, -3.0f, 0.0f);

    float alpha = 60.0f + 30.0f * sin(angulo * PI / 180.0f);
    glRotatef(alpha, 0.0f, 0.0f, 1.0f);

    glColor3f(0.85f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(5.0f, -0.4f);
        glVertex2f(5.0f,  0.4f);
        glVertex2f(0.0f,  0.4f);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, -0.4f);
        glVertex2f(5.0f, -0.4f);
        glVertex2f(5.0f,  0.4f);
        glVertex2f(0.0f,  0.4f);
    glEnd();

    glTranslatef(5.0f, 0.0f, 0.0f);

    float beta = -45.0f + 40.0f * cos(angulo * PI / 180.0f);
    glRotatef(beta, 0.0f, 0.0f, 1.0f);

    glColor3f(0.85f, 0.9f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.3f);
        glVertex2f(4.0f, -0.3f);
        glVertex2f(4.0f,  0.3f);
        glVertex2f(0.0f,  0.3f);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, -0.3f);
        glVertex2f(4.0f, -0.3f);
        glVertex2f(4.0f,  0.3f);
        glVertex2f(0.0f,  0.3f);
    glEnd();

    glTranslatef(4.0f, 0.0f, 0.0f);

    glRotatef(-(alpha + beta), 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0xAAAA);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -2.0f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glTranslatef(0.0f, -2.5f, 0.0f);

    glColor3f(0.95f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();

    glPopMatrix();

    glEnable(GL_LIGHTING);

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
    glutCreateWindow("Brazo Robotico 2D Animado");

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
