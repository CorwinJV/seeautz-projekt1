// Added 1/21/09

#ifndef ABORTSTATE_H
#define ABORTSTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"



class AbortState : public GameState
{
public:
	AbortState() {};
	AbortState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\abortfail.png", 1024, 120);
		img->mY = 618;
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\stoploop.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &AbortState::StopLoopCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool AbortState::Update();
	bool AbortState::Draw();
	bool StopLoopCallback();

private:
	oglTexture2D* img;
	// add private stuff here

};



#endif