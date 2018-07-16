/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

 // These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
 
 float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
 {
	// find the maximum distance traveled
	float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
	dMax = max(dMax, abs(obj2.getVelocity().getDx()));
	dMax = max(dMax, abs(obj2.getVelocity().getDy()));
	dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

	float distMin = std::numeric_limits<float>::max();
	for (float i = 0.0; i <= dMax; i++)
	{
	   Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
					  obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
	   Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
					  obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

	   float xDiff = point1.getX() - point2.getX();
	   float yDiff = point1.getY() - point2.getY();

	   float distSquared = (xDiff * xDiff) +(yDiff * yDiff);

	   distMin = min(distMin, distSquared);
	}

	return sqrt(distMin);
 }
 

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"

#include <vector>
#include <list>
 //using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5


/***************************************
* GAME CONSTRUCTOR
***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br)//, ship(br)
	{
	// Set up the initial conditions of the game
	score = 0;

	// TODO: Set your bird pointer to a good initial value (e.g., NULL)
	ship = new Ship(br);

	for (int i = 0; i < 5; i++)
	{
		rocks.push_back(new BigRock);
	}
	//getClosestDistance(ship, rocks);
}

/****************************************
* GAME DESTRUCTOR
****************************************/
Game :: ~Game()
{
	// TODO: Check to see if there is currently a bird allocated
	//       and if so, delete it.
	if (ship != NULL)
		delete ship;
}

/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
***************************************/
void Game::advance()
{
	if (ship != NULL)
	{
		advanceBullets();
		advanceRocks();

		ship->advance();

		if (ship->getPoint().getX() < -200.0)
		{
			
			ship->setPoint(200.0, ship->getPoint().getY());

		}
		
		if (ship->getPoint().getX() > 200.0)
		{
			
			ship->setPoint(-200.0, ship->getPoint().getY());

		}
		if (ship->getPoint().getY() < -200.0)
		{
			
			ship->setPoint(ship->getPoint().getX(), 200.0);

		}
		
		if (ship->getPoint().getY() > 200.0)
		{
			
			ship->setPoint(ship->getPoint().getX(), -200.0);

		}

		handleCollisions();
		cleanUpZombies();
	}
}

/***************************************
* GAME :: ADVANCE BULLETS
* Go through each bullet and advance it.
***************************************/
void Game::advanceBullets()
{
	
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();

			// has the bullet been alive for 40 frames?
			if (bullets[i].getCount() > 40)
			{
				bullets[i].kill();
				//cerr << bullets[i].getCount();
			}
			
			//teleport to the right
			if (bullets[i].getPoint().getX() < -200.0)
			{
				
				bullets[i].setPoint(200.0, bullets[i].getPoint().getY());

			}
			//teleport to the left.
			if (bullets[i].getPoint().getX() > 200.0)
			{
				
				bullets[i].setPoint(-200.0, bullets[i].getPoint().getY());

			}
			
			//teleport at the top
			if (bullets[i].getPoint().getY() < -200.0)
			{
				
				bullets[i].setPoint(bullets[i].getPoint().getX(), 200.0);

			}
			//teleport to the bottom.
			if (bullets[i].getPoint().getY() > 200.0)
			{
				
				bullets[i].setPoint(bullets[i].getPoint().getX(), -200.0);

			}

			if (!isOnScreen(bullets[i].getPoint()))
			{
				// the bullet has left the screen
				//bullets[i].kill();
			}
		}// watch for this bracket!!!!!!
		
	}
}

/**************************************************************************
* GAME :: ADVANCE BIRD
*
* 1. If there is no bird, create one with some probability
* 2. If there is a bird, and it's alive, advance it
* 3. Check if the bird has gone of the screen, and if so, "kill" it
**************************************************************************/
void Game::advanceRocks()
{
	
	for (list<Rocks*>::iterator it = rocks.begin(); it != rocks.end(); it++){
	
		
		(*it)->advance();
		if ((*it)->getPoint().getX() < -220.0)
		{
			
			(*it)->setPoint(220.0, (*it)->getPoint().getY());

		}
		
		if ((*it)->getPoint().getX() > 220.0)
		{
			
			(*it)->setPoint(-220.0, (*it)->getPoint().getY());

		}
		if ((*it)->getPoint().getY() < -220.0)
		{
			
			(*it)->setPoint((*it)->getPoint().getX(), 220.0);

		}
		
		if ((*it)->getPoint().getY() > 220.0)
		{
			
			(*it)->setPoint((*it)->getPoint().getX(), -220.0);

		}
		
	}
//
}

