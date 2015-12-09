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
	setLanding(false);

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::asignarLanding(Flight *f, Route a, Route b, Route c, Route d)
{
	setLanding(true);

	f->getRoute()->clear();
	f->getRoute()->push_back(d);
	f->getRoute()->push_front(c);
	f->getRoute()->push_front(b);
	f->getRoute()->push_front(a);
	//setLanding(false);

}
void
AirController::asignarWaiting(Flight *f, Route a, Route b, Route c, Route d)
{
	setLanding(false);
	f->getRoute()->clear();
	f->getRoute()->push_front(d);
	f->getRoute()->push_front(c);
	f->getRoute()->push_front(b);
	f->getRoute()->push_front(a);

}



void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			float R=8700;
			float x4=R*sin(15*pi/180), x5=R*sin(45*pi/180) ;//x6=R*sin(75*pi/180);
			float x7=R*sin(89*pi/180), x8=R*sin(45*pi/180), x9=R*sin(15*pi/180);
			float y4=-R*cos(15*pi/180), y5=-R*cos(45*pi/180) ;//y6=-R*cos(75*pi/180);
			float y7=R*cos(89*pi/180), y8=R*cos(45*pi/180), y9=R*cos(15*pi/180);

			Position pos0(3000.0, 0.0, 100.0);
			Position pos1(1500.0, 0.0, 50.0);
			Position pos2(200.0, 0.0, 25.0);
			Position pos3(-750.0, 0.0, 25.0);

			Position pos4(x4, y4, 150.0);
			Position pos41(x4, y4+1500.0, 150.0);
			Position pos42(x4-1000.0, y4+1500, 150.0);
			Position pos43(x4-1000.0, y4, 150.0);

			Position pos5(x5, y5, 150.0);
			Position pos51(x5-1220.60, y5+871.85759, 150.0);
			Position pos52(x5-2034.333, y5+290.6237, 150.0);
			Position pos53(x5-813.733, y5-581.2388, 150.0);

			Position pos7(x7, y7, 150.0);
			Position pos71(x7-1500, y7, 150.0);
			Position pos72(x7-1500, y7+3500, 150.0);
			Position pos73(x7, y7+3500, 150.0);

			Position pos8(x8, y8, 150.0);
			Position pos81(x8-1220.60, y8-871.85759, 150.0);
			Position pos82(x8-2034.333, y8-290.6237, 150.0);
			Position pos83(x8-813.733, y8+581.2388, 150.0);

			Position pos9(x9, y9, 150.0);
			Position pos91(x9, y9-1500.0, 150.0);
			Position pos92(x9-1000.0, y9-1500, 150.0);
			Position pos93(x9-1000.0, y9, 150.0);


			Route r0,r1,r2,r3, r4,r41,r42,r43, r5,r51,r52,r53;
			Route r7,r71,r72,r73, r8,r81,r82,r83, r9,r91,r92,r93;

			r0.pos = pos0;
			r0.speed = 170.0;
			r1.pos = pos1;
			r1.speed = 100.0;
			r2.pos = pos2;
			r2.speed = 50.0;
			r3.pos = pos3;
			r3.speed = 15.0;

			r4.pos = pos4;
			r4.speed = 205.0;
			r41.pos = pos41;
			r41.speed = 205.0;
			r42.pos = pos42;
			r42.speed = 205.0;
			r43.pos = pos43;
			r43.speed = 205.0;

			r5.pos = pos5;
			r5.speed = 205.0;
			r51.pos = pos51;
			r51.speed = 205.0;
			r52.pos = pos52;
			r52.speed = 205.0;
			r53.pos = pos53;
			r53.speed = 205.0;

			r7.pos = pos7;
			r7.speed = 205.0;
			r71.pos = pos71;
			r71.speed = 190.0;
			r72.pos = pos72;
			r72.speed = 190.0;
			r73.pos = pos73;
			r73.speed = 190.0;

			r8.pos = pos8;
			r8.speed = 205.0;
			r81.pos = pos81;
			r81.speed = 190.0;
			r82.pos = pos82;
			r82.speed = 190.0;
			r83.pos = pos83;
			r83.speed = 190.0;

			r9.pos = pos9;
			r9.speed = 205.0;
			r91.pos = pos91;
			r91.speed = 190.0;
			r92.pos = pos92;
			r92.speed = 190.0;
			r93.pos = pos93;
			r93.speed = 190.0;


			for(it = flights.begin(); it!=flights.end(); ++it)
			{

				float angulo=(atan((*it)->getPosition().get_x()/(*it)->getPosition().get_y()));
				float anguloGrados= angulo/pi*180;

				if(getLanding()==false)///SI NO HAY NADIE ATERRIZANDO VA A ATERRIZAR
				{//DIFERENTES RUTAS DE ATERRIZAJE SEGÚN LA ZONA POR LA QUE VENGAN
					if(((anguloGrados<0) && (anguloGrados>-30))&&((*it)->getRoute()->empty()))
					{
						asignarLanding(*it, r0, r1, r2, r3);
						(*it)->getRoute()->push_front(r4);
					}
					else if(((anguloGrados<-30) && (anguloGrados>-60))&&((*it)->getRoute()->empty()))
					{
						asignarLanding(*it, r0, r1, r2, r3);
						(*it)->getRoute()->push_front(r5);
					}
					else if(((anguloGrados>0) && (anguloGrados<30))&&((*it)->getRoute()->empty()))
					{
						asignarLanding(*it, r0, r1, r2, r3);
						(*it)->getRoute()->push_front(r9);
					}
					else if(((anguloGrados>30) && (anguloGrados<60))&&((*it)->getRoute()->empty()))
					{
						asignarLanding(*it, r0, r1, r2, r3);
						(*it)->getRoute()->push_front(r8);
					}
					else if((fabs(anguloGrados)>60)&&((*it)->getRoute()->empty()))
					{
						asignarLanding(*it, r0, r1, r2, r3);
						(*it)->getRoute()->push_front(r7);
					}
				}else//SI HAY ALGUIEN ATERRIZANDO REALIZAN RUTA DE ESPERA HASTA QUE QUEDE LIBRE
				{//DIFERENTES RUTAS DE ESPERA SEGÚN LA ZONA DE APROXIMACION
					if(((anguloGrados<0) && (anguloGrados>-30))&&((*it)->getRoute()->empty()))
					{
						asignarWaiting(*it, r41, r42, r43, r4);
						asignarWaiting(*it, r41, r42, r43, r4);
						asignarWaiting(*it, r41, r42, r43, r4);

						(*it)->getRoute()->push_front(r4);

					}
					else if(((anguloGrados<-30) && (anguloGrados>-60))&&((*it)->getRoute()->empty()))
					{
						asignarWaiting(*it, r51, r52, r53, r5);
						asignarWaiting(*it, r51, r52, r53, r5);
						asignarWaiting(*it, r51, r52, r53, r5);

						(*it)->getRoute()->push_front(r5);

					}
					else if(((anguloGrados>0) && (anguloGrados<30))&&((*it)->getRoute()->empty()))
					{
						asignarWaiting(*it, r91, r92, r93, r9);
						asignarWaiting(*it, r91, r92, r93, r9);
						asignarWaiting(*it, r91, r92, r93, r9);

						(*it)->getRoute()->push_front(r9);

					}
					else if(((anguloGrados>30) && (anguloGrados<60))&&((*it)->getRoute()->empty()))
					{
						asignarWaiting(*it, r81, r82, r83, r8);
						asignarWaiting(*it, r81, r82, r83, r8);
						asignarWaiting(*it, r81, r82, r83, r8);

						(*it)->getRoute()->push_front(r8);

					}
					else if((fabs(anguloGrados)>60)&&((*it)->getRoute()->empty()))
					{
						asignarWaiting(*it, r71, r72, r73, r7);
						asignarWaiting(*it, r71, r72, r73, r7);
						asignarWaiting(*it, r71, r72, r73, r7);

						(*it)->getRoute()->push_front(r7);

					}
/*
				if((*it)->getRoute()->empty())
				{
					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r0);
*/
				}
			}
}
