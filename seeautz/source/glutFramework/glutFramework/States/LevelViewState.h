#ifndef LEVELVIEWSTATE_H
#define LEVELVIEWSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class LevelViewState : public GameState
{
public:
	LevelViewState() {};
	LevelViewState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\levelview.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\logicview.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &LevelViewState::LogicViewCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool LevelViewState::Update();
	bool LevelViewState::Draw();
	bool LogicViewCallback();

private:
	oglTexture2D* img;
	// add private stuff here

};

#endif