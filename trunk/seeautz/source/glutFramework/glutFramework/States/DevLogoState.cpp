#include "DevLogoState.h"
#include ".\..\GameStateManager.h"

#include "MainMenuState.h"
#include "..\tempstate.h"
#include "..\oglGameVars.h"



bool DevLogoState::Update()
{
	/*int fadeinoutlength = 100;
	int pauselength = 100;
	int inbetween = 50;*/

	// logo 1
	int devlogofadeinstart = 0;		int devlogofadeinend = 100;
	int devlogofadeoutstart = 200;	int devlogofadeoutend = 300;

	// logo 2
	int logo2fadeinstart = 350;		int logo2fadeinend = 450;
	int logo2fadeoutstart = 550;	int logo2fadeoutend = 650;

	// logo 3
	int logo3fadeinstart = 700;		int logo3fadeinend = 800;
	int logo3fadeoutstart = 900;	int logo3fadeoutend = 10;

	double fadeinamt =  ((double)(devlogofadeinend  - devlogofadeinstart ) / 100) / 100;
	double fadeoutamt = ((double)(devlogofadeoutend - devlogofadeoutstart) / 100) / 100;

	timer++;

	// logo 1

	if(timer < devlogofadeinend)									 {		opacity += fadeinamt;	}
	if((timer > devlogofadeinend) && (timer < devlogofadeoutstart))	 {		opacity = 1.0;	        }
	if((timer > devlogofadeoutstart) && (timer < devlogofadeoutend)) {		opacity -= fadeoutamt;	}

	// load logo 2
	if(timer == logo2fadeinstart)
	{
		delete logo;
		logo = new oglTexture2D();
		if(logo != NULL)
			logo->loadImage("logopresents.png", 1024, 768);
		opacity = 0;
		fadeinamt =  ((double)(logo2fadeinend  - logo2fadeinstart ) / 100) / 100;
		fadeoutamt = ((double)(logo2fadeoutend - logo2fadeoutstart) / 100) / 100;
	}

	if((timer < logo2fadeinend) && (timer > logo2fadeinstart))	 {		opacity += fadeinamt;	}
	if((timer > logo2fadeinend) && (timer < logo2fadeoutstart))	 {		opacity = 1.0;	        }
	if((timer > logo2fadeoutstart) && (timer < logo2fadeoutend)) {		opacity -= fadeoutamt;	}

	// load logo 3
	if(timer == logo3fadeinstart)
	{
		delete logo;
		logo = new oglTexture2D();
		if(logo != NULL)
			logo->loadImage("logoprojekt1.png", 1024, 768);
		opacity = 0;
		fadeinamt =  ((double)(logo3fadeinend  - logo3fadeinstart ) / 100) / 100;
		fadeoutamt = ((double)(logo3fadeoutend - logo3fadeoutstart) / 100) / 100;
	}

	if((timer < logo3fadeinend) && (timer > logo3fadeinstart))	 {		opacity += fadeinamt;	}
	if((timer > logo3fadeinend) && (timer < logo3fadeoutstart))	 {		opacity = 1.0;	        }
	if((timer > logo3fadeoutstart) && (timer < logo3fadeoutend)) {		opacity -= fadeoutamt;	}

	if(timer > logo3fadeoutend+25)
	{
		GSM->addGameState<MainMenuState>();
		this->setStatus(DeleteMe);
	}
	return true;
}

bool DevLogoState::Draw()
{
	//logo->drawImage();
	logo->drawImageFaded(opacity);

	//std::cout<< "I drew something at " << timer << endl;
	return false;
}

DevLogoState::~DevLogoState()
{
	delete logo;
}
