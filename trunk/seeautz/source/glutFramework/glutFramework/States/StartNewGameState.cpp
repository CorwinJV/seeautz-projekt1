#include "StartNewGameState.h"
#include "..\GameStateManager.h"
#include "PreGameState.h"

bool StartNewGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool StartNewGameState::Draw()
{
	if(img != NULL)
		img->drawPixMap();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

void StartNewGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void StartNewGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}

bool StartNewGameState::button5Callback()
{
	GSM->addGameState<PreGameState>();
	this->setStatus(DeleteMe);
	glClearColor(0, 255, 255, 0);
#ifdef buttonWork
	std::cout << " BUTTON 5 CALLBACK WORKING ";
#endif
	return true;
} 