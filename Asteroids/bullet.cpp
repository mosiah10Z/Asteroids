#include "bullet.h"
#include "flyingObject.h"
#include "uiDraw.h"
#include "point.h"
#include "ship.h"
#define _USE_MATH_DEFINES
//#define _USE_MATH_DEFINES #include <math.h>
#include <cmath> // used for sin, cos, and M_PI
#define BULLET_SPEED 5.0
#define M_PI 3.14159265359

/********************************************************************
* Bullet constructor.Default.
***************************************************************/

Bullet::Bullet() : count(0)
{

}


/********************************************************************
* Bullet draw fucntion calls the draw dot.
***************************************************************/
void Bullet::draw()
{
	drawDot(getPoint());
	count++;

}

/********************************************************************
* Fire's the bullets by setting the point of origin to the point
* provided by the rifle, and then calculates the x and y coordinate
* of where the bullet should end up after every frame.
***************************************************************/
void Bullet::fire(Point point, float angle, float x, float y)
{

	setPoint(point.getX(), point.getY());
	//static float a; 
	//a += x;
	//static float b; 
	//b += y;

	velocity.setDx(/*velocity.getDx()+ */x+BULLET_SPEED * (-sin(M_PI / 180.0 * angle)));
	velocity.setDy(/*velocity.getDy() + */y+BULLET_SPEED * (cos(M_PI / 180.0 * angle)));


}

// Put your bullet methods here
