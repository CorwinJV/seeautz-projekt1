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

class oglSpriteFont
{
public:
	oglSpriteFont();
	oglSpriteFont(const std::string& filename, unsigned int size);

	~oglSpriteFont();

	void open(const std::string& filename, unsigned int size);
    void drawText(float x, float y, const std::string& str);

	// drawText
	// open
private:
};