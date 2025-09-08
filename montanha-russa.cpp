#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
struct Vector3 {
    double x, y, z;
};
Vector3 posicaoCamera;
Vector3 posicaoInicial{
    (GLfloat) 200,
    (GLfloat) 300,
    (GLfloat) 300,
};
Vector3 posicaoAlvo;

Vector3 alvoInicial {
    (GLfloat) 0,
    (GLfloat) 0,
    (GLfloat) 0,
};
Vector3 vetorV{
    (GLfloat) 0,
    (GLfloat) 0,
    (GLfloat) 1,
};
GLfloat velocidadeCamera = 5.0f;
GLfloat angle, fAspect, larguraJanela, alturaJanela;

std::vector<int> angulosPico;
std::vector<int> angulosVale;

double delta = 0.05;
float offsetxy = 5.0;
float frameRate = 100;

int pontos;
int posicao = 0;
int picos = 1;

double raioX = 100;
double raioY = 150;
double altura = 30;
double propM = 1.03;
double propP = 0.97;
double escala = 0.08;

bool primeiraPessoa = false;

Vector3 produtoVetorial(Vector3 u, Vector3 v){
    Vector3 resultado {
        (double) u.y*v.z - u.z*v.y,
        (double) u.z*v.x - u.x*v.z,
        (double) u.x*v.y - u.y*v.x

    };
    return resultado;

}

Vector3 normalizar(Vector3 v) {
    float norma = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (norma > 0.0f) {
        Vector3 resultado{
            v.x / norma,
            v.y / norma,
            v.z / norma
        };
        return resultado;
    }
    return v; 
}
// Função usada para especificar o volume de visualização

void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();
	// Especifica a projeção perspectiva
	gluPerspective(angle, fAspect, 0.1, 1000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(posicaoCamera.x, posicaoCamera.y, posicaoCamera.z,  // posição da câmera
              posicaoAlvo.x, posicaoAlvo.y, posicaoAlvo.z,          // posição do alvo
              vetorV.x, vetorV.y, vetorV.z);         // vetor UP da câmera*/
}

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
	glBegin(GL_QUADS);			// Face superior
		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
		glVertex3f(0.0, 10.0, 0.0);
		glVertex3f(0.0, 10.0, 80.0);
		glVertex3f(30.0, 10.0, 80.0);
		glVertex3f(30.0, 10.0, 0.0);
	glEnd();
	glBegin(GL_QUADS);			// Face inferior
		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(30.0, 0.0, 0.0);
		glVertex3f(30.0, 0.0, 80.0);
		glVertex3f(0.0, 0.0, 80.0);
	glEnd();
	glBegin(GL_QUADS);			// Face frontal
		glNormal3f(0.0, 0.0, 1.0); 	// Normal da face
		glVertex3f(0.0, 0.0, 80.0);
		glVertex3f(30.0, 0.0, 80.0);
		glVertex3f(30.0, 10.0, 80.0);
		glVertex3f(0.0, 10.0, 80.0);
	glEnd();
    glBegin(GL_QUADS);			// Face posterior
		glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
		glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);
        glVertex3f(30.0, 10.0, 0.0);
		glVertex3f(30.0, 0.0, 0.0);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 80.0);
		glVertex3f(0.0, 10.0, 80.0);
		glVertex3f(0.0, 10.0, 0.0);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral direita
		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
		glVertex3f(30.0, 10.0, 80.0);
		glVertex3f(30.0, 0.0, 80.0);
		glVertex3f(30.0, 0.0, 0.0);
		glVertex3f(30.0, 10.0, 0.0);
	glEnd();
	glPopMatrix();
}

void DesenhaSuportes(){
    double t;
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(5.0);
    Vector3 ponto{
        (double) 0,
        (double) 0,
        (double) 0
    };
    glBegin(GL_LINE_STRIP);     
    for (t = 0; t <= 2 * M_PI; t +=delta) { 
        ponto.x =raioX*propM*cos(t);
        ponto.y =raioY*propM*sin(t);
        ponto.z =altura*propM * sin(picos*t) + altura + offsetxy;

        glVertex3f(ponto.x, ponto.y, ponto.z);
    }

    ponto.x = raioX*propM;
    ponto.y =  0;
    ponto.z = altura + offsetxy;
    glVertex3f(ponto.x, ponto.y, ponto.z);
    glEnd();

    glBegin(GL_LINE_STRIP); 
    for (t = 0; t <= 2 * M_PI; t += delta) { 
        ponto.x = raioX*propP*cos(t);
        ponto.y = raioY*propP*sin(t);
        ponto.z = altura*propP * sin(picos*t) + altura + offsetxy;
        glVertex3f(ponto.x, ponto.y, ponto.z);
    }
    ponto.x = raioX*propP;
    ponto.y = 0;
    ponto.z = altura + offsetxy;
    glVertex3f(ponto.x, ponto.y, ponto.z);
    glEnd();


}

