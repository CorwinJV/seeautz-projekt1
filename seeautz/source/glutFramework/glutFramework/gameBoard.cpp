#include "gameBoard.h"
#include <vector>
#include <fstream>
#include "objectManager.h"
#include "robot.h"
#include "objectEnums.h"
#include "oglGameVars.h"
#include "Oswitch.h"
#include "Oteleport.h"

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
	mapOffsetX = 0;
	mapOffsetY = 0;
	scale = 1;

	imageBaseWidth = 144;
	imageBaseHeight = 72;

	hw = (imageWidth/2);	// half width
	hh = (imageHeight/2);	// half height

	imageWidth = imageBaseWidth *scale;
	imageHeight = imageBaseHeight *scale;

	screenWidth = 1024;
	screenHeight = 768;

	screenEdge = 0.01;
	moveSpeed = scale * 0.1;
	maxscale = 2.0;
	minscale = 0.2;
	centerX = 0;
	centerY = 0;
	Height = 0;
	Width = 0;
	overallWidth = (Height + Width) * hw;
	overallHeight = (Height + Width) * hh;

	// and lets make an object manager
	OM = new objectManager();
	objectList.clear();
	logicBank = GameVars->Instance()->getAllLogicBlocks();
	ourSound = new soundEffect;
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
	mapOffsetX = 0;
	mapOffsetY = 0;
	scale = 1;

	imageBaseWidth = 144;
	imageBaseHeight = 72;

	hw = (imageWidth/2);	// half width
	hh = (imageHeight/2);	// half height

	imageWidth = imageBaseWidth *scale;
	imageHeight = imageBaseHeight *scale;


	imageWidth *= scale;
	imageHeight *= scale;

	screenWidth = 1024;
	screenHeight = 768;

	screenEdge = 0.01;
	moveSpeed = scale * 0.1;
	maxscale = 2.0;
	minscale = 0.2;

	overallWidth = (Height + Width) * hw;
	overallHeight = (Height + Width) * hh;


	centerX = (int)((Width+1)/2);
	centerY = (int)((Height+1)/2);
	currentX = centerX;
	currentY = centerY;

	// time to setup offsets based on centers

	logicBank = GameVars->Instance()->getAllLogicBlocks();
	objectList.clear();
	ourSound = new soundEffect;
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
	int imageWidth = 144;
	int imageHeight = 72;
	imageWidth *= scale;
	imageHeight *= scale;
	int hw = (imageWidth/2);	// half width
	int hh = (imageHeight/2);	// half height

	int basex = 0;
	int basey = 0;
	int drawAtX = 0;
	int drawAtY = 0;


	for(int x = 0; x < Width; x++)
	{
		basex = x*hw;
		basey = x*hh;
		vector<mapTile*>::iterator itr = mapList[x].begin();
		for(int y = 0; y < Height; y++)
		{
			drawAtX = mapOffsetX + (x * hw - (y * hw) + (hw));
			drawAtY = mapOffsetY + (y * imageHeight - (y * hh) + (x * hh));
			if((*itr)->getIsActive())
				drawTile((*itr)->getType(), drawAtX, drawAtY, scale, true);
			else
				drawTile((*itr)->getType(), drawAtX, drawAtY, scale, false);
			itr++;
		}
	}
	// draw the robot/objects
	// todo - this will eventually iterate through all the objects in the 
	// game board and draw them in the proper spot if they should be drawn at all
	// for the time being, the only "object" that requires being drawn is the robot
	drawAtX = mapOffsetX + (robotX * hw - (robotY * hw) + (hw));
	drawAtY = mapOffsetY + (robotY * imageHeight - (robotY * hh) + (robotX * hh));

	drawObject(0, drawAtX, drawAtY, scale);
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

bool gameBoard::drawTile(tileTypeEnum nType, int txPos, int tyPos, double scale, bool isActive)
{
	glClearColor(128, 255, 128, 0);
	oglTexture2D* toDraw;

	toDraw = tileImages[nType];

	int tempdx = toDraw->dX;
	int tempdy = toDraw->dY;

	toDraw->dX *= scale;
	toDraw->dY *= scale;

	toDraw->mX = txPos;
	toDraw->mY = tyPos;

	if(isActive)
		toDraw->drawImageSegment(0.0, 0.0, 0.5, 0.0, 0.0, 1.0, 0.5, 1.0, 1);
	else
		toDraw->drawImageSegment(0.5, 0.0, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1);

	toDraw->dX = tempdx;
	toDraw->dY = tempdy;

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
	tempTile = new oglTexture2D(); tempTile->loadImage("tiles/TTeleport.png",	 144, 72); tileImages.push_back(tempTile);			
	robotImage = new oglTexture2D(); robotImage->loadImage("object/robotDefault.png", 195*0.45, 110*0.45);

}

