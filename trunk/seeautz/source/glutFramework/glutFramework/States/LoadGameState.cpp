#include "LoadGameState.h" 
#include "PreGameState.h"
#include "..\GameStateManager.h"

bool LoadGameState::Update()
{
	return true;
}

bool LoadGameState::Draw()
{
	return false;
}

bool LoadGameState::PreGameCallback()
{
	GSM->addGameState<PreGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 255, 0);

	return true;
} 

bool LoadGameState::tutorialCallback()
{
	GSM->addGameState<tutorialMap1>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
} 