void DesenhaCarrinho(){
    glPushMatrix();
        glTranslated(0, 0, 1);
        glScaled(0.08f,0.08f,0.08f);
        glColor3f(0.7f, 0.4f, 1.0f); 
	    glBegin(GL_QUADS);			// Face frontal
            glNormal3f(0.0, 0.0, 1.0); 	// Normal da face
            glVertex3f(40.0, 40.0, 80.0);
            glVertex3f(-40.0, 40.0, 80.0);
            glVertex3f(-40.0, -40.0, 80.0);
            glVertex3f(40.0, -40.0, 80.0);
	    glEnd();
		glColor3f(0.0f, 0.0f, 1.0f); //azul
	    glBegin(GL_QUADS);			// Face posterior
            glNormal3f(0.0, 0.0, -1.0);	// Normal da face
            glVertex3f(40.0, 40.0, 0.0);
            glVertex3f(40.0, -40.0, 0.0);
            glVertex3f(-40.0, -40.0, 0.0);
            glVertex3f(-40.0, 40.0, 0.0);
        glEnd();
        glColor3f(1.0f, 1.0f, 0.0f); //amarelo
        glBegin(GL_QUADS);			// Face inferior
            glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
            glVertex3f(-40.0, -40.0, 0.0);
            glVertex3f(40.0, -40.0, 0.0);
            glVertex3f(40.0, -40.0, 80.0);
            glVertex3f(-40.0, -40.0, 80.0);
        glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);			// Face lateral esquerda
            glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
            glVertex3f(-40.0, 40.0, 80.0);
            glVertex3f(-40.0, 40.0, 0.0);
            glVertex3f(-40.0, -40.0, 0.0);
            glVertex3f(-40.0, -40.0, 80.0);
        glEnd();
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_QUADS);			// Face lateral direita
            glNormal3f(1.0, 0.0, 0.0);	// Normal da face
            glVertex3f(40.0, 40.0, 80.0);
            glVertex3f(40.0, -40.0, 80.0);
            glVertex3f(40.0, -40.0, 0.0);
            glVertex3f(40.0, 40.0, 0.0);
        glEnd();
        glColor3f(0.0f, 1.0f, 1.0f);
        glBegin(GL_QUADS);			// Face superior
            glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
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
                    DesenhaCarrinho();
                glPopMatrix();
            }
        }

        // Desenhar suportes a cada 5 dormentes
        if (i % 5 == 0) {  
            Vector3 worldUp = {0, 0, 1};
            
            // Calcular o vetor lateral usando o produto vetorial. 
            // Isso dá um vetor perpendicular tanto à direção da 
            // pista quanto ao vetor up do mundo.
            Vector3 vetorLado = normalizar(produtoVetorial(derivada, worldUp));
            
            // A dimensão da dormente é 80, vamos usar metade disso 
            // e um fudge factor para cada lado
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
          
            glColor3f(0.5f, 0.35f, 0.05f); 
            glLineWidth(2.0);
            glBegin(GL_LINES);
                glVertex3f(pontoFinal1.x, pontoFinal1.y, pontoFinal1.z);
                glVertex3f(pontoFinal1.x, pontoFinal1.y, 0.0f);

                glVertex3f(pontoFinal2.x, pontoFinal2.y, pontoFinal2.z);
                glVertex3f(pontoFinal2.x, pontoFinal2.y, 0.0f);
            glEnd();
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

void Timer(int value) { 
    if(posicao<pontos-1){
        posicao++;
    }else{
        posicao = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(frameRate, Timer, value+1);
}

void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    EspecificaParametrosVisualizacao();
    
    // desenha os eixos x, y, z para melhor localizacao
    //DesenhaQuadrantes();

    // desenha o plano xy
    DesenhaPlano();

    // desenha o trilho
    DesenhaTrilho();

    //desenha uma arvore na origem :)
    DesenhaArvore();

    glutSwapBuffers();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLint largura, GLint altura) {
	// Para previnir uma divisão por zero
	if (altura == 0) altura = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, largura, altura);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)largura / (GLfloat)altura;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar teclas especiais
