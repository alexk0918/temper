#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>
#include "MiddleGround.h"

using namespace Webfoot;

TestLevel::TestLevel(){
	floor = NULL;
}

void TestLevel::Init(){
	floor = theImages->Load("Floor");

	floorPos = Point2F::Create(0, theScreen->SizeGet().y - 40);
	onGround = FALSE;
}

void TestLevel::Deinit(){
	if (floor){
		theImages->Unload(floor);
		floor = NULL;	
	}
}

void TestLevel::Update(unsigned int dt, Point2F catPosition){
	if (catPosition.y >= floorPos.y-20){
		onGround = TRUE;
	}
	else
	{
		onGround = FALSE;
	}
}

void  TestLevel::Draw(){
	floor->Draw(floorPos);
}