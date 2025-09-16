#include "Scene.h"
#include "Globals.h"
#include "VectorMath.h"
#include <GL/glut.h>
#include <math.h>
#include <vector>

void DesenhaArvore(){
    float alturaCaule = 30;
    float raioEsferas = 7;
    float correcao =4 ;
    float alturaTopo = alturaCaule - correcao + raioEsferas * 3;
    float alturaSegundaCamada = alturaCaule- correcao + raioEsferas * 2;
    float alturaPrimeiraCamada = alturaCaule- correcao + raioEsferas;

    // caule
    glColor3f(0.5f, 0.35f, 0.05f); // Cor de madeira
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    gluCylinder(quadratic, raioEsferas-2, raioEsferas-correcao, alturaCaule, 10, 10);

    glColor3f(0.0f, 0.7f, 0.0f);

    // folha do topo
    glPushMatrix();
        glTranslated(0, 0, alturaTopo);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    //segunda camada
    glPushMatrix();
        glTranslated(0, raioEsferas, alturaSegundaCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0, -raioEsferas, alturaSegundaCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(raioEsferas, 0, alturaSegundaCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-raioEsferas, 0, alturaSegundaCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    //terceira camada
    glPushMatrix();
        glTranslated(raioEsferas*2, 0, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-raioEsferas*2, 0, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,raioEsferas*2, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,-raioEsferas*2, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(raioEsferas, raioEsferas, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-raioEsferas, raioEsferas, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(raioEsferas, -raioEsferas, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-raioEsferas, -raioEsferas, alturaPrimeiraCamada);
        glutSolidSphere(raioEsferas, 10, 10);
    glPopMatrix();

}


void DesenhaCilindroEntrePontos(Vector3 p1, Vector3 p2, double radius, int subdivisions) {
    Vector3 v = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
    double height = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    if (height < 0.0001) return; // Avoid drawing zero-length cylinders

    Vector3 z_axis = {0.0, 0.0, 1.0};
    Vector3 v_normalized = normalizar(v);

    // Calculate the dot product to check for parallel/anti-parallel cases
    double dot_product = v_normalized.z;
    
    glPushMatrix();
        glTranslated(p1.x, p1.y, p1.z);

        // If the cylinder is anti-parallel to the Z-axis (pointing straight down)
        if (dot_product < -0.9999) {
            // We need to flip it 180 degrees. We can rotate around any axis in the XY plane.
            glRotated(180.0, 1.0, 0.0, 0.0);
        }
        // If the cylinder is parallel to the Z-axis (pointing straight up)
        else if (dot_product > 0.9999) {
            // No rotation is needed.
        }
        // The general case for all other orientations
        else {
            double angle = acos(dot_product) * 180.0 / M_PI;
            Vector3 axis = produtoVetorial(z_axis, v_normalized);
            glRotated(angle, axis.x, axis.y, axis.z);
        }

        GLUquadric* quadric = gluNewQuadric();
        gluCylinder(quadric, radius, radius, height, subdivisions, 1);
        gluDeleteQuadric(quadric);
    glPopMatrix();
}

void DesenhaQuadrantes() {
    glLineWidth(3.0);
    glBegin(GL_LINES);
        //eixo x negativo
        glColor3f(0.5, 0.5, 0.0);
        glVertex3i(-500, 0,0);
        glVertex3i(0, 0,0);
        //eixo x positivo
        glColor3f(1.0, 1.0, 0.0);
        glVertex3i(500, 0,0);
        glVertex3i(0, 0,0);

        //eixo y negativo
        glColor3f(0.5, 0.0, 0.5);
        glVertex3i(0, 0,0);
        glVertex3i(0, -500,0);

        //eixo y positivo rosa
        glColor3f(1.0, 0.0, 1.0);
        glVertex3i(0, 0,0);
        glVertex3i(0, 500,0);

        //eixo z negativo
        glColor3f(0.0,0.5, 0.5);
        glVertex3i(0,0, 0);
        glVertex3i(0,0, -500);

        //eixo z negativo
        glColor3f(0.0,1.0, 1.0);
        glVertex3i(0,0, 500);
        glVertex3i(0,0, 0);
    glEnd();
}

void DesenhaDormente(double escala){
    glPushMatrix();
    glScaled(escala,escala,escala);
    glRotated(90,0,0,1);
    glRotated(90,1,0,0);
    glTranslated(-15, -5, -40);
    glColor3f(0.5f, 0.35f, 0.05f); // Cor de madeira
    glBegin(GL_QUADS);          // Face superior
        glNormal3f(0.0, 1.0, 0.0);      // Normal da face
        glVertex3f(0.0, 10.0, 0.0);
        glVertex3f(0.0, 10.0, 80.0);
        glVertex3f(30.0, 10.0, 80.0);
        glVertex3f(30.0, 10.0, 0.0);
    glEnd();
    glBegin(GL_QUADS);          // Face inferior
        glNormal3f(0.0, -1.0, 0.0);     // Normal da face
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(30.0, 0.0, 0.0);
        glVertex3f(30.0, 0.0, 80.0);
        glVertex3f(0.0, 0.0, 80.0);
    glEnd();
    glBegin(GL_QUADS);          // Face frontal
        glNormal3f(0.0, 0.0, 1.0);  // Normal da face
        glVertex3f(0.0, 0.0, 80.0);
        glVertex3f(30.0, 0.0, 80.0);
        glVertex3f(30.0, 10.0, 80.0);
        glVertex3f(0.0, 10.0, 80.0);
    glEnd();
    glBegin(GL_QUADS);          // Face posterior
        glNormal3f(0.0, 0.0, -1.0);     // Normal da face
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);
        glVertex3f(30.0, 10.0, 0.0);
        glVertex3f(30.0, 0.0, 0.0);
    glEnd();
    glBegin(GL_QUADS);          // Face lateral esquerda
        glNormal3f(-1.0, 0.0, 0.0);     // Normal da face
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 80.0);
        glVertex3f(0.0, 10.0, 80.0);
        glVertex3f(0.0, 10.0, 0.0);
    glEnd();
    glBegin(GL_QUADS);          // Face lateral direita
        glNormal3f(1.0, 0.0, 0.0);  // Normal da face
        glVertex3f(30.0, 10.0, 80.0);
        glVertex3f(30.0, 0.0, 80.0);
        glVertex3f(30.0, 0.0, 0.0);
        glVertex3f(30.0, 10.0, 0.0);
    glEnd();
    glPopMatrix();
}

void DesenhaSuportes() {
    glColor3f(0.0f, 0.0f, 0.0f);
    double railRadius = 0.7;
    std::vector<Vector3> outerPoints;
    std::vector<Vector3> innerPoints;

    for (double t = 0; t <= 2 * M_PI; t += delta) {
        outerPoints.push_back({
            raioX * propM * cos(t),
            raioY * propM * sin(t),
            altura * propM * sin(picos * t) + altura + offsetxy
        });
    }

    for (double t = 0; t <= 2 * M_PI; t += delta) {
        innerPoints.push_back({
            raioX * propP * cos(t),
            raioY * propP * sin(t),
            altura * propP * sin(picos * t) + altura + offsetxy
        });
    }

    for (size_t i = 0; i < outerPoints.size() - 1; ++i) {
        DesenhaCilindroEntrePontos(outerPoints[i], outerPoints[i+1], railRadius, 6);
    }
    DesenhaCilindroEntrePontos(outerPoints.back(), outerPoints.front(), railRadius, 6);

    for (size_t i = 0; i < innerPoints.size() - 1; ++i) {
        DesenhaCilindroEntrePontos(innerPoints[i], innerPoints[i+1], railRadius, 6);
    }
    DesenhaCilindroEntrePontos(innerPoints.back(), innerPoints.front(), railRadius, 6);
}


void DesenhaCilindroSolido(double raio, double altura, int fatias, int pilhas) {
    GLUquadric* quadric = gluNewQuadric();
    if (quadric) {
        // corpo do cilindro
        gluCylinder(quadric, raio, raio, altura, fatias, pilhas);

        // tampa de cima
        glPushMatrix();
            glTranslated(0, 0, altura);
            gluDisk(quadric, 0, raio, fatias, 1);
        glPopMatrix();

        // tampa de baixo
        glPushMatrix();
            glRotatef(180.0, 1.0, 0.0, 0.0);
            gluDisk(quadric, 0, raio, fatias, 1);
        glPopMatrix();

        gluDeleteQuadric(quadric);
    }
}

void DesenhaCarrinhoComPassageiro() {
    glPushMatrix();

        glTranslated(0, 0, 5);
        // escalar o carrinho para ficar mais facil de ver o boneco
        glScaled(0.08f, 0.08f, 0.08f);

        glColor3f(0.7f, 0.7f, 0.7f);

        glBegin(GL_QUADS);
            // face do chao
            glNormal3f(0.0, 0.0, -1.0);
            glVertex3f(-40.0, -40.0, -40.0);
            glVertex3f(40.0, -40.0, -40.0);
            glVertex3f(40.0, 40.0, -40.0);
            glVertex3f(-40.0, 40.0, -40.0);

            // face da frente
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-40.0, 40.0, -40.0);
            glVertex3f(40.0, 40.0, -40.0);
            glVertex3f(40.0, 40.0, 10.0);
            glVertex3f(-40.0, 40.0, 10.0);

            // face de tras
            glNormal3f(0.0, -1.0, 0.0);
            glVertex3f(-40.0, -40.0, 10.0);
            glVertex3f(40.0, -40.0, 10.0);
            glVertex3f(40.0, -40.0, -40.0);
            glVertex3f(-40.0, -40.0, -40.0);

            // face direita
            glNormal3f(1.0, 0.0, 0.0);
            glVertex3f(40.0, -40.0, 10.0);
            glVertex3f(40.0, 40.0, 10.0);
            glVertex3f(40.0, 40.0, -40.0);
            glVertex3f(40.0, -40.0, -40.0);

            // face esquerda
            glNormal3f(-1.0, 0.0, 0.0);
            glVertex3f(-40.0, -40.0, -40.0);
            glVertex3f(-40.0, 40.0, -40.0);
            glVertex3f(-40.0, 40.0, 10.0);
            glVertex3f(-40.0, -40.0, 10.0);
        glEnd();

        // rodas
        glColor3f(0.2f, 0.2f, 0.2f); // cinza escuro
        float wheelRadius = 15.0f;
        float wheelWidth = 10.0f;

        // frente-direita
        glPushMatrix();
            glTranslated(40.0, 30.0, -40.0);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            DesenhaCilindroSolido(wheelRadius, wheelWidth, 10, 10);
        glPopMatrix();

        // frente-esquerda
        glPushMatrix();
            glTranslated(-40.0, 30.0, -40.0);
            glRotatef(-90.0, 0.0, 1.0, 0.0);
            DesenhaCilindroSolido(wheelRadius, wheelWidth, 10, 10);
        glPopMatrix();

        // tras-direita
        glPushMatrix();
            glTranslated(40.0, -30.0, -40.0);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            DesenhaCilindroSolido(wheelRadius, wheelWidth, 10, 10);
        glPopMatrix();

        // tras-esquerda
        glPushMatrix();
            glTranslated(-40.0, -30.0, -40.0);
            glRotatef(-90.0, 0.0, 1.0, 0.0);
            DesenhaCilindroSolido(wheelRadius, wheelWidth, 10, 10);
        glPopMatrix();

        // passageiro
        glPushMatrix();
            // posicionar dentro do carrinho
            glTranslated(0.0, -10.0, -30.0);

            // corpo (cone)
            glColor3f(0.0f, 0.5f, 1.0f);
            glutSolidCone(20.0, 60.0, 15, 15);

            // cabeça (esfera)
            glTranslated(0.0, 0.0, 60.0);
            glColor3f(1.0f, 0.8f, 0.6f);
            glutSolidSphere(15.0, 15, 15);
        glPopMatrix();

    glPopMatrix();
}


void DesenhaCarrinho(){
    glPushMatrix();
        glTranslated(0, 0, 1);
        glScaled(0.08f,0.08f,0.08f);
        glColor3f(0.7f, 0.4f, 1.0f);
        glBegin(GL_QUADS);          // Face frontal
            glNormal3f(0.0, 0.0, 1.0);  // Normal da face
            glVertex3f(40.0, 40.0, 80.0);
            glVertex3f(-40.0, 40.0, 80.0);
            glVertex3f(-40.0, -40.0, 80.0);
            glVertex3f(40.0, -40.0, 80.0);
        glEnd();
        glColor3f(0.0f, 0.0f, 1.0f); //azul
        glBegin(GL_QUADS);          // Face posterior
            glNormal3f(0.0, 0.0, -1.0); // Normal da face
            glVertex3f(40.0, 40.0, 0.0);
            glVertex3f(40.0, -40.0, 0.0);
            glVertex3f(-40.0, -40.0, 0.0);
            glVertex3f(-40.0, 40.0, 0.0);
        glEnd();
        glColor3f(1.0f, 1.0f, 0.0f); //amarelo
        glBegin(GL_QUADS);          // Face inferior
            glNormal3f(0.0, -1.0, 0.0);     // Normal da face
            glVertex3f(-40.0, -40.0, 0.0);
            glVertex3f(40.0, -40.0, 0.0);
            glVertex3f(40.0, -40.0, 80.0);
            glVertex3f(-40.0, -40.0, 80.0);
        glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);          // Face lateral esquerda
            glNormal3f(-1.0, 0.0, 0.0);     // Normal da face
            glVertex3f(-40.0, 40.0, 80.0);
            glVertex3f(-40.0, 40.0, 0.0);
            glVertex3f(-40.0, -40.0, 0.0);
            glVertex3f(-40.0, -40.0, 80.0);
        glEnd();

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);          // Face lateral direita
            glNormal3f(1.0, 0.0, 0.0);  // Normal da face
            glVertex3f(40.0, 40.0, 80.0);
            glVertex3f(40.0, -40.0, 80.0);
            glVertex3f(40.0, -40.0, 0.0);
            glVertex3f(40.0, 40.0, 0.0);
        glEnd();
        glColor3f(0.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);          // Face superior
            glNormal3f(0.0, 1.0, 0.0);      // Normal da face
            glVertex3f(-40.0, 40.0, 0.0);
            glVertex3f(-40.0, 40.0, 80.0);
            glVertex3f(40.0, 40.0, 80.0);
            glVertex3f(40.0, 40.0, 0.0);
        glEnd();
    glPopMatrix();
}

