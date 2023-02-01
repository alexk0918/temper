#ifndef __MAINGAME_H__
#define __MAINGAME_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include "Cats.h"
#include "MiddleGround.h"
#include <Array>

namespace Webfoot {

	class Cats;
	class TestLevel;
	class Sound;
//==============================================================================

class MainGame : public MenuState
{
public:
   typedef MenuState Inherited;

   MainGame();
   virtual ~MainGame() {};
   
   virtual void Init();
   virtual void Deinit();

   /// Call this on every frame to update the positions.
   virtual void Update();
   /// Call this on every frame to draw the images.
   virtual void Draw();
   ///void DrawPursiut(Point2F p1, Point2F p2, Point2F p3, Point2F p4, unsigned int progress);
   static MainGame instance;

protected:
   /// Returns the name of the GUI layer
   virtual const char* GUILayerNameGet();

   Cats* player;
   Image* background;
   TestLevel* level0;
   Sound* sounds[6];
   bool played;
   bool played2;


   /// The ball that bounces around the screen.
};

MainGame* const theMainGame = &MainGame::instance;

//==============================================================================
//==============================================================================

} //namespace Webfoot {

#endif //#ifndef __MAINGAME_H__
