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
	void Update();
	void Draw();
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);

	//=====================
	// Button Callbacks
	bool LogicBankUpArrowButtonClick();
	bool LogicBankDownArrowButtonClick();
	bool ExecutionListUpArrowButtonClick();
	bool ExecutionListDownArrowButtonClick();
	bool MainTabButtonClick();
	bool Sub1TabButtonClick();
	bool Sub2TabButtonClick();

	bool ExecuteButtonClick();
	bool AbortButtonClick();
	bool ResetButtonClick();
	void ClearExecutionList();

	void SetExecuteHandler(CFunctionPointer3R<bool, std::vector<logicBlock*>, std::vector<logicBlock*>, std::vector<logicBlock*>> clickHandler);
	void SetAbortHandler(CFunctionPointer0R<bool> clickHandler);
	void SetResetHandler(CFunctionPointer0R<bool> resetHandler);
private:
	MenuSys* myMenu;
	MenuSys* executingMenu;
	MenuSys* resetMenu;
	bool isButtonBeingClicked;
	bool isExecuting;

	oglTexture2D* menuBar;

	int mouseX;
	int mouseY;
	bool isMouseDragging;
	logicBlock* draggedBlock;

	int currentHoverBlockIndex;

	//=====================
	// Button Callbacks
	//CFunctionPointer1R<bool, std::vector<logicBlock*>> mExecuteHandler;
	CFunctionPointer3R<bool, std::vector<logicBlock*>, std::vector<logicBlock*>, std::vector<logicBlock*>> mExecuteHandler;
	CFunctionPointer0R<bool> mAbortHandler;
	CFunctionPointer0R<bool> mResetHandler;

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
	std::vector<logicBlock*> executionListSub1;
	std::vector<logicBlock*> executionListSub2;

	//======================
	// Instruction List Tabs
	enum instructionTab
	{
		TAB_MAIN,
		TAB_SUB1,
		TAB_SUB2
	};
	instructionTab curInstrTab;
};

#endif // LOGICINTERFACE_H