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
#include <math.h>
#include <stdio.h>

AirController::AirController() {
	// TODO Auto-generated constructor stub
	//setLanding(false);
}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}
void AirController::Land(Flight *flight, Route a, Route b, Route c, Route d)
{

	flight->setLanding(true);
	flight->getRoute()->clear();
	flight->getRoute()->push_front(d);
	flight->getRoute()->push_front(c);
	flight->getRoute()->push_front(b);
	flight->getRoute()->push_front(a);

}
void AirController::Waiting(Flight *flight, Route a, Route b, Route c, Route d, Route e, Route f, Route g, Route h, Route k, Route l, Route m, Route n)
{

	flight->setLanding(false);
	flight->getRoute()->clear();
	flight->getRoute()->push_front(n);
	flight->getRoute()->push_front(m);
	flight->getRoute()->push_front(l);
	flight->getRoute()->push_front(k);
	flight->getRoute()->push_front(h);
	flight->getRoute()->push_front(g);
	flight->getRoute()->push_front(f);
	flight->getRoute()->push_front(e);
	flight->getRoute()->push_front(d);
	flight->getRoute()->push_front(c);
	flight->getRoute()->push_front(b);
	flight->getRoute()->push_front(a);

}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			//Storm* storm;
			//float diferenciangulartorav;
			//float distanciatorav;
			//float radio;

			bool vacia = true;

			Position pos0(3500.0, 0.0, 100.0);
			Position pos1(1500.0, 0.0, 50.0);
			Position pos2(200.0, 0.0, 25.0);
			Position pos3(-750.0, 0.0, 25.0);

			//Rutas nuevas

			//Puntos de entrada
			Position pos18(3500.0, -1000.0, 50.0); //izq
			Position pos19(3500.0, 1000.0, 50.0); //derecha
			Position pos20(3500.0, 0.0, 50.0); //centro

			//Ruta de espera izquierda
			Position pos21(4000.0, -8000.0, 75.0);
			Position pos22(3000.0, -7000.0, 75.0);
			Position pos23(4000.0, -6000.0, 75.0);
			Position pos24(5000.0, -6000.0, 75.0);
			Position pos25(7500.0, -6000.0, 75.0);
			Position pos26(9000.0, -6000.0, 75.0);
			Position pos27(10500.0, -7000.0, 75.0);
			Position pos28(9000.0, -8000.0, 75.0);
			Position pos29(7500.0, -8000.0, 75.0);
			Position pos54(6000.0, -9000.0, 75.0);
			Position pos30(5000.0, -8000.0, 75.0);
			Position pos31(4500.0, -8000.0, 75.0);

			//Ruta de espera derecha
			Position pos32(4000.0, 8000.0, 75.0);
			Position pos33(3000.0, 7000.0, 75.0);
			Position pos34(4000.0, 6000.0, 75.0);
			Position pos35(5000.0, 6000.0, 75.0);
			Position pos36(7500.0, 6000.0, 75.0);
			Position pos37(9000.0, 6000.0, 75.0);
			Position pos38(10500.0, 7000.0, 75.0);
			Position pos39(9000.0, 8000.0, 75.0);
			Position pos40(7500.0, 8000.0, 75.0);
			Position pos55(6000.0, 9000.0, 75.0);
			Position pos41(5000.0, 8000.0, 75.0);
			Position pos42(4500.0, 8000.0, 75.0);

			//Ruta de espera centro
			Position pos56(11000.0, 1450.0, 75.0);
			Position pos43(4000.0, -1400.0, 75.0);
			Position pos44(3000.0, 0.0, 75.0);
			Position pos45(4000.0, 1400.0, 75.0);
			Position pos46(5000.0, 1400.0, 75.0);
			Position pos47(7500.0, 1400.0, 75.0);
			Position pos48(9000.0, 1400.0, 75.0);
			Position pos49(10500.0, 0.0, 75.0);
			Position pos50(9000.0, -1400.0, 75.0);
			Position pos51(7500.0, -1400.0, 75.0);
			Position pos52(5000.0, -1400.0, 75.0);
			Position pos53(4500.0, -1400.0, 75.0);




			Route r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17;
			Route r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56;

			r0.pos = pos0;
			r0.speed = 500.0;
			r1.pos = pos1;
			//r1.speed = 100.0;
			r2.pos = pos2;
			//r2.speed = 19.0;
			r3.pos = pos3;
			r3.speed = 15.0;

			r1.speed = 300;
			r2.speed = 30.0;

			//Rutas nuevas, velocidades

			//Puntos de entrada

			r18.speed = 500;
			r18.pos = pos18;
			r19.speed = 500;
			r19.pos = pos19;
			r20.speed = 500;
			r20.pos = pos20;

			//Rutas de espera

			r21.pos = pos21;
			r21.speed = 200;
			r22.pos = pos22;
			r22.speed = 200;
			r23.pos = pos23;
			r23.speed = 200;
			r24.pos = pos24;
			r24.speed = 200;
			r25.pos = pos25;
			r25.speed = 200;
			r26.pos = pos26;
			r26.speed = 200;
			r27.pos = pos27;
			r27.speed = 200;
			r28.pos = pos28;
			r28.speed = 200;
			r29.pos = pos29;
			r29.speed = 200;
			r30.pos = pos30;
			r30.speed = 200;
			r31.pos = pos31;
			r31.speed = 200;
			r32.pos = pos32;
			r32.speed = 200;
			r33.pos = pos33;
			r33.speed = 200;
			r34.pos = pos34;
			r34.speed = 200;
			r35.pos = pos35;
			r35.speed = 200;
			r36.pos = pos36;
			r36.speed = 200;
			r37.pos = pos37;
			r37.speed = 200;
			r38.pos = pos38;
			r38.speed = 200;
			r39.pos = pos39;
			r39.speed = 200;
			r40.pos = pos40;
			r40.speed = 200;
			r41.pos = pos41;
			r41.speed = 200;
			r42.pos = pos42;
			r42.speed = 200;
			r43.pos = pos43;
			r43.speed = 200;
			r44.pos = pos44;
			r44.speed = 200;
			r45.pos = pos45;
			r45.speed = 200;
			r46.pos = pos46;
			r46.speed = 200;
			r47.pos = pos47;
			r47.speed = 200;
			r48.pos = pos48;
			r48.speed = 200;
			r49.pos = pos49;
			r49.speed = 200;
			r50.pos = pos50;
			r50.speed = 200;
			r51.pos = pos51;
			r51.speed = 200;
			r52.pos = pos52;
			r52.speed = 200;
			r53.pos = pos53;
			r53.speed = 200;
			r54.pos = pos54;
			r54.speed = 200;
			r55.pos = pos55;
			r55.speed = 200;
			r56.pos = pos56;
			r56.speed = 200;
