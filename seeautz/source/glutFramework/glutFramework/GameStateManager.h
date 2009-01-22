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
<<<<<<< .mine
	int stateCount;	// id numbers
	int numStates;	// current number of states
=======
    //*** List<GameState2D> stateList;
	int stateCount;	// id numbers
	int numStates;	// current number of states
>>>>>>> .r39

public:

	GameStateManager();//(Game game)        : base(game)
    bool Initialize();

	template <class T>
	inline bool addGameState(State newState = Active)
	{

		stateCount++;
		numStates++;
<<<<<<< .mine

		std::cout << "GSM:addGAmeState - Adding new Gamestate " << std::endl;
=======

		std::cout << "GSM:addGAmeState - Adding new Gamestate ";
>>>>>>> .r39
		T* newGS = new T(*this, stateCount);
		newGS->setStatus(newState);
		stateList.push_back(newGS);
		return true;
		// if something bad happens, return false
	}

	int getStateCount();
	int getNumStates();
    bool removeGameStateAt(int index);
	bool removeGameStateID(int nukeID);
    bool removeTopGameState();//(GameState game)
	bool setState(int stateID, State newStatus);
    bool Update();//(GameTime gameTime)
    bool Draw();//(GameTime gameTime)
	bool setList(vector<GameState*> newlist);
};

#endif