#include "ExecutionModeState.h"
#include "SaveGameState.h"
#include "AbortState.h"

bool ExecutionModeState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool ExecutionModeState::Draw()
{
	if(img != NULL)
		//img->drawPixMap();
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool ExecutionModeState::SaveGameCallback()
{
	GSM->addGameState<SaveGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 0, 0);

	return true;
}

bool ExecutionModeState::AbortCallback()
{
	GSM->addGameState<AbortState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 0, 0, 0);

	return true;
}

void ExecutionModeState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void ExecutionModeState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}