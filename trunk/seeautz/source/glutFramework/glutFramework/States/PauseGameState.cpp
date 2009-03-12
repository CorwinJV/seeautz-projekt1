#include "PauseGameState.h"

bool PauseGameState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	GSM->setAllButTopPassive();
	return true;
}

bool PauseGameState::Draw()
{

	if(myMenu != NULL)
		myMenu->Draw();
	
	return false;
}

bool PauseGameState::SaveCallback()
{
	GSM->addGameState<SaveGameState>();
	return true;
}

bool PauseGameState::SaveQuitCallback()
{
	this->setStatus(DeleteMe);
	GSM->addGameState<SaveGameState>();
	exit(0);

	return true;
}
	
bool PauseGameState::QuitCallback()
{
	this->setStatus(DeleteMe);
	exit(0);

	return true;
}
	
bool PauseGameState::LevelSelectCallback()
{
	GSM->addGameState<LevelSelectState>();
	this->setStatus(DeleteMe);

	return true;
}
	
bool PauseGameState::MainMenuCallback()
{
	GSM->returnToMainMenu();

	return true;
}
	
bool PauseGameState::ReturnToGameCallback()
{
	this->setStatus(DeleteMe);

	return true;
}

void PauseGameState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void PauseGameState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}