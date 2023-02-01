#ifndef __MIDDLEGROUND_H__
#define __MIDDLEGROUND_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>


namespace Webfoot{
	class TestLevel{
	public:

		TestLevel();

		virtual void Init();
		virtual void Deinit();

		virtual void Update(unsigned int dt, Point2F catPosition);
		virtual void Draw();

		bool getHitDetection(){ return onGround; }

	protected:

		Point2F floorPos;
		Image* floor;

		bool onGround;

	};
}

#endif