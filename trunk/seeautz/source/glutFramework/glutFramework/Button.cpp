#include "Button.h"
#include <iostream>
#include "GameStateManager.h"

//constructor
Button::Button() : GameState()
{
}

//destructor
Button::~Button()
{
}

//functions that dont do anything, yey!
bool Button::Initialize()
{
	return true;
}

bool Button::Draw()
{
	return true;
}

int Button::getXPos()
{
	return true;
}

int Button::getYPos()
{
	return true;
}

bool Button::Remove()
{
	return true;
}

bool Button::Update()
{
	return true;
}

void Button::setButtonXPos(int position)
{

}

void Button::setButtonYPos(int position)
{

}

void Button::setButtonStatus(State buttonStatus)
{

}

State Button::getButtonStatus()
{
	return buttonStatus;
}