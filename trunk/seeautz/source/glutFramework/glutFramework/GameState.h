#ifndef GAMESTATE_H
#define GAMESTATE_H

enum State { 
				Active, // updating
				Hidden, // Not drawing
};

class GameState
{
protected:
	// Current State
	State currentStatus;

	bool displayCollisionDebug;
    int screenHeight;
    int screenWidth;

public:
	GameState();
	~GameState();
	
	virtual bool initialize();
	virtual bool Update();
    virtual bool Draw();
};

#endif