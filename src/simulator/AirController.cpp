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

using namespace std;

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty())
				{
					Flight* f = *it;
					assignWaiting(f);
				}

			}

			int numberlandings = 0;

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getLanding()==true)
				{
					numberlandings++;
				}
			}


			if (numberlandings == 0)
		 {
			 bool landingassigned = false;
			 for(it = flights.begin(); it!=flights.end(); ++it)
 			{
 				if((*it)->getPosition().get_x()>3500 & landingassigned == false)
 				{
 					Flight* f = *it;
 					assignLanding(f);
					landingassigned = true;
 				}
			}


}
}

void AirController::assignWaiting(Flight* f)
{
	Position pos0_dcha(7500.0, 14000.0, 100.0);
	Position pos1_dcha(7500.0, 7000.0, 100.0);
	Position pos2_dcha(-7500.0, 7000.0, 100.0);
	Position pos3_dcha(-7500.0, 14000.0, 100.0);
	Position pos4_dcha(5500.0, 12000.0, 50.0);


	Position pos1_izq(7500.0, -14000.0, 100.0);
	Position pos0_izq(7500.0, -7000.0, 100.0);
	Position pos3_izq(-7500.0, -7000.0, 100.0);
	Position pos2_izq(-7500.0, -14000.0, 100.0);
	Position pos4_izq(5500.0, -9000.0, 50.0);




	Route r0_dcha, r1_dcha, r2_dcha, r3_dcha;
	Route r4_dcha, r5_dcha, r6_dcha, r7_dcha;
	Route r0_izq, r1_izq, r2_izq, r3_izq;
	Route r4_izq, r5_izq, r6_izq, r7_izq;


	r0_dcha.pos = pos0_dcha;
	r0_dcha.speed = 200.0;
	r1_dcha.pos = pos1_dcha;
	r1_dcha.speed = 100.0;
	r2_dcha.pos = pos2_dcha;
	r2_dcha.speed = 100.0;
	r3_dcha.pos = pos3_dcha;
	r3_dcha.speed = 100.0;

	r4_dcha.pos = pos4_dcha;
	r4_dcha.speed = 100.0;


	r0_izq.pos = pos0_izq;
	r0_izq.speed = 200.0;
	r1_izq.pos = pos1_izq;
	r1_izq.speed = 100.0;
	r2_izq.pos = pos2_izq;
	r2_izq.speed = 100.0;
	r3_izq.pos = pos3_izq;
	r3_izq.speed = 100.0;

	r4_izq.pos = pos4_izq;
	r4_izq.speed = 100.0;


	if(f->getPosition().get_y()<0)
	{
		if (f->getPosition().get_y()>-9000 & f->getPosition().get_x()>0) {
			f->getRoute()->clear();
			f->getRoute()->push_back(r3_izq);
			f->getRoute()->push_front(r2_izq);
			f->getRoute()->push_front(r1_izq);
			f->getRoute()->push_front(r0_izq);
		}if (f->getPosition().get_x()<0) {
			f->getRoute()->clear();
			f->getRoute()->push_back(r3_izq);
			f->getRoute()->push_front(r2_izq);
			f->getRoute()->push_front(r4_izq);
		}else{
			f->getRoute()->clear();
			f->getRoute()->push_back(r3_izq);
			f->getRoute()->push_front(r2_izq);
			f->getRoute()->push_front(r1_izq);
		}
	}

	if(f->getPosition().get_y()>0)
	{
		if (f->getPosition().get_y()>7000 & f->getPosition().get_x()>0) {
			f->getRoute()->clear();
			f->getRoute()->push_back(r3_dcha);
			f->getRoute()->push_front(r2_dcha);
			f->getRoute()->push_front(r1_dcha);
			f->getRoute()->push_front(r0_dcha);
		}	if (f->getPosition().get_x()<0) {
			f->getRoute()->clear();
				f->getRoute()->push_back(r3_dcha);
				f->getRoute()->push_front(r2_dcha);
				f->getRoute()->push_front(r4_dcha);
			}else{
				f->getRoute()->clear();
			f->getRoute()->push_back(r3_dcha);
			f->getRoute()->push_front(r2_dcha);
			f->getRoute()->push_front(r1_dcha);
		}
	}
}

void AirController::assignLanding(Flight* f)
{
	f->setLanding(true);
	f->getRoute()->clear();

	Position pos0(7000.0, 0.0, 50.0);
	Position pos1(3000.0, 0.0, 50.0);
	Position pos2(1500.0, 0.0, 50.0);
	Position pos3(200.0, 0.0, 25.0);
	Position pos4(-750.0, 0.0, 25.0);

	Route r0, r1, r2, r3, r4;

	r0.pos = pos0;
	r0.speed = 500.0;
	r1.pos = pos1;
	r1.speed = 300.0;
	r2.pos = pos2;
	r2.speed = 100.0;
	r3.pos = pos3;
	r3.speed = 19.0;
	r4.pos = pos4;
	r4.speed = 15.0;

	f->getRoute()->push_back(r4);
	f->getRoute()->push_front(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);

}
