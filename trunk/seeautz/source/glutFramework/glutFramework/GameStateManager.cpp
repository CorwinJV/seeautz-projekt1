#include "GameStateManager.h"
#include <iostream>

GameStateManager::GameStateManager()//(Game game)        : base(game)
{
	Initialize();
}

bool GameStateManager::Initialize()
{
    // TODO: Add your initialization code here
	stateCount = -1;
	numStates = 0;

	return true;
	// if something bad happens, return false
}

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
	numStates--;

	return true;
	// if something bad happens, return false
}

bool GameStateManager::removeGameStateID(int nukeID)
{
	if (nukeID < 0) // make sure we have an index that's at least position 0
		return false;

	// erase the item at this index
	vector<GameState*>::iterator itr = stateList.begin();
	for (; itr != stateList.end(); itr++)
    {
		if((*itr)->getID() == nukeID)
		{
			stateList.erase(itr);
			numStates--;
			return true; // item is found and erased
		}
    }

	return false; // item wasn't found
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
		//std::cout << "State ID : " << (*itr)->getID() << " status is " << (*itr)->getStatus() << endl;

		if((*itr)->getStatus() == Active)
		{
			(*itr)->Update();
			//std::cout << "State ID : " << (*itr)->getID() << " has been updated" << endl;

		}
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
		if((*itr)->getStatus() <= Passive)
		{
			(*itr)->Draw();
			//std::cout << "State ID : " << (*itr)->getID() << " has been drawn" << endl;
		}
    }

	return true;
	// if something bad happens, return false
}

bool GameStateManager::setState(int stateID, State newStatus = Active)
{
	if (stateID < 0) // make sure we have an index that's at least position 0
		return false;

	// erase the item at this index
	vector<GameState*>::iterator itr = stateList.begin();
	for (; itr != stateList.end(); itr++)
    {
		if((*itr)->getID() == stateID)
		{
			(*itr)->setStatus(newStatus);
			return true; // item is found and erased
		}
    }
	return false; // item wasn't found
}

int GameStateManager::getStateCount()
{
	return stateCount;
}

int GameStateManager::getNumStates()
{
	return numStates;
}
