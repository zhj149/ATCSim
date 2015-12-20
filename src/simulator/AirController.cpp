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

#define DISTALERT 4000


AirController::AirController() {
	// TODO Auto-generated constructor stub
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

void AirController::Emergency(Flight *flight, Route a, Route b, Route c, Route d, Route e, Route f, Route g, Route h)
{
	flight->getRoute()->clear();
	flight->getRoute()->push_front(h);
	flight->getRoute()->push_front(g);
	flight->getRoute()->push_front(f);
	flight->getRoute()->push_front(e);
	flight->getRoute()->push_front(d);
	flight->getRoute()->push_front(c);
	flight->getRoute()->push_front(b);
	flight->getRoute()->push_front(a);
}

float AirController::getDistancia(float x1, float x2, float y1, float y2)
{
	float distancia;
	distancia = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return distancia;
}

float AirController::getDifAngulo(float x1, float x2, float y1, float y2)
{
	float difang;
	difang = atan2(y2-y1, x2-x1)*180/M_PI;
	return difang;
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			Storm *storm = Airport::getInstance()->getStorm();
			bool vacia = true;
			float dis;

			Position pos0(3500.0, 0.0, 100.0);
			Position pos1(1500.0, 0.0, 50.0);
			Position pos2(200.0, 0.0, 25.0);
			Position pos3(-750.0, 0.0, 25.0);

			//Rutas nuevas

			//Puntos de entrada
			Position pos18(3500.0, -1000.0, 150.0); //izq
			Position pos19(3500.0, 1000.0, 150.0); //derecha
			Position pos20(3500.0, 0.0, 150.0); //centro

			//Ruta de espera izquierda
			Position pos21(4000.0, -8000.0, 900.0);
			Position pos22(3000.0, -7000.0, 900.0);
			Position pos23(4000.0, -6000.0, 900.0);
			Position pos24(5000.0, -6000.0, 900.0);
			Position pos25(7500.0, -6000.0, 900.0);
			Position pos26(9000.0, -6000.0, 900.0);
			Position pos27(10500.0, -7000.0, 900.0);
			Position pos28(9000.0, -8000.0, 900.0);
			Position pos29(7500.0, -8000.0, 900.0);
			Position pos54(6000.0, -9000.0, 900.0);
			Position pos30(5000.0, -8000.0, 900.0);
			Position pos31(4500.0, -8000.0, 900.0);

			//Ruta de espera derecha
			Position pos32(4000.0, 8000.0, 900.0);
			Position pos33(3000.0, 7000.0, 900.0);
			Position pos34(4000.0, 6000.0, 900.0);
			Position pos35(5000.0, 6000.0, 900.0);
			Position pos36(7500.0, 6000.0, 900.0);
			Position pos37(9000.0, 6000.0, 900.0);
			Position pos38(10500.0, 7000.0, 900.0);
			Position pos39(9000.0, 8000.0, 900.0);
			Position pos40(7500.0, 8000.0, 900.0);
			Position pos55(6000.0, 9000.0, 900.0);
			Position pos41(5000.0, 8000.0, 900.0);
			Position pos42(4500.0, 8000.0, 900.0);

			//Ruta de espera centro
			Position pos56(11000.0, 1450.0, 600.0);
			Position pos43(4000.0, -1400.0, 600.0);
			Position pos44(3000.0, 0.0, 600.0);
			Position pos45(4000.0, 1400.0, 600.0);
			Position pos46(5000.0, 1400.0, 600.0);
			Position pos47(7500.0, 1400.0, 600.0);
			Position pos48(9000.0, 1400.0, 600.0);
			Position pos49(10500.0, 0.0, 600.0);
			Position pos50(9000.0, -1400.0, 600.0);
			Position pos51(7500.0, -1400.0, 600.0);
			Position pos52(5000.0, -1400.0, 600.0);
			Position pos53(4500.0, -1400.0, 600.0);

			//Ruta emergencia izquierda
			Position pos57(0.0, -8000.0, 1000.0);
			Position pos58(-1000.0, -8000.0, 1000.0);
			Position pos59(-2000.0, -7000.0, 1000.0);
			Position pos60(-1000.0, -6000.0, 1000.0);
			Position pos61(0.0, -6000.0, 1000.0);
			Position pos62(2000.0, -6000.0, 1000.0);
			Position pos63(3000.0, -7000.0, 1000.0);
			Position pos64(2000.0, -8000.0, 1000.0);

			//Ruta emergencia derecha
			Position pos65(0.0, 8000.0, 1000.0);
			Position pos66(-1000.0, 8000.0, 1000.0);
			Position pos67(-2000.0, 7000.0, 1000.0);
			Position pos68(-1000.0, 6000.0, 1000.0);
			Position pos69(0.0, 6000.0, 1000.0);
			Position pos70(2000.0, 6000.0, 1000.0);
			Position pos71(3000.0, 7000.0, 1000.0);
			Position pos72(2000.0, 8000.0, 1000.0);

			//Ruta emergencia centro

			Position pos73(-1000.0, -1000.0, 1000.0);
			Position pos74(-2500.0, -1000.0, 1000.0);
			Position pos75(-4000.0, -1000.0, 1000.0);
			Position pos76(-5500.0, -1000.0, 1000.0);
			Position pos77(-7000.0, 0.0, 1000.0);
			Position pos78(-5500.0, 1000.0, 1000.0);
			Position pos79(-4000.0, 1000.0, 1000.0);
			Position pos80(-2500.0, 2000.0, 1000.0);




			Route r0, r1, r2, r3;
			Route r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r50, r51, r52, r53, r54, r55, r56, r57, r58, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68, r69, r70, r71, r72, r73, r74, r75, r76, r77, r78, r79, r80;

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

			//Rutas emergencia
			r57.pos = pos57;
			r57.speed = 300;
			r58.pos = pos58;
			r58.speed = 300;
			r59.pos = pos59;
			r59.speed = 300;
			r60.pos = pos60;
			r60.speed = 300;
			r61.pos = pos61;
			r61.speed = 300;
			r62.pos = pos62;
			r62.speed = 300;
			r63.pos = pos63;
			r63.speed = 300;
			r64.pos = pos64;
			r64.speed = 300;
			r65.pos = pos65;
			r65.speed = 300;
			r66.pos = pos66;
			r66.speed = 300;
			r67.pos = pos67;
			r67.speed = 300;
			r68.pos = pos68;
			r68.speed = 300;
			r69.pos = pos69;
			r69.speed = 300;
			r70.pos = pos70;
			r70.speed = 300;
			r71.pos = pos71;
			r71.speed = 300;
			r72.pos = pos72;
			r72.speed = 300;
			r73.pos = pos73;
			r73.speed = 300;
			r74.pos = pos74;
			r74.speed = 300;
			r75.pos = pos75;
			r75.speed = 300;
			r76.pos = pos76;
			r76.speed = 300;
			r77.pos = pos77;
			r77.speed = 300;
			r78.pos = pos78;
			r78.speed = 300;
			r79.pos = pos79;
			r79.speed = 300;
			r80.pos = pos80;
			r80.speed = 300;


				if(storm != NULL){
					for(it = flights.begin(); it!=flights.end(); ++it){
						dis = getDistancia(storm->getPosition().get_x(), (*it)->getPosition().get_x(), storm->getPosition().get_y() , (*it)->getPosition().get_y());
							if(dis - storm->getRadious()< DISTALERT){
								if(storm->getPosition().get_y()<-1500 && (*it)->getRoute()->empty()) {
									Emergency(*it, r73, r74, r75, r76, r77, r78, r79, r80);
								}
								else if(storm->getPosition().get_y()>1500 && (*it)->getRoute()->empty()){
									Emergency(*it, r73, r74, r75, r76, r77, r78, r79, r80);
								}
								else if(storm->getPosition().get_y()<1500 && storm->getPosition().get_x()>-1500 && (*it)->getRoute()->empty()){
									Emergency(*it, r59, r58, r57, r64, r63, r62, r61, r60);
								}
							}
						}
					}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
						if((*it)->getPosition().get_y()<-1500 && (*it)->getRoute()->empty()) {
							Waiting(*it, r54, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r73, r74, r75, r76, r77, r78, r79, r80);
								}
						}
						else if((*it)->getPosition().get_y()>1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r55, r32, r33, r34, r35, r36, r37, r38, r39, r40, r41, r42);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r73, r74, r75, r76, r77, r78, r79, r80);
								}
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r56, r43, r44, r45, r46, r47, r48, r49, r50, r51, r52, r53);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r59, r58, r57, r64, r63, r62, r61, r60);
								}
						}
				}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if((*it)->getLanding())
						vacia = false;
				}


				if(storm != NULL)
				{
					for(it = flights.begin(); it!=flights.end(); ++it){
						if(storm->getBearing()>=0.19*M_PI && storm->getBearing()<=0.3*M_PI && dis - storm->getRadious()< DISTALERT){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
						else if(storm->getBearing()>=1.66*M_PI && storm->getBearing()<=1.83*M_PI && dis - storm->getRadious()< DISTALERT){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
						else if(storm->getBearing()>=0.66*M_PI && storm->getBearing()<=0.8*M_PI && dis - storm->getRadious()< DISTALERT){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
						else if(storm->getBearing()>=1.16*M_PI && storm->getBearing()<=1.33*M_PI && dis - storm->getRadious()< DISTALERT){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
					}
				}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if(vacia)
					{
						if((*it)->getPosition().get_y()<-1500)
						{
							Land(*it, r18, r1, r2, r3);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r73, r74, r75, r76, r77, r78, r79, r80);
								}
						}
						else if((*it)->getPosition().get_y()>1500)
						{
							Land(*it, r19, r1, r2, r3);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r73, r74, r75, r76, r77, r78, r79, r80);
								}
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500)
						{
							Land(*it, r20, r1, r2, r3);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r59, r58, r57, r64, r63, r62, r61, r60);
								}
						}
						vacia = false;
					}
				}


}
