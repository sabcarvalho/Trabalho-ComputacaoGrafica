#include "Scene.h"
#include "Globals.h"
#include "VectorMath.h"
#include <GL/glut.h>
#include <math.h>
#include <vector>

void DesenhaLua() {
    glPushMatrix();
    // Dar propriedades emissivas pra lua brilhar e nao ser afetada por outras luzes
    GLfloat mat_emission[] = { 1.0, 1.0, 0.8, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glColor3f(1.0f, 1.0f, 0.8f); // Uma cor bonitinha meio azul

    // Deixar a lua bem longe no ceu e bem grande
    glTranslatef(200, 300, 300);
    glutSolidSphere(30, 20, 20);

    // Resetar a propriedade emissiva pra outros objetos nao brilharem
    mat_emission[0] = 0.0; mat_emission[1] = 0.0; mat_emission[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glPopMatrix();
}

void DesenhaPosteDeLuz(float x, float y, float z, GLenum lightID) {
    glPushMatrix();
    // Primeiro, move para a posicao da base do poste no mundo
    glTranslatef(x, y, z);

    // Colocar a luz a 15 unidades da origem
    GLfloat light_pos[] = { 0.0f, 0.0f, 15.0f, 1.0f };

    glLightfv(lightID, GL_POSITION, light_pos);

    // Desenhar o poste
    glColor3f(0.2f, 0.2f, 0.2f); // Cinza escuro
    DesenhaCilindroSolido(0.5, 25.0, 8, 1);

    // Desenhar a lampada em cima do poste
    glTranslatef(0, 0, 25.0f);
    GLfloat mat_emission[] = { 1.0, 1.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow
    glutSolidSphere(2.0, 10, 10);

    // Resetar emissao
    mat_emission[0] = 0.0; mat_emission[1] = 0.0;
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    glPopMatrix();
}


void DesenhaTendaCone(float radius, float height, Color color1, Color color2) {
    // Salvar os atributos de iluminacao atuais
    glPushAttrib(GL_LIGHTING_BIT);

    int segments = 24;
    float angle_step = 2.0f * M_PI / segments;

    // Deixar o topo da tenda brilhoso, para parecer que a luz bate nele
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < segments; ++i) {
        if (i % 2 == 0) { glColor3f(color1.r, color1.g, color1.b); }
        else { glColor3f(color2.r, color2.g, color2.b); }
        Vector3 v1 = { radius * cos(i * angle_step), radius * sin(i * angle_step), 0 };
        Vector3 v2 = { radius * cos((i + 1) * angle_step), radius * sin((i + 1) * angle_step), 0 };
        Vector3 v3 = { 0, 0, height };
        Vector3 edge1 = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
        Vector3 edge2 = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };
        Vector3 normal = normalizar(produtoVetorial(edge1, edge2));
        glNormal3f(normal.x, normal.y, normal.z);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
    glPopMatrix();
    
    // Restaurar os atributos de iluminacao anteriores
    glPopAttrib();
}

void DesenhaTendaRetangular(float width, float depth, float height, Color mainColor, Color roofColor) {
    glPushAttrib(GL_LIGHTING_BIT);
    
    float half_width = width / 2.0f;
    float half_depth = depth / 2.0f;

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glPushMatrix();
    glColor3f(mainColor.r, mainColor.g, mainColor.b);
    glBegin(GL_QUADS);
        // Frente
        glNormal3f(0, 1, 0);
        glVertex3f(-half_width, half_depth, 0); glVertex3f(half_width, half_depth, 0);
        glVertex3f(half_width, half_depth, height); glVertex3f(-half_width, half_depth, height);
        // Tras
        glNormal3f(0, -1, 0);
        glVertex3f(-half_width, -half_depth, 0); glVertex3f(-half_width, -half_depth, height);
        glVertex3f(half_width, -half_depth, height); glVertex3f(half_width, -half_depth, 0);
        // Esquerda
        glNormal3f(-1, 0, 0);
        glVertex3f(-half_width, -half_depth, 0); glVertex3f(-half_width, half_depth, 0);
        glVertex3f(-half_width, half_depth, height); glVertex3f(-half_width, -half_depth, height);
        // Direita
        glNormal3f(1, 0, 0);
        glVertex3f(half_width, -half_depth, 0); glVertex3f(half_width, -half_depth, height);
        glVertex3f(half_width, half_depth, height); glVertex3f(half_width, half_depth, 0);
    glEnd();

    // Deixar o topo da tenda brilhoso, para parecer que a luz bate nele
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColor3f(roofColor.r, roofColor.g, roofColor.b);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-half_width, -half_depth, height); glVertex3f(-half_width, half_depth, height);
        glVertex3f(half_width, half_depth, height); glVertex3f(half_width, -half_depth, height);
    glEnd();
    glPopMatrix();
    
    glPopAttrib();
}


void DesenhaTendaQuadrada(float size, float height, Color wallColor, Color roofColor1, Color roofColor2) {
    glPushAttrib(GL_LIGHTING_BIT);

    float half_size = size / 2.0f;
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    glPushMatrix();
    glColor3f(wallColor.r, wallColor.g, wallColor.b);
    glBegin(GL_QUADS);
        // Frente
        glNormal3f(0, 1, 0);
        glVertex3f(-half_size, half_size, 0); glVertex3f(half_size, half_size, 0);
        glVertex3f(half_size, half_size, height); glVertex3f(-half_size, half_size, height);
        // Tras
        glNormal3f(0, -1, 0);
        glVertex3f(-half_size, -half_size, 0); glVertex3f(-half_size, -half_size, height);
        glVertex3f(half_size, -half_size, height); glVertex3f(half_size, -half_size, 0);
        // Esquerda
        glNormal3f(-1, 0, 0);
        glVertex3f(-half_size, -half_size, 0); glVertex3f(-half_size, half_size, 0);
        glVertex3f(-half_size, half_size, height); glVertex3f(-half_size, -half_size, height);
        // Direita
        glNormal3f(1, 0, 0);
        glVertex3f(half_size, -half_size, 0); glVertex3f(half_size, -half_size, height);
        glVertex3f(half_size, half_size, height); glVertex3f(half_size, half_size, 0);
    glEnd();

    // Deixar o topo da tenda brilhoso, para parecer que a luz bate nele
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_TRIANGLES);
        // Face da frente do telhado
        glColor3f(roofColor1.r, roofColor1.g, roofColor1.b);
        glNormal3f(0, 0.707, 0.707);
        glVertex3f(0, 0, height + half_size);
        glVertex3f(-half_size, half_size, height);
        glVertex3f(half_size, half_size, height);
        // Face de tras do telhado
        glColor3f(roofColor2.r, roofColor2.g, roofColor2.b);
        glNormal3f(0, -0.707, 0.707);
        glVertex3f(0, 0, height + half_size);
        glVertex3f(half_size, -half_size, height);
        glVertex3f(-half_size, -half_size, height);
        // Face esquerda do telhado
        glColor3f(roofColor1.r, roofColor1.g, roofColor1.b);
        glNormal3f(-0.707, 0, 0.707);
        glVertex3f(0, 0, height + half_size);
        glVertex3f(-half_size, -half_size, height);
        glVertex3f(-half_size, half_size, height);
        // Face direita do telhado
        glColor3f(roofColor2.r, roofColor2.g, roofColor2.b);
        glNormal3f(0.707, 0, 0.707);
        glVertex3f(0, 0, height + half_size);
        glVertex3f(half_size, half_size, height);
        glVertex3f(half_size, -half_size, height);
    glEnd();
    glPopMatrix();
    
    glPopAttrib();
}

