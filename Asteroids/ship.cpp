#include "ship.h"

// Put your ship methods here

#include "ship.h"
#include "point.h"
#include "uiDraw.h"

//#include <cassert>
//#define _USE_MATH_DEFINES
#define _USE_MATH_DEFINES 
#include <math.h>
#include <cmath> // used for sin, cos, and M_PI
#define SHIP_SPEED 0.5
//#define M_PI 3.14159265359
void Ship::draw() 
{
	//assert(angle >= ANGLE_MIN);
	//assert(angle <= ANGLE_MAX);
	
	//angle = ROTATE_AMOUNT;
	//angle -= ROTATE_AMOUNT;
	canThrust = 0;

	if (alive)
		drawShip(point, angle, canThrust);
	else
		return;

}

void Ship::rotateLeft()
{
	angle += ROTATE_AMOUNT;

	//if (angle < ANGLE_MIN)
	//{
		//angle = ANGLE_MIN;
	//}
	//cerr << "TURN left\n";
}


void Ship::rotateRight()
{
	angle -= ROTATE_AMOUNT;

	//if (angle > ANGLE_MAX)
	//{
		//angle = ANGLE_MAX;
	//}
	//cerr << "TURN right\n";
}

void Ship::thrust()
{
	if (alive)
	{
		canThrust = 1;
		drawShip(point, angle, canThrust);


		velocity.setDx(velocity.getDx() + SHIP_SPEED * (-sin(M_PI / 180.0 * angle)));
		velocity.setDy(velocity.getDy() + SHIP_SPEED * (cos(M_PI / 180.0 * angle)));
	}
	
}

void Ship::aboutFace()
{
	angle -= 15;
}
