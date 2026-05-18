#include <GL/glut.h>
#include <cmath>
#include <vector>

float anguloManual = 0.0f;

void dibujarPoligono() {
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 0.0f,  1.5f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    float rad = anguloManual * M_PI / 180.0f;
    float c = cos(rad);
    float s = sin(rad);

    float T[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        2, 1, 0, 1
    };

    float R[16] = {
        c,  s, 0, 0,
       -s,  c, 0, 0,
        0,  0, 1, 0,
        0,  0, 0, 1
    };

    float S[16] = {
        0.5, 0,   0, 0,
        0,   0.5, 0, 0,
        0,   0,   1, 0,
        0,   0,   0, 1
    };

    glPushMatrix();
        glMultMatrixf(T);
        glMultMatrixf(R);
        glMultMatrixf(S);

        dibujarPoligono();
    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
    anguloManual += 0.005f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Transformaciones Homogéneas Manuales");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
