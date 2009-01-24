#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "MenuSystem.h"

class GameStateManager;
class GameState
{
protected:
	// Current State
	State currentStatus;
	int stateID;

	bool displayCollisionDebug;
    int screenHeight;
    int screenWidth;
	
	GameStateManager *GSM;
	MenuSys *myMenu;

public:
	GameState();
	GameState(GameStateManager &Parent, int newID);
	~GameState();
	
	virtual bool setStatus(State newStatus);
	virtual State getStatus();
	virtual int getID();
	virtual bool initialize();
	virtual bool Update();
    virtual bool Draw();
};

#endif