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
#include <list>

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void assignLanding(Flight* f)
{
	if((*f).getLanding() == false){
		(*f).getRoute()->clear();
	}
	f->setLanding(true);
}

bool checkStormBearing(Storm s, Route r)
{
	float x, y, ang;
	x = s.getPosition().get_x() - r.pos.get_x();
	y = s.getPosition().get_y() - r.pos.get_y();
	ang = atan2(y,x);

	if(fabs(s.getBearing()) < fabs(ang + 0.09) || fabs(s.getBearing()) > fabs(ang - 0.09))
	{
		return true;
	}
}

bool checkStormDist(Storm& s, Route r)
{
	float x, y, dist;
	x = s.getPosition().get_x() - r.pos.get_x();
	y = s.getPosition().get_y() - r.pos.get_y();
	dist = sqrt(x*x+y*y);

	if(dist < 3*s.getRadious())
	{
		return true;
	}
}

/*
void assignWaitingPath(Flight* f)
{
	if((*f)->getPosition().get_y() < 0.0)

}
*/
void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			Storm* storm = Airport::getInstance()->getStorm();

			Route rrefland, rrefwe, rrefwo;
			float refspeed = 0.0;

			Position posrefland(3000.0, 0.0, 100.0);
			Position posrefwe(10000.0, -10000.0, 100.0);
			Position posrefwo(10000.0, 10000.0, 100.0);

			rrefland.pos = posrefland;
			rrefland.speed = refspeed;
			rrefwe.pos = posrefwe;
			rrefwe.speed = refspeed;
			rrefwo.pos = posrefwo;
			rrefwo.speed = refspeed;


			assignLanding(*flights.begin());

			int ordereast = 0;
			int orderwest = 0;

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if(ordereast == 0 || orderwest == 0){
					(*it)->setOrd(0);
					ordereast++;
					orderwest++;
				}else if((*it)->getPosition().get_y() < 0.0){
					(*it)->setOrd(ordereast);
					ordereast++;
				}else{
					(*it)->setOrd(orderwest);
					orderwest++;
				}
			}

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				//std::cerr<<(*it)->getInclination()<<std::endl;
				if((*it)->getLanding()){
					if(storm != NULL && checkStormDist(*storm, rrefland) && checkStormBearing(*storm, rrefland) && storm->getPosition().get_y() < 0.0){
						(*it)->avoidFromEast();
					}else if(storm != NULL && checkStormDist(*storm, rrefland) && checkStormBearing(*storm, rrefland) && storm->getPosition().get_y() > 0.0){
						(*it)->avoidFromWest();
					}else{
						(*it)->proceedLanding();
					}
				}else{
					if((*it)->getPosition().get_y() < 0.0){
						if(storm != NULL && checkStormDist(*storm, rrefwe)){
							(*it)->proceedWaitingWest();
						}else{
							(*it)->proceedWaitingEast();
						}
					}else{
						if(storm != NULL && checkStormDist(*storm, rrefwo)){
							(*it)->proceedWaitingEast();
						}else{
							(*it)->proceedWaitingWest();
						}
					}
				}
			}
}
