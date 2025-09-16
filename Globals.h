#ifndef GLOBALS_H
#define GLOBALS_H

#include <GL/glut.h>
#include <vector>
#include "VectorMath.h"

void EspecificaParametrosVisualizacao(void);

// Camera and View settings
extern Vector3 posicaoCamera;
extern Vector3 posicaoInicial;
extern Vector3 posicaoAlvo;
extern Vector3 alvoInicial;
extern Vector3 vetorV;
extern GLfloat velocidadeCamera;
extern GLfloat angle, fAspect, larguraJanela, alturaJanela;
extern bool primeiraPessoa;


// Animation settings
extern float frameRate;
extern int pontos;
extern int posicao;

// Roller coaster geometry
extern int picos;
extern double raioX;
extern double raioY;
extern double altura;
extern double propM;
extern double propP;
extern double escala;
extern double delta;
extern float offsetxy;

// Pre-calculated track angles
extern std::vector<int> angulosPico;
extern std::vector<int> angulosVale;

#endif // GLOBALS_H