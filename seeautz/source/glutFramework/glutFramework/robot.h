#ifndef ROBOT_H
#define ROBOT_H

using namespace std;

class robot : public object
{
//protected:
//	int				xPos;
//	int				yPos;
//	int				direction;
//	bool			active;
//	int				startXPos;
//	int				startYPos;
//	int				startDirection;
//	bool			startActive;
//	objectEnum		objectType;
//	oglTexture2D*	image;
//	vector<AiInstructions*>	instructionList;
//	vector<AiInstructions*>::iterator currentInstruction;


public:
	//default constructors, destructors
	robot();
	robot(int x, int y, int newDirection = 0, objectEnum newType = ONothing)
		:object(x, y, 0, ORobot){ }
	~robot();

	//virtual void	rotate(int);
	//virtual void	update();
	//virtual void	draw();
	//virtual int		getDirection();
	//virtual int		getXPos();
	//virtual void	setXPos(int);
	//virtual int		getYPos();
	//virtual void	setYPos(int);
	//virtual void	advanceCommand();
	//virtual void	setActive(bool);
	//virtual void	toggleActive();
	//virtual bool	getActive();
	//virtual AiInstructions*	getNextCommand();
	//virtual void	startOver();
};

#endif