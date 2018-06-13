#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

#ifndef OBJECT_H
#define OBJECT_H

/// CLASSE OBJECT ///========================================================================================///
/*  Descrição: 
 *    classe que qualquer objeto deve herdar, pois aqui estão condensadas as características
 *    mais comuns à todos os objetos.
 */
///===============///========================================================================================///
class Object{
public:
    // Prototipação dos Construtores:
    Object();
    Object(float currentX, float currentY, float currentZ);
    Object(float currentX, float currentY, float currentZ,
           bool  rotateX , bool  rotateY , bool  rotateZ , float newCenterDistance,
           float angle   , float newSizeX, float newSizeY, float newSizeZ);

    // Prototipação dos Métodos de Propósito Geral:
    void generate(float red, float green, float blue);

    // Prototipação dos Métodos Get:
    float getCoordinateX();
    float getCoordinateY();
    float getCoordinateZ();
    bool  getRotationX();
    bool  getRotationY();
    bool  getRotationZ();
    float getRotationAngleX();
    float getRotationAngleY();
    float getRotationAngleZ();
    float getSizeX();
    float getSizeY();
    float getSizeZ();
    float getCenterDistance();
    bool  getCollidedX();
    bool  getCollidedY();
    bool  getCollidedZ();
    // Prototipação dos Métodos Set:
    void setCoordinateX(float currentX);
    void setCoordinateY(float currentY);
    void setCoordinateZ(float currentZ);
    void setRotationX(bool rotateX);
    void setRotationY(bool rotateY);
    void setRotationZ(bool rotateZ);
    void setRotationAngleX(float rotateAngleX);
    void setRotationAngleY(float rotateAngleY);
    void setRotationAngleZ(float rotateAngleZ);
    void setSizeX(float newSizeX);
    void setSizeY(float newSizeY);
    void setSizeZ(float newSizeZ);
    void setCenterDistance(float newCenterDistance);
    void setCollidedX(bool newCollided);
    void setCollidedY(bool newCollided);
    void setCollidedZ(bool newCollided);

protected:
    // Coordenadas da posição do objeto:
    float coordinateX;
    float coordinateY;
    float coordinateZ;

    // Definidores de rotação do objeto:
    bool  rotationX;
    bool  rotationY;
    bool  rotationZ;
    float rotationAngleX;
    float rotationAngleY;
    float rotationAngleZ;

    // Definição do tamanho do objeto:
    float sizeX;
    float sizeY;
    float sizeZ;

    // Define a distância do limite da Hit Box do objeto
    float centerDistance;

    // Definidor de colisão do objeto:
    bool collidedX;
    bool collidedY;
    bool collidedZ;
};


// CONSTRUTORES //---------------------------------------------------------------------------//

Object::Object(){
    coordinateX = 0.0;
    coordinateY = 0.0;
    coordinateZ = 0.0;

    rotationX = false;
    rotationY = false;
    rotationZ = false;
    rotationAngleX = 0.0;
    rotationAngleY = 0.0;
    rotationAngleZ = 0.0;

    sizeX = 0.5;
    sizeY = 0.5;
    sizeZ = 0.5;

    centerDistance = 1.0;

    collidedX = false;
    collidedY = false;
    collidedZ = false;
}

Object::Object(float currentX, float currentY, float currentZ){
    coordinateX = currentX;
    coordinateY = currentY;
    coordinateZ = currentZ;

    rotationX = false;
    rotationY = false;
    rotationZ = false;
    rotationAngleX = 0.0;
    rotationAngleY = 0.0;
    rotationAngleZ = 0.0;

    sizeX = 0.5;
    sizeY = 0.5;
    sizeZ = 0.5;

    centerDistance = 1.0;

    collidedX = false;
    collidedY = false;
    collidedZ = false; 
}

Object::Object(float currentX, float currentY, float currentZ,
               bool  rotateX , bool  rotateY , bool  rotateZ , float newCenterDistance,
               float angle   , float newSizeX, float newSizeY, float newSizeZ){

    coordinateX = currentX;
    coordinateY = currentY;
    coordinateZ = currentZ;

    rotationX = rotateX;
    rotationY = rotateY;
    rotationZ = rotateZ;
    rotationAngleX = angle;
    rotationAngleY = 0.0;
    rotationAngleZ = 0.0;

    sizeX = newSizeX;
    sizeY = newSizeY;
    sizeZ = newSizeZ;

    centerDistance = newCenterDistance;

    collidedX = false;
    collidedY = false;
    collidedZ = false; 
}

//--------------//---------------------------------------------------------------------------//


// MÈTODOS DE PROPÒSITO GERAL //------------------------------------------------------------//

/* Método Generate:  
 *   Descrição: 
 *     Faz a geração do objeto e define sua posição, tamanho, rotação, cor, etc, ou
 *     seja, todas as informações acerca de suas características no espaço do universo,
 *     usualmente sendo chamado a cada frame de exibição para poder gerar novamente
 *     sua exibição;
 *
 *   Parâmetros:
 *     float red, float green, float blue:
 *       Definem a cor do objeto através do RGB.
 */