void gameBoard::cleanup()
{
	vector<oglTexture2D*>::iterator itr = tileImages.begin();
	for(; itr != tileImages.end(); itr++)
	{
		delete (*itr);
	}
	tileImages.clear();
	delete ourSound;


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

	cout << "attempting to open file: " << filename << endl;
	ifstream mapfile;
	//if(!mapfile)
	//	return false;

	mapfile.open(filename.c_str());
	//string line;
	
	int nWidth;
	int nHeight;
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
			// if its a start spot, add the robot to the object list
			if(temptile == TStart)
			{
				//OM->addNewObject<robot>(x, y, 1, ORobot);
				robot* tempObj;
				tempObj = new robot(x, y, 0, ORobot);
				objectList.push_back(tempObj);
				robotX = x;
				robotY = y;
				robotStartX = x;
				robotStartY = y;
				currentX = robotX;
				currentY = robotY;
			}
		}
	}

	// now lets see if there's any switches in the game map
	if(!mapfile.eof())
	{
		int switchcount;
		int teleportcount;
		mapfile >> switchcount;
		mapfile >> teleportcount;

		int numcnt;
		int myX;
		int myY;
		int tempX;
		int tempY;
		Oswitch* tempObj;
		Oteleport* tempObjT;

		// read in the switches

		for(int x = 0; x < switchcount; x++)
		{
			
			// switch data layout
			// # of tiles controlled
			mapfile >> numcnt;

			// x y of this switch
			mapfile >> myX;
			mapfile >> myY;
			
			tempObj = new Oswitch(myX, myY, 0, OSwitch);

			for(int sx = 0; sx < numcnt; sx++)
			{
				// x y of first tile controlled
				mapfile >> tempX;
				mapfile >> tempY;
				tempObj->addTarget(tempX, tempY);
				// ...
				// x y of nth tile controlled
			}
			switchList.push_back(tempObj);
		}

		// read in the teleporters
		for(int x = 0; x < teleportcount; x++)
		{

			mapfile >> myX;
			mapfile >> myY;
			mapfile >> tempX;
			mapfile >> tempY;
			tempObjT = new Oteleport(myX, myY, 0, OTeleport);
			tempObjT->setTarget(tempX, tempY);
			teleportList.push_back(tempObjT);
		}
	}

	mapfile.close();

	centerX = (int)((Width+1)/2);
	centerY = (int)((Height+1)/2);
	currentX = centerX;
	currentY = centerY;

	imageBaseWidth = 144;
	imageBaseHeight = 72;

	hw = (imageWidth/2);	// half width
	hh = (imageHeight/2);	// half height
	overallWidth = (Height + Width) * hw;
	overallHeight = (Height + Width) * hh;

	recalcPositions();

	currentX = robotX;
	currentY = robotY;

	return true;

}


bool gameBoard::setScale(double newScale)
{
	scale = newScale;
	return true;
}

double gameBoard::getScale()
{
	return scale;
}

void gameBoard::processMouse(int x, int y)
{
	mouseX = x;
	mouseY = y;
	mapScroll();

}

void gameBoard::processMouseClick(int button, int state, int x, int y)
{
	// Used for mouse wheel, has to be up
	if (state == GLUT_UP )
	{
		if ( button == GLUT_WHEEL_UP )
		{
			std::cout << "Mouse up" << endl;
		}
		else if( button == GLUT_WHEEL_DOWN )
		{
			std::cout << "Mouse down" << endl;
		}
		else if( button == GLUT_LEFT_BUTTON )
		{
			std::cout << "Mouse LB" << endl;
		}
		else if( button == GLUT_RIGHT_BUTTON )
		{
			std::cout << "Mouse RB" << endl;
		}
		else if( button == GLUT_MIDDLE_BUTTON )
		{
			std::cout << "Mouse MB" << endl;
		}
	}

	std::cout << "Button = " << button << " - State = " << state <<  endl;
}

void gameBoard::mapScroll()
{
	double mMoveSpeed = moveSpeed/2;
	// mouse stuff
	recalcPositions();

	// see if mouse is at top of screen
	if((mouseY > 0) && (mouseY < screenHeight*screenEdge))
	{
		//mapOffsetY+= moveSpeed;
		currentX-=mMoveSpeed;
		currentY-=mMoveSpeed;
	}

	// see if mouse is at bottom of screen
	if((mouseY < screenHeight) && (mouseY > (screenHeight - (screenHeight*screenEdge))))
	{
		//mapOffsetY-= moveSpeed;
		currentX+= mMoveSpeed;
		currentY+= mMoveSpeed;
	}
	// see if mouse is at left side of screen
	if((mouseX > 0) && (mouseX < screenWidth * screenEdge))
	{
		//mapOffsetX+= moveSpeed;
		currentX-=mMoveSpeed;
		currentY+=mMoveSpeed;
	}
	// see if mouse is at right side of screen
	if((mouseX < screenWidth) && (mouseX > (screenWidth - (screenWidth * screenEdge))))
	{
		//mapOffsetX-= moveSpeed;
		currentX+=mMoveSpeed;
		currentY-=mMoveSpeed;
	}

	verifyMapPosition();
}

