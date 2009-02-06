#ifndef OBJECT_H
#define OBJECT_H

#include "oglTexture2D.h"
#include "aiInstructionEnums.h"
#include <vector>

using namespace std;

class object
{
protected:
	int				xPos;
	int				yPos;
	int				direction;
	oglTexture2D*	image;
	vector<AiInstructions*>	instructionList;
	vector<AiInstructions*>::iterator currentInstruction;
	bool			active;

public:
	//default constructors, destructors
	object();
	object(int x, int y, int newDirection = 0);
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
	virtual AiInstructions*	getNextCommand();
};

#endif