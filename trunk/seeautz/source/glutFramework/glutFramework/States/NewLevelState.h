#ifndef NEWLEVELSTATE_H
#define NEWLEVELSTATE_H

#include ".\..\GameState.h" 

class NewLevelState : public GameState
{
public:
	NewLevelState() {};
	NewLevelState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool NewLevelState::Update();
	bool NewLevelState::Draw();

private:
	// add private stuff here

};


#endif