void gameBoard::keyboardInput(unsigned char c, int x, int y)
{
	vector<object*>::iterator oitr;
	vector<logicBlock*>::iterator lbitr;

	double kbmovespeed = moveSpeed;
	switch(c)
	{
	case 27:
		exit(0);
		break;
	case 'q': //up-left
		currentX -= kbmovespeed;
		break;
	case 'e': // up-right
		currentY -= kbmovespeed;
		break;
	case 'z': // down-left
		currentY += kbmovespeed;
		break;
	case 'c': // down-right
		currentX += kbmovespeed;
		break;

	case 'w': // up
		currentY -= kbmovespeed;
		currentX -= kbmovespeed;
		break;
	case 'a':  // left
		currentY += kbmovespeed;
		currentX -= kbmovespeed;
		break;
	case 'd': // right
		currentX += kbmovespeed;
		currentY -= kbmovespeed;
		break;
	case 's': // down
		currentY += kbmovespeed;
		currentX += kbmovespeed;
		break;
	case '-':	// zoom out (decrease scale)
		scale -= 0.05;
		break;
	case '=':	// zoom in (increase scale)
		scale += 0.05;
		break;
	case '\\':	// reset scale
		scale = 1;
		break;
	case ']':	// reset center on center of map
		currentX = centerX;
		currentY = centerY;
		break;
	case '[':	// center on robot
		currentX = robotX;
		currentY = robotY;
		break;
	// move forward
	case 'i':
	case 'I':
		// find the robot
		oitr = objectList.begin();
		for(;oitr != objectList.end(); oitr++)
		{
			if((*oitr)->getType() == ORobot)
			{
			// find forward in allLogicBlocks
				lbitr = logicBank->begin();
				for(;lbitr != logicBank->end(); lbitr++)
				{
					if((*lbitr)->enumInstruction == MOVE_FORWARD1)
					{
			//			// add move forward to the robot command queue
						(*oitr)->addCommand(*lbitr);
						std::cout << "added MOVE_FORWARD1 to robot command list " << endl;
						(*oitr)->coreDump();
					}
				}
			}
		}		
		break;
	// turn left
	case 'j':
	case 'J':
		// find the robot
		oitr = objectList.begin();
		for(;oitr != objectList.end(); oitr++)
		{
			if((*oitr)->getType() == ORobot)
			{
			// find turn left in allLogicBlocks
				lbitr = logicBank->begin();
				for(;lbitr != logicBank->end(); lbitr++)
				{
					if((*lbitr)->enumInstruction == TURN_LEFT1)
					{
			//			// add move forward to the robot command queue
						(*oitr)->addCommand(*lbitr);
						std::cout << "added TURN_LEFT1 to robot command list " << endl;
						(*oitr)->coreDump();
					}
				}
			}
		}	
		break;
	// turn right
	case 'l':
	case 'L':
		// find the robot
		oitr = objectList.begin();
		for(;oitr != objectList.end(); oitr++)
		{
			if((*oitr)->getType() == ORobot)
			{
			// find turn right in allLogicBlocks
				lbitr = logicBank->begin();
				for(;lbitr != logicBank->end(); lbitr++)
				{
					if((*lbitr)->enumInstruction == TURN_RIGHT1)
					{
			//			// add move forward to the robot command queue
						(*oitr)->addCommand(*lbitr);
						std::cout << "added TURN_RIGHT1 to robot command list " << endl;
						(*oitr)->coreDump();
					}
				}
			}
		}	
		break;
		break;
	// jump
	case 'u':
	case 'U':
		// find the robot
		oitr = objectList.begin();
		for(;oitr != objectList.end(); oitr++)
		{
			if((*oitr)->getType() == ORobot)
			{
			// find JUMP in allLogicBlocks
				lbitr = logicBank->begin();
				for(;lbitr != logicBank->end(); lbitr++)
				{
					if((*lbitr)->enumInstruction == JUMP)
					{
			//			// add move forward to the robot command queue
						(*oitr)->addCommand(*lbitr);
						std::cout << "added JUMP to robot command list " << endl;
						(*oitr)->coreDump();
					}
				}
			}
		}	
		break;
	// crouch
	case 'k':
	case 'K':
		// find the robot
		oitr = objectList.begin();
		for(;oitr != objectList.end(); oitr++)
		{
			if((*oitr)->getType() == ORobot)
			{
			// find CROUCH in allLogicBlocks
				lbitr = logicBank->begin();
				for(;lbitr != logicBank->end(); lbitr++)
				{
					if((*lbitr)->enumInstruction == CROUCH)
					{
			//			// add move forward to the robot command queue
						(*oitr)->addCommand(*lbitr);
						std::cout << "added CROUCH to robot command list " << endl;
						(*oitr)->coreDump();
					}
				}
			}
		}	
		break;
	// activate
	case 'o':
	case 'O':
		// find the robot
		oitr = objectList.begin();
		for(;oitr != objectList.end(); oitr++)
		{
			if((*oitr)->getType() == ORobot)
			{
			// find ACTIVATE in allLogicBlocks
				lbitr = logicBank->begin();
				for(;lbitr != logicBank->end(); lbitr++)
				{
					if((*lbitr)->enumInstruction == ACTIVATE)
					{
			//			// add move forward to the robot command queue
						(*oitr)->addCommand(*lbitr);
						std::cout << "added ACTIVATE to robot command list " << endl;
						(*oitr)->coreDump();
					}
				}
			}
		}	
		break;
	// punch
	case 'p':
	case 'P':
		// find the robot
		oitr = objectList.begin();
		for(;oitr != objectList.end(); oitr++)
		{
			if((*oitr)->getType() == ORobot)
			{
			// find PUNCH in allLogicBlocks
				lbitr = logicBank->begin();
				for(;lbitr != logicBank->end(); lbitr++)
				{
					if((*lbitr)->enumInstruction == PUNCH)
					{
			//			// add move forward to the robot command queue
						(*oitr)->addCommand(*lbitr);
						std::cout << "added PUNCH to robot command list " << endl;
						(*oitr)->coreDump();
					}
				}
			}
		}	
		break;
	case 't': // process next thing in robot loop
	case 'T':
		processRobot();
		break;
	case 'r':
	case 'R':
		robotX = robotStartX;
		robotY = robotStartY;
		break;

	case 'X':
		robotX--;
		currentX = robotX;
		break;
	case 'x':
		robotX++;
		currentX = robotX;
		break;
	case 'Y':
		robotY--;
		currentY = robotY;
		break;
	case 'y':
		robotY++;
		currentY = robotY;
		break;
	case '9':
		playSound();
		break;
	default:
		break;
	}

	
	if (scale > maxscale)	scale = maxscale;
	if (scale < minscale)	scale = minscale;
	keepRobotOnTheBoard();
	verifyMapPosition();	
	teleporterCheck();
}

