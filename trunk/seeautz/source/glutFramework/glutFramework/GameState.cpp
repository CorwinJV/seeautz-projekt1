#include "GameState.h"
#include "GameStateManager.h"

GameState::GameState()	// constructor
{
	stateID = 0;
    //graphics = new GraphicsDeviceManager(this);
    //content = new ContentManager(Services);
    // graphics.IsFullScreen = true;

    initialize();
}

GameState::GameState(GameStateManager &Parent, int newID)	// constructor
{
	GSM = &Parent;
	stateID = newID;
	myMenu = NULL;

	// logo image
	logoImage = new oglTexture2D;
	logoImage->loadImage("logoprojekt1narrow.png", 1024, 150);
	logoImage->mX = 0;
	logoImage->mY = 50;

	// background image
	backgroundImage = new oglTexture2D;
	backgroundImage->loadImage("CommandList.png",800, 500);
	backgroundImage->mX = 1024/2 - backgroundImage->dX/2;
	backgroundImage->mY = (768-logoImage->dY)/2 - backgroundImage->dY/2 + logoImage->dY;
    //graphics = new GraphicsDeviceManager(this);
    //content = new ContentManager(Services);
    // graphics.IsFullScreen = true;

    initialize();
}

GameState::~GameState()
{

}

bool GameState::initialize()
{
	// debug options
	displayCollisionDebug = true;

    // Initialize status
    currentStatus = Active;
	startTime = clock();

    // Initialize Spritebatch to render with
    //batchRender = new SpriteBatch(graphics.GraphicsDevice);

    // Initialize camera
    //camera = new Camera2D(batchRender, graphics.GraphicsDevice);

    // Initialize object manager
    //myObjManager = new GameObjectManager();


    // TODO: Create objects and add them to the object manager

    // get screen size
    //screenHeight = graphics.PreferredBackBufferHeight;
    //screenWidth = graphics.PreferredBackBufferWidth;

	return true;
	// if something horribly bad happens return false
}

bool GameState::Update()//GameTime gameTime)
{
	if(myMenu != NULL)
		myMenu->Update();
	
	// The only important line for managing objects
   // myObjManager.Update((float)gameTime.ElapsedGameTime.TotalSeconds);
    //myObjManager.CollectGarbage();

	return true;
	// if something horribly bad happens return false
}

bool GameState::Draw()//GameTime gameTime)
{
	if(myMenu != NULL)
		myMenu->Draw();
 
	//graphics.GraphicsDevice.Clear(Color.Black);

    //batchRender.Begin();
    /*foreach (BasicObject tempObject in myObjManager.ObjectList)
    {
        camera.DrawObject(tempObject);
        if (displayCollisionDebug)
            camera.DrawCollisionBoxes(tempObject);
    }*/
    //batchRender.End();

	return true;
	// if something horribly bad happens return false
}

bool GameState::setStatus(State newStatus)
{
	currentStatus = newStatus;
	return true;
}

State GameState::getStatus()
{
	return currentStatus;
}

int GameState::getID()
{
	return stateID;
}

void GameState::processMouse(int x, int y)
{

}

void GameState::processMouseClick(int button, int state, int x, int y)
{
	
}

void GameState::keyboardInput(unsigned char c, int x, int y)
{
	
	
}