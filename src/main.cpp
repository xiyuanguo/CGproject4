#include "windows.h"
#include "GL\gl.h"
#include "GL\glu.h"
#include "GL\glut.h"
#include<iostream>
#include"Scene.h"

using namespace std;

Scene s;
void init(void)
{

}
int width=400;
int height=400;

void  display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	/*float *b=new float[width*height*3];
	int index=0;
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			b[index*3+0]=255;
			b[index*3+1]=255-i*2;
			b[index*3+2]=255-j*2;
			index++;
		}
	}
	glRasterPos2f(-1,-1);
	glDrawPixels(width,height,GL_RGB,GL_FLOAT,(const GLvoid*)b);*/
	s.display();
	glutSwapBuffers(); 
	glFlush();
}
void  reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int main(int argc, char* argv[]){

	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(300,200);
	glutCreateWindow("hw2");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();  
	/*Sphere s(0,0,0,2);
	Ray r(Point(0,-8,0),Vector3(0,2,0));
	cout<<s.isRayHit(r)<<endl;
	cout<<s.hitPoint(r).x<<" "<<s.hitPoint(r).y<<" "<<s.hitPoint(r).z<<endl;*/
}