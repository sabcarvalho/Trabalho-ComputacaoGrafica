#include <GL/glut.h>
#include "Globals.h"
#include "Scene.h"
#include "VectorMath.h"

// Funcao para especificar os parametros de visualizacao
void EspecificaParametrosVisualizacao(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, 0.1, 1500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posicaoCamera.x, posicaoCamera.y, posicaoCamera.z,
              posicaoAlvo.x, posicaoAlvo.y, posicaoAlvo.z,
              vetorV.x, vetorV.y, vetorV.z);
}

// Callback principal de desenho
void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    EspecificaParametrosVisualizacao();

    DesenhaLua();
    DesenhaPlano();
    DesenhaCenario(); // Tendas, lampadas, pessoas, arvores
    DesenhaTrilho(); // Atracao principal

    glutSwapBuffers();
}

// Callback de timer de animacao
void Timer(int value) {
    if(posicao < pontos - 1){
        posicao++;
    } else {
        posicao = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(frameRate, Timer, value + 1);
}

// Callback de tamanho da janela
void AlteraTamanhoJanela(GLint largura, GLint altura) {
    if (altura == 0) altura = 1;
    glViewport(0, 0, largura, altura);
    fAspect = (GLfloat)largura / (GLfloat)altura;
    EspecificaParametrosVisualizacao();
}

// Callback de teclas especiais
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

// Callback de teclado normal
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

// Callback de botao do mouse
void GerenciaMouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) { frameRate -= 5; }
        if (button == GLUT_RIGHT_BUTTON) { frameRate += 5; }
    }
    glutPostRedisplay();
}

// Funcao de inicializacao
void Inicializa(void){
    glClearColor(0.05f, 0.05f, 0.2f, 1.0f); // Background escuro
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    // Glcolor para definir propriedades de material ambiente e difuso
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Luz ambiente geral (LUA)
    GLfloat light7_ambient[] = { 0.05f, 0.05f, 0.1f, 1.0f };
    GLfloat light7_diffuse[] = { 0.1f, 0.1f, 0.2f, 1.0f };
    GLfloat light7_specular[] = { 0.2f, 0.2f, 0.4f, 1.0f };
    GLfloat light7_position[] = { 0.5f, 0.5f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT7, GL_AMBIENT, light7_ambient);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, light7_diffuse);
    glLightfv(GL_LIGHT7, GL_SPECULAR, light7_specular);
    glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
    glEnable(GL_LIGHT7);

    // Propriedades comuns das lampadas (Luzes pontuais)
    GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.0f, 1.0f };
    GLfloat light0_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat light0_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    GLfloat constant_attenuation = 0.4f;
    GLfloat linear_attenuation = 0.007f;
    GLfloat quadratic_attenuation = 0.0008f; 

    // Aplicar para todas as luzes pontuais
    for (int i = 0; i < 6; ++i) {
        GLenum light = GL_LIGHT0 + i;
        glLightfv(light, GL_AMBIENT, light0_ambient);
        glLightfv(light, GL_DIFFUSE, light0_diffuse);
        glLightfv(light, GL_SPECULAR, light0_specular);
        glLightf(light, GL_CONSTANT_ATTENUATION, constant_attenuation);
        glLightf(light, GL_LINEAR_ATTENUATION, linear_attenuation);
        glLightf(light, GL_QUADRATIC_ATTENUATION, quadratic_attenuation);
        glEnable(light);
    }

    angle = 45;
    CalculaAngulos();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    larguraJanela = 800;
    alturaJanela = 600;
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