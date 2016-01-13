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
void AirController::Waiting(Flight *flight, Route a, Route b, Route c, Route d, Route e, Route f, Route g, Route h, Route k, Route l, Route m, Route n, Route o, Route p)
{

	flight->setLanding(false);
	flight->getRoute()->clear();
	flight->getRoute()->push_front(p);
	flight->getRoute()->push_front(o);
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

void AirController::Emergency(Flight *flight, Route a, Route b, Route c, Route d, Route e, Route f, Route g, Route h, Route k, Route l)
{
	flight->getRoute()->clear();
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
			std::list<Flight*>::iterator it2;
			std::list<Flight*>::iterator it3;
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

			//Ruta de espera izquierda modificada
			Position pos4(1500.0, -7000.0, 900.0);
			Position pos5(3000.0, -9000.0, 900.0);
			Position pos6(4500.0, -9000.0, 900.0);
			Position pos7(6000.0, -9000.0, 900.0);
			Position pos8(7500.0, -9000.0, 900.0);
			Position pos9(9000.0, -9000.0, 900.0);
			Position pos10(10500.0, -9000.0, 900.0);
			Position pos11(12000.0, -7000.0, 900.0);
			Position pos12(10500.0, -5000.0, 900.0);
			Position pos13(9000.0, -5000.0, 900.0);
			Position pos14(7500.0, -5000.0, 900.0);
			Position pos15(6000.0, -5000.0, 900.0);
			Position pos16(4500.0, -5000.0, 900.0);
			Position pos17(3000.0, -5000.0, 900.0);

			//Ruta espera derecha modificada
			Position pos21(1500.0, 7000.0, 900.0);
			Position pos22(3000.0, 9000.0, 900.0);
			Position pos23(4500.0, 9000.0, 900.0);
			Position pos24(6000.0, 9000.0, 900.0);
			Position pos25(7500.0, 9000.0, 900.0);
			Position pos26(9000.0, 9000.0, 900.0);
			Position pos27(10500.0, 9000.0, 900.0);
			Position pos28(12000.0, 7000.0, 900.0);
			Position pos29(10500.0, 5000.0, 900.0);
			Position pos30(9000.0, 5000.0, 900.0);
			Position pos31(7500.0, 5000.0, 900.0);
			Position pos32(6000.0, 5000.0, 900.0);
			Position pos33(4500.0, 5000.0, 900.0);
			Position pos34(3000.0, 5000.0, 900.0);

			//Ruta espera centro modificada

			Position pos35(3000.0, 0.0, 600.0);
			Position pos36(3000.0, -1000.0, 600.0);
			Position pos37(4500.0, -1000.0, 600.0);
			Position pos38(6000.0, -1000.0, 600.0);
			Position pos39(7500.0, -1000.0, 600.0);
			Position pos40(9000.0, -1000.0, 600.0);
			Position pos41(10500.0, -1000.0, 600.0);
			Position pos42(12000.0, 0.0, 600.0);
			Position pos43(10500.0, 1000.0, 600.0);
			Position pos44(9000.0, 1000.0, 600.0);
			Position pos45(7500.0, 1000.0, 600.0);
			Position pos46(6000.0, 1000.0, 600.0);
			Position pos47(4500.0, 1000.0, 600.0);
			Position pos48(3000.0, 1000.0, 600.0);


			//Ruta emergencia izquierda
			Position pos49(-1500.0, -6000.0, 1500.0);
			Position pos50(-3000.0, -6000.0, 1500.0);
			Position pos51(-4500.0, -6000.0, 1500.0);
			Position pos52(-6000.0, -6000.0, 1500.0);
			Position pos53(-7500.0, -7000.0, 1500.0);
			Position pos54(-6000.0, -8000.0, 1500.0);
			Position pos55(-4500.0, -8000.0, 1500.0);
			Position pos56(-3000.0, -8000.0, 1500.0);
			Position pos57(-1500.0, -8000.0, 1500.0);
			Position pos58(0.0, -7000.0, 1500.0);

			//Ruta emergencia derecha
			Position pos59(-1500.0, 6000.0, 2530.0);
			Position pos60(-3000.0, 6000.0, 2400.0);
			Position pos61(-4500.0, 6000.0, 2300.0);
			Position pos62(-6000.0, 6000.0, 2200.0);
			Position pos63(-7500.0, 7000.0, 2100.0);
			Position pos64(-6000.0, 8000.0, 2000.0);
			Position pos65(-4500.0, 8000.0, 1900.0);
			Position pos66(-3000.0, 8000.0, 1800.0);
			Position pos67(-1500.0, 8000.0, 1700.0);
			Position pos68(0.0, 7000.0, 1500.0);

			//Ruta emergencia centro

			Position pos69(-4500.0, -1400.0, 1500.0);
			Position pos70(-6000.0, -1400.0, 1500.0);
			Position pos71(-7500.0, -1400.0, 1500.0);
			Position pos72(-9000.0, -1400.0, 1500.0);
			Position pos73(-10500.0, 0.0, 1500.0);
			Position pos74(-9000.0, 1400.0, 1500.0);
			Position pos75(-7500.0, 1400.0, 1500.0);
			Position pos76(-6000.0, 1400.0, 1500.0);
			Position pos77(-4500.0, 1400.0, 1500.0);
			Position pos78(-3000.0, 0.0, 1500.0);




			Route r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18;
			Route r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32, r33, r34;
			Route r35, r36, r37, r38, r39, r40, r41, r42, r43, r44, r45, r46, r47, r48, r49, r50, r51;
			Route r52, r53, r54, r55, r56, r57, r58, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68;
			Route r69, r70, r71, r72, r73, r74, r75, r76, r77, r78;

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

			//Puntos de entrada

			r18.speed = 500;
			r18.pos = pos18;
			r19.speed = 500;
			r19.pos = pos19;
			r20.speed = 500;
			r20.pos = pos20;

			//Rutas de espera

			r4.pos = pos4;
			r4.speed = 300;
			r5.pos = pos5;
			r5.speed = 300;
			r6.pos = pos6;
			r6.speed = 300;
			r7.pos = pos7;
			r7.speed = 300;
			r8.pos = pos8;
			r8.speed = 300;
			r9.pos = pos9;
			r9.speed = 300;
			r10.pos = pos10;
			r10.speed = 300;
			r11.pos = pos11;
			r11.speed = 300;
			r12.pos = pos12;
			r12.speed = 300;
			r13.pos = pos13;
			r13.speed = 300;
			r14.pos = pos14;
			r14.speed = 300;
			r15.pos = pos15;
			r15.speed = 300;
			r16.pos = pos16;
			r16.speed = 300;
			r17.pos = pos17;
			r17.speed = 300;
			r21.pos = pos21;
			r21.speed = 300;
			r22.pos = pos22;
			r22.speed = 300;
			r23.pos = pos23;
			r23.speed = 300;
			r24.pos = pos24;
			r24.speed = 300;
			r25.pos = pos25;
			r25.speed = 300;
			r26.pos = pos26;
			r26.speed = 300;
			r27.pos = pos27;
			r27.speed = 300;
			r28.pos = pos28;
			r28.speed = 300;
			r29.pos = pos29;
			r29.speed = 300;
			r30.pos = pos30;
			r30.speed = 300;
			r31.pos = pos31;
			r31.speed = 300;
			r32.pos = pos32;
			r32.speed = 300;
			r33.pos = pos33;
			r33.speed = 300;
			r34.pos = pos34;
			r34.speed = 300;
			r35.pos = pos35;
			r35.speed = 300;
			r36.pos = pos36;
			r36.speed = 300;
			r37.pos = pos37;
			r37.speed = 300;
			r38.pos = pos38;
			r38.speed = 300;
			r39.pos = pos39;
			r39.speed = 300;
			r40.pos = pos40;
			r40.speed = 300;
			r41.pos = pos41;
			r41.speed = 300;
			r42.pos = pos42;
			r42.speed = 300;
			r43.pos = pos43;
			r43.speed = 300;
			r44.pos = pos44;
			r44.speed = 300;
			r45.pos = pos45;
			r45.speed = 300;
			r46.pos = pos46;
			r46.speed = 300;
			r47.pos = pos47;
			r47.speed = 300;
			r48.pos = pos48;
			r48.speed = 300;

			//Rutas emergencia
			r49.pos = pos49;
			r49.speed = 300;
			r50.pos = pos50;
			r50.speed = 300;
			r51.pos = pos51;
			r51.speed = 300;
			r52.pos = pos52;
			r52.speed = 300;
			r53.pos = pos53;
			r53.speed = 300;
			r54.pos = pos54;
			r54.speed = 300;
			r55.pos = pos55;
			r55.speed = 300;
			r56.pos = pos56;
			r56.speed = 300;
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


				if(storm != NULL){
					for(it = flights.begin(); it!=flights.end(); ++it){
						dis = getDistancia(storm->getPosition().get_x(), (*it)->getPosition().get_x(), storm->getPosition().get_y() , (*it)->getPosition().get_y());
							if(dis - storm->getRadious()< DISTALERT){
								if(storm->getPosition().get_y()<-1500 && (*it)->getRoute()->empty()) {
									Emergency(*it, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68);
								}
								else if(storm->getPosition().get_y()>1500 && (*it)->getRoute()->empty()){
									Emergency(*it, r58, r57, r56, r55, r54, r53, r52, r51, r50, r49);
								}
								else if(storm->getPosition().get_y()<1500 && storm->getPosition().get_x()>-1500 && (*it)->getRoute()->empty()){
									Emergency(*it, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68);
								}
							}
						}
					}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
						if((*it)->getPosition().get_y()<-1500 && (*it)->getRoute()->empty()) {
							Waiting(*it, r4, r17, r16, r15, r14, r13, r12, r11, r10, r9, r8, r7, r6, r5);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68);
								}
						}
						else if((*it)->getPosition().get_y()>1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r21, r34, r33, r32, r31, r30, r29, r28, r27, r26, r25, r24, r23, r22);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r58, r57, r56, r55, r54, r53, r52, r51, r50, r49);
								}
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500 && (*it)->getRoute()->empty()){
							Waiting(*it, r35, r48, r47, r46, r45, r44, r43, r42, r41, r40, r39, r38, r37, r36);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68);
								}
						}
				}

				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if((*it)->getLanding() && (*it)->getPosition().get_z()>30)
						vacia = false;
				}


				if(storm != NULL)
				{
					for(it = flights.begin(); it!=flights.end(); ++it){
						if(storm->getBearing()>=0.19*M_PI && storm->getBearing()<=0.3*M_PI){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
						else if(storm->getBearing()>=1.66*M_PI && storm->getBearing()<=1.83*M_PI){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
						else if(storm->getBearing()>=0.66*M_PI && storm->getBearing()<=0.8*M_PI){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
						else if(storm->getBearing()>=1.16*M_PI && storm->getBearing()<=1.33*M_PI){
							vacia = false;
							std::cout<<"Aeropuerto Cerrado"<<std::endl;
						}
					}
				}


				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					if(vacia && !(*it)->getLanding())
					{
						if((*it)->getPosition().get_y()<-1500)
						{
							Land(*it, r18, r1, r2, r3);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68);
								}
						}
						else if((*it)->getPosition().get_y()>1500)
						{
							Land(*it, r19, r1, r2, r3);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r58, r57, r56, r55, r54, r53, r52, r51, r50, r49);
								}
						}
						else if((*it)->getPosition().get_y()<1500 && (*it)->getPosition().get_x()>-1500)
						{
							Land(*it, r20, r1, r2, r3);
								if(storm != NULL && dis - storm->getRadious()< DISTALERT){
									Emergency(*it, r59, r60, r61, r62, r63, r64, r65, r66, r67, r68);
								}
						}
						vacia = false;
					}
				}

				for(it = flights.begin(); it!=flights.end(); ++it){
					for(it3 = it; it3!=flights.end(); ++it3){
						float distancia = getDistancia((*it)->getPosition().get_x(), (*it3)->getPosition().get_x(), (*it)->getPosition().get_y(), (*it3)->getPosition().get_y());
						if(distancia < 2000.0 && distancia > 0.0){
							float velocidad = (*it3)->getSpeed()/2;
							(*it)->setSpeed(velocidad);
							//(*it)->getBearing() == (*it)->getBearing()+M_PI/3;
							std::cout<<"Peligro de colision"<<std::endl;
						}
					}
				}


}
