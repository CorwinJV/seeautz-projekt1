#include "MainGameLoopState.h"
#include "LevelViewState.h"


bool MainGameLoopState::Update()
{
	return true;
}

bool MainGameLoopState::Draw()
{
	return false;
}

bool MainGameLoopState::LevelViewCallback()
{
	GSM->addGameState<LevelViewState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}