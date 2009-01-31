#include "SucceedState.h" 
#include "PostGameState.h"

bool SucceedState::Update()
{
	return true;
}

bool SucceedState::Draw()
{
	return false;
}

bool SucceedState::PostGameCallback()
{
	GSM->addGameState<PostGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}