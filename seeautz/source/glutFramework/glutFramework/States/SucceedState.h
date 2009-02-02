#ifndef SUCCEEDSTATE_H
#define SUCCEEDSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"

class SucceedState : public GameState
{
public:
	SucceedState() {};
	SucceedState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	//	img = new pixmap("statescreens/startnewgame.bmp");
	//	img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\postgame.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &SucceedState::PostGameCallback));
		Update();
	}

	bool SucceedState::Update();
	bool SucceedState::Draw();
	bool PostGameCallback();

private:
	// add private stuff here
};

#endif