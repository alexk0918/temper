#ifndef __CATS_H__
#define __CATS_H__

#include "Frog.h"
#include "MenuState.h"
#include "FrogMath.h"
#include <Array>


namespace Webfoot{
	class Cats{
	public:
		Cats();
		virtual ~Cats() {};

		virtual void Init();
		virtual void Deinit();

		virtual void Update(unsigned int dt, bool grounded);
		virtual void Draw();

		Point2F PositionGet() { return position; }
		Point2F VelocityGet() { return velocity; }

	protected:

		bool inAir;
		

		Point2F gravity;
		Point2F position;
		Point2F jumpPower;
		Point2F velocity;


		Sprite* cat;
		Sprite* crouching;
		Sprite* jumping;
		Sprite* falling;
	};
}


#endif