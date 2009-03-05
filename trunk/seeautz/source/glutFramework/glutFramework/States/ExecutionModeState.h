#ifndef EXECUTIONMODESTATE_H
#define EXECUTIONMODESTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class ExecutionModeState : public GameState
{
public:
	ExecutionModeState() {};
	ExecutionModeState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\executionmode.png", 1024, 120);
		img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\succeed.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &ExecutionModeState::SaveGameCallback));
		myMenu->addButton("..\\Content\\buttons\\abortfail.png", "button2down.png", "button2over.png", CreateFunctionPointer0R(this, &ExecutionModeState::AbortCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool ExecutionModeState::Update();
	bool ExecutionModeState::Draw();
	bool SaveGameCallback();
	bool AbortCallback();

private:
	oglTexture2D* img;
	// add private stuff here
};

#endif