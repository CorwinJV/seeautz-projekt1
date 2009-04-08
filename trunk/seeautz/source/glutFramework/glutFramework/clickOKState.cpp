#include "clickOKState.h" 
#include "GameStateManager.h"

bool clickOKState::Update()
{
	selected = false;
	deleted = false;
	created = false;
	noProfile = false;
	saved = false;
	reprogram = false;
	GSM->setAllButTopPassive();

	int check = GameVars->getPMStatus();
	switch(check)
	{
	case 0:
		selected = true;
		break;
	case 1:
		deleted = true;
		break;
	case 2:
		created = true;
		break;
	case 3:
		noProfile = true;
		break;
	case 4:
		saved = true;
		break;
	case 5:
		reprogram = true;
	default:
		break;
	}

	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool clickOKState::Draw()
{
	if((!saved) && (!reprogram))
	{
		clearBackground();
		logoImage->drawImage();
	}

	if(myMenu != NULL)
		myMenu->Draw();

	glColor3ub(0, 0, 0);

	int offX = 300;
	int offY = 250;

	int offInc = 30;
	int offAmt = 0;

	if(created)
	{
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been created.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to begin game.");
		offAmt++;
	}
	if(selected)
	{
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been selected."); 
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to select level.");
		offAmt++;
	}
	if(deleted)
	{
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been deleted.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to continue.");
		offAmt++;
	}
	if(noProfile)
	{
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "There are no existing profiles.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "to load click OK to continue.");
		offAmt++;
	}
	if(saved)
	{
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been saved.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to continue.");
		offAmt++;
	}
	if(reprogram)
	{
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "You have hit a reprogrammable");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "square. Your instruction list");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "has been cleared, and all of your");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "memory has been replenished");
		offAmt++;
	}

	GameVars->fontArial24.drawText(offX, 460, "Click \"Help\" to learn more");
	offAmt++;
	GameVars->fontArial24.drawText(offX, 490, "about the game.");
	offAmt++;
	return true;
}

bool clickOKState::clickOKCallback()
{
	/*if(selected)
	{
		GSM->addGameState<LevelSelectState>();
		selected = false;
	}*/
	//else if(noProfile)
	//{
	//	//GSM->addGameState<MainMenuState>();
	//	noProfile = false;
	//}
	//else if(created)
	//{
	//	//GSM->addGameState<playGame>();
	//	created = false;
	//}
	this->setStatus(DeleteMe);
	created = false;
	reprogram = false;
	saved = false;
	deleted = false;
	noProfile = false;
	selected = false;
	GameVars->setPMStatus(-1);

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

bool clickOKState::helpCallback()
{
	GSM->addGameState<helpScreenState>();

	return true;
}