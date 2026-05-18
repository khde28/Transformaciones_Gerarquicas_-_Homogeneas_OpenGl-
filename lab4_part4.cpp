#include <GL/glut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float timer = 0.0f;
float posX = 0.0f;
float dirX = 1.0f;
float speedX = 0.001f;

void drawRect(float width, float height, bool center = true) {
    float x = -width / 2.0f;
    float y = center ? -height / 2.0f : -height;

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

void drawJointedLimb(float w, float h, float angle, float subAngle, float r, float g, float b) {
    glPushMatrix();
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
        glColor3f(r, g, b);
        drawRect(w, h, false);

        glTranslatef(0.0f, -h, 0.0f);
        glRotatef(subAngle, 0.0f, 0.0f, 1.0f);
        glColor3f(r * 0.9f, g * 0.9f, b * 0.9f);
        drawRect(w * 0.9f, h * 0.9f, false);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glDisable(GL_LIGHTING);

    float swing = 35.0f * sin(timer);
    float kneeBack = (swing < 0) ? -swing * 1.5f : 5.0f;
    float kneeFront = (swing > 0) ? swing * 0.5f : 5.0f;

    glPushMatrix();

        glTranslatef(posX, 0.0f, 0.0f);

        glPushMatrix();
            glTranslatef(0.0f, -0.5f, 0.0f);
            drawJointedLimb(0.7f, 2.2f, -swing, kneeFront, 0.45f, 0.55f, 0.7f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, 1.8f, 0.0f);
            drawJointedLimb(0.5f, 1.8f, swing, -20.0f, 0.4f, 0.5f, 0.65f);
        glPopMatrix();

        glColor3f(0.7f, 0.8f, 1.0f);
        drawRect(1.2f, 4.0f, true);

        glPushMatrix();
            glTranslatef(0.2f, 2.6f, 0.0f);
            glColor3f(0.8f, 0.9f, 1.0f);
            drawRect(1.1f, 1.1f, true);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, -0.5f, 0.0f);
            drawJointedLimb(0.7f, 2.2f, swing, kneeBack, 0.6f, 0.7f, 0.9f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, 1.8f, 0.0f);
            drawJointedLimb(0.5f, 1.8f, -swing, -20.0f, 0.55f, 0.65f, 0.85f);
        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    timer += 0.0006f;
    if (timer > 2 * PI) timer -= 2 * PI;

    posX += speedX * dirX;

    if (posX > 6.0f) {
        dirX = -1.0f;
    } else if (posX < -6.0f) {
        dirX = 1.0f;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Caminata de Perfil con Translacion");

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.0, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
