#include "LoadGameState.h" 
#include "PreGameState.h"
#include "..\GameStateManager.h"

bool LoadGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool LoadGameState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool LoadGameState::PreGameCallback()
{
	GSM->addGameState<PreGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 255, 0);

	return true;
} 

bool LoadGameState::tutorialCallback()
{
	GSM->addGameState<tutorialMap1>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
} 

void LoadGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void LoadGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}