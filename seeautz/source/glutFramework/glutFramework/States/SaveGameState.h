#ifndef SAVEGAMESTATE_H
#define SAVEGAMESTATE_H

#include ".\..\GameState.h" 
#include "..\GameStateManager.h"
#include ".\..\oglTexture2D.h"
#include ".\..\oglGameVars.h"

class SaveGameState : public GameState
{
public:
	SaveGameState() {};
	SaveGameState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
		img = new oglTexture2D();
		if(img != NULL)
			img->loadImage("statescreens\\succeed.png", 1024, 120);
		img->mY = 618;

		myMenu = new MenuSys(250, 50, "blankmenu.png", Auto);
		myMenu->addButton("buttons\\postgame.png", "succeed.png", "button1over.png", CreateFunctionPointer0R(this, &SaveGameState::PauseGameCallback));
		Update();
	}

	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	bool SaveGameState::Update();
	bool SaveGameState::Draw();
	bool PauseGameCallback();
	bool SaveGameState::SavePlayerGame();

private:
	oglTexture2D* img;
	// add private stuff here
};

#endif