void Object::generate(float red, float green, float blue){
    glPushMatrix();
        // Muda o tamanho do objeto ao aplicar uma escala isotrópica em X, Y e Z
        //glScalef(size, size, size);
        // Faz a rotação em torno do eixo Y, sendo essa a única rotação possível
        // já que o Cacto deve sempre permanecer em pé

        glTranslatef(coordinateX, coordinateY, coordinateZ);
        glRotatef(rotationAngleX, 1.0, 0.0, 0.0);
        glRotatef(rotationAngleY, 0.0, 1.0, 0.0);
        glRotatef(rotationAngleZ, 0.0, 0.0, 1.0);
        // Aqui o cubo faz o movimento contrário ao da translação
        // aplicada pela câmera para cancelar com o +moviment dela
        // e consequentemente permanecer parado
        
        // OBS.: A translação deve sempre ocorrer após as outras mudanças pois a partir
        //       do momento em que o objeto sai da origem, qualquer rotação faria com que
        //       ele movesse em torno do eixo rotacionado (deslocando-o da posição correta)
        //       e qualquer mudança de escala o deslocaria implicitamente

        // Define a cor do objeto:
        
        glColor3f (red, green, blue);
        // Exibe o objeto:
        glBegin(GL_LINES);
            //glColor3f (1.0f, 0.0f, 0.0f); 
            glVertex3f(0.0f, 0.0f, 0.0f);   
            glVertex3f(1.0f, 0.0f, 0.0f);

            
            //glColor3f (0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);   
            glVertex3f(0.0f, 1.0f, 0.0f);

            //glColor3f (0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);   
            glVertex3f(0.0f, 0.0f, 1.0f);

            glVertex3f(1.0f, 0.0f, 1.0f);   
            glVertex3f(1.0f, 0.0f, 0.0f);

            glVertex3f(1.0f, 0.0f, 1.0f);    
            glVertex3f(0.0f, 0.0f, 1.0f);

            glVertex3f(1.0f, 0.0f, 1.0f);    
            glVertex3f(1.0f, 1.0f, 1.0f);

            glVertex3f(0.0f, 1.0f, 0.0f);   
            glVertex3f(1.0f, 1.0f, 0.0f);

            glVertex3f(0.0f, 1.0f, 0.0f);   
            glVertex3f(0.0f, 1.0f, 1.0f);

            glVertex3f(1.0f, 1.0f, 1.0f);   
            glVertex3f(1.0f, 1.0f, 0.0f);

            glVertex3f(1.0f, 1.0f, 1.0f);   
            glVertex3f(0.0f, 1.0f, 1.0f);

            glVertex3f(0.0f, 0.0f, 1.0f);   
            glVertex3f(0.0f, 1.0f, 1.0f);

            glVertex3f(1.0f, 0.0f, 0.0f);   
            glVertex3f(1.0f, 1.0f, 0.0f);
        glEnd();

        // Diagonal
        glColor3f (0.5, 0.5, 0.5);
        glBegin(GL_LINES); 
            glVertex3f(0.0f, 0.0f, 0.0f);   
            glVertex3f(1.0f, 1.0f, 1.0f);
        glEnd();
    glPopMatrix();
}

//----------------------------//------------------------------------------------------------//


// MÈTODOS GET E SET //---------------------------------------------------------------------//

// Métodos Get:
float Object::getCoordinateX(){
    return coordinateX;
}

float Object::getCoordinateY(){
    return coordinateY;
}

float Object::getCoordinateZ(){
    return coordinateZ;
}

bool Object::getRotationX(){
    return rotationX;
}

bool Object::getRotationY(){
    return rotationY;
}

bool Object::getRotationZ(){
    return rotationZ;
}

float Object::getRotationAngleX(){
    return rotationAngleX;
}

float Object::getRotationAngleY(){
    return rotationAngleY;
}

float Object::getRotationAngleZ(){
    return rotationAngleZ;
}

float Object::getSizeX(){
    return sizeX;
}

float Object::getSizeY(){
    return sizeY;
}

float Object::getSizeZ(){
    return sizeZ;
}

float Object::getCenterDistance(){
    return centerDistance;
}

bool Object::getCollidedX(){
    return collidedX;
}

bool Object::getCollidedY(){
    return collidedY;
}

bool Object::getCollidedZ(){
    return collidedZ;
}

// Métodos Set:
void Object::setCoordinateX(float currentX){
    coordinateX = currentX;
}

void Object::setCoordinateY(float currentY){
    coordinateY = currentY;
}

void Object::setCoordinateZ(float currentZ){
    coordinateZ = currentZ;
}

void Object::setRotationX(bool rotateX){
    rotationX = rotateX;
}

void Object::setRotationY(bool rotateY){
    rotationY = rotateY;
}

void Object::setRotationZ(bool rotateZ){
    rotationZ = rotateZ;
}

void Object::setRotationAngleX(float rotateAngleX){
    rotationAngleX = rotateAngleX;
}

void Object::setRotationAngleY(float rotateAngleY){
    rotationAngleY = rotateAngleY;
}

void Object::setRotationAngleZ(float rotateAngleZ){
    rotationAngleZ = rotateAngleZ;
}

void Object::setSizeX(float newSizeX){
    sizeX = newSizeX;
}

void Object::setSizeY(float newSizeY){
    sizeY = newSizeY;
}

void Object::setSizeZ(float newSizeZ){
    sizeZ = newSizeZ;
}

void Object::setCenterDistance(float newCenterDistance){
    centerDistance = newCenterDistance;
}

void Object::setCollidedX(bool newCollidedX){
    collidedX = newCollidedX;
}

void Object::setCollidedY(bool newCollidedY){
    collidedY = newCollidedY;
}

void Object::setCollidedZ(bool newCollidedZ){
    collidedZ = newCollidedZ;
}

//-------------------//---------------------------------------------------------------------//

///===============///========================================================================================///

#endif	// OBJECT_H