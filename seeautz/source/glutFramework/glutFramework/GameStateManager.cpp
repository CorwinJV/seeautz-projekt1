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

	// my VERY horribly horribly bad way of fixing the pointer issue with the vectors resizing themselves
	GameState* tempGS = new GameState(*this, stateCount);

	for(int x = 0; x < 500; x++)
	{
		stateList.push_back(tempGS);
	}

	stateList.erase(stateList.begin(), stateList.end());
	delete tempGS;

	
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

	delete (*itr);
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
			delete (*itr);
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

	// update statelist
	for (; itr != stateList.end(); itr++)
    {
<<<<<<< .mine
		std::cout << "GSM - State ID : " << (*itr)->getID() << " status is ";
		switch((*itr)->getStatus())
		{
		case 0:			std::cout << " Active ";			break;	
		case 1:			std::cout << " Passive ";			break;	
		case 2:			std::cout << " Hidden ";			break;
		case 3:			std::cout << " DeleteMe ";			break;
		default:		std::cout << " INVALID STATE ";		break;
		}			
		std::cout << endl;
=======
		std::cout << "GSM - State ID : " << (*itr)->getID() << " status is ";
		switch((*itr)->getStatus())
		{
		case 0:
			std::cout << " Active ";
			break;
		case 1:
			std::cout << " Passive ";
			break;
		case 2:
			std::cout << " Hidden ";
			break;
		case 3:
			std::cout << " DeleteMe ";
			break;
		default:
			std::cout << " INVALID STATE ";
			break;
		}			
		std::cout << endl;
>>>>>>> .r39

		if((*itr)->getStatus() == Active)
		{
			(*itr)->Update();
			std::cout << "GSM - State ID : " << (*itr)->getID() << " has been updated" << endl;

		}
    }

<<<<<<< .mine
	itr = stateList.end();
	itr--;

	// delete any states flagged for deletion
	for (; itr != stateList.begin(); itr--)
    {
		if((*itr)->getStatus() == DeleteMe)
		{
			std::cout << "GSM - State ID : " << (*itr)->getID() << " is about to be deleted" << endl;
			delete (*itr);
			stateList.erase(itr);
			numStates--;
			break;
		}
    }

=======
	itr = stateList.end();
		itr--;

	// delete any states flagged for deletion
	for (; itr != stateList.begin(); itr--)
    {
		if((*itr)->getStatus() == DeleteMe)
		{
			std::cout << "GSM - State ID : " << (*itr)->getID() << " is about to be deleted" << endl;
			delete (*itr);
			stateList.erase(itr);
			numStates--;
			break;
		}
    }

>>>>>>> .r39
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
			std::cout << "GSM - State ID : " << (*itr)->getID() << " has been drawn" << endl;
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

bool GameStateManager::setList(vector<GameState*> newlist)
{
	// delete stateList; // ?? not sure if this is needed or not
	stateList = newlist;
	return true;
}