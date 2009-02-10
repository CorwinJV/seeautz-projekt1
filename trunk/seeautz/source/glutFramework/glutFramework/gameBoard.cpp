#include "gameBoard.h"
#include <vector>
#include <fstream>
#include "objectManager.h"
#include "robot.h"
#include "objectEnums.h"

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

	screenEdge = 0.1;
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

	screenEdge = 0.1;
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

			drawTile((*itr)->getType(), drawAtX, drawAtY, scale);
			itr++;
		}
	}
	// draw the robot/objects
	// todo - this will eventually iterate through all the objects in the 
	// game board and draw them in the proper spot if they should be drawn at all
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

bool gameBoard::drawTile(tileTypeEnum nType, int txPos, int tyPos, double scale)
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

	toDraw->drawImage();

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
	robotImage = new oglTexture2D(); robotImage->loadImage("object/robotDefault.png", 50, 50);

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
			// if its a start spot, add the robot to the object list
			if(temptile == TStart)
			{
				OM->addNewObject<robot>(x, y, 1, ORobot);
				robotX = x;
				robotY = y;
			}
		}
	}

	mapfile.close();

	// find the start spot on the map and place the robot there

	// to add - reading t


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
//		vector<object*>::iterator itr = objectList.begin();
		
		// add move forward to the robot command queue

		
		break;
	// turn left
	case 'j':
	case 'J':
		break;
	// turn right
	case 'l':
	case 'L':
		break;
	// jump
	case 'u':
	case 'U':
		break;
	// crouch
	case 'k':
	case 'K':
		break;
	// activate
	case 'o':
	case 'O':
		break;
	// punch
	case 'p':
	case 'P':
		break;
	default:
		break;
	}

	if (scale > maxscale)	scale = maxscale;
	if (scale < minscale)	scale = minscale;

	verifyMapPosition();
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
	txPos += hw/1.5;
	//tyPos += hh;
	glClearColor(128, 255, 128, 0);
	oglTexture2D* toDraw;

	toDraw = robotImage;

	int tempdx = toDraw->dX;
	int tempdy = toDraw->dY;

	toDraw->dX *= scale;
	toDraw->dY *= scale;

	toDraw->mX = txPos;
	toDraw->mY = tyPos;

	toDraw->drawImage();

	toDraw->dX = tempdx;
	toDraw->dY = tempdy;

	return true;
}