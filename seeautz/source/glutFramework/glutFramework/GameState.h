#ifndef GAMESTATE_H
#define GAMESTATE_H

enum State { 
				Active,		// updating	and drawing
				Passive,	// drawing and not updating
				Hidden,		// not updating and not drawing
				DeleteMe,	// flagged for removal
};

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