void TeclasEspeciais(int key, int x, int y) {
    if(primeiraPessoa) return;
    Vector3 direcaoFrente = {
        posicaoAlvo.x - posicaoCamera.x,
        posicaoAlvo.y - posicaoCamera.y,
        posicaoAlvo.z - posicaoCamera.z
    };
    direcaoFrente = normalizar(direcaoFrente);

    Vector3 direcaoLado = normalizar(produtoVetorial(direcaoFrente, vetorV));

	if (key == GLUT_KEY_UP) { 
        posicaoCamera.z += 10;
    }
    if (key == GLUT_KEY_DOWN) { 
        posicaoCamera.z -= 10;
    }
    if (key == GLUT_KEY_RIGHT) {
        posicaoCamera.x += velocidadeCamera * direcaoLado.x;
        posicaoCamera.y += velocidadeCamera * direcaoLado.y;
        posicaoCamera.z += velocidadeCamera * direcaoLado.z;
    }
    if (key == GLUT_KEY_LEFT) { 
        posicaoCamera.x -= velocidadeCamera * direcaoLado.x;
        posicaoCamera.y -= velocidadeCamera * direcaoLado.y;
        posicaoCamera.z -= velocidadeCamera * direcaoLado.z;
    }
	
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}
// Função callback chamada para gerenciar teclado
void GerenciaTeclado(unsigned char key, int x, int y) {
    Vector3 direcaoFrente = {
        posicaoAlvo.x - posicaoCamera.x,
        posicaoAlvo.y - posicaoCamera.y,
        posicaoAlvo.z - posicaoCamera.z
    };
    direcaoFrente = normalizar(direcaoFrente);
    

	switch (key) {
        case 'x': //troca a visao para primeira ou terceira pessoa
            if(primeiraPessoa){
                posicaoCamera= posicaoInicial;
                posicaoAlvo = alvoInicial;
            }
			// a variavel primeiraPessoa bloqueia movimentos da camera quando se esta em primeira pessoa
            primeiraPessoa = !primeiraPessoa;
            break;
		case ' ': // restaura posição inicial da camera
            if(primeiraPessoa) return;
			posicaoCamera= posicaoInicial;
            posicaoAlvo = alvoInicial;
			break;
		case 'w':
            if(primeiraPessoa) return;
		    posicaoCamera.x += velocidadeCamera * direcaoFrente.x;
            posicaoCamera.y += velocidadeCamera * direcaoFrente.y;
            posicaoCamera.z += velocidadeCamera * direcaoFrente.z;
            break;
        case 's':
            if(primeiraPessoa) return;
	        posicaoCamera.x -= velocidadeCamera * direcaoFrente.x;
            posicaoCamera.y -= velocidadeCamera * direcaoFrente.y;
            posicaoCamera.z -= velocidadeCamera * direcaoFrente.z;
	        break;
		//trocas de quantidade de picos pelo teclado numerico
        case '1':
            picos = 1;
            CalculaAngulos();
            break;
        case '2':
            picos = 2;
            CalculaAngulos();
            break;
        case '3':
            picos = 3;
            CalculaAngulos();
            break;
        case '4':
            picos = 4;
            CalculaAngulos();
            break;
        case '5':
            picos = 5;
            CalculaAngulos();
            break;
        case '6':
            picos = 6;
            CalculaAngulos();
            break;
        case '7':
            picos = 7;
            CalculaAngulos();
            break;
        case '8':
            picos = 8;
            CalculaAngulos();
            break;
        case '9':
            picos = 9;
            CalculaAngulos();
            break;
	}
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y){
    //botao direito aumenta a velocidade do carrinho
	if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN){
	    frameRate -=5;
	}
    //botao esquerdo diminui a velocidade do carrinho
	if (button == GLUT_RIGHT_BUTTON and state == GLUT_DOWN){
	    frameRate += 5;
	}
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //aplica o zBuffer  
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}
// inicializa parametros
void Inicializa(void){
    
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);   //ativa o zBuffer
    
	angle = 45;
    CalculaAngulos();
    
}

int main(int argc, char** argv){
    glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
	
    glutInitWindowPosition(700,100);
    larguraJanela = 600;
    alturaJanela = 500;
    posicaoCamera= posicaoInicial;
    posicaoAlvo = alvoInicial;
	glutInitWindowSize(larguraJanela,alturaJanela);
	fAspect = (GLfloat)larguraJanela / (GLfloat)alturaJanela;
	angle = 45;
    glutCreateWindow("Projeto Montanha-Russa"); 
    AlteraTamanhoJanela(larguraJanela,alturaJanela);
	glutDisplayFunc(Desenha);
    glutMouseFunc(GerenciaMouse);
	glutReshapeFunc(AlteraTamanhoJanela); // Função para ajustar o tamanho da tela
    glutKeyboardFunc(GerenciaTeclado); // Define qual funcao gerencia o comportamento do teclado
    glutSpecialFunc(TeclasEspeciais); // Define qual funcao gerencia as teclas especiais
    glutTimerFunc(frameRate, Timer, 1); // registra a função callback para temporizador
	Inicializa();
	glutMainLoop();
}
