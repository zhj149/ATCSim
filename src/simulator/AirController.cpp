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
	f->setLanding(true);
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;

			Position pos0(5000.0, 0.0, 200.0);
			Position pos1(3500.0, 0.0, 100.0);
			Position pos2(1500.0, 0.0, 50.0);
			Position pos3(200.0, 0.0, 25.0);
			Position pos4(-750.0, 0.0, 25.0);
			Position posaec(15000, -10000.0, 500.0);
			Position posaoc(15000.0, 10000.0, 500.0);
			Position posaee(15000, -15000.0, 500.0);
			Position posaoe(15000.0, 15000.0, 500.0);
			Position poswe1(10000.0, -7500.0, 300.0);
			Position poswe2(5000.0, -5000.0, 300.0);
			Position poswe3(1500.0, -10000.0, 300.0);
			Position poswe4(8000.0, -12500.0, 300.0);
			Position poswo1(10000.0, 7500.0, 300.0);
			Position poswo2(5000.0, 5000.0, 300.0);
			Position poswo3(1500.0, 10000.0, 300.0);
			Position poswo4(8000.0, 12500.0, 300.0);

			Route raec, raoc, rwe1, rwe2, rwe3, rwe4, rwo1, rwo2, rwo3, rwo4, r0, r1, r2, r3, r4;

			r0.pos = pos0;
			r0.speed = 600.0;
			r1.pos = pos1;
			r1.speed = 400.0;
			r2.pos = pos2;
			r2.speed = 200.0;
			r3.pos = pos3;
			r3.speed = 100.0;
			r4.pos = pos4;
			r4.speed = 15.0;

			raec.pos = posaec;
			raec.speed = 700.0;
			raoc.pos = posaoc;
			raoc.speed = 700.0;

			rwe1.pos = poswe1;
			rwe1.speed = 400.0;
			rwe2.pos = poswe2;
			rwe2.speed = 400.0;
			rwe3.pos = poswe3;
			rwe3.speed = 400.0;
			rwe4.pos = poswe4;
			rwe4.speed = 400.0;

			rwo1.pos = poswo1;
			rwo1.speed = 400.0;
			rwo2.pos = poswo2;
			rwo2.speed = 400.0;
			rwo3.pos = poswo3;
			rwo3.speed = 400.0;
			rwo4.pos = poswo4;
			rwo4.speed = 400.0;


			it = flights.begin();
			assignLanding(*it);

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty())
				{

					if((*it)->getPosition().get_y() < 0.0)
					{
						if((*it)->getLanding()){
							(*it)->getRoute()->push_back(r0);
							(*it)->getRoute()->push_back(r1);
							(*it)->getRoute()->push_back(r2);
							(*it)->getRoute()->push_back(r3);
							(*it)->getRoute()->push_back(r4);
						}else{
							(*it)->getRoute()->push_front(raec);
							(*it)->getRoute()->push_back(rwe1);
							(*it)->getRoute()->push_back(rwe2);
							(*it)->getRoute()->push_back(rwe3);
							(*it)->getRoute()->push_back(rwe4);
						}

				  }else{
						if((*it)->getLanding()){
							(*it)->getRoute()->push_back(r0);
							(*it)->getRoute()->push_back(r1);
							(*it)->getRoute()->push_back(r2);
							(*it)->getRoute()->push_back(r3);
							(*it)->getRoute()->push_back(r4);
						}else{
							(*it)->getRoute()->push_front(raoc);
							(*it)->getRoute()->push_back(rwo1);
							(*it)->getRoute()->push_back(rwo2);
							(*it)->getRoute()->push_back(rwo3);
							(*it)->getRoute()->push_back(rwo4);
						}


					}

				}
			}
}
