#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "GameState.h"
using namespace std;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

private:
	vector<GameState*> mStateList;

};

#endif