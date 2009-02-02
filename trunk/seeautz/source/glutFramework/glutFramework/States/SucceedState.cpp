#include "SucceedState.h" 
#include "PostGameState.h"

bool SucceedState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool SucceedState::Draw()
{
	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();
	return false;
}

bool SucceedState::PostGameCallback()
{
	GSM->addGameState<PostGameState>();
	this->setStatus(DeleteMe);
	glClearColor(255, 0, 255, 0);

	return true;
}

void SucceedState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void SucceedState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}