void gameBoard::playSound()
{
	ourSound->playSound("sound\\click.wav");
}

void gameBoard::verifyMapPosition()
{
	recalcPositions();

	// max up ( checks bottom )
	if((mapOffsetY + overallHeight) < (screenHeight - screenHeight * screenEdge))
	{
		mapOffsetY = (screenHeight - screenHeight * screenEdge) - overallHeight;
	}
	// max down ( checks top )
	if((mapOffsetY) > (screenHeight * screenEdge))
	{
		mapOffsetY = screenHeight * screenEdge;
	}

	//// max left ( checking right )
	if((mapOffsetX + ((Width +2)*hw)) < (screenWidth - screenWidth * screenEdge))
	{
		mapOffsetX = (screenWidth - screenWidth * screenEdge) - ((Width+2)*hw);
	}

	//// max right ( checking left )
	if((mapOffsetX - ((Height-2)*hw)) > (screenWidth * screenEdge))
	{
		mapOffsetX = (screenWidth * screenEdge) + ((Height-2)*hw);
	}

	// now lets see if this board should be centered or not
	//if(overallWidth < screenWidth)
	//{
	//	// center horizontally
	//	mapOffsetX = ((int)((Height - Width)/2) * hw) + (int)(screenWidth/2) - (int)(overallWidth/2);
	//}
	//
	//if(overallHeight < screenHeight)
	//{
	//	// center vertically
	//	mapOffsetY = ((int)((Width - Height)/2) * hh) + (int)(screenHeight/2) - (int)(overallHeight/2);
	//}
}

void gameBoard::recalcPositions()
{
	if(currentX > Width)	currentX = Width;
	if(currentX < 0)		currentX = 0;
	if(currentY > Height)	currentY = Height;
	if(currentY < 0)		currentY = 0;

	// setting offsety based on center spot
	imageWidth = imageBaseWidth * scale;
	imageHeight = imageBaseHeight * scale;

	hw = imageWidth/2;
	hh = imageHeight/2;

	overallWidth = (((Height + Width) * hw) + hw);
	overallHeight = (((Height + Width) * hh) + hh);

	moveSpeed = scale * 0.1;	

	// setting offsetx based on center spot
	// start at the center of the screen
	mapOffsetX = (screenWidth/2) + (hw*currentY) - (hw*currentX);
	mapOffsetY = (screenHeight/2)- (hh*currentY) - (hh*currentX);
}

bool gameBoard::resetMap()
{
	OM->startOver();
	return true;
}


