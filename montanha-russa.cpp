#include <GL/glut.h>
#include <math.h>
#include <iostream>
struct Vector3 {
    double x, y, z;
};

GLfloat angle, fAspect, largura, altura;
Vector3 posicaoCamera;
Vector3 posicaoInicial{
    (GLfloat) 200,
    (GLfloat) 300,
    (GLfloat) 300,
};

Vector3 posicaoAlvo{
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
float delta = 0.1;
int pontos = 2*M_PI/delta;
int posicao = 0;
int picos = 2;
float offsetxy = 5.0; 

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

void DesenhaSuportes(double raioX, double raioY, double altura, double propM, double propP){
    double t;
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(3.0);
    Vector3 ponto{
        (double) 0,
        (double) 0,
        (double) 0
    };
    glBegin(GL_LINE_STRIP);     
    for (t = 0; t <= 2 * M_PI; t += 0.1) { 
        ponto.x =raioX*propM*cos(t);
        ponto.y =raioY*propM*sin(t);
        ponto.z =altura*propM * sin(picos*t) + altura + offsetxy;

        glVertex3f(ponto.x, ponto.y, ponto.z);
    }

    ponto.x = raioX*propM*cos(0);
    ponto.y =  raioY*propM*sin(0);
    ponto.z = altura*propM * sin(0) + altura + offsetxy;
    glVertex3f(ponto.x, ponto.y, ponto.z);
    glEnd();

    glBegin(GL_LINE_STRIP); 
    for (t = 0; t <= 2 * M_PI; t += 0.1) { 
        ponto.x = raioX*propP*cos(t);
        ponto.y = raioY*propP*sin(t);
        ponto.z = altura*propP * sin(picos*t) + altura + offsetxy;
        glVertex3f(ponto.x, ponto.y, ponto.z);
    }
    ponto.x = raioX*propP*cos(0);
    ponto.y = raioY*propP*sin(0);
    ponto.z = altura*propP * sin(0) + altura + offsetxy;
    glVertex3f(ponto.x, ponto.y, ponto.z);
    glEnd();
}

void DesenhaCarrinho(){
    glPushMatrix;
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
		glColor3f(0.0f, 0.0f, 1.0f);
	    glBegin(GL_QUADS);			// Face posterior
            glNormal3f(0.0, 0.0, -1.0);	// Normal da face
            glVertex3f(40.0, 40.0, 0.0);
            glVertex3f(40.0, -40.0, 0.0);
            glVertex3f(-40.0, -40.0, 0.0);
            glVertex3f(-40.0, 40.0, 0.0);
        glEnd();
        glColor3f(1.0f, 1.0f, 0.0f);
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
    glPopMatrix;
}

void DesenhaTrilho(){
    
    double t, anguloX, anguloY,anguloZ;
    double raioX = 100;
    double raioY = 150;
    double altura = 30;
    double propM = 1.03;
    double propP = 0.97;
    double escala = 0.08;
    if(picos==1){
        altura = 0;
    }
    //desenha curvas entre os dormentes (para dar ideia de suporte)
    DesenhaSuportes(raioX, raioY,altura, propM,propP);

    int i =0;
    
    double intervaloX=0;
    double intervaloY=0;

    //calcula o x do ultimo pico (ultimo da origem ate o raio X)
    for(t=raioX;t>0;t-=delta){
        double angulo = acos(t/raioX);
        double diferenca = altura - abs((altura*sin(picos*angulo)));
        if(diferenca <0.1){
            intervaloX = t;
            break;
        }
        angulo = abs(acos(t/raioX));
        diferenca = altura -(altura*abs(sin(picos*angulo)));
        if(diferenca <0.1){
            intervaloX = t;
            break;
        }
    }

    //calcula o y do ultimo pico (ultimo da origem ate o raio Y)
    for(t=raioY;t>0;t-=delta){
        double angulo = asin(t/raioX);
        double diferenca = abs(altura - altura*sin(picos*angulo));
        if(diferenca <0.1){
            intervaloY = t;
            break;
        }
        angulo = abs(asin(t/raioX));
        diferenca = altura - abs(altura*sin(picos*angulo));
        if(diferenca <0.1){
            intervaloY = t;
            break;
        }
    }

    for (t = 0; t <= 2 * M_PI; t += delta) {
        // calcula ponto com a curva parametrica 
        Vector3 ponto = {
            (double)(raioX * cos(t)),
            (double)(raioY * sin(t)),
            (double)(altura * sin(picos * t) + altura + offsetxy) //deixa em cima do plano xy
        };
        if(picos>1){
            // calcula derivada no ponto (tangente do ponto)
            Vector3 derivada = {
                (double)(raioX * (-sin(t))),
                (double)(raioY * cos(t)),
                (double)(picos* altura * cos(picos * t))
            };
            derivada = normalizar(derivada);
            // angulo entre a derivada projetada no eixo zy e versor do eixo y
            anguloX = acos(derivada.y/ sqrtf(derivada.y*derivada.y + 
                                        derivada.z*derivada.z)) * 180/M_PI;

            // angulo entre a derivada projetada no eixo zx e versor do eixo x                           
            anguloY = acos(derivada.x / sqrtf(derivada.x*derivada.x + 
                                        derivada.z*derivada.z)) *180/M_PI; 
            
            // se a derivada em z eh negativa, o angulo calculado estara no sentido horario
            // pois eh o menor angulo entre os dois vetores
            // entao, como o sentido positivo eh anti-horario, temos que deixar negativo                         
            if(derivada.z <0){
                anguloY = -anguloY;
                anguloX = -anguloX;
            }

            //se o ponto eh depois do ultimo pico em x, nao rotacionar em x
            if(abs(ponto.y)>intervaloY){
                anguloX = 0;
            }else{
                // correcao caso o angulo de rotacao seja maior que 90
                // para nao ficar de cabeca para baixo
                if(anguloX >90){
                    anguloX = anguloX - 180;
                }else if (anguloX <(-90)){
                    anguloX = anguloX +180;
                }
            }
            //se o ponto eh depois do ultimo pico em y, nao rotacionar em y
            if(abs(ponto.x)>intervaloX){
                anguloY = 0;
            }else{
                // correcao novamente
                if(anguloY >90){
                    anguloY = anguloY +180;
                }else if (anguloY <(-90)){
                    anguloY = anguloY-180;
                }
                // em y, o angulo calculado esta no sentido horario
                anguloY=-anguloY;
            }
        }
        
        
        // rotacao no eixo z usando o angulo t (transformando para radianos)
        anguloZ = t * 180.0 / M_PI ; 
        
        // Desenhar suportes a cada 5 dormentes
        if (i % 5 == 0) {
            // Recalcular a derivada para achar o vetor lateral
            Vector3 derivada = normalizar({
                (double)(raioX * (-sin(t))),
                (double)(raioY * cos(t)),
                (double)(picos* altura * cos(picos * t))
            });

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
        
        
        glPushMatrix();
            glTranslated(ponto.x, ponto.y, ponto.z);
            glRotated(anguloX,1,0,0);
            glRotated(anguloY,0,1,0);
            glRotated(anguloZ,0,0,1);
            DesenhaDormente(escala);
        glPopMatrix();
        

        // desenha carrinho de acordo com o tempo (animacao)
        // talvez colocar mais pontos para deixar a animacao mais fluida
        if(i == posicao){
            glPushMatrix();
                glTranslated(ponto.x, ponto.y, ponto.z);
                glRotated(anguloX,1,0,0);
                glRotated(anguloY,0,1,0);
                glRotated(anguloZ,0,0,1);
                DesenhaCarrinho();
            glPopMatrix();
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
    if(posicao<pontos){
        posicao++;
    }else{
        posicao = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(500, Timer, value+1);
}

// inicializa parametros
void Inicializa(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);   //ativa o zBuffer
    
	angle = 45;
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

void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    EspecificaParametrosVisualizacao();
    
    // desenha os eixos x, y, z para melhor localizacao
    DesenhaQuadrantes();

    // desenha o plano xy
    DesenhaPlano();

    // desenha o trilho
    DesenhaTrilho();

    glutSwapBuffers();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLint largura, GLint altura)
{
	// Para previnir uma divisão por zero
	if (altura == 0) altura = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, largura, altura);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)largura / (GLfloat)altura;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar teclas especiais
void TeclasEspeciais(int key, int x, int y)
{
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
		case ' ': // restaura posição inicial da camera
			posicaoCamera.x = posicaoInicial.x;
            posicaoCamera.y = posicaoInicial.y;
            posicaoCamera.z = posicaoInicial.z;
			break;
		case 'w':
		    posicaoCamera.x += velocidadeCamera * direcaoFrente.x;
            posicaoCamera.y += velocidadeCamera * direcaoFrente.y;
            posicaoCamera.z += velocidadeCamera * direcaoFrente.z;
            break;
        case 's':
	        posicaoCamera.x -= velocidadeCamera * direcaoFrente.x;
            posicaoCamera.y -= velocidadeCamera * direcaoFrente.y;
            posicaoCamera.z -= velocidadeCamera * direcaoFrente.z;
	        break;
        case '1':
            picos = 1;
            break;
        case '2':
            picos = 2;
            break;
        case '3':
            picos = 3;
            break;
        case '4':
            picos = 4;
            break;
	}
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
	
    glutInitWindowPosition(700,100);
    largura = 600;
    altura = 500;
    posicaoCamera.x = posicaoInicial.x;
    posicaoCamera.y = posicaoInicial.y;
    posicaoCamera.z = posicaoInicial.z;
	glutInitWindowSize(largura,altura);
	fAspect = (GLfloat)largura / (GLfloat)altura;
	angle = 45;
    glutCreateWindow("Projeto Montanha-Russa"); 
    AlteraTamanhoJanela(largura,altura);
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela); // Função para ajustar o tamanho da tela
    glutKeyboardFunc(GerenciaTeclado); // Define qual funcao gerencia o comportamento do teclado
    glutSpecialFunc(TeclasEspeciais); // Define qual funcao gerencia as teclas especiais
    glutTimerFunc(1000, Timer, 1); // registra a função callback para temporizador
	Inicializa();
	glutMainLoop();

}
