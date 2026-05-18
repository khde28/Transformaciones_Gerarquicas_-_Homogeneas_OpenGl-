#include <GL/glut.h>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

float angulo = 0.0f;

void matIdentidad(float m[16]) {
    for (int i = 0; i < 16; i++) m[i] = 0.0f;
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

void matTraslacion(float tx, float ty, float tz, float m[16]) {
    matIdentidad(m);
    m[12] = tx;
    m[13] = ty;
    m[14] = tz;
}

void matRotacionZ(float grados, float m[16]) {
    float rad = grados * (float)PI / 180.0f;
    float c = cosf(rad), s = sinf(rad);
    matIdentidad(m);
    m[0] =  c;  m[4] = -s;
    m[1] =  s;  m[5] =  c;
}

void drawRect(float x0, float y0, float x1, float y1,
              float fr, float fg, float fb) {
    glColor3f(fr, fg, fb);
    glBegin(GL_QUADS);
        glVertex2f(x0, y0);
        glVertex2f(x1, y0);
        glVertex2f(x1, y1);
        glVertex2f(x0, y1);
    glEnd();
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x0, y0);
        glVertex2f(x1, y0);
        glVertex2f(x1, y1);
        glVertex2f(x0, y1);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glDisable(GL_LIGHTING);

    float mT[16], mR[16];

    drawRect(-2.0f, -4.0f, 2.0f, -3.0f, 0.7f, 0.8f, 1.0f);

    float alpha = 60.0f + 30.0f * sinf(angulo * (float)PI / 180.0f);

    glPushMatrix();
        matTraslacion(0.0f, -3.0f, 0.0f, mT);
        glMultMatrixf(mT);

        matRotacionZ(alpha, mR);
        glMultMatrixf(mR);

        drawRect(0.0f, -0.4f, 5.0f, 0.4f, 0.85f, 0.8f, 0.9f);

        float beta = -45.0f + 40.0f * cosf(angulo * (float)PI / 180.0f);

        glPushMatrix();
            matTraslacion(5.0f, 0.0f, 0.0f, mT);
            glMultMatrixf(mT);

            matRotacionZ(beta, mR);
            glMultMatrixf(mR);

            drawRect(0.0f, -0.3f, 4.0f, 0.3f, 0.85f, 0.9f, 0.8f);

            glPushMatrix();
                matTraslacion(4.0f, 0.0f, 0.0f, mT);
                glMultMatrixf(mT);

                matRotacionZ(-(alpha + beta), mR);
                glMultMatrixf(mR);

                glColor3f(1.0f, 1.0f, 1.0f);
                glEnable(GL_LINE_STIPPLE);
                glLineStipple(2, 0xAAAA);
                glBegin(GL_LINES);
                    glVertex2f(0.0f,  0.0f);
                    glVertex2f(0.0f, -2.0f);
                glEnd();
                glDisable(GL_LINE_STIPPLE);

                matTraslacion(0.0f, -2.5f, 0.0f, mT);
                glMultMatrixf(mT);

                drawRect(-0.5f, -0.5f, 0.5f, 0.5f, 0.95f, 0.8f, 0.8f);

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();

    glEnable(GL_LIGHTING);
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
    glutCreateWindow("Homogenea P3: Brazo Robotico 2D Animado");

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
