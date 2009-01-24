#ifndef PROFILEMGRSTATE_H
#define PROFILEMGRSTATE_H

#include ".\..\GameState.h" 

class ProfileMgrState : public GameState
{
public:
	ProfileMgrState() {};
	ProfileMgrState(GameStateManager &Parent, int newID) : GameState(Parent, newID)
	{
	}

	bool ProfileMgrState::Update();
	bool ProfileMgrState::Draw();

private:
	// add private stuff here

};

#endif