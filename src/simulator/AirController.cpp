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
AirController::asignarLanding(Flight *f)
{
	float x03=12000, x02=9000, x01=6000, x0=5000, x1=1500, x2=200, x3=-750;
	float y0=0, y1=0, y2=0, y3=0;

	Position pos03bl(10000, -7000, 3000.0);
	Position pos03br(10000, 7000, 3000.0);
	Position pos03(x03, y0+1500, 2000.0);

	Position pos02bl(10000, -7000, 850.0);
	Position pos02br(10000, 7000, 850.0);
	Position pos02(x02, y0-1000, 850.0);

	Position pos01(x01, y0+1000, 300.0);

	Position pos0(x0, y0, 180.0);
	Position pos1(x1, y1, 50.0);
	Position pos2(x2, y2, 25.0);
	Position pos3(x3, y3, 25.0);

	Route r02br,r02bl, r03br,r03bl, r03, r02, r01, r0,r1,r2,r3;

	r02br.pos = pos02br;
	r02br.speed = 250.0;
	r03br.pos = pos03br;
	r03br.speed = 250.0;
	r02bl.pos = pos02bl;
	r02bl.speed = 250.0;
	r03bl.pos = pos03bl;
	r03bl.speed = 250.0;
	r03.pos = pos03;
	r03.speed = 250.0;
	r02.pos = pos02;
	r02.speed = 200.0;
	r01.pos = pos01;
	r01.speed = 200.0;
	r0.pos = pos0;
	r0.speed = 180.0;
	r1.pos = pos1;
	r1.speed = 150.0;
	r2.pos = pos2;
	r2.speed = 50.0;
	r3.pos = pos3;
	r3.speed = 15.0;

	f->getRoute()->clear();
	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);

	if ((f->getPosition().get_y())<0 && (f->getPosition().get_x())<7000)
	{
		if (f->getPosition().get_z()>1350)
		{
			f->getRoute()->push_front(r03);
			f->getRoute()->push_front(r03bl);

		}
		else if (f->getPosition().get_z()<550)
		{
			f->getRoute()->push_front(r01);
		}
		else
		{
			f->getRoute()->push_front(r02);
			f->getRoute()->push_front(r02bl);
		}
	}

	else if ((f->getPosition().get_y())>0 && (f->getPosition().get_x())<7000)
	{
		if (f->getPosition().get_z()>1350)
		{
			f->getRoute()->push_front(r03);
			f->getRoute()->push_front(r03br);

		}
		else if (f->getPosition().get_z()<550)
		{
			f->getRoute()->push_front(r01);
		}
		else
		{
			f->getRoute()->push_front(r02);
			f->getRoute()->push_front(r02br);
		}
	}
	else
	{
		if (f->getPosition().get_z()>1350)
		{
			f->getRoute()->push_front(r03);
		}
		else if (f->getPosition().get_z()<550)
		{
			f->getRoute()->push_front(r01);
		}
		else
		{
			f->getRoute()->push_front(r02);
		}
	}

	f->setisLanding(true);
	f->setisWaiting(false);

std::cout <<f->getId()<< " Proceda Aterrizaje" << std::endl;
}

void
AirController::asignarWaitingR(Flight *f)
{
	float yA=3500.0, yB=18000.0;
	float xC3=-2000.0, xC2=-3000.0;

	Position pos4r(17000.0, yA, 3000.0);
	Position pos5r(xC3, yA, 2200.0);
	Position pos6r(xC3, yB, 1800.0);
	Position pos7r(17000.0, yB, 1350.0);
	Position pos8r(16000.0, yA, 1050.0);
	Position pos9r(xC2, yA, 850.0);
	Position pos10r(xC2, yB, 550.0);
	Position pos11r(16000.0, yB, 300.0);
	Position pos12r(17000.0, yA, 220.0);
	Position pos12_5r(9000.0, yA, 200.0);

	Route r4r,r5r,r6r,r7r,r8r,r9r,r10r,r11r,r12r,r12_5r;

	r4r.pos = pos4r;
	r4r.speed = 100.0;
	r5r.pos = pos5r;
	r5r.speed = 100.0;
	r6r.pos = pos6r;
	r6r.speed = 100.0;
	r7r.pos = pos7r;
	r7r.speed = 100.0;
	r8r.pos = pos8r;
	r8r.speed = 100.0;
	r9r.pos = pos9r;
	r9r.speed = 100.0;
	r10r.pos = pos10r;
	r10r.speed = 100.0;
	r11r.pos = pos11r;
	r11r.speed = 100.0;
	r12r.pos = pos12r;
	r12r.speed = 100.0;

	r12_5r.pos = pos12_5r;
	r12_5r.speed = 100.0;

	f->getRoute()->clear();
	f->getRoute()->push_back(r12_5r);
	f->getRoute()->push_front(r12r);
	f->getRoute()->push_front(r11r);
	f->getRoute()->push_front(r10r);
	f->getRoute()->push_front(r9r);
	f->getRoute()->push_front(r8r);
	f->getRoute()->push_front(r7r);
	f->getRoute()->push_front(r6r);
	f->getRoute()->push_front(r5r);
	f->getRoute()->push_front(r4r);
}

