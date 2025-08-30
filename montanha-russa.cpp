#include <GL/glut.h>
#include <math.h>
#include <iostream>
GLfloat angle, fAspect, largura, altura, xcamera, ycamera, zcamera;
GLfloat xalvo;
float delta = 0.1;
int pontos = 2*M_PI/delta;
int posicao = 0;
struct Vector3 {
    double x, y, z;
};

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
    glRotated(90,1,0,0);
    glTranslated(-15, -5, -40);
    glColor3f(0.5f, 0.35f, 0.05f); // Cor de madeira
    //glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);			// Face superior
		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
		glVertex3f(0.0, 10.0, 0.0);
		glVertex3f(0.0, 10.0, 80.0);
		glVertex3f(30.0, 10.0, 80.0);
		glVertex3f(30.0, 10.0, 0.0);
	glEnd();
    //glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);			// Face inferior
		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(30.0, 0.0, 0.0);
		glVertex3f(30.0, 0.0, 80.0);
		glVertex3f(0.0, 0.0, 80.0);
	glEnd();
    //glColor3f(0.7f, 0.4f, 1.0f);
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
    //glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 80.0);
		glVertex3f(0.0, 10.0, 80.0);
		glVertex3f(0.0, 10.0, 0.0);
	glEnd();
	
	//glColor3f(0.0f, 1.0f, 0.0f);
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
        ponto.z =altura*propM * sin(2*t);

        glVertex3f(ponto.x, ponto.y, ponto.z);
    }

    ponto.x = raioX*propM*cos(0);
    ponto.y =  raioY*propM*sin(0);
    ponto.z = altura*propM * sin(2*0);
    glVertex3f(ponto.x, ponto.y, ponto.z);
    glEnd();

    glBegin(GL_LINE_STRIP); 
    for (t = 0; t <= 2 * M_PI; t += 0.1) { 
        ponto.x = raioX*propP*cos(t);
        ponto.y = raioY*propP*sin(t);
        ponto.z = altura*propP * sin(2*t);
        glVertex3f(ponto.x, ponto.y, ponto.z);
    }
    ponto.x = raioX*propP*cos(0);
    ponto.y = raioY*propP*sin(0);
    ponto.z = altura*propP * sin(2*0);
    glVertex3f(ponto.x, ponto.y, ponto.z);
    glEnd();
}
void DesenhaCarrinho(){
    glPushMatrix;
        glTranslated(0, 0, 1);
        glutWireCube(10.0f);
    glPopMatrix;
}
void DesenhaTrilho(){
    
    float x,y,z,t;
    double raioX = 100;
    double raioY = 100;
    double altura = 30;
    double propM = 1.03;
    double propP = 0.97;
    double escala = 0.08;

    //desenha curvas entre os dormentes (para dar ideia de suporte)
    DesenhaSuportes(raioX, raioY,altura, propM,propP);
    int i =0;
    for (t = 0; t <= 2 * M_PI; t += delta) {
        double angulo;
        //rotacao no eixo z usando o angulo t (transformando para radianos)
        // tirar o angulo 90 deixa cada dormente apontando para fora
        double anguloZ = t * 180.0 / M_PI - 90; 

        //calcula ponto com a curva parametrica 
        Vector3 ponto = {
            (double)(raioX * cos(t)),
            (double)(raioY * sin(t)),
            (double)(altura * sin(2 * t))
        };
        //calcula derivada no ponto (tangente do ponto)
        Vector3 derivada = {
            (double)(raioX * (-sin(t))),
            (double)(raioY * cos(t)),
            (double)(2*altura * cos(2 * t))
        };
        // precisamos calcular o angulo entre a tangente e o eixo z
        // usando a formula: cos(a) = (u.v)/(|u|.|v|)
        // sendo u o versor em z: u =(0,0,1) e v = derivada
        // entao, calculando o modulo da derivada
        float moduloDerivada = sqrtf(derivada.x*derivada.x + 
                                    derivada.y*derivada.y + 
                                    derivada.z*derivada.z);

        // caso o y eh menor que 0, o angulo que a formula retorna estara no sentido horario, 
        // entao eh preciso espelhar o ponto em torno de z
        if (derivada.y < 0){
            derivada.y = -derivada.y;
            moduloDerivada = sqrtf(derivada.x*derivada.x + 
                                    derivada.y*derivada.y + 
                                    derivada.z*derivada.z);
        }
        
        // calculando o ponto pela formula e passando para grau
        angulo = acos(derivada.z / moduloDerivada) *180/M_PI;

        // precisamos que o angulo para rotacao seja para o plano xy,
        // porem, o angulo em z eh complementar, e, dependendo do quadrante, 
        // subtrai de 90 ou diminui 90
        if((ponto.y> 0 && derivada.z <0) || (ponto.x>0 && derivada.z>0)){
            angulo = 90 -angulo;
        }else{
            angulo = angulo - 90;
        }
        
        glPushMatrix();
            glTranslated(ponto.x, ponto.y, ponto.z);
            glRotated(angulo,1,0,0);
            glRotated(angulo,0,1,0);
            glRotated(anguloZ,0,0,1);
            DesenhaDormente(escala);
        glPopMatrix();

        //desenha carrinho de acordo com o tempo (animacao)
        if(i == posicao){
            glPushMatrix();
                glTranslated(ponto.x, ponto.y, ponto.z);
                glRotated(angulo,1,0,0);
                glRotated(angulo,0,1,0);
                glRotated(anguloZ,0,0,1);
                DesenhaCarrinho();
            glPopMatrix();
        }
        i++;
    }

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
	gluLookAt(xcamera, ycamera, zcamera,  // posição da câmera
              xalvo, 0, 0,          // posição do alvo
              0, 0, 1);         // vetor UP da câmera
}

void Desenha(void)
{   int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    EspecificaParametrosVisualizacao();
    // desenha os eixos x, y, z para melhor localizacao
    DesenhaQuadrantes();

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
	if (key == GLUT_KEY_UP) {
		ycamera += 10;  
	}
	if (key == GLUT_KEY_DOWN) {
		ycamera -= 10;  
	}
	if (key == GLUT_KEY_RIGHT) {
		xcamera += 10;
	}
	if (key == GLUT_KEY_LEFT) {
		xcamera -= 10;
	}
	
    EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}
// Função callback chamada para gerenciar teclado
void GerenciaTeclado(unsigned char key, int x, int y) {
	switch (key) {
		case ' ': // restaura posição inicial da camera
			ycamera = 200;
            xcamera = 300;
            zcamera = 300;
            xalvo = 0;
			break;
			// movimentacao da camera em z
		case 'w':
		    zcamera -= 50;
            break;
        case 's':
	        zcamera += 50;
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
	glutInitWindowSize(largura,altura);
	fAspect = (GLfloat)largura / (GLfloat)altura;
    ycamera = 200;
    xcamera = 300;
    zcamera = 300;
    xalvo = 0;
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

