#ifndef STOPLOOPSTATE_H
#define STOPLOOPSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"

class StopLoopState : public GameState
{
public:
	StopLoopState() {};
	StopLoopState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	//	img = new pixmap("statescreens/startnewgame.bmp");
	//	img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("pregame.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &StopLoopState::PreGameCallback));
		Update();
	}

	bool StopLoopState::Update();
	bool StopLoopState::Draw();
	bool PreGameCallback();

private:
	// add private stuff here
};

#endif