#include "LevelViewState.h"
#include "LogicViewState.h"

bool LevelViewState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool LevelViewState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool LevelViewState::LogicViewCallback()
{
	GSM->addGameState<LogicViewState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void LevelViewState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void LevelViewState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}