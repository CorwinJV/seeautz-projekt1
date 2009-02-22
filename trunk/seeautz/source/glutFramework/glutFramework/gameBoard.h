#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "oglUtility.h"
#include "pixmap.h"
#include "mapTile.h"
#include "tileEnums.h"
#include "oglTexture2D.h"
#include "objectManager.h"
#include "robot.h"
#include "oglGameVars.h"
#include "Oswitch.h"
#include "Oteleport.h"
#include "sound.h"

#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class gameBoard
{
protected:

	enum GameBoardState
	{
		GB_VIEW,
		GB_LOGICVIEW, 
		GB_EXECUTION,
		GB_FINISHED
	};

	std::vector<std::vector<mapTile*>> mapList;
	std::vector<oglTexture2D*> tileImages;
	// 1 dimensional array of ai entities
	std::vector<object*> objectList;
	std::vector<Oswitch*> switchList;
	std::vector<Oteleport*> teleportList;
	objectManager *OM;
	oglTexture2D*	robotImage;
	std::vector<logicBlock*>* logicBank;		// The usable logic blocks

	int robotX;
	int robotY;
	int robotStartX;
	int robotStartY;

	int Width;
	int Height;

	int mouseX;
	int mouseY;
	
	double scale;
	double maxscale;
	double minscale;
	int    mapOffsetX, mapOffsetY;
	double centerX, centerY;
	double currentX, currentY;

	// more stuff
	double overallHeight;
	double overallWidth;

	double imageWidth;
	double imageHeight;
	int imageBaseWidth;
	int imageBaseHeight;
	double hw;
	double hh;
	int screenWidth;
	int screenHeight;
	double screenEdge;
	double moveSpeed;
	soundEffect *ourSound;
	clock_t timer;
	clock_t startTime;

	// temp for font testing
	bool drawText;

private:
	GameBoardState curState;

public:
	gameBoard();
	gameBoard(int nwidth, int nheight);
	~gameBoard();
	//bool resizeBoard(int x, int y);
	bool moveTile(int sX, int sY, int dX, int dY);
	bool update();
	bool draw();
	bool drawTile(tileTypeEnum ntype, int txPos, int tyPos, double scale, bool isActive);
	bool drawObject(int objectType, int txPos, int tyPos, double scale);
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
	bool resetMap();
	void processRobot();
	bool robotAtEndSquare();
	void teleporterCheck();
	void keepRobotOnTheBoard();
	void playSound();
	bool interfaceHasFiredExecuteOrder(std::vector<logicBlock*> executionList);
	bool interfaceHasFiredAbortOrder();

	bool RCcanRobotLeaveSquare(int direction);		        // can the robot leave this square in the direction it is facing
	bool RCwillRobotDieTryingToLeaveSquare(int direction);  // will the robot die trying to leave this square in the direction it is facing (regardless of if it can actually leave)
	bool RCwillRobotDieStayingHere();						// will the robot die by standing in this square
	bool RCcanRobotMoveForward(int direction, int destNum);	// can the robot move forward from our square to destNum squares (regardless of the consequences)
	bool RCmoveRobotForward();								// move the robot forward x squares
	void RCjumpRobotForward();								// jump the robot forward 2 squares	
	void RCcrouch();										// crouch under a square and appear at the other side
	void RCclimb();											// climb up a level or climb over a halfwall
	void RCpunch();							
	void RCactivate();
};

#endif