bool gameBoard::drawObject(int objectType, int txPos, int tyPos, double scale)
{
	// for now, lets just draw the robot, additional code to come
	txPos += (hh*0.7)+5;
	tyPos += (hh*0.2)+5;
	glClearColor(128, 255, 128, 0);
	oglTexture2D* toDraw;

	toDraw = robotImage;

	int tempdx = toDraw->dX;
	int tempdy = toDraw->dY;

	toDraw->dX *= scale;
	toDraw->dY *= scale;

	toDraw->mX = txPos;
	toDraw->mY = tyPos;

	// find the robot
	vector<object*>::iterator oitr = objectList.begin();
	for(;oitr != objectList.end(); oitr++)
	{
		if((*oitr)->getType() == ORobot)
		{
			// now lets see which direction its facing
			switch((*oitr)->getDirection())
			{
			case 0:
				toDraw->drawImageSegment(0.0, 0.0,	0.25, 0.0,
										 0.0, 1.0,  0.25, 1.0, 1);
				break;
			case 1:
				toDraw->drawImageSegment(0.25, 0.0,	0.5, 0.0,
										 0.25, 1.0, 0.5, 1.0, 1);
				break;
			case 2:
				toDraw->drawImageSegment(0.5, 0.0,	0.75, 0.0,
										 0.5, 1.0,  0.75, 1.0, 1);
				break;
			case 3:
				toDraw->drawImageSegment(0.75, 0.0,	1.0, 0.0,
										 0.75, 1.0, 1.0, 1.0, 1);
				break;
			}
		}
	}
	toDraw->dX = tempdx;
	toDraw->dY = tempdy;

	return true;
}

void gameBoard::processRobot()
{
	// find the robot
	vector<object*>::iterator oitr = objectList.begin();
	vector<Oswitch*>::iterator sitr = switchList.begin();
	//Oswitch* tempSwitch;
	tileTypeEnum robotSquare;
	int			 robotDirection;
	tileTypeEnum destType;
	bool		 destActive;

	for(;oitr != objectList.end(); oitr++)
	{
		if((*oitr)->getType() == ORobot)
		{
			switch((*oitr)->getNextCommand())
			{
			case MOVE_FORWARD1:
				this->RCmoveRobotForward();
				break;
			case TURN_LEFT1:
				(*oitr)->rotate(-1);
				break;
			case TURN_RIGHT1:
				(*oitr)->rotate(1);
				break;
			case CROUCH:  // just like move forward above, only far less squares that can be moved into
				break;
			case CLIMB:	  // just like move forward above, only far less squares that can be moved into
				break;
			case JUMP:	  // just like move forward above, only far less squares that can be moved into
				this->RCjumpRobotForward();
				//if(( !canRobotMoveForwardOutOfSquare() )&& !willRobotDieMovingForwardOutOfSquare()  
				//	&& !canRobotMoveForward()  &&  !willRobotDieStayingHere() )
				break;
			case PUNCH:	  // just like move forward above, only far less squares that can be moved into
				break;
			case MOVE_FORWARD_UNTIL_UNABLE: // just like move forward above, only no advancement of command until destination square is invalid and won't cause death
				break;
			case SUB:	// special case
				break;
			case LOOP:	// since this should always be displayed as the last command automatically, this isn't really needed
						// the object's ai list automagically loops when it gets to its end
				break;
			case ACTIVATE:	// for now lets just check for a door so we can see it working in testmap1
				int destX = 0;
				int destY = 0;
				robotSquare = mapList[robotX][robotY]->getType();
				robotDirection = (*oitr)->getDirection();

				// first lets see if anything happens based upon the square we're standing in....

				// are we standing in a door square facing the door in our own square?
				// if so, lets toggle it
				switch(robotDirection)
				{
				case 0:// facing up/right (up on map)					
					if(robotSquare == TDoorTR)
						mapList[robotX][robotY]->toggleActive();
					break;
				case 1:// facing down/right (right on map)
					if(robotSquare == TDoorBR)
						mapList[robotX][robotY]->toggleActive();
					break;
				case 2:// facing down/left (down on map)
					if(robotSquare == TDoorBL)
						mapList[robotX][robotY]->toggleActive();
					break;
				case 3:// facing up/left (left on map)
					if(robotSquare == TDoorTL)
						mapList[robotX][robotY]->toggleActive();
					break;
				}

				destX = robotX;
				destY = robotY;
				// now lets see if the robot is facing a door				
				switch(robotDirection)
				{
				case 0:// facing up/right (up on map)					

					destY = robotY -1;					
					break;
				case 1:// facing down/right (right on map)
					destX = robotX +1;
					break;
				case 2:// facing down/left (down on map)
					destY = robotY + 1;
					break;
				case 3:// facing up/left (left on map)
					destX = robotX -1;
					break;
				}

				// now lets check if the door that is facing the robot
				if((destX >= 0) && (destX < Width) && (destY >= 0) && (destY < Height))
				{
					destType = (mapList[destX][destY]->getType()) ;
					destActive = (mapList[destX][destY]->getIsActive());

					switch(robotDirection)
					{
					case 0:// facing up/right (up on map)					
						if(destType == TDoorBL)
							mapList[destX][destY]->toggleActive();
						break;
					case 1:// facing down/right (right on map)
						if(destType == TDoorTL)
							mapList[destX][destY]->toggleActive();
						break;
					case 2:// facing down/left (down on map)
						if(destType == TDoorTR)
							mapList[destX][destY]->toggleActive();
						break;
					case 3:// facing up/left (left on map)
						if(destType == TDoorBR)
							mapList[destX][destY]->toggleActive();
						break;
					}
				}

				// switches are crashing... will fix later
				// are we standing on a switch square?
				sitr = switchList.begin();

				int sx;
				int sy;

				if((robotSquare == TSwitch) ||
				   ((robotSquare == TSwitchTR) && (robotDirection == 0)) ||
				   ((robotSquare == TSwitchBR) && (robotDirection == 1)) ||
				   ((robotSquare == TSwitchBL) && (robotDirection == 2)) ||
				   ((robotSquare == TSwitchTL) && (robotDirection == 3)))

				{
					for(;sitr != switchList.end(); sitr++)
					{
						//  find the switch in the object list
						if(((*sitr)->getType() == OSwitch) && ((*sitr)->getXPos() == robotX) && ((*sitr)->getYPos() == robotY))
						{
							// process through its stuff
							//tempSwitch = (*sitr);
							for(int xyx = 0; xyx < (*sitr)->getNumTargets(); xyx++)
							{
								sx = (*sitr)->getNextX();
								sy = (*sitr)->getNextY();
								mapList[sx][sy]->toggleActive();
							}
						}
					}
				}
				break;
			}
		}
		(*oitr)->advanceCommand();
		centerX = robotX;
		centerY = robotY;
	}
}

