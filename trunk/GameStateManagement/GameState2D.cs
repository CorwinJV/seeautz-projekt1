#region Using Statements
using System;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Storage;
using System.IO;
using System.Xml;
using System.Xml.Serialization;
using System.Text;
#endregion

namespace M3EngineTests
{
    public enum State
    {
        Active, // Updating
        Hidden, // Not Drawing
    }

    public class GameState2D : Microsoft.Xna.Framework.Game
    {
        // Current State
        State currentStatus;

        // Graphics Device / Content Manager
        GraphicsDeviceManager graphics;
        ContentManager content;

        // Object Manager
        GameObjectManager myObjManager;

        // 2D Camera
        SpriteBatch batchRender;
        Camera2D camera;

        // Debug Options
        bool displayCollisionDebug = true;
        int screenHeight;
        int screenWidth;

        public GameState2D()
        {
            graphics = new GraphicsDeviceManager(this);
            content = new ContentManager(Services);
            // graphics.IsFullScreen = true;

            initialize();
        }

        public void initialize()
        {
            // Initialize status
            currentStatus = State.Active;

            // Initialize Spritebatch to render with
            batchRender = new SpriteBatch(graphics.GraphicsDevice);

            // Initialize camera
            camera = new Camera2D(batchRender, graphics.GraphicsDevice);

            // Initialize object manager
            myObjManager = new GameObjectManager();


            // TODO: Create objects and add them to the object manager

            // get screen size
            screenHeight = graphics.PreferredBackBufferHeight;
            screenWidth = graphics.PreferredBackBufferWidth;
        }

        public void Update(GameTime gameTime)
        {
            // The only important line for managing objects
            myObjManager.Update((float)gameTime.ElapsedGameTime.TotalSeconds);
            myObjManager.CollectGarbage();
        }

        public void Draw(GameTime gameTime)
        {
            graphics.GraphicsDevice.Clear(Color.Black);

            batchRender.Begin();
            foreach (BasicObject tempObject in myObjManager.ObjectList)
            {
                camera.DrawObject(tempObject);
                if (displayCollisionDebug)
                    camera.DrawCollisionBoxes(tempObject);
            }
            batchRender.End();
        }
    }
}
