#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include ".\..\GameState.h" 

class MainMenuState : public GameState
{
public:
	MainMenuState() {};
	MainMenuState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool MainMenuState::Update();
	bool MainMenuState::Draw();

private:

	// add private stuff here
	
};

#endif

