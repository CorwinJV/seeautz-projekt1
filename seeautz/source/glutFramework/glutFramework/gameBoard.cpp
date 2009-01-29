#include "gameBoard.h"
#include <vector>

using namespace std;

gameBoard::gameBoard()
{
	// make it all empty
	mapList.resize(1);
	for(int x = 0; x < 1; x++)
	{
		mapList[x].resize(1);
	}
	// populate it with default objects

	mapTile* temp;	

	for(int x = 0; x < 1; x++)
	{
		vector<mapTile*>::iterator itr = mapList[x].begin();
		
		for (; itr != mapList[x].end(); itr++)
		{
			temp = new mapTile(TEmpty, true);
			(*itr) = temp;
		}
	}
	initialize();
}

gameBoard::gameBoard(int nWidth, int nHeight)
{
	Width = nWidth;
	Height = nHeight;
	// make it all empty
	mapList.resize(nWidth);
	for(int x = 0; x < nWidth; x++)
	{
		mapList[x].resize(nHeight);
	}
	// populate it with default objects

	mapTile* temp;	

	for(int x = 0; x < nWidth; x++)
	{
		vector<mapTile*>::iterator itr = mapList[x].begin();
		
		for (; itr != mapList[x].end(); itr++)
		{
			temp = new mapTile(TEmpty, true);
			(*itr) = temp;
		}
	}
	initialize();
}

gameBoard::~gameBoard()
{
	// delete the vectors
	for(int x = 0; x < Width; x++)
		for(int y = 0; y < Height; y++)
			delete mapList[x][y];

	mapList.clear();
	cleanup();
}

bool gameBoard::update()
{
	for(int x = 0; x < Height; x++)
	{
		vector<mapTile*>::iterator itr = mapList[x].begin();
		
		for (; itr != mapList[x].end(); itr++)
		{
			(*itr)->update();
		}
	}
	return true;
}

bool gameBoard::draw()
{
	for(int x = 0; x < Width; x++)
	{
		vector<mapTile*>::iterator itr = mapList[x].begin();
		for(int y = 0; y < Height; y++)
		{
			drawTile((*itr)->getType(), x*158, y*72);
			itr++;
		}
	}
	return true;
}


bool gameBoard::moveTile(int sX, int sY, int dX, int dY)
{
	mapList[dX][dY] = mapList[sX][sY];
	return true;
}

bool gameBoard::setTileType(int x, int y, tileTypeEnum ntileType)
{
	mapList[x][y]->setType(ntileType);
	return true;
}

tileTypeEnum gameBoard::getTileType(int x, int y)
{
	return mapList[x][y]->getType();
}

bool gameBoard::drawTile(tileTypeEnum nType, int txPos, int tyPos)
{
	pixmap* toDraw;

	toDraw = tileImages[nType];
	//switch(nType)
	//{
	//case TEmpty:			// 0 empty		
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TDefault:		// 1 default floor tile
	//	toDraw = tileImages[TDefault];
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TRaised1:		// 2 raised 1 level
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TRaised2:		// 3 raised 2 levels
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TRaised3:		// 4 raised 3 levels
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TRaised4:		// 5 raised 4 levels
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case THalfTopL:		// 6 half top, left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case THalfTopR:		// 7 half top, right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case THalfBottomL:	// 8 half bottom, left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case THalfBottomR:	// 9 half bottom, right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TGap:			// 10 gap
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TElectric:		// 11 electric tile
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TElectricTL:	// 12 electric wall top left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TElectricTR:	// 13 electric wall top right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TElectricBL:	// 14 electric wall bottom left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TElectricBR:	// 15 electric wall bottom right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TIce:			// 16 ice tile
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TWater:			// 17 water tile
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TSwitchTL:		// 18 switch top left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TSwitchTR:		// 19 switch top right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TSwitchBL:		// 20 switch bottom left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TSwitchBR:		// 21 switch bottom right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TSwitch:		// 22 switch whole square
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TProgramTL:		// 23 reprogram spot top left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TProgramTR:		// 24 reprogram spot top right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TProgramBL:		// 25 reprogram spot bottom left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TProgramBR:		// 26 reprogram spot bottom right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TProgram:		// 27 reprogram spot
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TBreakableTL:	// 28 breakable top leftle
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TBreakableTR:	// 29 breakable top right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TBreakableBL:	// 30 breakable bottom left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TBreakableBR:	// 31 breakable bottom right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TSolid:			// 32 Solid Block
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TBreakable:		// 33 Solid Breakable Square
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TStart:			// 34 start square
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TEnd:			// 35 end square
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TDoorTL:		// 36 door top left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TDoorTR:		// 37 door top right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TDoorBL:		// 38 door bottom left
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//case TDoorBR:		// 39 door bottom right
	//	toDraw = NULL;		// set this to the proper image
	//	break;
	//default:
	//	toDraw = NULL;		// set image to error image
	//	break;
	//}

	toDraw->mX = txPos;
	toDraw->mY = tyPos;
	toDraw->drawPixMap();

	return true;
}

