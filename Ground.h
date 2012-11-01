#include <vector>
#include <string>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <opencv2/opencv.hpp>

namespace Ground{
	class Ground
	{
		double minX,minY,maxX,maxY,tile_size;
	public:
		Ground(double minX, double minY, double maxX, double maxY, double tile_size);
		~Ground();
	
		void drawGroundTex(GLuint num1, GLuint num2);
	};

	Ground::Ground(double minX, double minY, double maxX, double maxY, double tile_size){
		this->minX=minX;
		this->minY=minY;
		this->maxX=maxX;
		this->maxY=maxY;
		this->tile_size=tile_size;
	}
	Ground::~Ground(){

	} 

	void Ground::drawGroundTex(GLuint num1, GLuint num2){
			for (int i = minX; i < maxX/tile_size; ++i)
  		{
	    	for (int j = minY; j < maxY/tile_size; ++j)
	    	{
	    		if ((i+j)%2)
	    		{
	    			glBindTexture(GL_TEXTURE_2D, num1);
	    		}
	    		else{
	    			glBindTexture(GL_TEXTURE_2D, num2);
	    		}
	    		glColor3f(1,1,1);
					glEnable(GL_TEXTURE_2D);
					glBegin(GL_QUADS);
					glNormal3f(0.0,1.0,0.0);
					glTexCoord2f(0,0);glVertex3d(i * tile_size, 0.0, j * tile_size);
		      glTexCoord2f(1,0);glVertex3d((i + 1) * tile_size, 0.0, j * tile_size);
		      glTexCoord2f(1,1);glVertex3d((i + 1) * tile_size, 0.0, (j + 1) * tile_size);
		      glTexCoord2f(0,1);glVertex3d(i * tile_size, 0.0, (j + 1) * tile_size);
					glEnd();
					glDisable(GL_TEXTURE_2D);
    		}
  		}
	}
}