bool gameBoard::robotAtEndSquare()
{
	// find the end square
	if (mapList[robotX][robotY]->getType() == TEnd)
		return true;
	else
		return false;
}
void gameBoard::teleporterCheck()
{
	vector<Oteleport*>::iterator titr = teleportList.begin();
	// see if we're standing in a teleporter square
	if(mapList[robotX][robotY]->getType() == TTeleport)
	{
		// if we are, lets find the teleporter in the list
		for(;titr < teleportList.end(); titr++)
		{
			if((((*titr)->getXPos()) == robotX) && (((*titr)->getYPos()) == robotY))
			{
				// now lets teleport!
				robotX = (*titr)->getTargetX();
				robotY = (*titr)->getTargetY();
				keepRobotOnTheBoard();
			}
		}
	}
}

void gameBoard::keepRobotOnTheBoard()
{
	if(robotX < 0)			robotX = 0;
	if(robotX >= Width)		robotX = Width-1;
	if(robotY < 0)			robotY = 0;
	if(robotY >= Height)	robotY = Height-1;
}

bool gameBoard::interfaceHasFiredExecuteOrder(std::vector<logicBlock*> executionList)
{
	// Find the robot
	std::vector<object*>::iterator oitr = objectList.begin();

	for(;oitr != objectList.end(); oitr++)
	{
		if((*oitr)->getType() == ORobot)
		{
			(*oitr)->reset();
			robotX = robotStartX;
			robotY = robotStartY;
			
			// Add every element of executionList from the interface to
			// the robot's instruction list.
			std::vector<logicBlock*>::iterator exeItr = executionList.begin();
			(*oitr)->clearInstructions();
			for(; exeItr < executionList.end()-1; exeItr++)
			{
				(*oitr)->addCommand(*exeItr);
				(*oitr)->coreDump();
			}
		}
	}
	// Execute the instructions
	for(int x = 0; x < (int)executionList.size() - 1; x++)
	{
		startTime = clock();
		timer = clock();
		while(timer < (startTime + 1000) )
		{		
			timer = clock();
			// do nothing pause
		}
		
		//***********************************************************************
		//***********************************************************************
		//***********************************************************************
		//*** this block of code here is just for the time being, it is
		//*** implemented VERY VERY badly and should not be done here
		//*** this should be done elsewhere via a timer
		processRobot();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->draw();
		glutSwapBuffers();
		//***********************************************************************
		//***********************************************************************
		//***********************************************************************
	}
	return true;
}

