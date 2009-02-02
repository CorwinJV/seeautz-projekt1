#ifndef POSTGAMESTATE_H
#define POSTGAMESTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"

class PostGameState : public GameState
{
public:
	PostGameState() {};
	PostGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("..\\Content\\statescreens\\postgame.png", 1024, 120);
		img->mY = 618;
	
		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("..\\Content\\buttons\\newlevel.png", "button1down.png", "button1over.png", CreateFunctionPointer0R(this, &PostGameState::NewLevelCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool PostGameState::Update();
	bool PostGameState::Draw();
	bool NewLevelCallback();

private:
	oglTexture2D* img;
	// add private stuff here

};

#endif
