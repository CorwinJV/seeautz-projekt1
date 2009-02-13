#ifndef ROBOT_H
#define ROBOT_H

#include "oglTexture2D.h"
#include "aiInstructionEnums.h"
#include <vector>
#include "objectEnums.h"

using namespace std;

class robot : public object
{
	
//protected:
//	/*
//	int				xPos;
//	int				yPos;
//	int				direction;
//	oglTexture2D*	image;
//	vector<AiInstructions*>	instructionList;
//	vector<AiInstructions*>::iterator currentInstruction;
//	bool			active;
//*/
//
public:
	robot();
	robot(int x, int y, int newDirection = 0, objectEnum newType = ORobot) 
		: object(x, y, newDirection, newType){}

	

	/*
	virtual void	rotate(int);
	virtual void	update();
	virtual void	draw();
	virtual int		getDirection();
	virtual int		getXPos();
	virtual void	setXPos(int);
	virtual int		getYPos();
	virtual void	setYPos(int);
	virtual void	advanceCommand();
	virtual void	setActive(bool);
	virtual void	toggleActive();
	virtual bool	getActive();
	virtual AiInstructions*	getNextCommand();
	*/
};

#endif