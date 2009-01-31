#include "PreGameState.h"
#include "MainGameLoopState.h"

bool PreGameState::Update()
{
	return true;
}

bool PreGameState::Draw()
{
	return false;
}

bool PreGameState::MainGameCallback()
{
	GSM->addGameState<MainGameLoopState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}
 