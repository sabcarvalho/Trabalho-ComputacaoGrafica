#ifndef SCENE_H
#define SCENE_H

#include "VectorMath.h"

// Calculation function for track geometry
void CalculaAngulos();

// Main drawing functions for scene objects
void DesenhaPlano();
void DesenhaTrilho();
void DesenhaArvore();
void DesenhaQuadrantes();

// Helper drawing functions
void DesenhaCilindroEntrePontos(Vector3 p1, Vector3 p2, double radius, int subdivisions);
void DesenhaDormente(double escala);
void DesenhaSuportes();
void DesenhaCilindroSolido(double raio, double altura, int fatias, int pilhas);
void DesenhaCarrinhoComPassageiro();
void DesenhaCarrinho();

#endif // SCENE_H