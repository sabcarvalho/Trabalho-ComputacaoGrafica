#include <GL/glut.h>
#include "Globals.h"
#include "Scene.h"
#include "VectorMath.h"

// Function to set up the camera and projection
void EspecificaParametrosVisualizacao(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posicaoCamera.x, posicaoCamera.y, posicaoCamera.z,
              posicaoAlvo.x, posicaoAlvo.y, posicaoAlvo.z,
              vetorV.x, vetorV.y, vetorV.z);
}

// Main display callback
void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    EspecificaParametrosVisualizacao();

    DesenhaPlano();
    DesenhaTrilho();
    DesenhaArvore();
    //DesenhaQuadrantes();

    glutSwapBuffers();
}

// Animation timer callback
void Timer(int value) {
    if(posicao < pontos - 1){
        posicao++;
    } else {
        posicao = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(frameRate, Timer, value + 1);
}

// Window resize callback
void AlteraTamanhoJanela(GLint largura, GLint altura) {
    if (altura == 0) altura = 1;
    glViewport(0, 0, largura, altura);
    fAspect = (GLfloat)largura / (GLfloat)altura;
    EspecificaParametrosVisualizacao();
}

// Special keyboard keys callback
void TeclasEspeciais(int key, int x, int y) {
    if(primeiraPessoa) return;
    Vector3 direcaoFrente = {
        posicaoAlvo.x - posicaoCamera.x,
        posicaoAlvo.y - posicaoCamera.y,
        posicaoAlvo.z - posicaoCamera.z
    };
    direcaoFrente = normalizar(direcaoFrente);
    Vector3 direcaoLado = normalizar(produtoVetorial(direcaoFrente, vetorV));

    if (key == GLUT_KEY_UP) { posicaoCamera.z += 10; }
    if (key == GLUT_KEY_DOWN) { posicaoCamera.z -= 10; }
    if (key == GLUT_KEY_RIGHT) {
        posicaoCamera.x += velocidadeCamera * direcaoLado.x;
        posicaoCamera.y += velocidadeCamera * direcaoLado.y;
    }
    if (key == GLUT_KEY_LEFT) {
        posicaoCamera.x -= velocidadeCamera * direcaoLado.x;
        posicaoCamera.y -= velocidadeCamera * direcaoLado.y;
    }

    glutPostRedisplay();
}

// Regular keyboard keys callback
void GerenciaTeclado(unsigned char key, int x, int y) {
    Vector3 direcaoFrente = {
        posicaoAlvo.x - posicaoCamera.x,
        posicaoAlvo.y - posicaoCamera.y,
        posicaoAlvo.z - posicaoCamera.z
    };
    direcaoFrente = normalizar(direcaoFrente);

    switch (key) {
        case 'x':
            if(primeiraPessoa){
                posicaoCamera = posicaoInicial;
                posicaoAlvo = alvoInicial;
            }
            primeiraPessoa = !primeiraPessoa;
            break;
        case ' ':
            if(!primeiraPessoa) {
                posicaoCamera = posicaoInicial;
                posicaoAlvo = alvoInicial;
            }
            break;
        case 'w':
            if(!primeiraPessoa) {
                posicaoCamera.x += velocidadeCamera * direcaoFrente.x;
                posicaoCamera.y += velocidadeCamera * direcaoFrente.y;
                posicaoCamera.z += velocidadeCamera * direcaoFrente.z;
            }
            break;
        case 's':
            if(!primeiraPessoa) {
                posicaoCamera.x -= velocidadeCamera * direcaoFrente.x;
                posicaoCamera.y -= velocidadeCamera * direcaoFrente.y;
                posicaoCamera.z -= velocidadeCamera * direcaoFrente.z;
            }
            break;
        case '1': picos = 1; CalculaAngulos(); break;
        case '2': picos = 2; CalculaAngulos(); break;
        case '3': picos = 3; CalculaAngulos(); break;
        case '4': picos = 4; CalculaAngulos(); break;
        case '5': picos = 5; CalculaAngulos(); break;
        case '6': picos = 6; CalculaAngulos(); break;
        case '7': picos = 7; CalculaAngulos(); break;
        case '8': picos = 8; CalculaAngulos(); break;
        case '9': picos = 9; CalculaAngulos(); break;
    }
    glutPostRedisplay();
}

// Mouse button callback
void GerenciaMouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) { frameRate -= 5; }
        if (button == GLUT_RIGHT_BUTTON) { frameRate += 5; }
    }
    glutPostRedisplay();
}

// One-time initialization function
void Inicializa(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    angle = 45;
    CalculaAngulos();
}

// Main function
int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    larguraJanela = 600;
    alturaJanela = 500;
    glutInitWindowSize(larguraJanela, alturaJanela);
    glutInitWindowPosition(700, 100);
    glutCreateWindow("Projeto Montanha-Russa");

    posicaoCamera = posicaoInicial;
    posicaoAlvo = alvoInicial;

    Inicializa();

    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutKeyboardFunc(GerenciaTeclado);
    glutSpecialFunc(TeclasEspeciais);
    glutMouseFunc(GerenciaMouse);
    glutTimerFunc(frameRate, Timer, 1);

    glutMainLoop();
    return 0;
}