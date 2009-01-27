#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "oglUtility.h"
#include "pixmap.h"
#include <cstring>
#include <iostream>
#include "mapTile.h"
#include <vector>
#include "tileEnums.h"

class gameBoard
{
protected:
	std::vector<std::vector<mapTile*>> mapList;
	// 1 dimensional array of ai entities
	int Width;
	int Height;

public:
	gameBoard(int nwidth, int nheight);
	~gameBoard();
	//bool resizeBoard(int x, int y);
	bool moveTile(int sX, int sY, int dX, int dY);
	bool update();
	bool draw();
	bool drawTile(tileTypeEnum ntype, int txPos, int tyPos);
	bool setTileType(int x, int y, tileTypeEnum ntileType);
	tileTypeEnum getTileType(int x, int y);	
	// bool addentity

};

#endif