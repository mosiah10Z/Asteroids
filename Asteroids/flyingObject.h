#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"


#include <iostream>
using namespace std;
/********************************************************************
* The FlyingO Class.
* contains methods and member variables that are the same between
* Bird and Bullet.
***************************************************************/
class FlyingObject
{
protected:
	Point point;
	Velocity velocity;
	bool alive;
	float angle;
public:
	FlyingObject();
	FlyingObject(float x, float y) : alive(1) { setPoint(x, y);  };
	Point getPoint() const;
	void setPoint(float x, float y);
	Velocity getVelocity() const;
	bool isAlive();

	void kill();
	virtual void advance();

};


// Put your FlyingObject class here




#endif /* flyingObject_h */
