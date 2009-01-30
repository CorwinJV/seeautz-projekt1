#include "oglTexture2D.h"

oglTexture2D::oglTexture2D() 
	: mX(0), mY(0), mWidth(0), mHeight(0),
	texture(NULL)
{

}

oglTexture2D::~oglTexture2D()
{

}

bool oglTexture2D::loadImage(std::string filename)
{
	ilInit();
	glEnable(GL_TEXTURE_2D);
	gluOrtho2D(0.0, 1024.0, 768.0, 0.0);
	glClearDepth(0.0f);
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate DevIL image and make current context
	ILuint image = NULL;
	ilGenImages(1, &image);
	ilBindImage(image);

	// Load in the image
	if(!ilLoadImage(filename.c_str()))
	{
		std::cout << "oglTexture2D::loadImage failed to load" 
			<< filename << std::endl;
		return false;
	}
	mWidth = ilGetInteger(IL_IMAGE_WIDTH);
	mHeight = ilGetInteger(IL_IMAGE_HEIGHT);

	// Copy to OpenGL texture
	if(!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
	{
		std::cout << "oglTexture2D::loadImage unable to convert image"
			<< " into display friendly format." << std::endl;
		return false;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Use nice (linear) scaling 
	glTexParameteri(GL_TEXTURE_2D, 
		GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Use nice (linear) scaling 
	glTexImage2D(GL_TEXTURE_2D, 0
		, ilGetInteger(IL_IMAGE_BPP), mWidth, mHeight, 
		0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, 
		ilGetData()); 
	
	// Free DevIL image since we have it in a texture now 
	ILubyte* data = ilGetData();
	ilDeleteImages(1, &image);
	ILenum Error;
	while ((Error = ilGetError()) != IL_NO_ERROR) 
	{ 
		std::cout << "DevIL Loading error: " << Error; 
	} 
	return true;
}

bool oglTexture2D::drawImage()
{
	// Bind texture to current context 
	glBindTexture(GL_TEXTURE_2D, texture); 
	// Set the alpha 
	glColor4f(1.0, 1.0, 1.0, 1.0); 

	// Draw texture using a quad 
	glBegin(GL_POLYGON); 
		// Top left 
		glTexCoord2f(0.0, 0.0); 
		glVertex2i(mX, mY); 
		// Top right 
		glTexCoord2f(1.0, 0.0); 
		glVertex2i(mX + mWidth, mY); 
		// Bottom right 
		glTexCoord2f(1.0, 1.0); 
		glVertex2i(mX + mWidth, mY + mHeight); 
		// Bottom left 
		glTexCoord2f(0.0, 1.0); 
		glVertex2i(mX, mY + mHeight); 
		// Finish quad drawing 
	glEnd();

	return true;
}

	//// Top left 
	//	glTexCoord2f(0.0, 0.0); 
	//	glVertex2i(mX, mY); 
	//	// Top right 
	//	glTexCoord2f(1.0, 0.0); 
	//	glVertex2i(mX + mWidth, mY); 
	//	// Bottom right 
	//	glTexCoord2f(1.0, 1.0); 
	//	glVertex2i(mX + mWidth, mY + mHeight); 
	//	// Bottom left 
	//	glTexCoord2f(0.0, 1.0); 
	//	glVertex2i(mX, mY + mHeight); 
	//	// Finish quad drawing 