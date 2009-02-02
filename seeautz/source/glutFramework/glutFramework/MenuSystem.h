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
#include "consoleDefines.h"
#include "oglTexture2D.h"


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

	bool leftButtonDown;
	bool rightButtonDown;
	int mouseXPos;
	int mouseYPos;

	oglTexture2D* menuImage;
	vector<Button*> buttonList;

public:
	MenuSys(int xpos, int ypos, string imgname, Justification nbuttonJust = Auto);
	MenuSys();
	~MenuSys();

	//template <class T>
	inline bool addButton(string buttonImageNormal = "normal.png", string buttonImageClicked = "clicked.png", string buttonImageHover = "hover.png", int buttonXpos = 0, int buttonYpos = 0)
	{
		numButtons++;
#ifdef menuWork
		std::cout << "MS:addButton - Adding new Button " << std::endl;
#endif
		Button* newButton = new Button(buttonXpos, buttonYpos, buttonImageNormal, buttonImageClicked, buttonImageHover);  // this needs to be implemented for button constructor

		buttonList.push_back(newButton);
		recalcButtonPositions();
		return true;
		// if something bad happens, return false
	}

	inline bool addButton(string buttonImageNormal, string buttonImageClicked, string buttonImageHover, CFunctionPointer0R<bool> clickEventHandler)
	{
		numButtons++;
#ifdef menuWork
		std::cout << "MS:addButton - Adding new Button " << std::endl;
#endif
		Button* newButton = new Button(0, 0, buttonImageNormal, buttonImageClicked, buttonImageHover);  // this needs to be implemented for button constructor
		
		// Click handler (callback / function pointer)
		if(clickEventHandler)
			newButton->setClickHandler(clickEventHandler);

		buttonList.push_back(newButton);
		recalcButtonPositions();
		return true;
	}

	virtual void recalcButtonPositions();
	virtual void setMenuXPos(int position);
	virtual void setMenuYPos(int position);
	virtual int getXPos();
	virtual int getYPos();
	virtual int getMouseXPos();
	virtual int getMouseYPos();
	virtual void setMousePos(int x, int y);
	virtual void processMouse(int x, int y);
	virtual void processMouseClick(int button, int state, int x, int y);
	virtual void setLeftButtonStatus(bool);
	virtual void setRightButtonStatus(bool);
	virtual bool Initialize();
	virtual bool Update();
    virtual bool Draw();
	virtual bool Remove();
};

#endif