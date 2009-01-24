// Added 1/21/09

#ifndef ABORTSTATE_H
#define ABORTSTATE_H

#include ".\..\GameState.h" 
class AbortState : public GameState
{
public:
	AbortState() {};
	AbortState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool AbortState::Update();
	bool AbortState::Draw();

private:
	// add private stuff here

};



#endif