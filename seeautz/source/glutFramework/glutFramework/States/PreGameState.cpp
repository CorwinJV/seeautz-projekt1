#include "PreGameState.h"
#include "MainGameLoopState.h"

bool PreGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool PreGameState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool PreGameState::MainGameCallback()
{
	GSM->addGameState<MainGameLoopState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}
 
void PreGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void PreGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}