/**************************************************************************
* GAME :: CREATE BIRD
* Create a bird of a random type according to the rules of the game.
**************************************************************************/
Rocks* Game::createRocks()
{
	Rocks* newRocks = NULL;
	//newRocks = new BigRock;

	// TODO: Fill this in
	if (random(1, 4) == 1)
		newRocks = new BigRock;
	else if (random(1, 4) == 2)
		newRocks = new SmallRock;
	else if (random(1, 4) == 3)
		newRocks = new MediumRock;
	else if (random(1, 6) > 3)
		newRocks = new BigRock;

	return newRocks;
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
* Check for a collision between a bird and a bullet.
**************************************************************************/
void Game::handleCollisions()
{
	for (list<Rocks*>::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		//if (getClosestDistance(ship, (*(*it))));
		//ship->kill();
		

		if (ship->isAlive())
		{
			//if (fabs(ship->getPoint().getX() - (*it)->getPoint().getX()) < ((*it)->getRadius() + 10)
			//	&& fabs(ship->getPoint().getY() - (*it)->getPoint().getY()) < ((*it)->getRadius() + 10))
				if (getClosestDistance(*ship, (*(*it))) < ((*it)->getRadius() + 10))
			{
				//cerr << getClosestDistance(ship, (*(*it)));
				(*it)->kill();
				//uncomment bellow to kill the ship on collission
				ship->kill();
				
				//ship = NULL;
				//delete ship;

			}


			// now check for a hit (if it is close enough to any live bullets)
			for (int i = 0; i < bullets.size(); i++)
			{


				if (bullets[i].isAlive())
				{
					// this bullet is alive, see if its too close

					// check if the bird is at this point (in case it was hit)
					if ((*it) != NULL && (*it)->isAlive())
					{
						// BTW, this logic could be more sophisiticated, but this will
						// get the job done for now...
						//if (fabs(bullets[i].getPoint().getX() - (*it)->getPoint().getX()) < (*it)->getRadius()
							//&& fabs(bullets[i].getPoint().getY() - (*it)->getPoint().getY()) < (*it)->getRadius())
						if (getClosestDistance(bullets[i], (*(*it))) < (*it)->getRadius())
						{
							//we have a hit! print the closest distance 
							cerr << getClosestDistance(bullets[i], (*(*it))) << endl;
							// hit the bird
							int points = (*it)->hit();
							score += points;
							(*it)->kill();

							//cerr << (*it)->isAlive(); clean up


							// the bullet is dead as well
							bullets[i].kill();
						}
					}
				} // if bullet is alive

			} // for bullets
		}
	}
}

/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets out of the list, deallocate bird)
**************************************************************************/
void Game::cleanUpZombies()
{
	for (list<Rocks*>::iterator it = rocks.begin(); it != rocks.end();/**/ )
	{
		if ((*it)->isAlive() == 0 && (*it)->getRadius() == 16)
		{
			rocks.push_back(new MediumRock((*it)->getPoint().getX(), 
				(*it)->getPoint().getY(), 
				(*it)->getVelocity().getDx(), 
				1.0 + (*it)->getVelocity().getDy()));
			rocks.push_back(new MediumRock((*it)->getPoint().getX(), 
				(*it)->getPoint().getY(), 
				(*it)->getVelocity().getDx(), -1.0 + 
				(*it)->getVelocity().getDy()));
			rocks.push_back(new SmallRock((*it)->getPoint().getX(), 
				(*it)->getPoint().getY(), 
				(*it)->getVelocity().getDx() + 2.0, 
				(*it)->getVelocity().getDy()));
			delete *it;
			it = rocks.erase(it);

		}
		
		else if ((*it)->isAlive() == 0 && (*it)->getRadius() == 8)
		{
			rocks.push_back(new SmallRock((*it)->getPoint().getX(), 
				(*it)->getPoint().getY(), 
				(*it)->getVelocity().getDx() + 3.0, 
				(*it)->getVelocity().getDy()));
			rocks.push_back(new SmallRock((*it)->getPoint().getX(), 
				(*it)->getPoint().getY(), 
				(*it)->getVelocity().getDx() - 3.0, 
				(*it)->getVelocity().getDy()));
			delete *it;
			it = rocks.erase(it);
		}
		else if ((*it)->isAlive() == 0 && (*it)->getRadius() == 4)
		{
			delete *it;
			it = rocks.erase(it);
		}
		else
			++it;
	}
	
	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!bullet.isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...


			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}

}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{
	if (ship != NULL && ship->isAlive())
	{
		// Change the direction of the rifle
		if (ui.isLeft())
		{
			ship->rotateLeft();
		}

		if (ui.isRight())
		{
			ship->rotateRight();
		}
		if (ui.isUp())
		{
			ship->thrust();
		}
		if (ui.isDown())
		{
			ship->aboutFace();
		}

		// Check for "Spacebar
		if (ui.isSpace())
		{
			//added recoil due to the power of the gun
			//rifle.moveRight();
			if (ship->isAlive())
			{

				Bullet newBullet;
				newBullet.fire(ship->getPoint(), ship->getAngle(), ship->getVelocity().getDx(), ship->getVelocity().getDy());
			//	Bullet newBullet2;
			//	newBullet2.fire(ship->getPoint(), ship->getAngle() + 4, ship->getVelocity().getDx(), ship->getVelocity().getDy());
			//	Bullet newBullet3;
			//	newBullet3.fire(ship->getPoint(), ship->getAngle() - 4, ship->getVelocity().getDx(), ship->getVelocity().getDy());

				bullets.push_back(newBullet);
			//	bullets.push_back(newBullet2);
			//	bullets.push_back(newBullet3);
			}

		}
	}
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{
	// draw the bird

	// TODO: Check if you have a valid bird and if it's alive
	// then call it's draw method
	for (list<Rocks*>::iterator it = rocks.begin(); it != rocks.end(); it++)
	{
		
		(*it)->draw(); //cerr << "draw my rock";
		
	}

	// draw the ship
	ship->draw();

	// draw the bullets, if they are alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}

	// Put the score on the screen
	//Point scoreLocation;
	//scoreLocation.setX(topLeft.getX() + 5);
	//scoreLocation.setY(topLeft.getY() - 5);

	//drawNumber(scoreLocation, score);

}