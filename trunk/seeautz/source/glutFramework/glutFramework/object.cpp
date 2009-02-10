#include "object.h"

object::object()
{
	xPos = 0;
	yPos = 0;
	direction = 0;
	active = true;
}

object::object(int x, int y, int newDirection, objectEnum newType)
{
	setXPos(x);
	setYPos(y);
	direction = newDirection;
	active = true;
	objectType = newType;
}

object::~object()
{
	delete image;
	std::cout << "tick tick tick boom" << endl;
}

bool object::getActive()
{
	return active;
}

int object::getDirection()
{
	return direction;
}

int object::getXPos()
{
	return xPos;
}

int object::getYPos()
{
	return yPos;
}

void object::setActive(bool activate)
{
	active = activate;
}

void object::toggleActive()
{
	if(active == true)
		active = false;
	else
		active = true;
}

void object::rotate(int rotation)
{
	//send in a +1 for left, -1 for right
	direction += rotation;

	if(direction < 0)	direction = 3;
	if(direction > 3)	direction = 0;
}

void object::setXPos(int x)
{
	xPos = x;
}

void object::setYPos(int y)
{
	yPos = y;
}

void object::advanceCommand()
{
	currentInstruction++;
	if(currentInstruction == instructionList.end())
		currentInstruction = instructionList.begin();
}

AiInstructions* object::getNextCommand()
{
	return *currentInstruction;
}

void object::draw()
{
	
}

void object::update()
{
	//advance animation code here
}

void object::startOver()
{	
	xPos = startXPos;
	yPos = startYPos;
	direction = startDirection;
	active = startActive;
}