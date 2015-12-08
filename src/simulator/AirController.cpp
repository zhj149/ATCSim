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
	ruta_ocupada = false;
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AssignWaiting(Flight *f, Route p1, Route p2, Route p3, Route p4, Route p5, Route p6)
{
	f->setLanding(false);
	f->getRoute()->clear();
	f->getRoute()->push_front(p1);
	f->getRoute()->push_front(p2);
	f->getRoute()->push_front(p3);
	f->getRoute()->push_front(p4);
	f->getRoute()->push_front(p5);
	f->getRoute()->push_front(p6);
}

void
AssignLanding(Flight *f, Route p1, Route p2, Route p3)
{
	f->setLanding(true);
	f->getRoute()->clear();
	f->getRoute()->push_back(p1);
	f->getRoute()->push_back(p2);
	f->getRoute()->push_back(p3);
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			std::list<Flight*>::iterator it1;
			std::list<Route> route;
			std::list<Route>::iterator r;

			Position pos0_0_A(11000.0, 0.0, 100.0);
			Position pos0_1_A(9500.0, 2500.0, 100.0);
			Position pos0_2_A(6500.0, 0.0, 100.0);
			Position pos0_3_A(9500.0, -2500.0, 100.0);
			Position pos0_0_B(7000.0, -7500.0, 100.0);
			Position pos0_1_B(9500.0, -4000.0, 100.0);
			Position pos0_2_B(6500.0, -1500.0, 100.0);
			Position pos0_3_B(4000.0, -4500.0, 100.0);
			Position pos0_0_C(7000.0, 7500.0, 100.0);
			Position pos0_1_C(9500.0, 4000.0, 100.0);
			Position pos0_2_C(6500.0, 1500.0, 100.0);
			Position pos0_3_C(4000.0, 4500.0, 100.0);
			Position pos1(2000.0, 0.0, 50.0);
			Position pos2(200.0, 0.0, 25.0);
			Position pos3(-750.0, 0.0, 25.0);

			Route r0_0_A, r0_1_A,r0_2_A,r0_3_A, r0_0_B, r0_1_B,r0_2_B,r0_3_B;
			Route r0_0_C, r0_1_C,r0_2_C,r0_3_C, r1, r2, r3;

			r0_0_A.pos = pos0_0_A;
			r0_0_A.speed = 500.0;
			r0_1_A.pos = pos0_1_A;
			r0_1_A.speed = 500.0;
			r0_2_A.pos = pos0_2_A;
			r0_2_A.speed = 500.0;
			r0_3_A.pos = pos0_3_A;
			r0_3_A.speed = 500.0;
			r0_0_B.pos = pos0_0_B;
			r0_0_B.speed = 500.0;
			r0_1_B.pos = pos0_1_B;
			r0_1_B.speed = 500.0;
			r0_2_B.pos = pos0_2_B;
			r0_2_B.speed = 500.0;
			r0_3_B.pos = pos0_3_B;
			r0_3_B.speed = 500.0;
			r0_0_C.pos = pos0_0_C;
			r0_0_C.speed = 500.0;
			r0_1_C.pos = pos0_1_C;
			r0_1_C.speed = 500.0;
			r0_2_C.pos = pos0_2_C;
			r0_2_C.speed = 500.0;
			r0_3_C.pos = pos0_3_C;
			r0_3_C.speed = 500.0;
			r1.pos = pos1;
			r1.speed = 450.0;
			r2.pos = pos2;
			r2.speed = 19.0;
			r3.pos = pos3;
			r3.speed = 15.0;
			/*
			for(r = route.begin();r != route.end(); ++r)
			{
				if(((*it)->getPosition().get_x()== r->pos.get_x())&& ((*it)->getPosition().get_y()== r->pos.get_y()))
					(*it)->setLanding(true);
			}
			*/
			/*for(it = flights.begin(); it!=flights.end(); ++it){
				if((*it)->getLanding()==true)
					ruta_ocupada = true;
			}
			*/

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				ruta_ocupada = false;

				if((*it)->getRoute()->empty()){
					if((*it)->getPosition().get_y()>= 1500.0){
						AssignWaiting(*it, r0_2_C,r0_1_C,r0_0_C,r0_3_C,r0_2_C,r0_1_C);
					}
					else if((*it)->getPosition().get_y()<=-1500.0){
						AssignWaiting(*it, r0_2_B,r0_1_B,r0_0_B,r0_3_B,r0_2_B,r0_1_B);
					}else{
						AssignWaiting(*it, r0_2_A,r0_1_A,r0_0_A,r0_3_A,r0_2_A,r0_1_A);
					}
					for(it1 = flights.begin(); it1!=flights.end(); ++it1)
					{
						if((*it1)->getLanding()==true){
							ruta_ocupada = true;
						}
						if(ruta_ocupada == false){
							AssignLanding(*it, r1,r2,r3);
						}

					}
					if(ruta_ocupada == false){
						AssignLanding(*it, r1,r2,r3);
					}
				}
			}
}
