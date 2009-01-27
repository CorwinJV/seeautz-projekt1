#include "gameBoard.h"

using namespace std;
//class gameBoard()
//{
//protected:
//	vector<vector<mapTile>> mapListX;
//	// 1 dimensional array of ai entities
//	int Width;
//	int Height;
//
//public:
		//	gameBoard(int nwidth, int nheight);
//	~gameBoard();
//  bool resizeBoard(int x, int y);
		//	bool moveTile(int sX, int sY, int dX, int dY);
//	bool update();
//	bool draw();
		//	bool setTileType(int x, int y, tileTypeEnum ntileType);
		//	bool getTileType(int x, int y);	
//	// bool addentity
//
//};

//bool gameBoard::resizeBoard(int x, int y)
//{
//	mapList.resize(x);
//	
//	for(int i = 0; i < x; i++)
//	{
//		mapList[x].resize(i);
//	}
//}

gameBoard::gameBoard(int nWidth, int nHeight)
{
	// make it all empty
	mapList.resize(nWidth);
	for(int x = 0; x < nWidth; x++)
	{
		mapList[x].resize(nHeight);
	}
	// populate it with default objects

	mapTile* temp;	

	for(int x = 0; x < nHeight; x++)
	{
		vector<mapTile*>::iterator itr = mapList[x].begin();
		
		for (; itr != mapList[x].end(); itr++)
		{
			temp = new mapTile(TEmpty, true);
			(*itr) = temp;
		}
	}
}

gameBoard::~gameBoard()
{
	// delete the vectors
	for(int x = 0; x < Width; x++)
		for(int y = 0; y < Height; y++)
			delete mapList[x][y];

	mapList.clear();
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
	for(int x = 0; x < Height; x++)
	{
		vector<mapTile*>::iterator itr = mapList[x].begin();
		for(int y = 0; y < Width; y++)
		{
			//drawTile((*itr)->getType(), x, y);
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
