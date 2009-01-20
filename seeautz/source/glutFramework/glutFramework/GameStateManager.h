#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "GameState.h"
using namespace std;

class GameStateManager
{

private:
	// Members
	vector<GameState*> stateList;
    //*** List<GameState2D> stateList;


public:

	GameStateManager();//(Game game)        : base(game)
    bool Initialize();

	template <class T>
	inline bool addGameState()
	{
		T* newGS = new T();
		stateList.push_back(newGS);
		return true;
		// if something bad happens, return false
	}

    bool removeGameStateAt(int index);
    bool removeTopGameState();//(GameState game)
    bool Update();//(GameTime gameTime)
    bool Draw();//(GameTime gameTime)
};

#endif