#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "Cats.h"

using namespace Webfoot;

Cats::Cats(){
	cat = NULL;
	crouching = NULL;
	jumping = NULL;
	falling = NULL;
}

void Cats::Init(){
	//sprite stuff
	cat = frog_new Sprite();
	cat->Init("Sprites/Sprites", "Cat");

	crouching = frog_new Sprite();
	crouching->Init("Sprites/Sprites", "Crouch");

	jumping = frog_new Sprite();
	jumping->Init("Sprites/Sprites", "Jump");

	falling = frog_new Sprite();
	falling->Init("Sprites/Sprites", "Fall");

	// Cat be in the middle of the screen
	position = Point2F::Create(theScreen->SizeGet().x / 2, theScreen->SizeGet().y - 80);

	//movement I guess
	gravity.Set(0.0f, .5f);
	velocity.Set(0.0f, 0.0f);

	//i dont think i do anything with this... oops
	cat->PositionSet(position - (cat->SizeGet(1) / 2));
	crouching->PositionSet(position - (crouching->SizeGet(1) / 2));

	//sprite animation/visibility
	crouching->VisibleSet(FALSE);
	jumping->VisibleSet(FALSE);
	falling->VisibleSet(TRUE);
	falling->ScaleSet(Point2F::Create(2.0f, 2.0f));
	falling->PlayTypeSet(SpriteAnimation::PlayType(1));
	jumping->PlayTypeSet(SpriteAnimation::PlayType(1));

	//stuff that i dont know how to describe :D
	DebugPrintf("%7.2lf, %7.2lf \n", position.x, position.y);
	jumpPower.Set(0.0f, 0.0f);
	inAir = TRUE;
}

void Cats::Deinit(){
	//stuff goes bye bye
	if (cat){
		SmartDeinitDelete(cat);
	}
	if (crouching){
		SmartDeinitDelete(crouching);
	}
	if (falling){
		SmartDeinitDelete(falling);
	}
	if (jumping){
		SmartDeinitDelete(jumping);
	}
}

void Cats::Update(unsigned int dt, bool grounded){
	//update the sprites
	cat->Update(dt);
	crouching->Update(dt);
	falling->Update(dt);

	//make position move
	position += velocity;


	//Sprites
	cat->PositionSet(position);
	crouching->PositionSet(position);
	falling->PositionSet(position);
	jumping->PositionSet(position);

	//put at top of screen
	if (position.y >= theScreen->SizeGet().y){
		position.y = 0;
	}
	//bottom screen
	if (position.y <= 0){
		position.y = theScreen->SizeGet().y;
	}
	//checks the bool
	switch (grounded)
	{
	default:
		//should be falling
		inAir = TRUE;
		velocity += gravity;

		//not fall to fast
		if (velocity.y >= 20){
			velocity.y = 20;
		}
		//make it so if youre falling y would be positive
		if (gravity.y > 0){
			cat->VisibleSet(FALSE);
			crouching->VisibleSet(FALSE);
			falling->VisibleSet(TRUE);
		}
		break;
	case TRUE:
		//crouching getting ready to jump
		if (theKeyboard->KeyPressed(KEY_SPACE)){
			cat->VisibleSet(FALSE);
			crouching->VisibleSet(TRUE);
			//DebugPrintf("R: %6d, G: %6d, B: %6d", crouching->ColorGet().red, crouching->ColorGet().green, crouching->ColorGet().blue);
			jumpPower.y -= .5;
			jumpPower.x += .5;
			if (jumpPower.x > 5.0f){
				jumpPower.x = 5.0f;
			}
			//trys to make sure the power doesnt go to high... 20 is def to high but im lazy
			if (jumpPower.y > -0.5f){
				DebugPrintf("Max power hit");
				jumpPower.y = -0.5f;
			}
		}
		else
		{
			//makes sure they are set to 0 only once
			if (inAir == TRUE){
				jumpPower.Set(0, 0);
				velocity.Set(0, 0);
				inAir = FALSE;
			}
			//change sprites
			cat->VisibleSet(TRUE);
			crouching->VisibleSet(FALSE);
			falling->VisibleSet(FALSE);
		}
		//once space is released
		if (theKeyboard->KeyJustReleased(KEY_SPACE)){
			DebugPrintf("space unpressed"); 
			velocity = jumpPower;
			position.y -= .2;
		}
		//gravity.Set(0.0f, 0.0f);
	}
	if (position.x >= theScreen->SizeGet().x){
		position.x = 0;
	}
}

void Cats::Draw(){
	cat->Draw();
	crouching->Draw();
	jumping->Draw();
	falling->Draw();
}