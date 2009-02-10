#ifndef OBJECT_H
#define OBJECT_H

#include "oglTexture2D.h"
#include "aiInstructionEnums.h"
#include <vector>
#include "objectEnums.h"
#include "logicBlock.h"

using namespace std;

class object
{
protected:
	int				xPos;
	int				yPos;
	int				direction;
	bool			active;
	int				startXPos;
	int				startYPos;
	int				startDirection;
	bool			startActive;
	objectEnum		objectType;
	oglTexture2D*	image;
	vector<logicBlock*>	instructionList;
	vector<logicBlock*>::iterator currentInstruction;


public:
	//default constructors, destructors
	object();
	object(int x, int y, int newDirection = 0, objectEnum newType = ONothing);
	~object();

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
	virtual AiInstructions	getNextCommand();
	virtual void	startOver();
	virtual objectEnum		getType();
	virtual void	addCommand(logicBlock *newCommand);
	virtual void	removeLastCommand();
	virtual void	coreDump();
};

#endif