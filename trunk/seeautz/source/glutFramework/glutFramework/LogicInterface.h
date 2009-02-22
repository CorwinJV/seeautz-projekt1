#ifndef LOGICINTERFACE_H
#define LOGICINTERFACE_H

#include "oglUtility.h"
#include "oglTexture2D.h"
#include "aiInstructionEnums.h"
#include "logicBlock.h"
#include "oglGameVars.h"
#include "MenuSystem.h"
#include "FunctionPointer.h"

#include <vector>
#include <string>

using namespace BE;

class LogicInterface
{
public:
	LogicInterface();
	~LogicInterface() {}
	void Draw();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);

	bool UpArrowButtonClick();
	bool DownArrowButtonClick();
	bool LeftArrowButtonClick();
	bool RightArrowButtonClick();
	bool ExecuteButtonClick();
	bool AbortButtonClick();

	void SetExecuteHandler(CFunctionPointer1R<bool, std::vector<logicBlock*>> clickHandler);
	void SetAbortHandler(CFunctionPointer0R<bool> clickHandler);
private:
	MenuSys* myMenu;
	bool isButtonBeingClicked;

	oglTexture2D* menuBar;
	int bottomBarXOffset;
	int sideBarYOffset;
	bool isMouseDragging;
	logicBlock* draggedBlock;
	CFunctionPointer1R<bool, std::vector<logicBlock*>> mExecuteHandler;
	CFunctionPointer0R<bool> mAbortHandler;

	std::vector<logicBlock*>* logicBank;		// The usable logic blocks
	std::vector<logicBlock*> executionList;	// The command to give the robot
};

#endif // LOGICINTERFACE_H