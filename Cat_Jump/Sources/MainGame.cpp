#include "Frog.h"
#include "MainGame.h"
#include "MainUpdate.h"
#include "FrogMath.h"
#include <Array>

const char* Sounds[] =
{
	"Sounds/Destroy",
	"Sounds/Hit",
	"Sounds/Music",
	"Sounds/Shoot",
	"Sounds/Slowdown",
	"Sounds/Thrust"
};

enum  Sounds
{
	SOUND_DESTROY,
	SOUND_HIT,
	SOUND_MUSIC,
	SOUND_SHOOT,
	SOUND_SLOWDOWN,
	SOUND_THRUST,
	SOUND_COUNT
};
using namespace Webfoot;

MainGame MainGame::instance;

//==============================================================================

/// Main GUI
#define GUI_LAYER_NAME "MainGame"

//-----------------------------------------------------------------------------

MainGame::MainGame()
{
	player = NULL;
	background = NULL;
	level0 = NULL;
}

//-----------------------------------------------------------------------------

void MainGame::Init()
{
   Inherited::Init();

   player = frog_new Cats();
   player->Init();

   level0 = frog_new TestLevel();
   level0->Init();
   
   background = theImages->Load("background");
   for (int i = 0; i < SOUND_COUNT; i++){ sounds[i] = theSounds->Load(Sounds[i]); }
   played = false;
   played2 = false;
}

//-----------------------------------------------------------------------------

void MainGame::Deinit()
{
   // Deinitialize and delete the ball.
	if (player){
		player->Deinit();
		frog_delete player;
		player = NULL;
	}
	if (background){
		theImages->Unload(background);
		background = NULL;
	}
	if (level0){
		level0->Deinit();
		frog_delete level0;
		level0 = NULL;
	}

   Inherited::Deinit();
}

//-----------------------------------------------------------------------------

const char* MainGame::GUILayerNameGet()
{
   return GUI_LAYER_NAME;
}

//-----------------------------------------------------------------------------

void MainGame::Update()
{
   Inherited::Update();

   unsigned int dt = theClock->LoopDurationGet();

   level0->Update(dt, player->PositionGet());
   player->Update(dt, level0->getHitDetection());

   if (theKeyboard->KeyJustReleased(KEY_SPACE))
   {
	   sounds[SOUND_SHOOT]->Play(NULL, false);
   }

   if (player->VelocityGet().y > 15 && played == false)
   {
	   sounds[SOUND_DESTROY]->Play(NULL, false);
	   played2 = true;
   }

   if (player->PositionGet().x >= theScreen->SizeGet().x - 100 && played == false)
   {
	   sounds[SOUND_THRUST]->Play(NULL, false);
	   played = true;
   }

   // Return to the previous menu if the escape key is pressed.
   if(!theStates->StateChangeCheck() && theKeyboard->KeyJustPressed(KEY_ESCAPE))
   {
      theMainGame->StateChangeTransitionBegin(true);
      theStates->Pop();
   }
}

//-----------------------------------------------------------------------------

void MainGame::Draw()
{
	background->Draw();
	level0->Draw();
	player->Draw();
	
}

//==============================================================================
