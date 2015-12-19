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
AirController::assignWaiting4(Flight* f)
{
	f->setLanding(false);
	f->getRoute()->clear();

	Position pos0(7700.0,700.0 , 2500.0);
	Position pos1(3700.0, 700.0, 2500.0);
	Position pos2(3700.0, 4000.0, 2500.0);
	Position pos3(7700.0, 4000.0, 2500.0);

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
AirController::assignWaiting3(Flight* f)
{
	f->setLanding(false);
	f->getRoute()->clear();

	Position pos0(7700.0, 2000.0, 500.0);
	Position pos1(3700.0, 2000.0, 500.0);
	Position pos2(3700.0, 8000.0, 500.0);
	Position pos3(7700.0, 8000.0, 500.0);

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
AirController::assignWaiting2(Flight* f)
{
	f->setLanding(false);
	f->getRoute()->clear();

	Position pos0(7700.0,-700.0 , 2500.0);
	Position pos1(3700.0, -700.0, 2500.0);
	Position pos2(3700.0, -4000.0, 2500.0);
	Position pos3(7700.0, -4000.0, 2500.0);

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
AirController::assignWaiting1(Flight* f)
{
	f->setLanding(false);
	f->getRoute()->clear();

	Position pos0(7700.0, -2000.0, 500.0);
	Position pos1(3700.0, -2000.0, 500.0);
	Position pos2(3700.0, -8000.0, 500.0);
	Position pos3(7700.0, -8000.0, 500.0);

	Route r0, r1, r2, r3;

	r0.pos = pos0;
	r0.speed = 200.0;
	r1.pos = pos1;
	r1.speed = 200.0;
	r2.pos = pos2;
	r2.speed = 200.0;
	r3.pos=pos3;
	r3.speed=200.0;


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
  
			std::list<Flight*>::iterator it2;
			   

				for(it2 = flights.begin(); it2!=flights.end(); ++it2)
				{
				if((*it2)->getLanding()) 
					counter=counter+1;
				}

				if(counter==0){
					
					assignLanding(flights.front());
				
				 if ((*it)->getRoute()->size()!=0)
				 {

	 			  Position posbase2(4700.0,-700.0 , 2500.0);
				  Position posbase4(4700.0,700.0 , 2500.0);

				  Route r;
				  Position p;
			
				  std::list<Route>::iterator itr;
				  itr=(*it)->getRoute()->begin();

				  r=*itr;

				  p=r.pos;

				  if(p.get_x()==posbase2.get_x() &&
				     p.get_y()==posbase2.get_y() &&
				     p.get_z()==posbase2.get_z()){assignWaiting1(*it);}

				  if(p.get_x()==posbase4.get_x() &&
				     p.get_y()==posbase4.get_y() &&
				     p.get_z()==posbase4.get_z()){assignWaiting3(*it);}
				 }  
				}
				else if ( counter!=0 && (*it)->getRoute()->empty()){				
				 	
					if((*it)->getPosition().get_y()<=0){
		
					   if((*it)->getPosition().get_z()<=2000)
						{assignWaiting1(*it);}
					
					   else {assignWaiting2(*it);}

					}else{

					   if((*it)->getPosition().get_z()<=2000)
						{assignWaiting3(*it);}
					
					   else {assignWaiting4(*it);}
					}
				}		
			    
		} 
}
					

		

