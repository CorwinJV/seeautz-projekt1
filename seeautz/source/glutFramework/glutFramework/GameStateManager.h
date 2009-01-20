#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "GameState.h"
using namespace std;

class GameStateManager
{

private:
	// Members
	vector<GameState*> mStateList;
    //*** List<GameState2D> stateList;


public:

	GameStateManager();//(Game game)        : base(game)
    bool Initialize();
    bool addGameState();
    bool removeGameStateAt(int index);
    bool removeGameState();//(GameState game)
    bool Update();//(GameTime gameTime)
    bool Draw();//(GameTime gameTime)
};

#endif