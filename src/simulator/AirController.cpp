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
#include "Flight.h"
#include "AirController.h"
#include "Airport.h"
#include "Storm.h"
#include "Position.h"
#include <list>

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}
void AirController::AssignWaiting(Flight *f, Route r1, Route r2, Route r3, Route r4)
{
	f->setLanding(false);
	f->getRoute()->clear();
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r3);
	f->getRoute()->push_front(r4);
}

void AirController::AssignLanding(Flight *f, Route p1, Route p2, Route p3,Route p4)
{
	f->setLanding(true);
	f->getRoute()->clear();
	f->getRoute()->push_back(p1);
	f->getRoute()->push_back(p2);
	f->getRoute()->push_back(p3);
	f->getRoute()->push_back(p4);
}


void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			std::list<Flight*>::iterator it2;

			Position pos0(3500.0, 0.0, 100.0);
			Position pos1(1500.0, 0.0, 50.0);
			Position pos2(200.0, 0.0, 25.0);
			Position pos3(-750.0, 0.0, 25.0);

			Position poscentral(13000.0,0.0,100.0);
			Position posderecha(11000.0,11000.0,100.0);
			Position posizq(11000.0,-11000.0,100.0);

			Position esperaizq_1(11000.0,0.0,100.0);
			Position esperaizq_2(9000.0, 2000.0,100.0);
			Position esperaizq_3(7000.0,0.0,100.0);
			Position esperaizq_4(9000.0,2000.0,100.0);

			Position esperader_1(9000.0,-4000.0,100.0);
			Position esperader_2(11000.0,-6000.0,100.0);
			Position esperader_3(8000.0,-4000.0,100.0);
			Position esperader_4(8000.0,-6000.0,100.0);

			Position esperacen_1(8000.0,1000.0,100.0);
			Position esperacen_2(10000.0,-1000.0,100.0);
			Position esperacen_3(9000.0,1000.0,100.0);
 			Position esperacen_4(9000.0,-1000.0,100.0);

			/*Position esperaizq2_1();
			Position esperaizq2_2();
			Position esperaizq2_3();
			Position esperaizq2_4();

			Position esperader2_1();
			Position esperader2_2();
			Position esperader2_3();
			Position esperader2_4();

			Position esperacen2_1();
			Position esperacen2_2();
			Position esperacen2_3();
			Position esperacen2_4();
*/

			Route r0, r1, r2, r3;

			Route r1d,r2d,r3d,r4d,r1i,r2i,r3i,r4i,r1c,r2c,r3c,r4c;

			r0.pos = pos0;
			r0.speed = 500.0;
			r1.pos = pos1;
			r1.speed = 100.0;
			r2.pos = pos2;
			r2.speed = 19.0;
			r3.pos = pos3;
			r3.speed = 15.0;

			r1d.pos = esperader_1;
			r1d.speed = 300.0;
			r2d.pos = esperader_2;
			r2d.speed = 300.0;
			r3d.pos = esperader_3;
			r3d.speed = 300.0;
			r4d.pos = esperader_4;
			r4d.speed = 300.0;

			r1i.pos = esperaizq_1;
			r1i.speed = 300.0;
			r2i.pos = esperaizq_2;
			r2i.speed = 300.0;
			r4i.pos = esperaizq_4;
			r4i.speed = 300.0;


			r1c.pos = esperacen_1;
			r1c.speed = 300.0;
			r2c.pos = esperacen_2;
			r2c.speed = 300.0;
			r3c.pos = esperacen_3;
			r3c.speed = 300.0;
			r4c.pos = esperacen_4;
			r4c.speed = 300.0;


			for(it = flights.begin(); it!=flights.end(); ++it)
			{

				busy_route = false;

				if((*it)->getRoute()->empty())
				{
					if((*it)->getPosition().get_y()>= 2000.0){
						AssignWaiting(*it, r1i,r2i,r3i,r4i);
					}
					else if((*it)->getPosition().get_y()<= -2000.0){
						AssignWaiting(*it, r1d,r2d,r3d,r4d);
					}else{
						AssignWaiting(*it, r1c,r2c,r3c,r4c);
					}
					for(it2 = flights.begin(); it2!=flights.end(); ++it2)
					{
						if((*it2)->getLanding()==true){
							busy_route = true;
						}
						if(busy_route == false){
							AssignLanding(*it, r0,r1,r2,r3);
						}

					}
					if(busy_route == false){
						AssignLanding(*it, r0,r1,r2,r3);
						printf("Estoy Aterrizando");
					}

				}
			}
}
