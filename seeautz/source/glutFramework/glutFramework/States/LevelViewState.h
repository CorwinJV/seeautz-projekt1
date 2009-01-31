#ifndef LEVELVIEWSTATE_H
#define LEVELVIEWSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"

class LevelViewState : public GameState
{
public:
	LevelViewState() {};
	LevelViewState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
//		img = new pixmap("statescreens/startnewgame.bmp");
//		img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("logicview.png", "button1down.bmp", "button1over.bmp", CreateFunctionPointer0R(this, &LevelViewState::LogicViewCallback));
		Update();
	}

	bool LevelViewState::Update();
	bool LevelViewState::Draw();
	bool LogicViewCallback();

private:
	// add private stuff here

};

#endif