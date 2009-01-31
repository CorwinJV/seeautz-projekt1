#ifndef EXECUTIONMODESTATE_H
#define EXECUTIONMODESTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"

class ExecutionModeState : public GameState
{
public:
	ExecutionModeState() {};
	ExecutionModeState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
//		img = new pixmap("statescreens/startnewgame.bmp");
//		img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("succeed.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &ExecutionModeState::SucceedCallback));
		myMenu->addButton("abortfail.png", "button2down.bmp", "button2over.bmp", CreateFunctionPointer0R(this, &ExecutionModeState::AbortCallback));
		Update();
	}

	bool ExecutionModeState::Update();
	bool ExecutionModeState::Draw();
	bool SucceedCallback();
	bool AbortCallback();

private:

	// add private stuff here
};

#endif