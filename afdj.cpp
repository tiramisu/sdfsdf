//C++
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

//OpenGL
#include <GL/glew.h>
#include <GL/glut.h>

//OpenCV
#include <opencv2/opencv.hpp>

//C
#include <cmath>

//my include file
#include "Texture.h"
#include "Ground.h"


//Constant
#define KEY_ESC 27
#define PAI 3.1415926535

//instance
Texture::Texture texture;
Ground::Ground ground(-10,-10,10,10,1);

//mouse
int xBegin=0,yBegin=0;
int mButton=10;
int mState=10;

//looking angle & position
double px=0,py=0,pz=0;
double twist,elevation,azimuth;

//view
const float nearw = 0.1, farw = 30.0, fovy = 60.0;

//draw character
void *font = GLUT_BITMAP_HELVETICA_10;
void DrawString(const std::string str,void *font,float x,float y)
{
	glWindowPos2f(x,y);
	int sz=str.size();
	for (int i = 0; i < sz; ++i)
	{
		glutBitmapCharacter(font, str[i]);
	}
}
//keyboard event
void keyboard( unsigned char key, int x, int y )
{
	if ( key == KEY_ESC ) exit( 0 );
	if ( key == 'w') {
		px+=cos(azimuth)*0.5;
		pz+=sin(azimuth)*0.5;
	}
}

//click event
void click( int button, int state, int x, int y )
{
	if (state == GLUT_DOWN && button==GLUT_LEFT_BUTTON) {
		mButton=button;
		mState=state;
		xBegin = x;
		yBegin = y;
		px+=cos(azimuth)*0.5;
		px = fmin(px,10);
		px = fmax(px,-10);
		pz+=sin(azimuth)*0.5;
		pz = fmin(pz,10);
		pz = fmax(pz,-10);
	}
	if (state==GLUT_UP)
	{
		mButton=10;
		mState=10;
	}
}

//drag event
void drag(int x, int y)
{
	int xDisp, yDisp;

	xDisp = x - xBegin;
	yDisp = y - yBegin;
	switch(mButton){
	default:
		azimuth =fmod(azimuth + xDisp/100.0,2*M_PI);
		elevation = fmax(elevation + yDisp/100.0,-M_PI/2.0);
		elevation = fmin(elevation + yDisp/100.0,M_PI/2.0);
		break;
	}
	xBegin = x;
	yBegin = y;
}

//motion event
void motion(int x, int y){
	int xDisp, yDisp;

	xDisp = x - xBegin;
	yDisp = y - yBegin;
	azimuth =fmod(azimuth + xDisp/50.0,2*M_PI);
	elevation = fmax(elevation + yDisp/50.0,-M_PI/2.0);
	elevation = fmin(elevation + yDisp/50.0,M_PI/2.0);
	xBegin = x;
	yBegin = y;
}

//init texture load
void init (char *progname)
{
	glutInitWindowPosition(0, 0);
	glutInitWindowSize( 400, 400);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(progname);
	glClearColor (1.0, 0.0, 0.0, 1.0);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(click);
	glutMotionFunc(drag);
	glutPassiveMotionFunc(motion);
	glShadeModel( GL_SMOOTH );
	glEnable( GL_LIGHT0 );
	if(!texture.loadTexture("./texture/zzzz.jpeg",1)){
		std::cout<<"LoadGLTextures error\n";
		exit(1);
	}
	if(!texture.loadTexture("./texture/dc.jpeg",2)){
		std::cout<<"LoadGLTextures error\n";
		exit(1);
	}
}

//reshape
void reshape(int width, int height)
{
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, nearw, farw);
	glMatrixMode(GL_MODELVIEW);
}
//timer
void timer(int flag)
{
	if(flag==1){
		if (mButton==GLUT_LEFT_BUTTON && mState == GLUT_DOWN)
		{
			px+=cos(azimuth)*0.5;
			px = fmin(px,10);
			px = fmax(px,-10);
			pz+=sin(azimuth)*0.5;
			pz = fmin(pz,10);
			pz = fmax(pz,-10);
		}
		glutPostRedisplay();
		glutTimerFunc(30,timer,1);
	}
}


//display
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable( GL_DEPTH_TEST );
	//glEnable(GL_LIGHTING);
	glEnable( GL_NORMALIZE);
	glEnable( GL_AUTO_NORMAL);
	{
		glPushMatrix();
		{
			gluLookAt( 0.0 + px , 1.0 + py , 0 + pz, px + cos(azimuth), 1.0 - sin(elevation) + py,pz + sin(azimuth), 0, 1, 0);

			ground.drawGroundTex(1, 2);

		}
		glPopMatrix();

		glPushMatrix();
		DrawString("px:"+boost::lexical_cast<std::string>(px)+" pz:"+boost::lexical_cast<std::string>(pz), font, 10, 5);
		glPopMatrix();
	}

	//glDisable( GL_LIGHTING );
	glDisable( GL_DEPTH_TEST );

	glutSwapBuffers();
}

//main
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	init(argv[0]);
	glewInit();
	glutReshapeFunc (reshape);
	glutDisplayFunc(display);
	glutTimerFunc(30,timer,1);
	glutMainLoop();
	return 0;
}