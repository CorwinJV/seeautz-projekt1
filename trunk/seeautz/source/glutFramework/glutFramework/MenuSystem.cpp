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

int MenuSys::getMouseXPos()
{
	return mouseXPos;
}

int MenuSys::getMouseYPos()
{
	return mouseYPos;
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

void MenuSys::processMouse(int x, int y)
{
	setMousePos(x, y);
#ifdef mouseWork
	std::cout << "MOUSE POSITION:: " << x << ", " << y << endl;
#endif

	// process buttons with mouse coords
	vector<Button*>::iterator itr = buttonList.begin();

	// update buttonlist
	for (; itr != buttonList.end(); itr++)
    {
		if( (*itr)->checkInBounds(x, y) )
		{
			(*itr)->setButtonStatus(Hover);
		}
		else
		{
			(*itr)->setButtonStatus(Normal);
		}
    }


	/*if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		setLeftButtonStatus(true);
		#ifdef mouseWork
		std::cout<<"Left button Pressed" << endl;
		#endif
	}
	if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		setLeftButtonStatus(false);
		#ifdef mouseWork
		std::cout<<"Left button not Pressed" << endl;
		#endif
	}

	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		setRightButtonStatus(true);
		#ifdef mouseWork
		std::cout<<"right button Pressed" << endl;
		#endif
	}
	if (button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		setRightButtonStatus(false);
		#ifdef mouseWork
		std::cout<<"right button not Pressed" << endl;
		#endif
	}*/
}

void MenuSys::processMouseClick(int button, int state, int x, int y)
{
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		vector<Button*>::iterator itr = buttonList.begin();
		for(; itr != buttonList.end(); itr++)
		{
			int mX = (*itr)->getXPos();
			int mY = (*itr)->getYPos();
			if((*itr)->checkInBounds(x, y))
			{
				(*itr)->callClickHandler();
			}
			
			//(*itr)->buttonYPos);
			//(*itr)->buttonXPos);
			//(*itr)->callClickHandler();
		}
	}
}

void MenuSys::setMousePos(int x, int y)
{
	mouseXPos = x;
	mouseYPos = y;
}

void MenuSys::setLeftButtonStatus(bool left)
{
	leftButtonDown = left;
}

void MenuSys::setRightButtonStatus(bool right)
{
	rightButtonDown = right;
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