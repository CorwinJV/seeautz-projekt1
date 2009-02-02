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
		myMenu->addButton("..\\Content\\buttons\\succeed.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &ExecutionModeState::SucceedCallback));
		myMenu->addButton("..\\Content\\buttons\\abortfail.png", "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &ExecutionModeState::AbortCallback));
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