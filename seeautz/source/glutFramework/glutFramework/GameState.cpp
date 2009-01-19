#include "GameState.h"

GameState::GameState()	// constructor
{
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
    // The only important line for managing objects
   // myObjManager.Update((float)gameTime.ElapsedGameTime.TotalSeconds);
    //myObjManager.CollectGarbage();

	return true;
	// if something horribly bad happens return false
}

bool GameState::Draw()//GameTime gameTime)
{
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