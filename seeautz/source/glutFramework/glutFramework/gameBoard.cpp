#include "gameBoard.h"
#include <vector>
#include <fstream>

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
	scale = 100;
	mapOffsetX = 100;
	mapOffsetY = 100;
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
	mapOffsetX = 100;
	mapOffsetY = 100;
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
	int hw = (int)(144/2);
	int hh = (int)(72/2);
	int basex = 0;
	int basey = 0;
	int drawAtX = 0;
	int drawAtY = 0;
	
	mapOffsetX+=2;
	mapOffsetY++;

	if(mapOffsetX > 1024)
		mapOffsetX = 0;

	if(mapOffsetY > 768)
		mapOffsetY = 0;

	for(int x = 0; x < Width; x++)
	{
		basex = x*hw;
		basey = x*hh;
		vector<mapTile*>::iterator itr = mapList[x].begin();
		for(int y = 0; y < Height; y++)
		{
			drawAtX = mapOffsetX + x*hw - (y * hw) + hw;
			drawAtY = mapOffsetY + y*72 - (y * hh) + (x * hh);

			drawTile((*itr)->getType(), drawAtX, drawAtY);
			//basey = y*hh;
			//std::cout << "Drawing Tile Type " << (*itr)->getType() << " at " <<  (x - (x*basex)) - y*hh + mapOffsetX << ", " <<  y-(y*basey) + mapOffsetY << endl;
			//drawTile((*itr)->getType(), (x - (x*basex)) - y*hh + mapOffsetX,  y-(y*basey) + mapOffsetY);
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
	glClearColor(128, 255, 128, 0);
	oglTexture2D* toDraw;

	toDraw = tileImages[nType];

	toDraw->mX = txPos;
	toDraw->mY = tyPos;
	toDraw->drawImage();
	return true;
}

void gameBoard::initialize()
{
	oglTexture2D* tempTile;
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TEmpty.png",		 144, 72); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDefault.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised1.png",	 144, 72); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised2.png",	 144, 72); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised3.png",	 144, 72); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TRaised4.png",	 144, 72); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfTopL.png",	 144, 72); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfTopR.png",	 144, 72); tileImages.push_back(tempTile);
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfBottomL.png", 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/THalfBottomR.png", 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TGap.png",		 144, 72); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectric.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricTL.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricTR.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricBL.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TElectricBR.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TIce.png",		 144, 72); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TWater.png",		 144, 72); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchTL.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchTR.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchBL.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitchBR.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSwitch.png",		 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramTL.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramTR.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramBL.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgramBR.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TProgram.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableTL.png", 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableTR.png", 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableBL.png", 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakableBR.png", 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TSolid.png",		 144, 72); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TBreakable.png",	 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TStart.png",		 144, 72); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TEnd.png",		 144, 72); tileImages.push_back(tempTile);		
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorTL.png",		 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorTR.png",		 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorBL.png",		 144, 72); tileImages.push_back(tempTile);	
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TDoorBR.png",		 144, 72); tileImages.push_back(tempTile);			


}

void gameBoard::cleanup()
{
	vector<oglTexture2D*>::iterator itr = tileImages.begin();
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

bool gameBoard::setOffsets(int x, int y)
{
	mapOffsetX = x;
	mapOffsetY = y;
	return true;
}

bool gameBoard::LoadGameMapFromFile(std::string filename)
{
	/*tutorialmap1 = new gameBoard(1, 3);

	tutorialmap1->setTileType(0, 2, TStart);
	tutorialmap1->setTileType(0, 1, TDoorBL);
	tutorialmap1->setTileType(0, 0, TEnd);*/

	cout << "attempting to open file: " << filename << endl;
	ifstream mapfile;
	//if(!mapfile)
	//	return false;

	mapfile.open(filename.c_str());
	//string line;
	
	int nWidth;
	int nHeight;
	//nWidth << mapfile;
	mapfile >> nWidth;
	mapfile >> nHeight;

	// make it all empty
	mapList.resize(nWidth);
	for(int x = 0; x < nWidth; x++)
	{
		mapList[x].resize(nHeight);
	}

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
	Width = nWidth;
	Height = nHeight;

	int temptile;

	for(int y = 0; y < Height; y++)
	{
		for(int x = 0; x < Width; x++)
		{
			mapfile >> temptile;
			this->setTileType(x, y, (tileTypeEnum)temptile);
		}
	}

	mapfile.close();

	return true;

}