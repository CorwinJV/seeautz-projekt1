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
    /// <summary>
    /// This is the class which manages all game states. Game states can be menus or games.
    /// Game states derived from GameState2D 
    /// </summary>
    public class GameStateManager : Microsoft.Xna.Framework.DrawableGameComponent
    {
        // Members
        List<GameState2D> stateList;


        public GameStateManager(Game game)
            : base(game)
        {

            stateList = new List<GameState2D>();
        }


        /// <summary>
        /// Allows the game component to perform any initialization it needs to before starting
        /// to run.  This is where it can query for any required services and load content.
        /// </summary>
        public override void Initialize()
        {
            // TODO: Add your initialization code here

            base.Initialize();
        }

        /// <summary>
        /// Adds a GameState2D to be managed.
        /// </summary>
        public void addGameState()
        {
            GameState2D newGS = new GameState2D();
            stateList.Add(newGS);
        }

        /// <summary>
        /// Removes a gamestate by index.
        /// </summary>
        /// <param name="index">Position in list to remove at</param>
        public void removeGameStateAt(int index)
        {
            stateList.RemoveAt(index);
        }

        /// <summary>
        /// Removes a gamestate.
        /// </summary>
        /// <param name="GameState2D">GameState to remove</param>
        public void removeGameState(GameState2D game)
        {
            stateList.Remove(game);
        }


        /// <summary>
        /// Allows the game component to update itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        public override void Update(GameTime gameTime)
        {
            // TODO: Add your update code here
            for (int i = 0; i < stateList.Count; i++)
            {
                stateList[i].Update(gameTime);
            }

            base.Update(gameTime);
        }

        public override void Draw(GameTime gameTime)
        {
            for (int i = 0; i < stateList.Count; i++)
            {
                stateList[i].Draw(gameTime);
            }

            base.Draw(gameTime);
        }
    }
}


