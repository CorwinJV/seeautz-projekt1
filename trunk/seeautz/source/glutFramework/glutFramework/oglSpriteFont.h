//=================================
// oglSpriteFont
//    This class is designed to
// meet most interfaces set forth
// by the GLFT_Font class. 
// It's a Sprite Font class that
// allows us to load in custom
// sprite-fonts (non-true-type)
// and draw them on the screen.
// -Corwin VanHook
// 4/8/09
//
#include <string>
#include <vector>
#include "oglTexture2D.h"

class oglSpriteFont
{
public:
	oglSpriteFont();
	oglSpriteFont(const std::string& filename, unsigned int size);

	~oglSpriteFont();

	void init();

	void open(const std::string& filename, unsigned int size);
    void drawText(float x, float y, const std::string& str);

	// drawText
	// open

private:
	std::vector<char> drawMe;

	oglTexture2D* fontImage;
	int charWidth;
	int charHeight;
	int charSize;
	int numColumns;
	int maxAsciiCount;

	void parseText(const std::string& parseMe);
};