void gameBoard::initialize()
{
	//pixmap* temp;
	//temp = new pixmap("TEmpty.bmp");

	tileImages.push_back(new pixmap("tiles/TEmpty.bmp"));			
	tileImages.push_back(new pixmap("tiles/TDefault.bmp"));		
	tileImages.push_back(new pixmap("tiles/TRaised1.bmp"));
	tileImages.push_back(new pixmap("tiles/TRaised2.bmp"));
	tileImages.push_back(new pixmap("tiles/TRaised3.bmp"));
	tileImages.push_back(new pixmap("tiles/TRaised4.bmp"));
	tileImages.push_back(new pixmap("tiles/THalfTopL.bmp"));
	tileImages.push_back(new pixmap("tiles/THalfTopR.bmp"));
	tileImages.push_back(new pixmap("tiles/THalfBottomL.bmp"));	
	tileImages.push_back(new pixmap("tiles/THalfBottomR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TGap.bmp"));			
	tileImages.push_back(new pixmap("tiles/TElectric.bmp"));	
	tileImages.push_back(new pixmap("tiles/TElectricTL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TElectricTR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TElectricBL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TElectricBR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TIce.bmp"));			
	tileImages.push_back(new pixmap("tiles/TWater.bmp"));		
	tileImages.push_back(new pixmap("tiles/TSwitchTL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TSwitchTR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TSwitchBL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TSwitchBR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TSwitch.bmp"));		
	tileImages.push_back(new pixmap("tiles/TProgramTL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TProgramTR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TProgramBL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TProgramBR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TProgram.bmp"));		
	tileImages.push_back(new pixmap("tiles/TBreakableTL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TBreakableTR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TBreakableBL.bmp"));	
	tileImages.push_back(new pixmap("tiles/TBreakableBR.bmp"));	
	tileImages.push_back(new pixmap("tiles/TSolid.bmp"));		
	tileImages.push_back(new pixmap("tiles/TBreakable.bmp"));	
	tileImages.push_back(new pixmap("tiles/TStart.bmp"));		
	tileImages.push_back(new pixmap("tiles/TEnd.bmp"));			
	tileImages.push_back(new pixmap("tiles/TDoorTL.bmp"));		
	tileImages.push_back(new pixmap("tiles/TDoorTR.bmp"));		
	tileImages.push_back(new pixmap("tiles/TDoorBL.bmp"));		
	tileImages.push_back(new pixmap("tiles/TDoorBR.bmp"));			


}

void gameBoard::cleanup()
{
	vector<pixmap*>::iterator itr = tileImages.begin();
	for(; itr != tileImages.end(); itr++)
	{
		delete (*itr);
	}
	tileImages.clear();


	//while(tileImages.begin() != tileImages.end())
	//{
	//	
	//	
	//}

}