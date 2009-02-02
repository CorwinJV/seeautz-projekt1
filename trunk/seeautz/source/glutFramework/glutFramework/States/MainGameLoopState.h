#ifndef MAINGAMELOOPSTATE_H
#define MAINGAMELOOPSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"


class MainGameLoopState : public GameState
{
public:
	MainGameLoopState() {};
	MainGameLoopState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	//	img = new pixmap("statescreens/startnewgame.bmp");
	//	img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\levelview.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &MainGameLoopState::LevelViewCallback));
		Update();
	}

	bool MainGameLoopState::Update();
	bool MainGameLoopState::Draw();
	bool LevelViewCallback();

private:

	// add private stuff here

};

#endif