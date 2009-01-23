#ifndef MENUSYS_H
#define MENUSYS_H
#include "oglUtility.h"
#include "GameState.h"
#include "pixmap.h"
#include "Button.h"
#include <cstring>
#include <vector>
#include <iostream>

using namespace std;

class MenuSys
{
protected:
    int menuHeight;
    int menuWidth;
	int menuXPos;
	int menuYPos;
	int numButtons;
	pixmap* menuImage;
	vector<Button*> buttonList;

public:
	MenuSys(int xpos = 0, int ypos = 0, string imgname = "");
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