#include "MenuSystem.h"
#include <iostream>
#include "GameStateManager.h"

//constructor
MenuSys::MenuSys() : GameState()
{
}

//destructor
MenuSys::~MenuSys()
{
}

//functions that dont do anything, yey!
bool MenuSys::Initialize()
{
	return true;
}

bool MenuSys::Draw()
{
	return true;
}

int MenuSys::getXPos()
{
	return true;
}

int MenuSys::getYPos()
{
	return true;
}

bool MenuSys::Remove()
{
	return true;
}

bool MenuSys::Update()
{
	return true;
}

void MenuSys::setMenuXPos(int position)
{

}

void MenuSys::setMenuYPos(int position)
{

}