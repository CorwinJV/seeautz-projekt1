#include "AbortState.h"
#include "StopLoopState.h"

bool AbortState::Update()
{
	return true;
}

bool AbortState::Draw()
{
	return false;
}

bool AbortState::StopLoopCallback()
{
	GSM->addGameState<StopLoopState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}