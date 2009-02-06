#include "DevLogoState.h"
#include ".\..\GameStateManager.h"

#include "MainMenuState.h"
#include "..\tempstate.h"
#include "..\oglGameVars.h"


bool DevLogoState::Update()
{
	// start/end times are given as seconds duration based on start of the state
	// logo 1
	int devlogofadeinstart = 0;		int devlogofadeinend = 1;
	int devlogofadeoutstart = 2;	int devlogofadeoutend = 3;

	// logo 2
	int logo2fadeinstart = 3.5;		int logo2fadeinend = 4.5;
	int logo2fadeoutstart = 5.5;	int logo2fadeoutend = 6.5;

	// logo 3
	int logo3fadeinstart = 7;		int logo3fadeinend = 8;
	int logo3fadeoutstart = 9;	int logo3fadeoutend = 10;

	// per tick shall be
	// start time * 1000 = start
	// end time * 1000 = end
	// end - start = total # of ticks we will need
	// 1 / total ticks = fade amount per tick

	double fadeinamt =  ((devlogofadeinend*1000)  - (devlogofadeinstart * 1000)) * 0.00001;
	double fadeoutamt = ((devlogofadeoutend*1000) - (devlogofadeoutstart* 1000)) * 0.00001;

	// logo 1

	// at any given point... our fade in amount is...
	// current time - start time * fadeinamt

	timer = clock() - startTime;

	if(timer < (devlogofadeinend*1000))									 
	{		
		opacity = (clock() - (devlogofadeinstart*1000)) * fadeinamt * 0.1;
	}
	if((timer > (devlogofadeinend*1000)) && (timer < (devlogofadeoutstart*1000)))	 {		opacity = 1.0;	        }


	// since we're going backwards, we do 1 - our old formula
	if( (timer > (devlogofadeoutstart*1000) && (timer < (devlogofadeoutend*1000))))
	{		
		opacity = 1 - (clock() - (devlogofadeoutstart*1000)) * fadeoutamt * 0.1;
	}

	//// load logo 2
	//if(timer == logo2fadeinstart)
	//{
	//	delete logo;
	//	logo = new oglTexture2D();
	//	if(logo != NULL)
	//		logo->loadImage("logopresents.png", 1024, 768);
	//	opacity = 0;
	//	fadeinamt =  ((double)(logo2fadeinend  - logo2fadeinstart ) / 100) / 100;
	//	fadeoutamt = ((double)(logo2fadeoutend - logo2fadeoutstart) / 100) / 100;
	//}

	//if((timer < logo2fadeinend) && (timer > logo2fadeinstart))	 {		opacity += fadeinamt;	}
	//if((timer > logo2fadeinend) && (timer < logo2fadeoutstart))	 {		opacity = 1.0;	        }
	//if((timer > logo2fadeoutstart) && (timer < logo2fadeoutend)) {		opacity -= fadeoutamt;	}

	//// load logo 3
	//if(timer == logo3fadeinstart)
	//{
	//	delete logo;
	//	logo = new oglTexture2D();
	//	if(logo != NULL)
	//		logo->loadImage("logoprojekt1.png", 1024, 768);
	//	opacity = 0;
	//	fadeinamt =  ((double)(logo3fadeinend  - logo3fadeinstart ) / 100) / 100;
	//	fadeoutamt = ((double)(logo3fadeoutend - logo3fadeoutstart) / 100) / 100;
	//}

	//if((timer < logo3fadeinend) && (timer > logo3fadeinstart))	 {		opacity += fadeinamt;	}
	//if((timer > logo3fadeinend) && (timer < logo3fadeoutstart))	 {		opacity = 1.0;	        }
	//if((timer > logo3fadeoutstart) && (timer < logo3fadeoutend)) {		opacity -= fadeoutamt;	}

	if(timer > devlogofadeoutend*1000)
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
