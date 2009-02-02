#include "StopLoopState.h"
#include "PreGameState.h"

bool StopLoopState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool StopLoopState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool StopLoopState::PreGameCallback()
{
	GSM->addGameState<PreGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void StopLoopState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void StopLoopState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}