/*
				for(it = flights.begin(); it!=flights.end(); ++it)
				{
						if((*it)->getPosition().get_y()<-1500 && (*it)->getRoute()->empty()) {
							Waiting(*it, r54, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31);
						}
						else if((*it)->getPosition().get_y()>1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r55, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42);
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r56, r43, r44, r45, r46, r47, r48, r49, r50, r51, r52, r53);
						}
				}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if((*it)->getLanding())
						vacia = false;
				}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if(vacia)
					{
						if((*it)->getPosition().get_y()<-1500)
						{
							Land(*it, r18, r1, r2, r3);
						}
						else if((*it)->getPosition().get_y()>1500)
						{
							Land(*it, r19, r1, r2, r3);
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500)
						{
							Land(*it, r20, r1, r2, r3);
						}
						vacia = false;
					}
				}
*/
				//Prueba tormenta

				//diferenciangulartorav = atan((storm->getPosition().get_y()-(*it)->getPosition().get_y())/(storm->getPosition().get_x()-(*it)->getPosition().get_x()));
				//distanciatorav = sqrt((storm->getPosition().get_y()-(*it)->getPosition().get_y())*(storm->getPosition().get_y()-(*it)->getPosition().get_y())+(storm->getPosition().get_x()-(*it)->getPosition().get_x())*(storm->getPosition().get_x()-(*it)->getPosition().get_x()));

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
						if((*it)->getPosition().get_y()<-1500 && (*it)->getRoute()->empty()) {
							Waiting(*it, r54, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31);
						}
						else if((*it)->getPosition().get_y()>1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r55, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42);
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r56, r43, r44, r45, r46, r47, r48, r49, r50, r51, r52, r53);
						}
				}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if((*it)->getLanding())
						vacia = false;
				}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if(vacia)
					{
						if((*it)->getPosition().get_y()<-1500)
						{
							Land(*it, r18, r1, r2, r3);
						}
						else if((*it)->getPosition().get_y()>1500)
						{
							Land(*it, r19, r1, r2, r3);
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500)
						{
							Land(*it, r20, r1, r2, r3);
						}
						vacia = false;
					}
				}


}