void CalculaAngulos(){
    if(picos==1) delta= 0.05;
    else delta = 0.05 / (picos/2.0 );
    pontos = 2*M_PI/delta;
    angulosPico.clear();
    angulosVale.clear();

    const double EPS = 1e-8;
    double t, val, denom, ang;
    //calcula onde eh o primeiro pico no eixo y
    double primeiroPico = M_PI/(picos*2);

    //calcula onde eh o ultimo vale no eixo y
    double ultimoVale = 2*M_PI - primeiroPico;
    ultimoVale = round(ultimoVale * 100.0) / 100.0;

    //calcula os angulos da origem ate o primeiro pico
    for(t=0;t<=primeiroPico;t+=delta){
        double cosT = cos(t);
        double sinT = sin(t);
        double cosP = cos(picos * t);
        double sinP = sin(picos * t);

        Vector3 ponto = {
            (double)(raioX * cosT),
            (double)(raioY * sinT),
            (double)(altura * sinP + altura + offsetxy) //deixa em cima do plano xy
        };

        // calcula derivada no ponto (tangente do ponto)
        Vector3 derivada = {
                (double)(raioX * -sinT),
                (double)(raioY * cosT),
                (double)(picos* altura * cosP)
            };
        derivada = normalizar(derivada);

        // modulo da derivada projetada no eixo zy
        denom = sqrt(derivada.y*derivada.y + derivada.z*derivada.z);

        //evitar divisao por zero
        if (denom > EPS) {
            val = derivada.y / denom;
        } else {
            val = 1.0; // tangente quase vertical: angulo 0
        }

        // angulo entre a derivada projetada no eixo zy e versor do eixo y
        ang = acos(val) * 180.0 / M_PI;
        //acresenta no vetor de angulos
        angulosPico.push_back(ang);
    }
    angulosPico.pop_back();
    angulosPico.push_back(0); //forca o pico nao ter angulacao

    //calcula os angulos do ultimo vale ate a origem
    for(t=(ultimoVale+delta);t<=2*M_PI;t+=delta){
        double cosT = cos(t);
        double sinT = sin(t);
        double cosP = cos(picos * t);
        double sinP = sin(picos * t);

        Vector3 ponto = {
            (double)(raioX * cosT),
            (double)(raioY * sinT),
            (double)(altura * sinP + altura + offsetxy) //deixa em cima do plano xy
        };
        // calcula derivada no ponto (tangente do ponto)
        Vector3 derivada = {
                (double)(raioX * -sinT),
                (double)(raioY * cosT),
                (double)(picos* altura * cosP)
            };
        derivada = normalizar(derivada);

        // modulo da derivada projetada no eixo zy
        denom = sqrt(derivada.y*derivada.y + derivada.z*derivada.z);

        // prevencao para divisao por zero e valores fora
        if (denom > EPS) {
            val = derivada.y / denom;
        } else {
            val = 1.0;
        }
        // angulo entre a derivada projetada no eixo zy e versor do eixo y
        ang = acos(val) * 180.0 / M_PI;
        angulosVale.push_back(ang);

    }
}

