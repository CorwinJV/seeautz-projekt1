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

	bool LogicBankUpArrowButtonClick();
	bool LogicBankDownArrowButtonClick();
	bool ExecutionListUpArrowButtonClick();
	bool ExecutionListDownArrowButtonClick();

	bool ExecuteButtonClick();
	bool AbortButtonClick();
	void ClearExecutionList();

	void SetExecuteHandler(CFunctionPointer1R<bool, std::vector<logicBlock*>> clickHandler);
	void SetAbortHandler(CFunctionPointer0R<bool> clickHandler);
private:
	MenuSys* myMenu;
	bool isButtonBeingClicked;

	oglTexture2D* menuBar;
	bool isMouseDragging;
	logicBlock* draggedBlock;
	CFunctionPointer1R<bool, std::vector<logicBlock*>> mExecuteHandler;
	CFunctionPointer0R<bool> mAbortHandler;

	//======================
	// Size and Positional Variables
	screenBox sideBarBox;
	int executionListYOffset;
	int sideBarColumnCount;
	
	screenBox bottomBarBox;
	int logicBankYOffset;

	int instructionBlockW;
	int instructionBlockH;
	int instructionSpacing;

	int logicBankNumColumns;
	int logicBankNumRowsOnScreen;

	int instructionListNumColumns;
	int instructionListNumRowsOnScreen;
	
	screenBox logicBankBox;
	screenBox instructionListBox;

	std::vector<logicBlock*>* logicBank;		// The usable logic blocks
	std::vector<logicBlock*> executionList;	// The command to give the robot
};

#endif // LOGICINTERFACE_H