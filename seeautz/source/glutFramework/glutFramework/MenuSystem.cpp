#include "MenuSystem.h"
#include <iostream>
#include "GameStateManager.h"
#include <cstring>

//constructor
MenuSys::MenuSys(int xpos, int ypos, string imgname, Justification nbuttonJust)
: menuImage(NULL)
{
	menuXPos = xpos;
	menuYPos = ypos;
	menuImage = new pixmap(imgname.c_str());
	menuImage->mX = xpos;
	menuImage->mY = ypos;
	numButtons = 0;
	buttonJust = nbuttonJust;
}

MenuSys::MenuSys()
{
	menuXPos = 0;
	menuYPos = 0;
	menuImage = NULL;
	numButtons = 0;
	buttonJust = None;
}

//destructor
MenuSys::~MenuSys()
{
	vector<Button*>::iterator itr = buttonList.begin();

	// delete buttonlist contents
	for (; itr != buttonList.end(); itr++)
    {
		(*itr)->~Button();
    }
	buttonList.clear();
	delete menuImage;
}

//functions that dont do anything, yey!
bool MenuSys::Initialize()
{
	return true;
}

bool MenuSys::Draw()
{
	// draw myself first, then draw the buttons
	if(menuImage != NULL)
		menuImage->drawPixMap();

	vector<Button*>::iterator itr = buttonList.begin();

	// update buttonlist
	for (; itr != buttonList.end(); itr++)
    {
		(*itr)->Draw();
    }
	return true;
}

int MenuSys::getXPos()
{
	return menuXPos;
}

int MenuSys::getYPos()
{
	return menuYPos;
}

bool MenuSys::Remove()
{
	return true;
}

bool MenuSys::Update()
{
	// any menu maitenance goes here
	vector<Button*>::iterator itr = buttonList.begin();

	// update buttonlist
	for (; itr != buttonList.end(); itr++)
    {
		(*itr)->Update();
    }
	return true;
}

void MenuSys::setMenuXPos(int position)
{
	menuXPos = position;
}

void MenuSys::setMenuYPos(int position)
{
	menuYPos = position;
}

void MenuSys::recalcButtonPositions()
{
	if((buttonJust == Auto) && (menuImage != NULL))
	{
		if(numButtons > 0)
		{
			double tempheight = 0;
			double offsety = 0;
			double totalheight = 0;
			double currentspot = 0;

			for(int x = 0; x < numButtons; x++)
			{
				totalheight += buttonList[x]->getHeight();			
			}
			tempheight = menuImage->height - totalheight;
			offsety = (tempheight / numButtons);
			currentspot = offsety/2;

			currentspot += menuImage->mY;
			for(int x = 0; x < numButtons; x++)
			{
				buttonList[x]->setButtonYPos(currentspot);
				buttonList[x]->setButtonXPos((((menuImage->mX + menuImage->width + menuImage->mX) / 2) - (buttonList[x]->getWidth()/2)));
				currentspot += buttonList[x]->getHeight();
				currentspot += offsety;
			}
		}
	}
}