// #include <vector>
// #include <string>
// #include <iostream>
// #include <GL/glut.h>
// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <opencv2/opencv.hpp>

namespace Texture{

	class Texture
	{
	public:
		Texture();
		~Texture();
	
		bool loadTexture(std::string file, int i);
		void setTexture(int i);
	};

	Texture::Texture(){
	}
	Texture::~Texture(){
		
	}

	bool Texture::loadTexture(std::string file,int i){
	IplImage *image1=cvLoadImage(file.c_str(),CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);

	if(image1==NULL)
		return false;

	cvCvtColor(image1, image1, CV_BGR2RGB);
	cvFlip(image1,NULL,0);

	//glGenTextures(i, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, i);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image1->width,image1->height, GL_RGB,GL_UNSIGNED_BYTE,image1->imageData);

	cvReleaseImage( &image1 );
	return true;
	}

	void Texture::setTexture(int i){
		glBindTexture(GL_TEXTURE_2D,i);
	}
}