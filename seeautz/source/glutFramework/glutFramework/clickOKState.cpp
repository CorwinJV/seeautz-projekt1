#include "clickOKState.h" 
#include "GameStateManager.h"

bool clickOKState::Update()
{
	if(myMenu != NULL)
		myMenu->Update();
	return true;
}

bool clickOKState::Draw()
{
	clearBackground();
	logoImage->drawImage();

	if(img != NULL)
		img->drawImage();

	if(myMenu != NULL)
		myMenu->Draw();

	glColor3ub(0, 0, 0);

	if(created)
		GameVars->fontArial24.drawText(250, 300, "Profile has been created, click OK ");
	else if(selected)
		GameVars->fontArial24.drawText(250, 300, "Profile has been selected, click OK ");
	else if(deleted)
		GameVars->fontArial24.drawText(250, 300, "Profile has been deleted, click OK ");

	return true;
}

bool clickOKState::clickOKCallback()
{
	this->setStatus(DeleteMe);
	return true;
}

void clickOKState::processMouse(int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouse(x, y);
}

void clickOKState::processMouseClick(int button, int state, int x, int y)
{
	if(myMenu != NULL)
		myMenu->processMouseClick(button, state, x, y);
}