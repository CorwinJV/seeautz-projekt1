#ifndef GAMESTATE_H
#define GAMESTATE_H

enum State { 
				Active, // updating
				Hidden, // Not drawing
};

class GameState
{
private:
	// Current State
	State currentStatus;

	bool displayCollisionDebug;
    int screenHeight;
    int screenWidth;

public:
	GameState();
	~GameState();
	
	bool initialize();
	bool Update();
    bool Draw();
};

#endif