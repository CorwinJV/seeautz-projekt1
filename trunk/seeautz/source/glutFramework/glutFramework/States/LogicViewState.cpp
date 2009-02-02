#include "LogicViewState.h"
#include "ExecutionModeState.h"

bool LogicViewState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool LogicViewState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool LogicViewState::ExecutionModeCallback()
{
	GSM->addGameState<ExecutionModeState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void LogicViewState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void LogicViewState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}