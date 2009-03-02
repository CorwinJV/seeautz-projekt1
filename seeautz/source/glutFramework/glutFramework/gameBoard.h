#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "oglUtility.h"
//#include "pixmap.h"
#include "mapTile.h"
#include "tileEnums.h"
#include "oglTexture2D.h"
#include "objectManager.h"
#include "robot.h"
#include "oglGameVars.h"
#include "Oswitch.h"
#include "Oteleport.h"
#include "sound.h"
#include "subroutine.h"

#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>


enum GameBoardState
{
	GB_PREGAME,			// for the very start of the map, to show the level name, a brief description and points available
	GB_VIEWSCORE,		// used for viewing score stats after completion of level
	GB_LOGICVIEW,		// used to view screen where you are adding logic blocks
	GB_EXECUTION,		// used when robot is executing logic blocks
	GB_FINISHED,			// used to load next level after score is displayed
	GB_ROBOTDIED,		// take a wild guess what this state is for
	GB_YOUWIN,
};

class gameBoard
{
protected:
	std::vector<std::vector<mapTile*>> mapList;
	std::vector<oglTexture2D*> tileImages;
	// 1 dimensional array of ai entities
	std::vector<object*> objectList;
	std::vector<Oswitch*> switchList;
	std::vector<Oteleport*> teleportList;
	objectManager *OM;
	oglTexture2D*	robotImage;
	std::vector<logicBlock*>* logicBank;		// The usable logic blocks
	subroutine*	  SUB1;
	subroutine*   SUB2;

	int robotX;
	int robotY;
	int robotStartX;
	int robotStartY;
	int robotReprogramX;
	int robotReprogramY;

	bool didWeJustTeleport;
	bool robotAlive;

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
	bool processSub(int whichSub);
	bool delayAdvance;

	bool moveTile(int sX, int sY, int dX, int dY);
	bool drawTile(tileTypeEnum ntype, int txPos, int tyPos, double scale, bool isActive);
	bool drawObject(int objectType, int txPos, int tyPos, double scale);
	bool setTileType(int x, int y, tileTypeEnum ntileType);
	tileTypeEnum getTileType(int x, int y);	
	void initialize();
	void cleanup();
	bool setOffsets(int x, int y);
	bool setScale(double newScale);
	double getScale();
	void verifyMapPosition();
	void recalcPositions();
	bool resetMap();
	void processRobot();
	void teleporterCheck();
	void keepRobotOnTheBoard();
	void playSound();
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

private:
	GameBoardState curState;

public:
	gameBoard();
	gameBoard(int nwidth, int nheight);
	~gameBoard();
	//bool resizeBoard(int x, int y);
	bool update();
	bool draw();
	bool LoadGameMapFromFile(std::string filename);
	void setState(GameBoardState state);

	// bool addentity
	void processMouse(int x, int y);
	void processMouseClick(int button, int state, int x, int y);
	void mapScroll();
	void keyboardInput(unsigned char c, int x, int y);
	bool robotAtEndSquare();
		
	bool interfaceHasFiredExecuteOrder(std::vector<logicBlock*> executionList, std::vector<logicBlock*> executionListSub1, std::vector<logicBlock*> executionListSub2);
	bool interfaceHasFiredAbortOrder();
	bool interfaceHasFiredResetOrder();

	GameBoardState getCurState();							// returns the current state of the gameBoard	
};

#endif
