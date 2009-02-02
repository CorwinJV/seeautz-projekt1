#ifndef NEWLEVELSTATE_H
#define NEWLEVELSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class NewLevelState : public GameState
{
public:
	NewLevelState() {};
	NewLevelState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\newlevel.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\stoploop.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &NewLevelState::StopLoopCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool NewLevelState::Update();
	bool NewLevelState::Draw();
	bool StopLoopCallback();

private:
	oglTexture2D* img;
	// add private stuff here

};


#endif