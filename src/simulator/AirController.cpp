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
	//landing = false;
}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::assignLanding(Flight *f, Route r12, Route r11, Route r10)
{
	setLanding(true);
	f->getRoute()->clear();

	f->getRoute()->push_back(r12);
	f->getRoute()->push_front(r11);
	f->getRoute()->push_front(r10);
}

void
AirController::assignRoute(Flight *f, Route r14, Route r13, Route r15, Route r9, Route r8, Route r17)
{
     if (f->getPosition().get_y()<= 0){	
         f->getRoute()->push_front(r14);
         f->getRoute()->push_front(r13);
         f->getRoute()->push_front(r15);
     }else if(f->getPosition().get_y()>0){
	 f->getRoute()->push_front(r9); 
	 f->getRoute()->push_front(r8); 
         f->getRoute()->push_front(r17); 
     }            		
}

void
AirController::assignWaiting(Flight *f, Route r0, Route r3, Route r2, Route r1, Route r5, Route r6, Route r4, Route r7, 
			     Route r18, Route r19, Route r20, Route r16, Route r24, Route r21, Route r23, Route r22)
{
	setLanding(false);
	f->getRoute()->clear();

	if(f->getPosition().get_y()<=-8500){
	   f->getRoute()->push_front(r1);
	   f->getRoute()->push_front(r2);
	   f->getRoute()->push_front(r3);
	   f->getRoute()->push_front(r0);
	}else if (f->getPosition().get_y()>8500) {
           f->getRoute()->push_front(r7);
	   f->getRoute()->push_front(r4);
	   f->getRoute()->push_front(r6);
	   f->getRoute()->push_front(r5);
        }else if((f->getPosition().get_y()<=0)&&(f->getPosition().get_y()>-8500)) {
           f->getRoute()->push_front(r18);
	   f->getRoute()->push_front(r19);
	   f->getRoute()->push_front(r20);
	   f->getRoute()->push_front(r16);
	}else if ((f->getPosition().get_y()>0)&&(f->getPosition().get_y()<=8500)){
           f->getRoute()->push_front(r24);
	   f->getRoute()->push_front(r21);
	   f->getRoute()->push_front(r23);
	   f->getRoute()->push_front(r22);
	}
	
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;

			//zona 1 izq arriba RUTA ESPERA 1
	
			Position pos0(-2000.0, -12000.0, 500.0);
			Position pos1(-2000.0, -3500.0, 500.0);
			Position pos2(-9000.0, -3500.0, 500.0);
			Position pos3(-9000.0, -12000.0, 500.0);
			
			//zona 2 der arriba RUTA ESPERA 2

			Position pos4(-9000.0, 3500.0, 500.0);
			Position pos5(-2000.0, 12000.0, 500.0);
			Position pos6(-9000.0, 12000.0, 500.0);
			Position pos7(-2000.0, 3500.0, 500.0);
			
			//RUTAS ESPERA SEGUNDA ALTURA

			//zona 1 izq arriba RUTA ESPERA 1
	
			Position pos16(-2000.0, -12000.0, 1000.0);
			Position pos18(-2000.0, -3500.0, 1000.0);
			Position pos19(-9000.0, -3500.0, 1000.0);
			Position pos20(-9000.0, -12000.0, 1000.0);
			
			//zona 2 der arriba RUTA ESPERA 2

			Position pos21(-9000.0, 3500.0, 1000.0);
			Position pos22(-2000.0, 12000.0, 1000.0);
			Position pos23(-9000.0, 12000.0, 1000.0);
			Position pos24(-2000.0, 3500.0, 1000.0);


			//zona izq 

			Position pos13(9000.0, -12000.0, 100.0);
			Position pos14(9000.0, -3500.0, 50.0);
			Position pos15(2000.0, -12000.0, 100.0);
			
			//zona der

			Position pos8(9000.0, 12000.0, 100.0);
			Position pos9(9000.0, 3500.0, 50.0);
			Position pos17(2000.0, 12000.0, 100.0);

			//pista
			Position pos10(1500.0, 0.0, 50.0);
			Position pos11(200.0, 0.0, 25.0);
			Position pos12(-750.0, 0.0, 25.0);
		

			Route r0, r1, r2, r3, r4, r5, r6, r7, r8, r9,  r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24;

			//RUTAS DE ESPERA
			r0.pos = pos0;
			r0.speed = 50.0;
			r1.pos = pos1;
			r1.speed = 50.0;
			r2.pos = pos2;
			r2.speed = 50.0;
			r3.pos = pos3;
			r3.speed = 50.0;

			r4.pos = pos4;
			r4.speed = 50.0;
			r5.pos = pos5;
			r5.speed = 50.0;
			r6.pos = pos6;
			r6.speed = 50.0;
			r7.pos = pos7;
			r7.speed = 50.0;

			//RUTAS ESPERA ALTURA 2
			r16.pos = pos16;
			r16.speed = 50.0;
			r18.pos = pos18;
			r18.speed = 50.0;
			r19.pos = pos19;
			r19.speed = 50.0;
			r20.pos = pos20;
			r20.speed = 50.0;

			r21.pos = pos21;
			r21.speed = 50.0;
			r22.pos = pos22;
			r22.speed = 50.0;
			r23.pos = pos23;
			r23.speed = 50.0;
			r24.pos = pos24;
			r24.speed = 50.0;


			//RUTAS
			r15.pos = pos15;
			r15.speed = 500.0;
			r13.pos = pos13;
			r13.speed = 500.0;
			r14.pos = pos14;
			r14.speed = 300.0;
	
			r8.pos = pos8;
			r8.speed = 500.0;
			r9.pos = pos9;
			r9.speed = 300.0;
			r17.pos = pos17;
			r17.speed = 500.0;

			//pista
			r10.pos = pos10;
			r10.speed = 40.0;
			r11.pos = pos11;
			r11.speed = 19.0;
			r12.pos = pos12;
			r12.speed = 15.0;
			
			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty())
				{
					if(getLanding()==false)
					{  
						assignLanding((*it), r12, r11, r10);
						assignRoute((*it), r14, r13, r15, r9,r8, r17);


					}else if(getLanding() == true){
					    	assignWaiting((*it),r0,r3,r2,r1,r5,r6,r4,r7,r18,r19,r20,r16,r24,r21,r23,r22);
						
					}		        
			      	 }    
			}			
}
