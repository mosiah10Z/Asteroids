#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "point.h"
#include "flyingObject.h"



#define ANGLE_MAX 360000
#define ANGLE_MIN -36000
#define ANGLE_START 180

#define RIFLE_MOVE_AMOUNT 3

class Ship : public FlyingObject
{
private:
	//Point point;

	/**********************************************************
	* angle - The angle of the rifles in degrees.
	*  Assumes that straight right is 0 degrees and up is 90.
	**********************************************************/
	//float angle;
	bool canThrust;

public:
	Ship(const Point & point) : FlyingObject(0.0, 0.0), canThrust(0)//,// Point(point) 
	{ angle = ANGLE_START; 
	velocity.setDx(0.0);
		velocity.setDy(0.0);
	}

	/****************
	* Basic Getters
	****************/
	float getAngle() const { return angle; }
	Point getPoint() const { return point; }
	

	/*****************
	* Drawing
	*****************/
	void draw();

	/*****************
	* Movement
	*****************/
	void rotateLeft();
	void rotateRight();
	void thrust();
	void aboutFace();

};

// Put your Ship class here


#endif /* ship_h */
