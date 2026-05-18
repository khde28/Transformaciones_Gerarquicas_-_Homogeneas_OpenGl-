#include <GL/glut.h>
#include <cmath>

float angulo = 0.0f;
float traslacionX = -3.0f;
float escalaGlobal = 0.5f;
bool creciendo = true;

float velocidadRotacion = 0.07f;
float velocidadTraslacion = 0.0005f;
float velocidadEscalado = 0.0001f;

void multiplicarMatrices(const float A[16], const float B[16], float C[16]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[j * 4 + i] = 0.0f;
            for (int k = 0; k < 4; k++) {
                C[j * 4 + i] += A[k * 4 + i] * B[j * 4 + k];
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 2.0, 12.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    float rad = angulo * 3.14159f / 180.0f;
    float c = cos(rad);
    float s = sin(rad);
    float R[16] = { c, 0, -s, 0, 0, 1, 0, 0, s, 0, c, 0, 0, 0, 0, 1 };

    float T[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, traslacionX, 0, 0, 1 };

    float S[16] = { escalaGlobal, 0, 0, 0, 0, escalaGlobal, 0, 0, 0, 0, escalaGlobal, 0, 0, 0, 0, 1 };

    float matrizTR[16], matrizFinal[16];
    multiplicarMatrices(T, R, matrizTR);
    multiplicarMatrices(S, matrizTR, matrizFinal);

    glPushMatrix();
    glMultMatrixf(matrizFinal);

    glColor3f(0.5f, 0.7f, 1.0f);
    glutSolidTeapot(1.5);

    glPopMatrix();
    glutSwapBuffers();
}

void idle() {
    angulo += velocidadRotacion;
    if (angulo > 360.0f) angulo -= 360.0f;

    traslacionX += velocidadTraslacion;
    if (traslacionX > 3.0f) traslacionX = -3.0f;

    if (creciendo) {
        escalaGlobal += velocidadEscalado;
        if (escalaGlobal > 1.2f) creciendo = false;
    } else {
        escalaGlobal -= velocidadEscalado;
        if (escalaGlobal < 0.5f) creciendo = true;
    }

    glutPostRedisplay();
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);

    GLfloat luz_posicion[] = { 5.0f, 5.0f, 5.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);

    GLfloat luz_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_color);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Tetera 3D con Velocidades Controlables");

    initLighting();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
