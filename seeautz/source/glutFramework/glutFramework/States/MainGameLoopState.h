#ifndef MAINGAMELOOPSTATE_H
#define MAINGAMELOOPSTATE_H

#include ".\..\GameState.h" 

class MainGameLoopState : public GameState
{
public:
	MainGameLoopState() {};
	MainGameLoopState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool MainGameLoopState::Update();
	bool MainGameLoopState::Draw();

private:

	// add private stuff here

};

#endif