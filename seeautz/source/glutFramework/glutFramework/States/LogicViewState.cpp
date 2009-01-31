#include "LogicViewState.h"
#include "ExecutionModeState.h"

bool LogicViewState::Update()
{
	return true;
}

bool LogicViewState::Draw()
{
	return false;
}

bool LogicViewState::ExecutionModeCallback()
{
	GSM->addGameState<ExecutionModeState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}