#include "Button.h"
#include <iostream>
#include <cstring>
#include "GameStateManager.h"

//constructor
Button::Button(int buttonXPos, int buttonYPos, string normalImage, string clickedImage, string hoverImage) 
: hover(NULL) , normal(NULL) , clicked(NULL)
{	
	setButtonXPos(buttonXPos);
	setButtonYPos(buttonYPos);

	normal = new oglTexture2D();
	if(normal != NULL)
		normal->loadImage(normalImage.c_str(), 551, 50);

	clicked = new oglTexture2D();
	if(clicked != NULL)
		clicked->loadImage(clickedImage.c_str(), 551, 50);

	hover = new oglTexture2D();
	if(hover != NULL)
		hover->loadImage(hoverImage.c_str(), 551, 50);

	//normal =	new pixmap(normalImage.c_str());
	//clicked =	new pixmap(clickedImage.c_str());
	//hover =		new pixmap(hoverImage.c_str());


	buttonStatus = Normal;

	Initialize();
}

//destructor
Button::~Button()
{
	delete normal;
	delete clicked;
	delete hover;
}

bool Button::Initialize()
{


	return true;
}

bool Button::Draw()
{
	switch(buttonStatus)
	{
	case Normal:
		if(normal != NULL)
			//normal->drawPixMap();
			normal->drawImage();
		break;
	case Clicked:
		if(clicked != NULL)
			//clicked->drawPixMap();
			clicked->drawImage();
		break;
	case Hover:
		if(hover != NULL)
			//hover->drawPixMap();
			hover->drawImage();
		break;
	}

	return true;
}

int Button::getXPos()
{
	return buttonXPos;
}

int Button::getYPos()
{
	return buttonYPos;
}

bool Button::Remove()
{
	return true;
}

bool Button::Update()
{
	if(normal != NULL)
		normal->mY = buttonYPos;

	if(hover != NULL)
		hover->mY = buttonYPos;

	if(clicked != NULL)
		clicked->mY = buttonYPos;

	if(normal != NULL)
		normal->mX = buttonXPos;

	if(hover != NULL)
		hover->mX = buttonXPos;

	if(clicked != NULL)
		clicked->mX = buttonXPos;


	//check for mouse position
	//update button images
	return true;
}

void Button::setClickHandler(CFunctionPointer0R<bool> clickHandler)
{
	mClickHandler = clickHandler;
}

bool Button::callClickHandler()
{
	if(mClickHandler)
	{
		return mClickHandler();
	}
	else
	{
		return false;
	}
}

void Button::setButtonXPos(int position)
{
	buttonXPos = position;

	if(normal != NULL)
		normal->mX = buttonXPos;

	if(hover != NULL)
		hover->mX = buttonXPos;

	if(clicked != NULL)
		clicked->mX = buttonXPos;
}

void Button::setButtonYPos(int position)
{
	buttonYPos = position;

	if(normal != NULL)
		normal->mY = buttonYPos;

	if(hover != NULL)
		hover->mY = buttonYPos;

	if(clicked != NULL)
		clicked->mY = buttonYPos;
}

void Button::setButtonStatus(buttonState newButtonStatus)
{
	buttonStatus = newButtonStatus;
}

buttonState Button::getButtonStatus()
{
	return buttonStatus;
}

void Button::setButtonXYPos(int positionX, int positionY)
{
	buttonXPos = positionX;
	buttonYPos = positionY;

}

int Button::getHeight()
{
	return normal->dY;
}

int Button::getWidth()
{
	return normal->dX;
}

bool Button::checkInBounds(int x, int y)
{
	// dX and dY should be width and height
	if (((x > normal->mX) && (x < (normal->mX + normal->dX))) &&
		(y > normal->mY) && (y < (normal->mY + normal->dY)))
		return true;
	else 
		return false;
}