#ifndef OGLTEXTURE2D_H
#define OGLTEXTURE2D_H

#include <IL\il.h>
#include <IL\ilu.h>
#include <iostream>
#include <string>
#include "oglUtility.h"


class oglTexture2D
{
public:
	oglTexture2D();
	~oglTexture2D();
	bool loadImage(std::string);
	bool drawImage();

	int mX;
	int mY;

private:
	GLuint texture;
	int mWidth;
	int mHeight;
};

#endif