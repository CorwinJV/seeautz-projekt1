#include "MainGameLoopState.h"
#include "LevelViewState.h"


bool MainGameLoopState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool MainGameLoopState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool MainGameLoopState::LevelViewCallback()
{
	GSM->addGameState<LevelViewState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void MainGameLoopState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void MainGameLoopState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}