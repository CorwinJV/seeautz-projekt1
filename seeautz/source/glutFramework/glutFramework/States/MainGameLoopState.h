#ifndef MAINGAMELOOPSTATE_H
#define MAINGAMELOOPSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class MainGameLoopState : public GameState
{
public:
	MainGameLoopState() {};
	MainGameLoopState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\maingameloop.png", 1024, 120);
		img->mY = 618;

	
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\levelview.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &MainGameLoopState::LevelSelectCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool MainGameLoopState::Update();
	bool MainGameLoopState::Draw();
	bool LevelSelectCallback();

private:
	oglTexture2D* img;
	// add private stuff here

};

#endif