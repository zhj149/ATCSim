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
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;

			Position pos0(3500.0, 0.0, 100.0);
			Position pos1(1500.0, 0.0, 50.0);
			Position pos2(200.0, 0.0, 25.0);
			Position pos3(-750.0, 0.0, 25.0);
			//Puntos de entrada al aeropuerto
			Position pos4(4500.0, -400.0, 150.0);
			Position pos5(3000.0, 400.0, 150.0);


			//Ruta de espera 1
			Position pos6(6000.0, -2000.0, 200.0);
			Position pos7(6000.0, -7000.0, 200.0);
			Position pos8(4000.0, -3500.0, 200.0);
			Position pos9(8000.0, -3500.0, 200.0);
			//Ruta de espera 2
			Position pos10(6000.0, 2000.0, 200.0);
			Position pos11(6000.0, 7000.0, 200.0);
			Position pos12(4000.0, 3500.0, 200.0);
			Position pos13(8000.0, 3500.0, 200.0);
			//Ruta de espera 3
			Position pos14(12000.0, 0.0, 200.0);
			Position pos15(10000.0, 1000.0, 200.0);
			Position pos16(8000.0, 0.0, 200.0);
			Position pos17(10000.0, -1000.0, 200.0);


			Route r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17;

			r0.pos = pos0;
			r0.speed = 500.0;
			r1.pos = pos1;
			r1.speed = 100.0;
			r2.pos = pos2;
			r2.speed = 19.0;
			r3.pos = pos3;
			r3.speed = 15.0;

			//Velocidad y posición de las entradas al aeropuerto
			r4.pos = pos4;
			r4.speed = 500;
			r5.pos = pos5;
			r5.speed = 300;

			//Velocidad y posición de las rutas de espera
			r6.pos = pos6;
			r6.speed = 200;
			r7.pos = pos7;
			r7.speed = 200;
			r8.pos = pos8;
			r8.speed = 200;
			r9.pos = pos9;
			r9.speed = 200;
			r10.pos = pos10;
			r10.speed = 200;
			r11.pos = pos11;
			r11.speed = 200;
			r12.pos = pos12;
			r12.speed = 200;
			r13.pos = pos13;
			r13.speed = 200;
			r14.pos = pos14;
			r14.speed = 200;
			r15.pos = pos15;
			r15.speed = 200;
			r16.pos = pos16;
			r16.speed = 200;
			r17.pos = pos17;
			r17.speed = 200;


			for(it = flights.begin(); it!=flights.end(); ++it)
			{/*
				//Original
				if((*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r0);

				}*/
				//Gira sin parar en la ruta de espera
				/*while ((*it)->getPosition().get_y()<-1500 && (*it)->getRoute()->empty()) {
					(*it)->getRoute()->push_front(r7);
					(*it)->getRoute()->push_front(r8);
					(*it)->getRoute()->push_front(r6);
					(*it)->getRoute()->push_front(r9);
					(*it)->getRoute()->push_front(r7);
				}
				while((*it)->getPosition().get_y()>1500 && (*it)->getRoute()->empty()){
					(*it)->getRoute()->push_front(r13);
					(*it)->getRoute()->push_front(r11);
					(*it)->getRoute()->push_front(r12);
					(*it)->getRoute()->push_front(r10);
					(*it)->getRoute()->push_front(r13);
				}
				*/

				//Realiza rutas de espera y luego aterriza sin criterio
				if((*it)->getPosition().get_y()<-1500 && (*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r0);
					(*it)->getRoute()->push_front(r4);
					(*it)->getRoute()->push_front(r6);
					(*it)->getRoute()->push_front(r9);
					(*it)->getRoute()->push_front(r7);
					(*it)->getRoute()->push_front(r8);
					(*it)->getRoute()->push_front(r6);
					(*it)->getRoute()->push_front(r9);
					(*it)->getRoute()->push_front(r7);
				}
				else if((*it)->getPosition().get_y()>1500 && (*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r5);
					(*it)->getRoute()->push_front(r10);
					(*it)->getRoute()->push_front(r13);
					(*it)->getRoute()->push_front(r11);
					(*it)->getRoute()->push_front(r12);
					(*it)->getRoute()->push_front(r10);
					(*it)->getRoute()->push_front(r13);
				}
				else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500 && (*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r0);
					(*it)->getRoute()->push_front(r15);
					(*it)->getRoute()->push_front(r14);
					(*it)->getRoute()->push_front(r17);
					(*it)->getRoute()->push_front(r16);
					(*it)->getRoute()->push_front(r15);
					(*it)->getRoute()->push_front(r14);
				}

				/*
				//Entrada de izquierda, derecha y centro sin rutas de espera
				if((*it)->getPosition().get_y()<-500 && (*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r0);
					(*it)->getRoute()->push_front(r4);
				}
				else if((*it)->getPosition().get_y()>500 && (*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r5);
				}
				else if((*it)->getPosition().get_y()<500 && (*it)->getPosition().get_x()>-500 && (*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r0);
				}
				*/
			}

}
