#ifndef MENUSYS_H
#define MENUSYS_H

///      Hey guys. When I moved to put a MenuSys pointer into the base GameState
/// it fucked everything up because MenuSystem.h and Button.h both had 
/// references to GameState.h which means we put the compiler in a nice little
/// infinite loop xD.
///      I moved the definition for the "State" enum into
/// oglUtility for now. I know it's not the best fix but I think that it
/// will work for everything we need it to. -Corwin

#include "oglUtility.h"
#include "pixmap.h"
#include "Button.h"
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

enum Justification{ 
				None,		// no justification - use default values
				Auto		// automatically justified
};

class MenuSys
{
protected:
    int menuHeight;
    int menuWidth;
	int menuXPos;
	int menuYPos;
	int numButtons;
	Justification buttonJust;

	pixmap* menuImage;
	vector<Button*> buttonList;

public:
	MenuSys(int xpos, int ypos, string imgname, Justification nbuttonJust = Auto);
	MenuSys();
	~MenuSys();

	//template <class T>
	inline bool addButton(int buttonXpos = 0, int buttonYpos = 0, string buttonImageNormal = "normal.bmp", string buttonImageClicked = "clicked.bmp", string buttonImageHover = "hover.bmp")
	{
		numButtons++;
		std::cout << "MS:addButton - Adding new Button " << std::endl;
		Button* newButton = new Button(buttonXpos, buttonYpos, buttonImageNormal, buttonImageClicked, buttonImageHover);  // this needs to be implemented for button constructor
		buttonList.push_back(newButton);
		recalcButtonPositions();
		return true;
		// if something bad happens, return false
	}

	inline bool addButton(string buttonImageNormal = "normal.bmp", string buttonImageClicked = "clicked.bmp", string buttonImageHover = "hover.bmp")
	{
		numButtons++;
		std::cout << "MS:addButton - Adding new Button " << std::endl;
		Button* newButton = new Button(0, 0, buttonImageNormal, buttonImageClicked, buttonImageHover);  // this needs to be implemented for button constructor
		buttonList.push_back(newButton);

		recalcButtonPositions();
		return true;
		// if something bad happens, return false
	}
	
	virtual void recalcButtonPositions();
	virtual void setMenuXPos(int position);
	virtual void setMenuYPos(int position);
	virtual int getXPos();
	virtual int getYPos();
	virtual bool Initialize();
	virtual bool Update();
    virtual bool Draw();
	virtual bool Remove();
};

#endif