void
AirController::asignarWaitingL(Flight *f)
{
	float yA=3500.0, yB=18000.0;
	float xC3=-2000.0, xC2=-3000.0;

	Position pos4l(17000.0, -yA, 3000.0);
	Position pos5l(xC3, -yA, 2200.0);
	Position pos6l(xC3, -yB, 1800.0);
	Position pos7l(17000.0, -yB, 1350.0);
	Position pos8l(16000.0, -yA, 1050.0);
	Position pos9l(xC2, -yA, 850.0);
	Position pos10l(xC2, -yB, 550.0);
	Position pos11l(16000.0, -yB, 300.0);
	Position pos12l(17000.0, -yA, 220.0);
	Position pos12_5l(9000.0, -yA, 200.0);

	Route r4l,r5l,r6l,r7l,r8l,r9l,r10l,r11l,r12l, r12_5l;

	r4l.pos = pos4l;
	r4l.speed = 100.0;
	r5l.pos = pos5l;
	r5l.speed = 100.0;
	r6l.pos = pos6l;
	r6l.speed = 100.0;
	r7l.pos = pos7l;
	r7l.speed = 100.0;
	r8l.pos = pos8l;
	r8l.speed = 100.0;
	r9l.pos = pos9l;
	r9l.speed = 100.0;
	r10l.pos = pos10l;
	r10l.speed = 100.0;
	r11l.pos = pos11l;
	r11l.speed = 100.0;
	r12l.pos = pos12l;
	r12l.speed = 100.0;
	r12_5l.pos = pos12_5l;
	r12_5l.speed = 100.0;

	f->getRoute()->clear();
	f->getRoute()->push_back(r12_5l);
	f->getRoute()->push_front(r12l);
	f->getRoute()->push_front(r11l);
	f->getRoute()->push_front(r10l);
	f->getRoute()->push_front(r9l);
	f->getRoute()->push_front(r8l);
	f->getRoute()->push_front(r7l);
	f->getRoute()->push_front(r6l);
	f->getRoute()->push_front(r5l);
	f->getRoute()->push_front(r4l);
}

void
AirController::asignarWaitingCenter1(Flight *f)
{
	float	xC1=-4000.0, xC2=-17000.0;
	float yCR=2500.0, yCL=14500.0, incYC=-1000;;
	float zC1=3000.0, zC2=2000;

	Position posC1(xC1, yCL, zC1);
	Position posC2(xC2, yCL, zC1-400);
	Position posC3(xC2, yCR, zC1-600);
	Position posC4(xC1, yCR, zC1-800);

	Position posC5(xC1, yCL+incYC, zC2);
	Position posC6(xC2, yCL+incYC, zC2-400);
	Position posC7(xC2, yCR+incYC, zC2-600);
	Position posC8(xC1, yCR+incYC, zC2-800);

	Route r1c,r2c,r3c,r4c,r5c,r6c,r7c,r8c;

	r1c.pos = posC1;
	r1c.speed = 100.0;
	r2c.pos = posC2;
	r2c.speed = 100.0;
	r3c.pos = posC3;
	r3c.speed = 100.0;
	r4c.pos = posC4;
	r4c.speed = 100.0;
	r5c.pos = posC5;
	r5c.speed = 100.0;
	r6c.pos = posC6;
	r6c.speed = 100.0;
	r7c.pos = posC7;
	r7c.speed = 100.0;
	r8c.pos = posC8;
	r8c.speed = 100.0;

	f->getRoute()->clear();
	f->getRoute()->push_back(r8c);
	f->getRoute()->push_front(r7c);
	f->getRoute()->push_front(r6c);
	f->getRoute()->push_front(r5c);
	f->getRoute()->push_front(r4c);
	f->getRoute()->push_front(r3c);
	f->getRoute()->push_front(r2c);
	f->getRoute()->push_front(r1c);
}

