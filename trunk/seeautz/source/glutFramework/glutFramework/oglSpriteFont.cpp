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
	charSize = size * 1.5;
	if(fontImage != NULL)
	{
		delete fontImage;
	}
	fontImage = new oglTexture2D;
	fontImage->loadImage(filename, 1024, 512);
	fontImage->dX = 1024;
	fontImage->dY = 512;

	kernAmount = 35.37 + (64-charSize)*0.4;

	//kernAmount = charSize/64 - 1;
}

void oglSpriteFont::drawText(float x, float y, const std::string &str)
{
	// temp here, this is for figuring this shit out...

	//kernAmount = kernTweakb + (64-charSize)*kernTweak;
	// strip the string into chars
	parseText(str);
	int offsetX = x;
	int offsetY = y;

	if(fontImage != NULL)
	{
		for(int i = 0; i < (int)drawMe.size(); i++)
		{
			// Check the current character (drawMe[i]) to see what 
			// image segment we need to draw in fontImage
			int currentCharacter = drawMe[i];

			// Draw the image segment
			fontImage->mX = offsetX + (i * charWidth) - (i*kernAmount);
			fontImage->mY = offsetY;

			int currentRow = currentCharacter / (numColumns);
			int currentColumn =  currentCharacter % (numColumns);
			double bW = (double)fontImage->dX;
			double bY = (double)fontImage->dY;
			
			fontImage->drawImageSegment((currentColumn * charWidth)/bW, (currentRow * charHeight)/bY,			     ((currentColumn * charWidth) + charWidth)/bW, (currentRow * charHeight)/bY, 
										(currentColumn * charWidth)/bW, ((currentRow * charHeight) + charHeight)/bY, ((currentColumn * charWidth) + charWidth)/bW, ((currentRow * charHeight) + charHeight)/bY, 
										1.0, charSize, charSize);
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
	kernAmount = 15;
	kernTweak = 0.1;
	kernTweakb = 0.1;
}

void oglSpriteFont::parseText(const std::string& parseMe)
{
	drawMe.clear();
	for(int x = 0; x < (int)parseMe.length(); x++)
	{
		drawMe.push_back(*(parseMe.substr(x, 1).c_str()));
	}
}