void DesenhaPessoa(Color clothingColor) {
    glPushMatrix();
    // Corpo (cone)
    glColor3f(clothingColor.r, clothingColor.g, clothingColor.b);
    glutSolidCone(1.7, 5.0, 15, 15);
    // Cabeça (esfera)
    glTranslatef(0, 0, 5.0);
    glColor3f(1.0f, 0.8f, 0.6f); // Pele
    glutSolidSphere(1.3, 15, 15);
    glPopMatrix();
}

void DesenhaPalhaco(Color clothingColor, Color balloonColor) {
    glPushMatrix(); // Salvar a posicao do palhaco na cena
    
    // Desenhar a pessoa
    DesenhaPessoa(clothingColor);

    // Desenhar o chapeu
    glPushMatrix();
        glColor3f(1.0f, 0.0f, 1.0f);
        glTranslatef(0, 0, 6.3); // No topo da cabeca
        glutSolidCone(0.7, 2.5, 10, 1);
    glPopMatrix(); 

    // Desenhar o balao
    glPushMatrix();
        glBegin(GL_LINES);
            glColor3f(0.1f, 0.1f, 0.1f); // Linha preta
            glVertex3f(1.5, 0.0, 3.0);   // Comecar da mao
            glVertex3f(2.5, 0.0, 10.0);  // Ir para cima e um pouco a direita
        glEnd();
        glTranslatef(2.5, 0.0, 10.0); // Mover para o final da linha
        glColor3f(balloonColor.r, balloonColor.g, balloonColor.b);
        glutSolidSphere(1.8, 15, 15);
    glPopMatrix();

    glPopMatrix();
}

