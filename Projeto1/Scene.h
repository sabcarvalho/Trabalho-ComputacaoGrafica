#ifndef SCENE_H
#define SCENE_H

#include "VectorMath.h"
#include "Globals.h"

// Funcao para angulos
void CalculaAngulos();

// Funcoes para desenhar os props do cenario
void DesenhaLua();
void DesenhaCenario();
void DesenhaPosteDeLuz(float x, float y, float z, GLenum lightID);
void DesenhaTendaCone(float radius, float height, Color color1, Color color2);
void DesenhaTendaQuadrada(float size, float height, Color wallColor, Color roofColor1, Color roofColor2);
void DesenhaPessoa(Color clothingColor);
void DesenhaPalhaco(Color clothingColor, Color balloonColor);

// Funcoes para objetos do carrinho
void DesenhaPlano();
void DesenhaTrilho();
void DesenhaArvore();
void DesenhaQuadrantes();

// Funcoes helpers para desenhar cilindros entre pontos
void DesenhaCilindroEntrePontos(Vector3 p1, Vector3 p2, double radius, int subdivisions);
void DesenhaDormente(double escala);
void DesenhaSuportes();
void DesenhaCilindroSolido(double raio, double altura, int fatias, int pilhas);
void DesenhaCarrinhoComPassageiro();
void DesenhaCarrinho();

#endif
