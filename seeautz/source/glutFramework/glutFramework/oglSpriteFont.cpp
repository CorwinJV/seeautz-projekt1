#include "oglSpriteFont.h"

oglSpriteFont::oglSpriteFont() : fontImage(NULL), charWidth(0),
	charHeight(0), charSize(0), numColumns(0), maxAsciiCount(127)
{
	init();
	init();
}

oglSpriteFont::~oglSpriteFont()
{
	if(fontImage != NULL)
	{
		delete fontImage;
	}
}

oglSpriteFont::oglSpriteFont(const std::string &filename, unsigned int size)
{
	init();
	oglSpriteFont::open(filename, size);
}

void oglSpriteFont::open(const std::string &filename, unsigned int size)
{
	charSize = size;
	if(fontImage != NULL)
	{
		delete fontImage;
	}
	fontImage = new oglTexture2D;
	fontImage->loadImage(filename, 1024, 512);
}

void oglSpriteFont::drawText(float x, float y, const std::string &str)
{
	// strip the string into chars
	parseText(str);
	int offsetX = x;
	int offsetY = y;

	if(fontImage != NULL)
	{
		for(int i = 0; i < drawMe.size(); i++)
		{
			// Check the current character (drawMe[i]) to see what 
			// image segment we need to draw in fontImage
			int currentCharacter = drawMe[i];

			// Draw the image segment
			fontImage->mX = offsetX + (i * charWidth);
			fontImage->mY = offsetY;

			int currentRow = currentCharacter / (numColumns);
			int currentColumn =  currentCharacter % (numColumns);

			fontImage->drawImageSegment((currentColumn * charWidth), (currentRow * charHeight), (currentColumn * charWidth) + charWidth, (currentRow * charHeight), (currentColumn * charWidth) + charWidth, (currentRow * charHeight) + charHeight, (currentColumn * charWidth) + charWidth, (currentRow * charHeight) + charHeight, 1.0);

		}
	}
}

void oglSpriteFont::init()
{
	charWidth = 64;
	charHeight = 64;
	numColumns = 16;
	charSize = 64;
	fontImage = NULL;
}

void oglSpriteFont::parseText(const std::string& parseMe)
{
	drawMe.clear();
	for(int x = 0; x < (int)parseMe.length(); x++)
	{
		drawMe.push_back(*(parseMe.substr(x, 1).c_str()));
	}
}