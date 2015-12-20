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
void AirController::AssignWaiting(Flight *f, Route r1, Route r2, Route r3, Route r4,bool wait)
{
	f->setLanding(false);
	f->getRoute()->clear();
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r3);
	f->getRoute()->push_front(r4);
	wait = true;
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

		//	Position poscentral(13000.0,0.0,100.0);
		//	Position posderecha(11000.0,11000.0,100.0);
		//	Position posizq(11000.0,-11000.0,100.0);

			Position esperaizq_1(5000.0,4000.0,100.0);
			Position esperaizq_2(8000.0,4000.0,100.0);
			Position esperaizq_3(8000.0,7000.0,100.0);
			Position esperaizq_4(5000.0,7000.0,100.0);

			Position esperader_1(5000.0,-4000.0,100.0);
			Position esperader_2(8000.0,-4000.0,100.0);
			Position esperader_3(8000.0,-7000.0,100.0);
			Position esperader_4(5000.0,-7000.0,100.0);

			Position esperacen_1(5000.0,0.0,100.0);
			Position esperacen_2(8000.0,0.0,100.0);
			Position esperacen_3(8000.0,1500.0,100.0);
 			Position esperacen_4(5000.0, 1500.0,100.0);

			Position esperaizq2_1(5000.0,4000.0,100.0);
			Position esperaizq2_2(5000.0,2500.0,100.0);
			Position esperaizq2_3(8000.0,2500.0,100.0);
			Position esperaizq2_4(8000.0,4000.0,100.0);

			Position esperader2_1(5000.0,-4000.0,100.0);
			Position esperader2_2(5000.0,-2500.0,100.0);
			Position esperader2_3(8000.0,-2500.0,100.0);
			Position esperader2_4(8000.0,-4000.0,100.0);

			Position esperacen2_1(5000.0,0.0,100.0);
			Position esperacen2_2(5000.0,-1500.0,100.0);
			Position esperacen2_3(8000.0,-1500.0,100.0);
			Position esperacen2_4(8000.0,0.0,100.0);


			Route r0, r1, r2, r3;

			Route r1d,r2d,r3d,r4d,r1i,r2i,r3i,r4i,r1c,r2c,r3c,r4c,r12d,r22d,r32d,r42d,r12i,r22i,r32i,r42i,r12c,r22c,r32c,r42c;

			r0.pos = pos0;
			r0.speed = 500.0;
			r1.pos = pos1;
			r1.speed = 100.0;
			r2.pos = pos2;
			r2.speed = 19.0;
			r3.pos = pos3;
			r3.speed = 15.0;

			r1d.pos = esperader_1;
			r1d.speed = 500.0;
			r2d.pos = esperader_2;
			r2d.speed = 500.0;
			r3d.pos = esperader_3;
			r3d.speed = 500.0;
			r4d.pos = esperader_4;
			r4d.speed = 500.0;

			r1i.pos = esperaizq_1;
			r1i.speed = 500.0;
			r2i.pos = esperaizq_2;
			r2i.speed = 500.0;
			r3i.pos = esperaizq_3;
			r3i.speed = 500.0;
			r4i.pos = esperaizq_4;
			r4i.speed = 500.0;

			r1c.pos = esperacen_1;
			r1c.speed = 500.0;
			r2c.pos = esperacen_2;
			r2c.speed = 500.0;
			r3c.pos = esperacen_3;
			r3c.speed = 500.0;
			r4c.pos = esperacen_4;
			r4c.speed = 500.0;

			r12d.pos = esperader2_1;
			r12d.speed = 500.0;
			r22d.pos = esperader2_2;
			r22d.speed = 500.0;
			r32d.pos = esperader2_3;
			r32d.speed = 500.0;
			r42d.pos = esperader2_4;
			r42d.speed = 500.0;

			r12i.pos = esperaizq2_1;
			r12i.speed = 500.0;
			r22i.pos = esperaizq2_2;
			r22i.speed = 500.0;
			r32i.pos = esperaizq2_3;
			r32i.speed = 500.0;
			r42i.pos = esperaizq2_4;
			r42i.speed = 500.0;

			r12c.pos = esperacen2_1;
			r12c.speed = 500.0;
			r22c.pos = esperacen2_2;
			r22c.speed = 500.0;
			r32c.pos = esperacen2_3;
			r32c.speed = 500.0;
			r42c.pos = esperacen2_4;
			r42c.speed = 500.0;

			for(it = flights.begin(); it!=flights.end(); ++it)
			{

				busy_route = false;
				busy_wait_route = false;

				if((*it)->getRoute()->empty())
				{
					if((*it)->getPosition().get_y()>= 2000.0){
						AssignWaiting(*it, r4i,r3i,r2i,r1i,busy_wait_route);
						if(busy_wait_route == true)
						AssignWaiting(*it, r42i,r32i,r22i,r12i,busy_wait_route);
					}
					else if((*it)->getPosition().get_y()<= -2000.0){
						AssignWaiting(*it, r4d,r3d,r2d,r1d,busy_wait_route);
						if(busy_wait_route == true)
						AssignWaiting(*it, r42d,r32d,r22d,r12d,busy_wait_route);
					}else{
						AssignWaiting(*it, r4c,r3c,r2c,r1c,busy_wait_route);
						if(busy_wait_route == true)
						AssignWaiting(*it, r42c,r32c,r22c,r12c,busy_wait_route);
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
					}

				}
			}
}

/*  Procedimiento para detectar tormentas y esquivarlas
				if(storm!= NULL)
				{
					Route rst1,rst2,rst3,rst4;

					double X_plane,Y_plane,Z_plane;
					double St_X,St_Y,St_Z;

					X_plane = (*it)->getPosition().get_x();
					Y_plane = (*it)->getPosition().get_y();
					Z_plane = (*it)->getPosition().get_z();
					St_X = storm->getPosition().get_x();
					St_Y = storm->getPosition().get_y();
					St_Z = storm->getPosition().get_z();

					double Dist_Storm = sqrt((St_X-X_plane)*(St_X-X_plane)+(St_Y-Y_plane)*(St_Y-Y_plane));

						if(Dist_Storm < DISTANCE_STORM)
						{
							Position storm1(X_plane,Y_plane,Z_plane);
							rst1.pos = storm1;
							Position storm2(X_plane+1000.0,Y_plane+2000.0,Z_plane);
							rst2.pos = storm2;
							Position  storm3(X_plane+4000.0,Y_plane+3000.0,Z_plane);
							rst3.pos = storm3;
							Position  storm4(X_plane+6000.0,Y_plane+2000.0,Z_plane);
							rst4.pos = storm4;
							AssignWaiting(*it,rst4,rst3,rst2,rst1,busy_wait_route);
						}
					}*/
