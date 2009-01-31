#include "ExecutionModeState.h"
#include "SucceedState.h"
#include "AbortState.h"

bool ExecutionModeState::Update()
{
	return true;
}

bool ExecutionModeState::Draw()
{
	return false;
}

bool ExecutionModeState::SucceedCallback()
{
	GSM->addGameState<SucceedState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

bool ExecutionModeState::AbortCallback()
{
	GSM->addGameState<AbortState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}