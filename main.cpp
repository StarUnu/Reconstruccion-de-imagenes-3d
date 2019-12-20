#include <GL/glut.h>
#include "BmpLoader.h"
#include <iostream>
BmpLoader bl;
using namespace std;
double theta=0;
unsigned int ID;
void display();
void anim();
void reshape(int, int);

void init(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void LoadTexture(){
    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_2D,ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D,GL_RGB,bl.iWidth,bl.iHeight,GL_RGB,GL_UNSIGNED_BYTE,bl.textureData);
}

int main(int argc, char ** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glOrtho(0.0f,1.0f,1.0f,0.0f,0.0f,1.0f);
    glutInitWindowSize(1200,700);
    glutCreateWindow("Imagen");
    LoadTexture();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(anim);
    init();
    glutMainLoop();
    return 0;
}

void display(){
    glEnable(GL_TEXTURE_2D);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-6.0);
    glRotatef(theta,1.0,2.0,0.0);
    for(int i = 0; i<6;i++){
        glPushMatrix();
        if(i==1){
            glTranslatef(1.0,0.0,0.0);
            glRotatef(90,0.0,1.0,0.0);
            glTranslatef(1.0,0.0,0.0);
        }else if (i==2){
            glTranslatef(0.0,0.0,-2.0);
            glRotatef(180.0,0.0,1.0,0.0);
        }else if (i==3){
            glTranslatef(-1.0,0.0,0.0);
            glRotatef(-90.0,0.0,1.0,0.0);
            glTranslatef(-1.0,0.0,0.0);
        }else if (i==4){
            glTranslatef(0.0,1.0,0.0);
            glRotatef(-90.0,1.0,0.0,0.0);
            glTranslatef(0.0,1.0,0.0);
        }else if (i==5){
            glTranslatef(0.0,-1.0,0.0);
            glRotatef(90.0,1.0,0.0,0.0);
            glTranslatef(0.0,-1.0,0.0);
        }
        /*glBegin(GL_QUADS);
            glTexCoord2f(1.0,1.0);  glVertex3f(1.0,1.0,0.0);
            glTexCoord2f(0.0,1.0);  glVertex3f(-1.0,1.0,0.0);
            glTexCoord2f(0.0,0.0);  glVertex3f(-1.0,-1.0,0.0);
            glTexCoord2f(1.0,0.0);  glVertex3f(1.0,-1.0,0.0);
        glEnd();*/

        glBegin(GL_POINTS);
        for(int i=0;i<bl.cont;i++){
             glVertex3f(bl.f[i],bl.c[i],0);
        }
        glEnd();

        /*Malla
        glBegin(GL_LINES);
        for(int i=0;i<bl.cont;i=i+200){
             glVertex3f(bl.f[i],bl.c[i],0);
             glVertex3f(bl.f[i],bl.c[i],-2.0);
        }
        glEnd();*/

        /*Solido*/
        glBegin(GL_LINES);
        for(int i=0;i<bl.cont;i++){

             for(int j=0;j<bl.cont;j=j+bl.cont/3){
                glVertex3f(bl.f[i],bl.c[i],0);
                glVertex3f(bl.f[j],bl.c[j],-2.0);
             }
        }
        glEnd();

        glPopMatrix();
    }
    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);
}
void reshape (int w,int h){
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,50.0);
    glMatrixMode(GL_MODELVIEW);
}
void anim(){
    glutPostRedisplay();
    theta+=0.04;
}
