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
#include "Storm.h"



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
AssignLanding(Flight *f, Route p1,Route p2, Route p3, Route p4)
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
			std::list<Flight*>::iterator it1;
			std::list<Route> route;
			std::list<Route>::iterator r;



//Centro
			Position pos0_0_A(11000.0, 0.0, 75.0);
			Position pos0_1_A(9500.0, 2500.0, 75.0);
			Position pos0_2_A(6500.0, 0.0, 75.0);
			Position pos0_3_A(9500.0, -2500.0, 75.0);
//Lado izquierdo
			Position pos0_0_B(9000.0, -9500.0, 75.0);
			Position pos0_1_B(11500.0, -6000.0, 75.0);
			Position pos0_2_B(8500.0, -3500.0, 75.0);
			Position pos0_3_B(8000.0, -6500.0, 75.0);
//Lado derecho
			Position pos0_0_C(9000.0, 9500.0, 75.0);
			Position pos0_1_C(11500.0, 6000.0, 75.0);
			Position pos0_2_C(8500.0, 3500.0, 75.0);
			Position pos0_3_C(6000.0, 6500.0,75.0);
//Aprox. final
			Position pos1_A(4000.0, 0.0, 75.0);
			Position pos1_B(4000.0, -1500, 75.0);
			Position pos1_C(4000.0, 1500, 75.0);
			Position pos2(1500.0, 0.0, 50.0);
			Position pos3(100.0, 0.0, 25.0);
			Position pos4(-750.0, 0.0, 25.0);

			Route r0_0_A, r0_1_A,r0_2_A,r0_3_A, r0_0_B, r0_1_B,r0_2_B,r0_3_B;
			Route r0_0_C, r0_1_C,r0_2_C,r0_3_C, r1_A, r1_B, r1_C, r2, r3, r4;

//Centro
			r0_0_A.pos = pos0_0_A;
			r0_0_A.speed = 250.0;
			r0_1_A.pos = pos0_1_A;
			r0_1_A.speed = 100.0;
			r0_2_A.pos = pos0_2_A;
			r0_2_A.speed = 100.0;
			r0_3_A.pos = pos0_3_A;
			r0_3_A.speed = 100.0;
//Lado izquierdo
			r0_0_B.pos = pos0_0_B;
			r0_0_B.speed = 250.0;
			r0_1_B.pos = pos0_1_B;
			r0_1_B.speed = 100.0;
			r0_2_B.pos = pos0_2_B;
			r0_2_B.speed = 100.0;
			r0_3_B.pos = pos0_3_B;
			r0_3_B.speed = 100.0;
//Lado derecho
			r0_0_C.pos = pos0_0_C;
			r0_0_C.speed = 250.0;
			r0_1_C.pos = pos0_1_C;
			r0_1_C.speed = 100.0;
			r0_2_C.pos = pos0_2_C;
			r0_2_C.speed = 100.0;
			r0_3_C.pos = pos0_3_C;
			r0_3_C.speed = 100.0;
//Aprox. final
			r1_A.pos = pos1_A;
			r1_A.speed = 500.0;
			r1_B.pos = pos1_B;
			r1_B.speed = 500.0;
			r1_C.pos = pos1_C;
			r1_C.speed = 500.0;
			r2.pos = pos2;
			r2.speed = 400.0;
			r3.pos = pos3;
			r3.speed = 30.0;
			r4.pos = pos4;
			r4.speed = 15.0;


			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty()){
					if((*it)->getPosition().get_y()>= 1000.0){
						AssignWaiting(*it, r0_2_C,r0_1_C,r0_0_C,r0_3_C,r0_2_C,r0_1_C);
					}
					else if((*it)->getPosition().get_y()<=-1000.0){
						AssignWaiting(*it, r0_2_B,r0_1_B,r0_0_B,r0_3_B,r0_2_B,r0_1_B);
					}else{
						AssignWaiting(*it, r0_2_A,r0_1_A,r0_0_A,r0_3_A,r0_2_A,r0_1_A);
					}
				}
			}
			ruta_ocupada = false;
			for(it = flights.begin(); it!=flights.end(); ++it){
				if((*it)->getLanding()){
				ruta_ocupada = true;
				}
			}
				for(it = flights.begin(); it !=flights.end(); ++it){
					if(not ruta_ocupada ){
						if((*it)->getPosition().get_y()>= 1000.0){
							AssignLanding(*it, r1_C, r2,r3,r4);
						}
						else if((*it)->getPosition().get_y()<=-1000.0){
							AssignLanding(*it, r1_B,r2,r3,r4);
						}else{
							AssignLanding(*it, r1_A,r2,r3,r4);
						}
							ruta_ocupada=true;
					}
				}
}