void DesenhaTrilho(){

    double t, anguloX, anguloZ;

    //desenha curvas entre os dormentes (para dar ideia de suporte)
    DesenhaSuportes();

    int i = 0; //flag para o carrinho e suportes

    double num_angulosP = angulosPico.size();
    double num_angulosV = angulosVale.size();

    int contadorP = 0;
    int contadorV = num_angulosV-1;
    int controladorP = 1;
    int controladorV = -1;

    for (t = 0; t <= 2 * M_PI; t += delta) {
        Vector3 ponto, derivada;

        // calcula ponto com a curva parametrica
        double cosT = cos(t);
        double sinT = sin(t);
        double cosP = cos(picos * t);
        double sinP = sin(picos * t);

        ponto = {
            (double)(raioX * cosT),
            (double)(raioY * sinT),
            (double)(altura * sinP + altura + offsetxy) //deixa em cima do plano xy
        };

        double componenteZ = ponto.z - altura - offsetxy;
        if(componenteZ>=0){ //se o ponto esta "subindo" usar angulos calculados em angulosPico
            contadorV = num_angulosV-1; //reseta contagem de angulos do vale
            anguloX = angulosPico[contadorP];
            contadorP+=controladorP;
            if(contadorP == 0 || contadorP == (num_angulosP - 1)){
                controladorP = -controladorP;
            }

        }else{
            contadorP = 0;
            anguloX = angulosVale[contadorV];
            contadorV+=controladorV;
            if(contadorV == 0 || contadorV == (num_angulosV - 1)){
                controladorV = -controladorV;
            }

        }

        //se a derivada em z e negativa, inverter o sinal
        if((picos* altura * cosP)<0){
            anguloX = -anguloX;
        }


        // rotacao no eixo z usando o angulo t (transformando para radianos)
        anguloZ = t * 180.0 / M_PI ;

        if(i%5 == 0 || (i==posicao && primeiraPessoa)){
            // calcula derivada no ponto (tangente do ponto) quando precisa
            derivada = {
                    (double)(raioX * -sinT),
                    (double)(raioY * cosT),
                    (double)(picos* altura * cosP)
                };
            derivada = normalizar(derivada);
        }

        // desenha dormente
        if(i%2 == 0){
            glPushMatrix();
                glTranslated(ponto.x, ponto.y, ponto.z);
                glRotated(anguloZ,0,0,1);
                glRotated(anguloX,1,0,0);

            DesenhaDormente(escala);
            glPopMatrix();
        }

        if(i == posicao){
            // coloca a camera em primeira pessoa
            if(primeiraPessoa){
                posicaoCamera.x = ponto.x;
                posicaoCamera.y = ponto.y;
                posicaoCamera.z = ponto.z + vetorV.z*5.0;
                posicaoAlvo.x = ponto.x+derivada.x* 30.0;
                posicaoAlvo.y = ponto.y+derivada.y* 30.0;
                posicaoAlvo.z = ponto.z + derivada.z * 30.0;
                EspecificaParametrosVisualizacao();
            }else{
                // desenha carrinho de acordo com o tempo (animacao)
                glPushMatrix();
                    glTranslated(ponto.x, ponto.y, ponto.z);
                    glRotated(anguloZ,0,0,1);
                    glRotated(anguloX,1,0,0);
                    DesenhaCarrinhoComPassageiro();
                glPopMatrix();
            }
        }


        if (i % 5 == 0) {
            Vector3 worldUp = {0, 0, 1};
            Vector3 vetorLado = normalizar(produtoVetorial(derivada, worldUp));
            double halfWidth = 40.0 * escala * 1.1;

            Vector3 pontoFinal1 = {
                ponto.x + vetorLado.x * halfWidth,
                ponto.y + vetorLado.y * halfWidth,
                ponto.z + vetorLado.z * halfWidth
            };
            Vector3 pontoFinal2 = {
                ponto.x - vetorLado.x * halfWidth,
                ponto.y - vetorLado.y * halfWidth,
                ponto.z - vetorLado.z * halfWidth
            };

            Vector3 groundPoint1 = {pontoFinal1.x, pontoFinal1.y, 0.0f};
            Vector3 groundPoint2 = {pontoFinal2.x, pontoFinal2.y, 0.0f};
            double supportRadius = 0.7;

            glColor3f(0.5f, 0.35f, 0.05f);
            DesenhaCilindroEntrePontos(pontoFinal1, groundPoint1, supportRadius, 8);
            DesenhaCilindroEntrePontos(pontoFinal2, groundPoint2, supportRadius, 8);
        }
        i++;
    }
}

void DesenhaPlano() {
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0); // Normal apontando para cima em Z
        glVertex3f(-500.0f, -500.0f, 0.0f);
        glVertex3f( 500.0f, -500.0f, 0.0f);
        glVertex3f( 500.0f,  500.0f, 0.0f);
        glVertex3f(-500.0f,  500.0f, 0.0f);
    glEnd();
}
