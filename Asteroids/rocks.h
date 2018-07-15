#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#define _USE_MATH_DEFINES
//#define _USE_MATH_DEFINES #include <math.h>
#include <cmath> // used for sin, cos, and M_PI
#define BULLET_SPEED 1
#define M_PI 3.14159265359


#include "uiDraw.h"

// Define the following classes here:
//   Rock
#include "flyingObject.h"
/*******************************************************************************
* Bird, derived from flying object, which will serve as the parent of the
* lander, scaredbird, standardbird and toughbird.
*****************************************************************************/
class Rocks : public FlyingObject
{
private:
	
	int hitPoints;
public:
	//default constructor calling the non default constructor of FlyingO
	// sets where the bird will spawn, randomly on the left edge of the screen. 
	Rocks(float x, float y) : FlyingObject(x, y)//random(-195.0, 195.5), random(-195.0, 195.5))
	{
		/*if (point.getY() < 0.0)
		{
			velocity.setDy(random(0.0, 4.0));
			velocity.setDx(random(3.0, 6.0));
		}
		else
		{
			velocity.setDy(random(-4.0, 0.0));
			velocity.setDx(random(3.0, 6.0));
		}
		//velocity.setDy(2);
		//velocity.setDx(2);
		//point.setX(random(10.0,60.0));
		//point.setY(12.3);
		cerr << point.getX() << point.getY();
		cerr << "calling the rock constructor??";*/
	}

	//Rocks(Point point);
	virtual void draw() = 0;
	virtual int hit() { kill(); return 1; };
	virtual int getRadius() = 0;
	//virtual void advance() = 0;

};
//   BigRock



/*********************************************************************
* Class for the Standard bird, derived from the Bird class.
*********************************************************************/
class BigRock : public Rocks
{
private:
	float radius;
	int rotation;
public:
	BigRock() : radius(16.0), rotation(1), Rocks(random(-195.0, 195.5), random(-195.0, 195.5))
	{
		//point.setX(10.0);
		//cerr << "WRONG";
		int angle(random(0, 360));
		velocity.setDx(/*velocity.getDx()+ */ BULLET_SPEED * (-sin(M_PI / 180.0 * angle)));
		velocity.setDy(/*velocity.getDy() + */ BULLET_SPEED * (cos(M_PI / 180.0 * angle)));
	}

	//The draw function of the standard bird, which is set to 
	//virtual, to ensure that the correct function gets called. 
	virtual void draw() { drawLargeAsteroid(point, rotation+=BIG_ROCK_SPIN);  };
	virtual int hit() { kill(); return 1; };
	virtual int getRadius() { return radius; }


};
//   MediumRock

class MediumRock : public Rocks
{
private:
	float radius;
	int rotation;
public:
	MediumRock() : radius(8), rotation(1), Rocks(10.1, 15.3)//, //Rocks()
	{
		
		velocity.setDx(random(-1.0, 1.0));
		velocity.setDy(random(-1.0, 1.0));
	}
	
	MediumRock(float x, float y, float brockX, float brockY) : radius(8.0), rotation(1), Rocks(x, y)//, //Rocks()
	{
		//cerr << isAlive();
		velocity.setDx(brockX);
		velocity.setDy(brockY);
	}

	//The draw function of the standard bird, which is set to 
	//virtual, to ensure that the correct function gets called. 
	virtual void draw() { drawMediumAsteroid(point, rotation += MEDIUM_ROCK_SPIN); };
	virtual int hit() { kill(); return 1; };
	virtual int getRadius() { return radius; }


};
//   SmallRock

class SmallRock : public Rocks
{
private:
	float radius;
	int rotation;
public:
	SmallRock() : radius(4.0), rotation(1), Rocks(10.1, 15.3)// //Rocks()
	{
		velocity.setDx(random(-3.0, 3.0));
		velocity.setDy(random(-4.0, 4.0));
	}
	SmallRock(float x, float y, float brockX, float brockY) : radius(4.0), rotation(1), Rocks(x, y)//, //Rocks()
	{
		//cerr << isAlive();
		velocity.setDx(brockX);
		velocity.setDy(brockY);
	}
	
	virtual void draw() { drawSmallAsteroid(point, rotation += SMALL_ROCK_SPIN); };
	virtual int hit() { kill(); return 1; };
	virtual int getRadius() { return radius; }


};

#endif /* rocks_h */
