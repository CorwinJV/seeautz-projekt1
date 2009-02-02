#include "PostGameState.h"
#include "NewLevelState.h"

bool PostGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool PostGameState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool PostGameState::NewLevelCallback()
{
	GSM->addGameState<NewLevelState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void PostGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void PostGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}