#ifndef LOGICVIEWSTATE_H
#define LOGICVIEWSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"


class LogicViewState : public GameState
{
public:
	LogicViewState() {};
	LogicViewState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		//img = new pixmap("statescreens/startnewgame.bmp");
		//img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\executionmode.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &LogicViewState::ExecutionModeCallback));
		Update();
	}

	bool LogicViewState::Update();
	bool LogicViewState::Draw();
	bool ExecutionModeCallback();

private:
	// add private stuuf here

};
#endif