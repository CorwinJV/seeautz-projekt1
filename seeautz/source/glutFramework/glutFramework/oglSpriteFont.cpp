#include "oglSpriteFont.h"

oglSpriteFont::oglSpriteFont()
{

}

oglSpriteFont::~oglSpriteFont()
{

}

oglSpriteFont::oglSpriteFont(const std::string &filename, unsigned int size)
{
	//oglSpriteFont::open(filename, size);
}

void oglSpriteFont::open(const std::string &filename, unsigned int size)
{
	charSize = size;
	fontImage = new oglTexture2D;
	fontImage->loadImage(filename, 1024, 512);

}

void oglSpriteFont::drawText(float x, float y, const std::string &str)
{
	// strip the string into chars
	parseText(str);
	int offsetX = x;
	int offsetY = y;

}

void oglSpriteFont::init()
{
	charWidth = 64;
	charHeight = 64;
	numColumns = 16;
	charSize = 64;
}

void oglSpriteFont::parseText(const std::string& parseMe)
{
	drawMe.clear();
	for(int x = 0; x < (int)parseMe.length(); x++)
	{
		drawMe.push_back(*(parseMe.substr(x, 1).c_str()));
	}
}