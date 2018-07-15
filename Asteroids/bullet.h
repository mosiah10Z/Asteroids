#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"

/********************************************************************
* The Bullet Class. Derived from the FlyingObject class.
* contains methods pertaining to where the bullet should fly and initiated.
***************************************************************/
class Bullet : public FlyingObject
{
private:
	int count;

public:
	Bullet();
	void draw();
	virtual int getCount() { return count; }

	void fire(Point point, float angle, float x, float y);

};

// Put your Bullet class here




#endif /* bullet_h */
