#include "StopLoopState.h"
#include "PreGameState.h"

bool StopLoopState::Update()
{
	return true;
}

bool StopLoopState::Draw()
{
	return false;
}

bool StopLoopState::PreGameCallback()
{
	GSM->addGameState<PreGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}