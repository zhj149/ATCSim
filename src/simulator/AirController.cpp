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


void
AirController::assignLanding(Flight* f)
{
	f->setLanding(true);
	f->getRoute()->clear();

	Position pos0(3500.0, 0.0, 100.0);
	Position pos1(1500.0, 0.0, 50.0);
	Position pos2(200.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	Route r0, r1, r2, r3;

	r0.pos = pos0;
	r0.speed = 500.0;
	r1.pos = pos1;
	r1.speed = 100.0;
	r2.pos = pos2;
	r2.speed = 19.0;
	r3.pos = pos3;
	r3.speed = 15.0;


	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
}

void
AirController::assignWaiting3(Flight* f)
{
	f->setLanding(false);
	f->getRoute()->clear();

	Position pos0(15000.0,-15000.0 , 4000.0);
	Position pos1(5000.0, -15000.0, 4000.0);
	Position pos2(5000.0, 15000.0, 4000.0);
	Position pos3(15000.0, 15000.0, 4000.0);

	Route r0, r1, r2, r3;

	r0.pos = pos0;
	r0.speed = 300.0;
	r1.pos = pos1;
	r1.speed = 300.0;
	r2.pos = pos2;
	r2.speed = 300.0;
	r3.pos = pos3;
	r3.speed = 300.0;


	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
}


void
AirController::assignWaiting2(Flight* f)
{
	f->setLanding(false);
	f->getRoute()->clear();

	Position pos0(12000.0,-12000.0 , 2000.0);
	Position pos1(8000.0, -12000.0, 2000.0);
	Position pos2(8000.0, 12000.0, 2000.0);
	Position pos3(12000.0, 12000.0, 2000.0);

	Route r0, r1, r2, r3;

	r0.pos = pos0;
	r0.speed = 200.0;
	r1.pos = pos1;
	r1.speed = 200.0;
	r2.pos = pos2;
	r2.speed = 200.0;
	r3.pos = pos3;
	r3.speed = 200.0;


	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
}

void
AirController::assignWaiting1(Flight* f)
{
	f->setLanding(false);
	f->getRoute()->clear();

	Position pos0(6000.0,-8000.0 , 700.0);
	Position pos3(4500.0, 0.0, 700.0);
	Position pos2(6000.0, 8000.0, 700.0);
	Position pos1(7500.0, 0.0, 700.0);

	Route r0, r1, r2, r3;

	r0.pos = pos0;
	r0.speed = 150.0;
	r1.pos = pos1;
	r1.speed = 140.0;
	r2.pos = pos2;
	r2.speed = 120.0;
	r3.pos=pos3;
	r3.speed=100.0;


	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;

			int counter;
			counter=0;

			for(it = flights.begin(); it!=flights.end(); ++it)

			{  
								
											
				if((*it)->getLanding()) {counter=counter+1;/*std::cout<<counter<<std::endl;*/}
				else{
				   if((*it)->getRoute()->empty()){				
				 			
					if((*it)->getPosition().get_z()<=1000)

					{
						//std::cout<<"wait1"<<std::endl;
						assignWaiting1(*it);

					}
					else if((*it)->getPosition().get_z()>1000 &&
							(*it)->getPosition().get_z()<=3000)
					{

						assignWaiting2(*it);
						//std::cout<<"wait2"<<std::endl;
					}
					else if((*it)->getPosition().get_z()>3000)
					{
						//std::cout<<"wait3"<<std::endl;
						assignWaiting3(*it);			
					}
				   }

				}		
			    

				if (counter==0){
					
					Position posbase1(4500.0, 0.0, 700.0);
					Position posbase2(12000.0, 12000.0, 2000.0);
					Position posbase3(15000.0, 15000.0, 4000.0);

					Route r;
					Position p;
			
					std::list<Route>::iterator itr;
					itr=(*it)->getRoute()->begin();

					r=*itr;

					p=r.pos;

					if(p.get_x()==posbase1.get_x() &&
					   p.get_y()==posbase1.get_y() &&
					   p.get_z()==posbase1.get_z()){assignLanding(*it);/*std::cout<<"landing"<<std::endl;*/}
	
					if(p.get_x()==posbase2.get_x() &&
					   p.get_y()==posbase2.get_y() &&
					   p.get_z()==posbase2.get_z()){assignWaiting1(*it);/*std::cout<<"wait_1"<<std::endl;*/}

					if(p.get_x()==posbase3.get_x() &&
					   p.get_y()==posbase3.get_y() &&
					   p.get_z()==posbase3.get_z()){assignWaiting2(*it);/*std::cout<<"wait_2"<<std::endl;*/}
				}
		}
}
