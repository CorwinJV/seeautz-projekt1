#include "LevelViewState.h"
#include "LogicViewState.h"

bool LevelViewState::Update()
{
	return true;
}

bool LevelViewState::Draw()
{
	return false;
}

bool LevelViewState::LogicViewCallback()
{
	GSM->addGameState<LogicViewState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}