#ifndef VELOCITY_H
#define VELOCITY_H


// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project


/*******************************************
* The velocity of the flyingo
*
********************************************/
class Velocity
{
private:
	float dx;
	float dy;

public:
	Velocity();
	Velocity(float newX, float newY);
	float getDx();
	float getDy();
	void setDx(float newX);
	void setDy(float newY);
};

#endif /* velocity_h */
