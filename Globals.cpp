#include "Globals.h"

// Camera and View settings
Vector3 posicaoCamera;
Vector3 posicaoInicial{200.0f, 300.0f, 300.0f};
Vector3 posicaoAlvo;
Vector3 alvoInicial{0.0f, 0.0f, 0.0f};
Vector3 vetorV{0.0f, 0.0f, 1.0f};
GLfloat velocidadeCamera = 5.0f;
GLfloat angle, fAspect, larguraJanela, alturaJanela;
bool primeiraPessoa = false;

// Animation settings
float frameRate = 100;
int pontos;
int posicao = 0;

// Roller coaster geometry
int picos = 1;
double raioX = 100;
double raioY = 150;
double altura = 30;
double propM = 1.03;
double propP = 0.97;
double escala = 0.08;
double delta = 0.05;
float offsetxy = 5.0;

// Pre-calculated track angles
std::vector<int> angulosPico;
std::vector<int> angulosVale;