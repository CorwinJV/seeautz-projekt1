#include "NewLevelState.h"
#include "StopLoopState.h"

bool NewLevelState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool NewLevelState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool NewLevelState::StopLoopCallback()
{
	GSM->addGameState<StopLoopState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void NewLevelState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void NewLevelState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}