void DesenhaCenario() {
    // ARVORES
    glPushMatrix();
        glTranslatef(0, 250, 0);
        glScalef(1.5, 1.5, 1.5);
        DesenhaArvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(200, 150, 0);
        DesenhaArvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-220, 150, 0);
        glScalef(1.2, 1.2, 1.2);
        DesenhaArvore();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-240, -150, 0);
        DesenhaArvore();
    glPopMatrix();

    // PESSOAS E TENDAS
    // TENDA PRINCIPAL
    glPushMatrix();
        glTranslatef(0, 0, 0);
        DesenhaTendaCone(40, 50, {1.0, 0.1, 0.1}, {1.0, 1.0, 1.0});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, -55, 0);
        glRotatef(180, 0, 0, 1);
        DesenhaPalhaco({0.1, 0.8, 0.8}, {1.0, 0.5, 0.0});
    glPopMatrix();
    // UM TANTAO DE GENTE
    glPushMatrix();
        glTranslatef(150, 50, 0);
        glRotatef(30, 0, 0, 1);
        DesenhaTendaCone(15, 20, {0.0, 0.5, 1.0}, {1.0, 1.0, 1.0});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-120, -100, 0);
        DesenhaTendaQuadrada(25, 15, {1.0, 0.5, 0.0}, {1.0, 1.0, 1.0}, {1.0, 0.5, 0.0});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(80, -20, 0);
        DesenhaPessoa({0.2, 0.8, 0.2});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(90, -25, 0);
        glRotatef(-20, 0, 0, 1);
        DesenhaPessoa({0.8, 0.2, 0.8});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-50, 70, 0);
        DesenhaPalhaco({1.0, 1.0, 0.0}, {1.0, 0.0, 0.0});
    glPopMatrix();
    // OUTRO TANTAO DE GENTE E TENDAS
    glPushMatrix();
        glTranslatef(140, -150, 0);
        DesenhaTendaQuadrada(30, 18, {0.2, 0.8, 0.8}, {1.0, 1.0, 1.0}, {0.2, 0.8, 0.8});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(165, -140, 0);
        DesenhaPessoa({0.9, 0.1, 0.1});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(170, -145, 0);
        glRotatef(45, 0, 0, 1);
        DesenhaPessoa({0.1, 0.1, 0.9});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-160, 130, 0);
        glRotatef(-45, 0, 0, 1);
        DesenhaTendaCone(20, 25, {0.5, 0.0, 0.5}, {1.0, 1.0, 0.0});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-130, 150, 0);
        DesenhaPalhaco({0.1, 0.9, 0.1}, {0.0, 0.5, 1.0});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 200, 0);
        glRotatef(10, 0, 0, 1);
        DesenhaTendaRetangular(40, 20, 15, {0.4, 0.2, 0.0}, {0.8, 0.1, 0.1});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-5, 185, 0);
        DesenhaPessoa({0.9, 0.9, 0.9});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-10, 180, 0);
        DesenhaPessoa({0.1, 0.1, 0.1});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-15, 175, 0);
        DesenhaPessoa({0.9, 0.5, 0.1});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-180, -50, 0);
        DesenhaTendaCone(18, 22, {0.1, 0.8, 0.1}, {1.0, 1.0, 1.0});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-200, -60, 0);
        glRotatef(90, 0, 0, 1);
        DesenhaPalhaco({0.1, 0.1, 0.8}, {1.0, 1.0, 0.0});
    glPopMatrix();
    // OUTRO TANTAO DE GENTE E TENDAS
    glPushMatrix();
        glTranslatef(80, 220, 0);
        DesenhaTendaQuadrada(20, 12, {0.9, 0.1, 0.5}, {1.0, 1.0, 1.0}, {0.9, 0.1, 0.5});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(75, 205, 0);
        glRotatef(-90, 0, 0, 1);
        DesenhaPessoa({0.3, 0.3, 0.3});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(85, 205, 0);
        glRotatef(-90, 0, 0, 1);
        DesenhaPessoa({0.8, 0.8, 0.2});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-200, 70, 0);
        glRotatef(-30, 0, 0, 1);
        DesenhaTendaRetangular(30, 15, 12, {0.1, 0.5, 0.1}, {0.1, 0.8, 0.1});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-190, 85, 0);
        DesenhaPessoa({0.5, 0.5, 0.5});
    glPopMatrix();
    // TANTAO DE GENTE E TENDAS FINAL
    glPushMatrix();
        glTranslatef(210, -50, 0);
        glRotatef(-90, 0, 0, 1);
        DesenhaTendaRetangular(35, 18, 14, {0.8, 0.8, 0.8}, {0.2, 0.2, 0.8});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(200, -40, 0);
        DesenhaPessoa({0.9, 0.1, 0.1});
    glPopMatrix();
    glPushMatrix();
        glTranslatef(200, -60, 0);
        DesenhaPessoa({0.1, 0.1, 0.9});
    glPopMatrix();
     glPushMatrix();
        glTranslatef(50, -100, 0);
        DesenhaPalhaco({0.9, 0.2, 0.6}, {0.2, 0.9, 0.9});
    glPopMatrix();

    // Lampadas na entrada da tenda principal
    DesenhaPosteDeLuz(-25, -45, 0, GL_LIGHT0);
    DesenhaPosteDeLuz(25, -45, 0, GL_LIGHT2);

    // Entre duas tendas
    DesenhaPosteDeLuz(40, 210, 0, GL_LIGHT1);  

    // Perto da laranjinha
    DesenhaPosteDeLuz(-140, -120, 0, GL_LIGHT3); 

    // Perto da azul no canto
    DesenhaPosteDeLuz(170, 20, 0, GL_LIGHT4);
    
    // Entre duas tendas
    DesenhaPosteDeLuz(-180, 100, 0, GL_LIGHT5); 
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


void DesenhaCilindroEntrePontos(Vector3 p1, Vector3 p2, double radius, int subdivisions) {
    Vector3 v = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
    double height = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    if (height < 0.0001) return; // Nunca desenhar cilindros muito pequenos

    Vector3 z_axis = {0.0, 0.0, 1.0};
    Vector3 v_normalized = normalizar(v);
    
    // Calcular o produto escalar para verificar casos de paralelismo/anti-paralelismo
    double dot_product = v_normalized.z;
    
    glPushMatrix();
        glTranslated(p1.x, p1.y, p1.z);

        // Se for anti-paralelo ao eixo Z (apontando reto pra baixo)
        if (dot_product < -0.9999) {
            // Precisamos rotacionar 180 graus
            glRotated(180.0, 1.0, 0.0, 0.0);
        }
        // Se for paralelo ao eixo Z (apontando reto pra cima)
        else if (dot_product > 0.9999) {
            // Nao precisamos fazer nada
        }
        // Caso geral para qualquer outra orientacao
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