void
AirController::asignarWaitingCenter2(Flight *f)
{
	float	xC1=-4000.0, xC2=-17000.0;
	float yCR=2500.0, yCL=14500.0, incYC=-1000;;
	float zC1=3000.0, zC2=2000;

	Position posC1(xC1, -yCL, zC1);
	Position posC2(xC2, -yCL, zC1-400);
	Position posC3(xC2, -yCR, zC1-600);
	Position posC4(xC1, -yCR, zC1-800);

	Position posC5(xC1, -yCL+incYC, zC2);
	Position posC6(xC2, -yCL+incYC, zC2-400);
	Position posC7(xC2, -yCR+incYC, zC2-600);
	Position posC8(xC1, -yCR+incYC, zC2-800);

	Route r1c,r2c,r3c,r4c,r5c,r6c,r7c,r8c;

	r1c.pos = posC1;
	r1c.speed = 100.0;
	r2c.pos = posC2;
	r2c.speed = 100.0;
	r3c.pos = posC3;
	r3c.speed = 100.0;
	r4c.pos = posC4;
	r4c.speed = 100.0;
	r5c.pos = posC5;
	r5c.speed = 100.0;
	r6c.pos = posC6;
	r6c.speed = 100.0;
	r7c.pos = posC7;
	r7c.speed = 100.0;
	r8c.pos = posC8;
	r8c.speed = 100.0;

	f->getRoute()->clear();
	f->getRoute()->push_back(r8c);
	f->getRoute()->push_front(r7c);
	f->getRoute()->push_front(r6c);
	f->getRoute()->push_front(r5c);
	f->getRoute()->push_front(r4c);
	f->getRoute()->push_front(r3c);
	f->getRoute()->push_front(r2c);
	f->getRoute()->push_front(r1c);
}

void
AirController::asignarWaiting(Flight *f)
{
			if((f->getPosition().get_y()>=0) && (f->getPosition().get_x()>=15000) )
				{
					asignarWaitingR(f);
				}
			else if((f->getPosition().get_y()<0)&&(f->getPosition().get_x()>=15000))
				{
					asignarWaitingL(f);
				}
			else if((f->getPosition().get_y()>0)&&(f->getPosition().get_x()<15000))
				{
					asignarWaitingCenter1(f);
				}
			else
				{
					asignarWaitingCenter2(f);
				}
f->setisWaiting(true);
f->setisLanding(false);
//std::cout <<f->getId()<< " Realice ruta de espera" << std::endl;
}

