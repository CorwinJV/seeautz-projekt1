#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "oglUtility.h"
#include "pixmap.h"
#include <cstring>
#include <iostream>
#include "mapTile.h"
#include <vector>
#include "tileEnums.h"
#include "oglTexture2D.h"
#include <string>

class gameBoard
{
protected:
	std::vector<std::vector<mapTile*>> mapList;
	std::vector<oglTexture2D*> tileImages;
	// 1 dimensional array of ai entities
	int Width;
	int Height;

	int mouseX;
	int mouseY;
	
	double scale;
	double maxscale;
	double minscale;
	int mapOffsetX, mapOffsetY;

	// more stuff
	double overallHeight;
	double overallWidth;

	int imageWidth;
	int imageHeight;
	int hw;
	int hh;
	int screenWidth;
	int screenHeight;
	double screenEdge;
	double moveSpeed;

public:
	gameBoard();
	gameBoard(int nwidth, int nheight);
	~gameBoard();
	//bool resizeBoard(int x, int y);
	bool moveTile(int sX, int sY, int dX, int dY);
	bool update();
	bool draw();
	bool drawTile(tileTypeEnum ntype, int txPos, int tyPos, double scale);
	bool setTileType(int x, int y, tileTypeEnum ntileType);
	tileTypeEnum getTileType(int x, int y);	
	void initialize();
	void cleanup();
	bool LoadGameMapFromFile(std::string filename);
	bool setOffsets(int x, int y);
	bool setScale(double newScale);
	double getScale();
	// bool addentity
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void mapScroll();
	void verifyMapPosition();
	void recalcPositions();
	void keyboardInput(unsigned char c, int x, int y);

};

#endif
