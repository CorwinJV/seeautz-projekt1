#ifndef LEVELVIEWSTATE_H
#define LEVELVIEWSTATE_H

#include ".\..\GameState.h" 

class LevelViewState : public GameState
{
public:
	LevelViewState() {};
	LevelViewState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool LevelViewState::Update();
	bool LevelViewState::Draw();

private:
	// add private stuff here

};

#endif