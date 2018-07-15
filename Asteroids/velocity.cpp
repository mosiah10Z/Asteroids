#include "velocity.h"


// Put your velocity methods here
/***********************************************************************
* Source File:
*    Velocity
* Author:
*    Gil Mosiah Querubin
* Summary:
*    Everything we need to know about velocity.
************************************************************************/
#include "velocity.h"

/**********************************************************************
* default constructor for the velocity class.
**********************************************************************/
Velocity::Velocity() : dx(0), dy(0)
{

}

/**********************************************************************
* non default constructor for the velocity class.
**********************************************************************/
Velocity::Velocity(float newX, float newY)
{
	setDx(newX);
	setDy(newY);
}

/**********************************************************************
* returns the private member, dx.
**********************************************************************/
float Velocity::getDx()
{
	return dx;
}

/**********************************************************************
* returns the private member, dy.
**********************************************************************/
float  Velocity::getDy()
{
	return dy;
}

/**********************************************************************
* sets dx to the parameter.
**********************************************************************/
void Velocity::setDx(float newX)
{
	dx = newX;
}

/**********************************************************************
* sets dy to the parameter passed.
**********************************************************************/
void Velocity::setDy(float newY)
{
	dy = newY;
}