#ifndef LOGICINTERFACE_H
#define LOGICINTERFACE_H

#include "oglUtility.h"
#include "oglTexture2D.h"
#include "aiInstructionEnums.h"
#include "logicBlock.h"
#include "oglGameVars.h"

#include <vector>
#include <string>

class LogicInterface
{
public:
	LogicInterface();
	~LogicInterface();
	void Draw();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);


private:
	oglTexture2D* menuBar;
	int bottomBarXOffset;
	int sideBarYOffset;
	bool isMouseDragging;
	logicBlock* draggedBlock;

	std::vector<logicBlock*>* logicBank;		// The usable logic blocks
	std::vector<logicBlock*> executionList;	// The command to give the robot
};

#endif // LOGICINTERFACE_H