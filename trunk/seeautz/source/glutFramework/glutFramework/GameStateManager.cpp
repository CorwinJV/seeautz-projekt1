#include "GameStateManager.h"

GameStateManager::GameStateManager()//(Game game)        : base(game)
{
	Initialize();
}

bool GameStateManager::Initialize()
{
    // TODO: Add your initialization code here

	return true;
	// if something bad happens, return false
}

template <class T>
bool GameStateManager::addGameState()
{
	T* newGS = new T();
	stateList.push_back(newGS)
	return true;
	// if something bad happens, return false
}

;

bool GameStateManager::removeGameStateAt(int index)
{
	if (index < 0) // make sure we have an index that's at least position 0
		return false;

	// erase the item at this index
	vector<GameState*>::iterator itr = stateList.begin();
	for(int i = 0; i < index; i++)
	{
		itr++;
		if(itr >= stateList.end()) // lets also make sure that we're working within the confines of the vector
		{
			return false;
		}
	}

	stateList.erase(itr);

	return true;
	// if something bad happens, return false
}


bool GameStateManager::removeTopGameState()
{
	stateList.pop_back();
	return true;
	// if something bad happens, return false
}


bool GameStateManager::Update()
{
    // TODO: Add your update code here
	vector<GameState*>::iterator itr = stateList.begin();

	for (; itr != stateList.end(); itr++)
    {
		(*itr)->Update();
    }

	return true;
	// if something bad happens, return false
}

bool GameStateManager::Draw()//(GameTime gameTime)
{
    // TODO: Add your update code here
	vector<GameState*>::iterator itr = stateList.begin();

	for (; itr != stateList.end(); itr++)
    {
		(*itr)->Draw();
    }

	return true;
	// if something bad happens, return false
}