#include "NewLevelState.h"
#include "StopLoopState.h"

bool NewLevelState::Update()
{
	return true;
}

bool NewLevelState::Draw()
{
	return false;
}

bool NewLevelState::StopLoopCallback()
{
	GSM->addGameState<StopLoopState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}