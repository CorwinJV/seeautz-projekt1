#include "clickOKState.h" 
#include "GameStateManager.h"

bool clickOKState::Update()
{
	
	GSM->setAllButTopPassive();

	check = (clickOKenum)GameVars->getPMStatus();

	if(myMenu != NULL)
		myMenu->Update();

	return true;
}

bool clickOKState::Draw()
{
	if((check != saved) && (check != reprogram))
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

	switch(check)
	{
	case created:
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been created.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to begin game.");
		offAmt++;
		break;
	case selected:
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been selected."); 
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to select level.");
		offAmt++;
		break;
	case deleted:
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been deleted.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to continue.");
		offAmt++;
		break;
	case noProfile:
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "There are no existing profiles.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "to load click OK to continue.");
		offAmt++;
		break;
	case saved:
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Profile has been saved.");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "Click OK to continue.");
		offAmt++;
		break;
	case reprogram:
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "You have hit a reprogrammable");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "square. Your instruction list");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "has been cleared, and all of your");
		offAmt++;
		GameVars->fontArial24.drawText(offX, offY + offAmt*offInc, "memory has been replenished");
		offAmt++;
		break;
	default:
		break;
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
	}
	else if(noProfile)
	{
		GSM->addGameState<MainMenuState>();
	}
	else if(created)
	{
		GSM->addGameState<playGame>();
	}*/
	this->setStatus(DeleteMe);
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