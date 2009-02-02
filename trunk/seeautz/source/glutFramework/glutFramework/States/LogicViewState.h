#ifndef LOGICVIEWSTATE_H
#define LOGICVIEWSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class LogicViewState : public GameState
{
public:
	LogicViewState() {};
	LogicViewState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\logicview.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\executionmode.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &LogicViewState::ExecutionModeCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool LogicViewState::Update();
	bool LogicViewState::Draw();
	bool ExecutionModeCallback();

private:
	oglTexture2D* img;
	// add private stuuf here

};
#endif