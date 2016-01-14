/*
 * AirController.cpp
 *
 *  Created on: 21/07/2014
 *      Author: paco
 *
 *  Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include "Common.h"
#include <list>

using namespace std;

AirController::AirController() {
	// TODO Auto-generated constructor stub
	int i, j;

	/* It initializes the height table */
	for (i=0; i<(NUMBER_OF_SECTORS); i++)
		for (j=0; j<(MAX_NUMBER_OF_HEIGHTS_BY_SECTOR); j++)
			free_Height [i][j] = true;


}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::assignWaiting(Flight *f)
{
	Route r0,r1,r2,r3,r4,r5;
	float x_w, y_w, z;
	int sector_Id;


	f->setLanding(false);
	f->getRoute()->clear();

	float x_avion = f->getPosition().get_x();
	float y_avion = f->getPosition().get_y();

	if (y_avion <= LINE1_2)      //SECTOR1
	{
		sector_Id = SECTOR_1;
		x_w = X_INIT_SECTOR1;
		y_w = Y_INIT_SECTOR1;

	}else if((LINE1_2 < y_avion)&&(y_avion < LINE2_3)){    //SECTOR 2
		sector_Id = SECTOR_2;
		x_w = X_INIT_SECTOR2;
		y_w = Y_INIT_SECTOR2;

	}else if((LINE2_3 <= y_avion)&&(y_avion < LINE3_4)){   //SECTOR 3
		sector_Id = SECTOR_3;
		x_w = X_INIT_SECTOR3;
		y_w = Y_INIT_SECTOR3;

	}else if(y_avion >=LINE3_4){      //SECTOR 4
		sector_Id = SECTOR_4;
		x_w = X_INIT_SECTOR4;
		y_w = Y_INIT_SECTOR4;

	}//the last elseif


	/* It assigns a height if this has not been assigned yet */
	f->setSector(sector_Id);
	if (f->getAssignedHeight () == (int) 0)
		f->setAssignedHeight (giveFreeHeight (sector_Id));

	z = f->getAssignedHeight ();

	/* Way points assignments */
	Position pos0(x_w + MAX_WAIT_ROUTE_LENGTH, y_w, z);
	Position pos1(x_w + INTERMEDIAN_WAIT_ROUTE_LENGTH, y_w - MAX_WAIT_ROUTE_WIDE, z);
	Position pos2(x_w - INTERMEDIAN_WAIT_ROUTE_LENGTH, y_w - MAX_WAIT_ROUTE_WIDE, z);
	Position pos3(x_w - MAX_WAIT_ROUTE_LENGTH, y_w, z);
	Position pos4(x_w - INTERMEDIAN_WAIT_ROUTE_LENGTH, y_w + MAX_WAIT_ROUTE_WIDE, z);
	Position pos5(x_w + INTERMEDIAN_WAIT_ROUTE_LENGTH, y_w + MAX_WAIT_ROUTE_WIDE, z);

	r0.pos = pos0;
	r0.speed = 100.0;
	r1.pos = pos1;
	r2.pos = pos2;
	r3.pos = pos3;
	r4.pos = pos4;
	r5.pos = pos5;
	r1.speed = r2.speed = r3.speed = r4.speed = r5.speed = r0.speed;

	/* Routes to be followed until get runway */
	f->getRoute()->push_back(r5);
	f->getRoute()->push_front(r4);
	f->getRoute()->push_front(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
}

void
AirController::assignLanding(Flight *f)
{
	Route r0,r1,r2,r3,r4,r5;
	Position pos4, pos5;

	/* It frees the assigned height */
	if (f->getAssignedHeight() != (int) 0)
		releaseHeight(f->getSector(), f->getAssignedHeight());
	f->setLanding(true);
	f->getRoute()->clear();

//****************GENERAL LANDING ROUTE********************************************

	Position pos0(4500.0, 0.0, 100.0);
	Position pos1(1000.0, 0.0, 50.0);
	Position pos2(200.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	r0.pos = pos0;
	r0.speed = 150.0;
	r1.pos = pos1;
	r1.speed = 100.0;
	r2.pos = pos2;
	r2.speed = 50.0;
	r3.pos = pos3;
	r3.speed = 15.0;


	/* To assing the landing route, depending if the flight comes from left or right */
	if(f->getPosition().get_y()<=0)
	{
		Position pos5(8000, -5000.0, 100.0);
		Position pos4(6000, -2500.0, 100.0);

		r5.pos = pos5;
		r5.speed = 400.0;
		r4.pos = pos4;
		r4.speed = 200.0;

	}else {  /* f->getPosition().get_y()>0 */

		Position pos5(8000, 5000.0, 100.0);
		Position pos4(6000, 2500.0, 100.0);

		r5.pos = pos5;
		r5.speed = 400.0;
		r4.pos = pos4;
		r4.speed = 200.0;
	}

	/* Routes in the landing process */
	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
	f->getRoute()->push_front(r4);
	f->getRoute()->push_front(r5);

}


float
AirController::giveFreeHeight (int sector_Id)
{
	int j;
	int height_Id;
	float selected_Height;

	/* To detect if all heights has already been assigned */
	height_Id = MAX_NUMBER_OF_HEIGHTS_BY_SECTOR + 1;

	/* Look for a free height */
	for (j=0; j<(MAX_NUMBER_OF_HEIGHTS_BY_SECTOR); j++)
	{
		if (free_Height[sector_Id-1][j] == true)
		{
			height_Id = j;
			j = MAX_NUMBER_OF_HEIGHTS_BY_SECTOR;
		}
	}

	/* Once found, it returns this height. If not, it return the height by default */
	switch (height_Id)
	{
		case HEIGHT_ID_1:
			selected_Height = HEIGHT_1;
			free_Height[sector_Id-1][height_Id] = false;
			break;
		case HEIGHT_ID_2:
			selected_Height = HEIGHT_2;
			free_Height[sector_Id-1][height_Id] = false;
			break;
		case HEIGHT_ID_3:
			selected_Height = HEIGHT_3;
			free_Height[sector_Id-1][height_Id] = false;
			break;
		default:
			selected_Height = HEIGHT_BY_DEFAULT;
			break;

	}


	return ((float) selected_Height);
}


void
AirController::releaseHeight (int sector_Id, float height)
{
	switch ((int) height)
	{
		case (int) HEIGHT_1:
			free_Height[sector_Id-1][HEIGHT_ID_1] = true;
			break;
		case (int) HEIGHT_2:
			free_Height[sector_Id-1][HEIGHT_ID_2] = true;
			break;
		case (int) HEIGHT_3:
			free_Height[sector_Id-1][HEIGHT_ID_3] = true;
			break;
		default:
			break;
	}

	return;
}

void
AirController::checkFreeRunway(Flight *f, bool *routeState)
{
	float x_avion = f->getPosition().get_x();
	float y_avion = f->getPosition().get_y();

	if (f->getLanding()){

		if((x_avion>=0)&&(x_avion<=4000)&&(y_avion>=-100)&&(y_avion<=100))
		{
			*routeState=false;
			f->setLanding(false);

		}else{
			*routeState=true;
		}
	}
}

void
AirController::avoidStorm(Flight* theFlight, Storm* theStorm)
{
	float d_Now, d_Further;  // Current and further distance between the flight and the storm
	float x_Flight_Now, y_Flight_Now, x_Flight_Further, y_Flight_Further; // Current and further flight positions
	float x_Storm_Now, y_Storm_Now, x_Storm_Further, y_Storm_Further; // Current and further storm positions
	float new_Bearing;
	float new_x, new_y;
	float timing;
	Route avoid_storm_point;


	/* If the flight is currently landing, we suppose the storm wiil not affect this landing */
	if (theFlight->getLanding())
		return;

	/* If the distance between the flight and the storm is larger than the security distance, thers nothing to do */
	d_Now = theFlight->getPosition().distance(theStorm->getPosition());
	if (d_Now > (COLLISION_DISTANCE + SECURITY_DISTANCE_STORM + theStorm->getRadious()))
		return;

	/* It gets the current positions */
	x_Flight_Now = theFlight->getPosition().get_x();
	y_Flight_Now = theFlight->getPosition().get_y();
	x_Storm_Now = theStorm->getPosition().get_x();
	y_Storm_Now = theStorm->getPosition().get_y();

	/* It calculates the flight's further positions (a delta time after) */
	x_Flight_Further = x_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * cos(theFlight->getBearing());
	y_Flight_Further = y_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * sin(theFlight->getBearing());

	/* It calculates the storm's further positions (a delta time after) */
	x_Storm_Further = x_Storm_Now + theStorm->getSpeed() * APERIODOFTIME * cos(theStorm->getBearing());
	y_Storm_Further = y_Storm_Now + theStorm->getSpeed() * APERIODOFTIME * sin(theStorm->getBearing());

	/* It calculates the further distance between the flight and the storm */
	d_Further = sqrt (pow((x_Storm_Further - x_Flight_Further),2) + pow((y_Storm_Further - y_Flight_Further),2));

	if (d_Further > d_Now)    // The distance between the flight and the storm is increasing
		return;

	else      // We increase the flight bearing to detect if the distance will be larger or shorter
	{
		new_Bearing = normalizePi (theFlight->getBearing() + BEARING_VARIATION);
		x_Flight_Further = x_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * cos(new_Bearing);
		y_Flight_Further = y_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * sin(new_Bearing);

		/* It calculates the further distance between the flight and the storm */
		d_Further = sqrt (pow((x_Storm_Further - x_Flight_Further),2) + pow((y_Storm_Further - y_Flight_Further),2));

		if (d_Further <= d_Now)    // This new bearing decreases the distance so we must select the opposite
			new_Bearing = normalizePi (theFlight->getBearing() - BEARING_VARIATION);

		/* In order to calculate the new waypoints, we will consider the time to collision */
		timing = 3* d_Now / (theFlight->getSpeed() + theStorm->getSpeed());

		/* It calculates the waypoints to avoid the storm */
		new_x = x_Flight_Now + theFlight->getSpeed() * timing * cos(new_Bearing);
		new_y = y_Flight_Now + theFlight->getSpeed() * timing * sin(new_Bearing);

		/* It sets the new route */
		Position pos_avoid_storm(new_x, new_y, theFlight->getPosition().get_z());
		avoid_storm_point.pos = pos_avoid_storm;
		avoid_storm_point.speed = theFlight->getSpeed();

		//cout<<"X	"<<new_x<<"Y	"<<new_y<<"New bearing"<<new_Bearing<<endl;

		theFlight->getRoute()->push_front(avoid_storm_point);
	}

	return;
}



void
AirController::avoidFlightsCollisions (Flight* theFlight, Flight* theOtherFlight)
{

/*
	float d_Now, d_Further;  // Current and further distance between the flight and the storm
	float x_Flight_Now, y_Flight_Now, x_Flight_Further, y_Flight_Further; // Current and further flight positions
	float x_F2_Now, y_F2_Now, x_F2_Further, y_F2_Further; // Current and further F2 positions
	float new_Bearing;
	float new_x, new_y;
	float timing;
	Route avoid_F2_point;


	/* If the flight is currently landing, we suppose the F2 wiil not affect this landing
	if (theFlight->getLanding())
		return;

	/* If the distance between the flight and the F2 is larger than the security distance, thers nothing to do *
	d_Now = theFlight->getPosition().distance(theOtherFlight->getPosition());
	if (d_Now > (COLLISION_DISTANCE + SECURITY_DISTANCE))
		return;

	/* It gets the current positions *
	x_Flight_Now = theFlight->getPosition().get_x();
	y_Flight_Now = theFlight->getPosition().get_y();
	x_F2_Now = theOtherFlight->getPosition().get_x();
	y_F2_Now = theOtherFlight->getPosition().get_y();

	/* It calculates the flight's further positions (a delta time after) *
	x_Flight_Further = x_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * cos(theFlight->getBearing());
	y_Flight_Further = y_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * sin(theFlight->getBearing());

	/* It calculates the F2's further positions (a delta time after) *
	x_F2_Further = x_F2_Now + theOtherFlight->getSpeed() * APERIODOFTIME * cos(theOtherFlight->getBearing());
	y_F2_Further = y_F2_Now + theOtherFlight->getSpeed() * APERIODOFTIME * sin(theOtherFlight->getBearing());

	/* It calculates the further distance between the flight and the F2 *
	d_Further = sqrt (pow((x_F2_Further - x_Flight_Further),2) + pow((y_F2_Further - y_Flight_Further),2));

	if (d_Further > d_Now)    // The distance between the flight and the F2 is increasing
		return;

	else      // We increase the flight bearing to detect if the distance will be larger or shorter
	{
		new_Bearing = normalizePi (theFlight->getBearing() + BEARING_VARIATION);
		x_Flight_Further = x_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * cos(new_Bearing);
		y_Flight_Further = y_Flight_Now + theFlight->getSpeed() * APERIODOFTIME * sin(new_Bearing);

		/* It calculates the further distance between the flight and the F2 *
		d_Further = sqrt (pow((x_F2_Further - x_Flight_Further),2) + pow((y_F2_Further - y_Flight_Further),2));

		if (d_Further <= d_Now)    // This new bearing decreases the distance so we must select the opposite
			new_Bearing = normalizePi (theFlight->getBearing() - BEARING_VARIATION);

		/* In order to calculate the new waypoints, we will consider the time to collision *
		timing = 3* d_Now / (theFlight->getSpeed() + theOtherFlight->getSpeed());

		/* It calculates the waypoints to avoid the F2 *
		new_x = x_Flight_Now + theFlight->getSpeed() * timing * cos(new_Bearing);
		new_y = y_Flight_Now + theFlight->getSpeed() * timing * sin(new_Bearing);

		/* It sets the new route *
		Position pos_avoid_F2(new_x, new_y, theFlight->getPosition().get_z());
		avoid_F2_point.pos = pos_avoid_F2;
		avoid_F2_point.speed = theFlight->getSpeed();

		//cout<<"X	"<<new_x<<"Y	"<<new_y<<"New bearing"<<new_Bearing<<endl;

//		theFlight->getRoute()->push_front(avoid_F2_point);
		theFlight->setBearing(new_Bearing);
	}


	return;
*/

	float aux_Bearing;


	if (theFlight == theOtherFlight)
		return;

	/* It works if these flights are not landing */

	if ((theFlight->getLanding()==false) && (theOtherFlight->getLanding()==false))
		{
		if (theFlight->getPosition().distance(theOtherFlight->getPosition()) < COLLISION_DISTANCE+ SECURITY_DISTANCE)
			{
			// The reference Flight's route need to be modified in order to avoid the collision
			aux_Bearing = theFlight->getBearing() + BEARING_VARIATION;
			theFlight->setBearing(normalizePi(aux_Bearing));
			}
		}

	return;
}



void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	Storm *storm = Airport::getInstance()->getStorm();
	std::list<Flight*>::iterator it, it2;


	for(it = flights.begin(); it!=flights.end(); it++)
	{
		if((*it)->getRoute()->empty()){

			if (routeState==false){

				assignLanding((*it));

			}else { /* routeState==true */

				assignWaiting((*it));
			}
		}

		checkFreeRunway((*it), &routeState);

	/*To avoid storm*/

		if(storm != NULL)
		{
			if ((*it)->getStormAvoided())
			{

				if((*it)->getPosition().distance(storm->getPosition()) >= (COLLISION_DISTANCE + SECURITY_DISTANCE_STORM + storm->getRadious()))
				{
					(*it)->setStormAvoided(false);
				}

			}
			else
			{
				if((*it)->getPosition().distance(storm->getPosition()) <= (COLLISION_DISTANCE + SECURITY_DISTANCE_STORM + storm->getRadious()))
				{

					avoidStorm((*it), storm);
					(*it)->setStormAvoided(true);
				}
			}
		}
	}

	// To avoid no flights landing

	int counter = 0;

	for(it = flights.begin(); it!=flights.end(); it++)
	{
		if((*it)->getLanding())
			counter++;
	}


	if(counter == 0)
		routeState=false;


	/*It avoids the collision between two aircrafts */

/*
	for(it = flights.begin(); it!=flights.end(); it++)
	{
		for (it2 = flights.begin(); it2!=flights.end(); it2++)
		{
				if (!(*it)->getLanding())
			//	avoidFlightsCollisions (*it, *it2);
		}
	}
*/

/*
	for(it = flights.begin(); it!=flights.end(); it++)
	{
		if (!(*it)->getLanding())
		{
			it2=it;
			do
			{
				it2++;
				avoidFlightsCollisions (*it, *it2);
			}while(it2!=flights.end());

		}
	}*/


}
