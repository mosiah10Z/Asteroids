#include "flyingObject.h"


// Put your FlyingObjectbject method bodies here
/********************************************************************
* The default constructor of the FlyingObject class. sets alive to 1.
***************************************************************/
FlyingObject::FlyingObject() : alive(1)
{
	return;
}

/********************************************************************
* return the point of the flying object.
***************************************************************/
Point FlyingObject::getPoint() const
{
	return point;
}

/********************************************************************
* gets velocity of the flying object.
***************************************************************/
Velocity FlyingObject::getVelocity() const
{
	return velocity;
}

/********************************************************************
* returns whether the state of the flying object.
***************************************************************/
bool FlyingObject::isAlive()
{
	return alive;
}

/********************************************************************
* sets the value of alive to zero.
***************************************************************/
void FlyingObject::kill()
{
	alive = false;

}

/********************************************************************
* advances the flying object according to its point and velocity.
***************************************************************/
void FlyingObject::advance()
{
	point.addX(velocity.getDx());
	point.addY(velocity.getDy());


}

/********************************************************************
* Sets the x and y coordinate of the flying object.
***************************************************************/
void FlyingObject::setPoint(float x, float y)
{
	point.setX(x);
	point.setY(y);
}