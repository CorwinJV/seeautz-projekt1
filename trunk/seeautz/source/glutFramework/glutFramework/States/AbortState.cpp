#include "AbortState.h"
#include "StopLoopState.h"

bool AbortState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool AbortState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool AbortState::StopLoopCallback()
{
	GSM->addGameState<StopLoopState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 0, 0);

	return true;
}

void AbortState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void AbortState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}