float
AirController::DistanciaAv_Punto(Flight *f,float x2,float y2, float z2 )
{
	float x1=f->getPosition().get_x();
	float y1=f->getPosition().get_y();
	float z1=f->getPosition().get_z();
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

float
AirController::DistanciaAv_Av(Flight *f1,Flight *f2 )
{
	float x1=f1->getPosition().get_x();
	float y1=f1->getPosition().get_y();
	float z1=f1->getPosition().get_z();
	float x2=f2->getPosition().get_x();
	float y2=f2->getPosition().get_y();
	float z2=f2->getPosition().get_z();
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}
float
AirController::DistanciaStorm_Aeropuerto(Storm *s)
{
	Position pos3(0, 0, 25.0);

	float x1=s->getPosition().get_x();
	float y1=s->getPosition().get_y();
	float z1=s->getPosition().get_z();

	float x2=pos3.get_x();
	float y2=pos3.get_y();
	float z2=pos3.get_z();
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}
float
AirController::DistanciaStorm_Av(Storm *s,Flight *f)
{
	float x1=s->getPosition().get_x();
	float y1=s->getPosition().get_y();
	float z1=s->getPosition().get_z();

	float x2=f->getPosition().get_x();
	float y2=f->getPosition().get_y();
	float z2=f->getPosition().get_z();
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

float
AirController::GetAnguloGiro(Storm *s,Flight *f)
{
	float x0=f->getPosition().get_x();
	float y0=f->getPosition().get_y();
	float x1=s->getPosition().get_x();
	float y1=s->getPosition().get_y();
	float pendiente_recta=(y1-y0)/(x1-x0);
	float pendiente_recta_tangente=(-1)/pendiente_recta;
	return atan(pendiente_recta_tangente);
}

float
AirController::DistanciaAvion_WayPoint(Flight *f)
{
	float x1=f->getPosition().get_x();
	float y1=f->getPosition().get_y();
	float z1=f->getPosition().get_z();

	float x1p=1500, y1p=0;
	Position pos1(x1p, y1p, 50.0);
	float x2=pos1.get_x();
	float y2=pos1.get_y();
	float z2=pos1.get_z();
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
}

void
AirController::TCAS_System(Flight *f, Flight *f2 )
{
	if (f!=f2)
	{
		float dist_margen2=500;
		float dist_seguridad2=1000+dist_margen2;
		float Distancia_Av1_Av2=DistanciaAv_Av((f), (f2));
		if (Distancia_Av1_Av2<dist_seguridad2)
		{
			float h2=sqrt(Distancia_Av1_Av2*Distancia_Av1_Av2+dist_seguridad2*dist_seguridad2);
			float alpha2=asin(dist_seguridad2/h2);
			(f)->setBearing(alpha2);
			//(f)->setSpeed(f->getSpeed()+10);
			//(f2)->setSpeed(f->getSpeed()-20);
			(f2)->setBearing(-alpha2);
			std::cout << "TCAS activado" << std::endl;
		}
	}
}

void
AirController::EvitarStorm(Storm *s,Flight *f)
{
	if (s != NULL)
	{
		float Radio_Strom= s->getRadious();
		float dist_margen=2500;
		float dist_seguridad=Radio_Strom+dist_margen;
		float Distancia_Av_Strom=DistanciaStorm_Av(s, (f));

		if (Distancia_Av_Strom<dist_seguridad)
		{
				if ((f->getPosition().get_y()<=0) &&(f->getPosition().get_x()>=-3000.0))
					{
						asignarWaitingCenter1(f);
						//std::cout << "1" << std::endl;
					}
					else if ((f->getPosition().get_y()>=0) && (f->getPosition().get_x()>=-3000.0))
					{
						asignarWaitingCenter2(f);
						//std::cout << "2" << std::endl;
					}
					if ((f->getPosition().get_y()<=0) &&(f->getPosition().get_x()<=-3000.0))
					{
						asignarWaitingR(f);
						//std::cout << "3" << std::endl;
					}
					else if ((f->getPosition().get_y()>=0) && (f->getPosition().get_x()<=-3000.0))
					{
						asignarWaitingL(f);
						//std::cout << "4" << std::endl;
					}
		}
	}

/*/////////////////PARTE Esquivo Rapido //////////////
		float Radio_Strom= s->getRadious();
		float dist_margen=2500;
		float dist_seguridad=Radio_Strom+dist_margen;
		float Distancia_Av_Strom=DistanciaStorm_Av(s, (f));
		float angulo=GetAnguloGiro(s,f);
		if (Distancia_Av_Strom<dist_seguridad)
		{
			(f)->setBearing(angulo);
		}
	}
*//////////////////////////////////////////////////////////
}

/////////////////////////////////////////AMBITO DE CONTROL ////////////////
void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it, it2, it3;
			Storm *storm = Airport::getInstance()->getStorm();

/////////////////////////RUTAS DE ESPERA////////////////////////////////////
for(it = flights.begin(); it!=flights.end(); ++it)
{
	if (((*it)->getRoute()->empty())&&(it == flights.begin()))
			{
				asignarLanding(*it);
			}
	else if ((*it)->getRoute()->empty())
			{
				asignarWaiting(*it);
			}
}
for(it = flights.begin(); it!=flights.end(); ++it)
{
	if ((it == flights.begin())&&((*it)->getisWaiting())&&(!(*it)->getisLanding()))
			{
				asignarLanding(*it);
			}
}
/////////////////////////////////TORMENTA/////////////////////////////////////
/*
for(it = flights.begin(); it!=flights.end(); ++it)
{
	if (((*it)->getisWaiting())&&(!(*it)->getisLanding()))
	{
		EvitarStorm(storm,(*it));
	}
}
*/
///////////////////////////////////////CHOQUE AVIONES///////////////////////
for(it = flights.begin(); it!=flights.end(); ++it)
{
	for(it2 = flights.begin(); it2!=flights.end(); ++it2)
	{
		TCAS_System((*it),(*it2));
	}
}
}//Cierre del doWork