bool gameBoard::RCcanRobotLeaveSquare(int direction)
{
	// we just need to know information about our own square
	tileTypeEnum robotSquare = mapList[robotX][robotY]->getType();
	bool robotSquareActive = mapList[robotX][robotY]->getIsActive();

	// squares that can be left
	if( (robotSquare == TDefault) ||
		(robotSquare == TRaised1) ||
		(robotSquare == TRaised2) ||
		(robotSquare == TRaised3) ||
		(robotSquare == TRaised4) ||
		(robotSquare == TElectric) ||
		((robotSquare == TElectricTL) && (direction != 3)) ||
		((robotSquare == TElectricTR) && (direction != 0)) || 
		((robotSquare == TElectricBL) && (direction != 2)) ||
		((robotSquare == TElectricBR) && (direction != 1)) ||
		(robotSquare == TIce) ||
		(robotSquare == TWater) ||
		(robotSquare == TSwitchTL) ||
		(robotSquare == TSwitchTR) ||
		(robotSquare == TSwitchBL) ||
		(robotSquare == TSwitchBR) ||
		(robotSquare == TSwitch) ||
		(robotSquare == TProgramTL) ||
		(robotSquare == TProgramTR) ||
		(robotSquare == TProgramBL) ||
		(robotSquare == TProgramBR) ||
		(robotSquare == TProgram) ||
		((robotSquare == TBreakableTL) && (!robotSquareActive)) ||
		((robotSquare == TBreakableTR) && (!robotSquareActive)) ||
		((robotSquare == TBreakableBL) && (!robotSquareActive)) ||
		((robotSquare == TBreakableBR) && (!robotSquareActive)) ||
		(robotSquare == TSolid) ||
		(robotSquare == TStart) ||
		(robotSquare == TEnd) ||
		( (robotSquare == TDoorTL) && (((direction == 3) && (!robotSquareActive)) || (direction != 3))) ||
		( (robotSquare == TDoorTR) && (((direction == 0) && (!robotSquareActive)) || (direction != 0))) ||
		( (robotSquare == TDoorBL) && (((direction == 2) && (!robotSquareActive)) || (direction != 2))) ||
		( (robotSquare == TDoorBR) && (((direction == 1) && (!robotSquareActive)) || (direction != 1))))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool gameBoard::RCwillRobotDieTryingToLeaveSquare(int direction)
{
	tileTypeEnum robotSquare = mapList[robotX][robotY]->getType();
	bool robotSquareActive = mapList[robotX][robotY]->getIsActive();
	
	if (((robotSquare == TElectricTL) || 
		 (robotSquare == TElectricTR) ||
		 (robotSquare == TElectricBL) ||
		 (robotSquare == TElectricBR)) && robotSquareActive)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool gameBoard::RCcanRobotMoveForward(int direction, int destNum)
{
	int destX;
	int destY;
	tileTypeEnum robotSquare;
	tileTypeEnum destType;
	bool destActive;

	destX = robotX;
	destY = robotY;

	switch(direction)
	{
	case 0:// facing up/right (up on map)
		destY = robotY -destNum;					
		break;
	case 1:// facing down/right (right on map)
		destX = robotX +destNum;
		break;
	case 2:// facing down/left (down on map)
		destY = robotY + destNum;
		break;
	case 3:// facing up/left (left on map)
		destX = robotX -destNum;
		break;
	}

	destType = mapList[destX][destY]->getType();
	destActive = mapList[destX][destY]->getIsActive();

	robotSquare = mapList[robotX][robotY]->getType();
				
	if((destX >= 0) && (destX < Width) && (destY >= 0) && (destY < Height))
	{
		destType = (mapList[destX][destY]->getType()) ;
		destActive = (mapList[destX][destY]->getIsActive());
					
		if ( (destType == TDefault) || 
			 ((destType == TRaised1) && ((robotSquare == TRaised1) || (robotSquare == TRaised2) || (robotSquare == TRaised3) || (robotSquare == TRaised4))) ||
			 ((destType == TRaised2) && ((robotSquare == TRaised2) || (robotSquare == TRaised3) || (robotSquare == TRaised4))) ||
			 ((destType == TRaised3) && ((robotSquare == TRaised3) || (robotSquare == TRaised4)))||
			 ((destType == TRaised4) && ((robotSquare == TRaised4))) ||
			 (destType == TGap) || 
			 (destType == TElectric) ||
			 ((destType == TElectricTL) && (direction != 1)) || 
			 ((destType == TElectricTR) && (direction != 2)) ||
			 ((destType == TElectricBL) && (direction != 0)) ||
			 ((destType == TElectricBR) && (direction != 3)) ||
			 (destType == TIce) ||
			 (destType == TWater) ||
			 (destType == TSwitchTL) ||
			 (destType == TSwitchTR) ||
			 (destType == TSwitchBL) ||
			 (destType == TSwitchBR) ||
			 (destType == TSwitch) ||
			 (destType == TProgramTL) ||
			 (destType == TProgramTR) ||
			 (destType == TProgramBL) ||
			 (destType == TProgramBR) ||
			 (destType == TProgram) ||
			 (destType == TBreakableTL) ||
			 (destType == TBreakableTR) ||
			 (destType == TBreakableBL) ||
			 (destType == TBreakableBR) ||
			 ((destType == TBreakable) && (!destActive)) ||
			 ((destType == TSolid) && (!destActive)) ||
			 (destType == TStart) ||
			 (destType == TEnd) ||
			 ( (destType == TDoorTL) && (((direction == 0) || (direction == 2) || (direction == 3)) || !destActive)) ||
			 ( (destType == TDoorTR) && (((direction == 0) || (direction == 1) || (direction == 3)) || !destActive)) ||
			 ( (destType == TDoorBL) && (((direction == 1) || (direction == 2) || (direction == 3)) || !destActive)) ||
			 ( (destType == TDoorBR) && (((direction == 0) || (direction == 1) || (direction == 2)) || !destActive)) ||
			 (destType == TTeleport))
		{
			return true; 
		}
	}
	return false;
}
bool gameBoard::RCwillRobotDieStayingHere()
{
	// robot vars
	tileTypeEnum robotSquare;

	robotSquare = mapList[robotX][robotY]->getType();
	bool robotSquareActive = mapList[robotX][robotY]->getIsActive();

	// if robot square = a bad square, return true, otherwise return false
	if(	(robotSquare == TGap) ||
		(robotSquare == TWater) ||
		((robotSquare == TElectric) && (robotSquareActive == true))
		)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void gameBoard::RCmoveRobotForward()
{
	// first thing's first, lets find the robot
	std::vector<object*>::iterator oitr = objectList.begin();

	for(;oitr != objectList.end(); oitr++)
	{
		if((*oitr)->getType() == ORobot)
		{
			int robotDirection = (*oitr)->getDirection();

			// lets see if we are going to die attempting to leave this squiare
			if(this->RCwillRobotDieTryingToLeaveSquare(robotDirection))
			{
				// yes we died
				(*oitr)->setAlive(false);
				return;
			}

			// at this point we're still alive, now lets see if we can leave this square
			if(!this->RCcanRobotLeaveSquare(robotDirection))
			{
				// no we can't leave
				return;
			}

			// now lets see if we can move forward a square
			if(!this->RCcanRobotMoveForward(robotDirection, 1))
			{
				// no we can't move forward
				return;
			}

			// ok at this point we're not dead, we can leave our square, and we can move forward into the next square
			// lets move forward and see what happens!

			int destX = robotX;
			int destY = robotY;
			switch(robotDirection)
			{
			case 0:// facing up/right (up on map)
				destY = robotY -1;					
				break;
			case 1:// facing down/right (right on map)
				destX = robotX +1;
				break;
			case 2:// facing down/left (down on map)
				destY = robotY + 1;
				break;
			case 3:// facing up/left (left on map)
				destX = robotX -1;
				break;
			}
			if( (destX >=0) && (destX < Width) )
				robotX = destX;
			if( (destY >=0) && (destY < Height) )
				robotY = destY;

			(*oitr)->setXPos(robotX);
			(*oitr)->setYPos(robotY);
			
			// now that we've moved forward
			// lets see if we're about to die
			if(this->RCwillRobotDieStayingHere())
			{
				// yes we died
				(*oitr)->setAlive(true);
			}
		}				
	}
};

void gameBoard::RCjumpRobotForward()
{
	// first thing's first, lets find the robot
	std::vector<object*>::iterator oitr = objectList.begin();

	int distanceToMove = 2;

	for(;oitr != objectList.end(); oitr++)
	{
		if((*oitr)->getType() == ORobot)
		{
			int robotDirection = (*oitr)->getDirection();

			// lets see if we are going to die attempting to leave this squiare
			if(this->RCwillRobotDieTryingToLeaveSquare(robotDirection))
			{
				// yes we died
				(*oitr)->setAlive(false);
				return;
			}

			// at this point we're still alive, now lets see if we can leave this square
			if(!this->RCcanRobotLeaveSquare(robotDirection))
			{
				// no we can't leave
				return;
			}

			// now lets see if our jump can allow us to move forward from our square to the destination square
			if(!this->RCcanRobotMoveForward(robotDirection, 2))
			{
				// no we can't actually land at the destination square
				// lets check the one square infront of us and see if that can be landed on instead
				if(!this->RCcanRobotMoveForward(robotDirection, 1))
				{
					// no we can't even move forward 1 square, you're screwed, stay put
					return;
				}
				else
				{
					// at least we can move forward 1 square, lets set our distance to 1
					distanceToMove = 1;
				}
			}
			else
			{
				// wow we can jump two squares forward! amazing!
				// lets see if we can also clear the square infront of us
				if(!this->RCcanRobotMoveForward(robotDirection, 1))
				{
					// nope we cannot even move out of this square, we'll just have to stay put
					return;
				}
			}

			// ok at this point we're not dead, we can leave our square, and we can either jump 2 squares clearing the middle
			// square, or can jump forward 1 square, at least we're not dead.. yet
			// lets do the jump and see what happens!

			int destX = robotX;
			int destY = robotY;
			switch(robotDirection)
			{
			case 0:// facing up/right (up on map)
				destY = robotY - distanceToMove;					
				break;
			case 1:// facing down/right (right on map)
				destX = robotX + distanceToMove;
				break;
			case 2:// facing down/left (down on map)
				destY = robotY + distanceToMove;
				break;
			case 3:// facing up/left (left on map)
				destX = robotX - distanceToMove;
				break;
			}
			if( (destX >=0) && (destX < Width) )
				robotX = destX;
			if( (destY >=0) && (destY < Height) )
				robotY = destY;

			(*oitr)->setXPos(robotX);
			(*oitr)->setYPos(robotY);
			
			// now that we've moved forward
			// lets see if we're about to die
			if(this->RCwillRobotDieStayingHere())
			{
				// yes we died
				(*oitr)->setAlive(true);
			}
		}				
	}	
};

void gameBoard::RCcrouch()
{
}
void gameBoard::RCclimb()
{
}
void gameBoard::RCpunch()
{
}