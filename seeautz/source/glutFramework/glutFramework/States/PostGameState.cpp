#include "PostGameState.h"
#include "NewLevelState.h"

bool PostGameState::Update()
{
	return true;
}

bool PostGameState::Draw()
{
	return false;
}

bool PostGameState::NewLevelCallback()
{
	GSM->addGameState<NewLevelState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}