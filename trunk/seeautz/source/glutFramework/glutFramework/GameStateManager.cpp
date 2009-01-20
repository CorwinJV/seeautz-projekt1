#include "GameStateManager.h"

GameStateManager::GameStateManager()//(Game game)        : base(game)
{
    //stateList = new List<GameState2D>();
}

bool GameStateManager::Initialize()
{
    // TODO: Add your initialization code here

    //base.Initialize();

	return true;
	// if something bad happens, return false
}

/// <summary>
/// Adds a GameState2D to be managed.
/// </summary>
bool GameStateManager::addGameState()
{
    //GameState2D newGS = new GameState2D();
    //stateList.Add(newGS);

	return true;
	// if something bad happens, return false
}

/// <summary>
/// Removes a gamestate by index.
/// </summary>
/// <param name="index">Position in list to remove at</param>
bool GameStateManager::removeGameStateAt(int index)
{
    //stateList.RemoveAt(index);

	return true;
	// if something bad happens, return false
}

/// <summary>
/// Removes a gamestate.
/// </summary>
/// <param name="GameState2D">GameState to remove</param>
bool GameStateManager::removeGameState()//(GameState game)
{
    //stateList.Remove(game);

	return true;
	// if something bad happens, return false
}


/// <summary>
/// Allows the game component to update itself.
/// </summary>
/// <param name="gameTime">Provides a snapshot of timing values.</param>
bool GameStateManager::Update()//(GameTime gameTime)
{
    // TODO: Add your update code here
    //for (int i = 0; i < stateList.Count; i++)
    {
      //  stateList[i].Update(gameTime);
    }

    //base.Update(gameTime);

	return true;
	// if something bad happens, return false
}

bool GameStateManager::Draw()//(GameTime gameTime)
{
    //for (int i = 0; i < stateList.Count; i++)
    {
      //  stateList[i].Draw(gameTime);
    }

    //base.Draw(gameTime);

	return true;
	// if something bad happens, return false
}