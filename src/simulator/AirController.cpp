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
#define MARGENSEGURIDAD 2000
#define MARGENSEGURIDAD_AIRPORT 1000
#define VELOCIDADANTICOLISION 10
#define ALTURAANTICOLISION 1500


AirController::AirController() {
	ruta_ocupada = false;
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

double
CalcularDistancia(double x1, double y1, double x2, double y2)
{
  double distancia;
  distancia= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  return distancia;
}

void
AirController::AssignWaiting(Flight *f)
{
	//Centro
				Position pos0_0_A(11000.0, 0.0, 500.0);
				Position pos0_1_A(9500.0, 2500.0, 500.0);
				Position pos0_2_A(6500.0, 0.0, 500.0);
				Position pos0_3_A(9500.0, -2500.0, 500.0);
	//Lado izquierdo
				Position pos0_0_B(13500.0, -13500.0, 500.0);
				Position pos0_1_B(13500.0, -2000.0, 500.0);
				Position pos0_2_B(5000.0, -2000.0, 500.0);
				Position pos0_3_B(5000.0, -13500.0, 500.0);
	//Lado derecho
				Position pos0_0_C(13500.0, 13500.0, 500.0);
				Position pos0_1_C(13500.0, 2000.0, 500.0);
				Position pos0_2_C(5000.0, 2000.0, 500.0);
				Position pos0_3_C(5000.0, 13500.0,500.0);



				Route r0_0_A, r0_1_A,r0_2_A,r0_3_A, r0_0_B, r0_1_B,r0_2_B,r0_3_B;
				Route r0_0_C, r0_1_C,r0_2_C,r0_3_C;

	//Centro
				r0_0_A.pos = pos0_0_A;
				r0_0_A.speed = 200.0;
				r0_1_A.pos = pos0_1_A;
				r0_1_A.speed = 100.0;
				r0_2_A.pos = pos0_2_A;
				r0_2_A.speed = 100.0;
				r0_3_A.pos = pos0_3_A;
				r0_3_A.speed = 100.0;
	//Lado izquierdo
				r0_0_B.pos = pos0_0_B;
				r0_0_B.speed = 200.0;
				r0_1_B.pos = pos0_1_B;
				r0_1_B.speed = 100.0;
				r0_2_B.pos = pos0_2_B;
				r0_2_B.speed = 100.0;
				r0_3_B.pos = pos0_3_B;
				r0_3_B.speed = 100.0;
	//Lado derecho
				r0_0_C.pos = pos0_0_C;
				r0_0_C.speed = 200.0;
				r0_1_C.pos = pos0_1_C;
				r0_1_C.speed = 100.0;
				r0_2_C.pos = pos0_2_C;
				r0_2_C.speed = 100.0;
				r0_3_C.pos = pos0_3_C;
				r0_3_C.speed = 100.0;

	f->setLanding(false);
	f->setAvoidingStorm(false);
	f->getRoute()->clear();

	if(f->getPosition().get_y()>= 1000.0){
		f->getRoute()->push_front(r0_3_C);
		f->getRoute()->push_front(r0_2_C);
		f->getRoute()->push_front(r0_1_C);
		f->getRoute()->push_front(r0_0_C);
	}
	else if(f->getPosition().get_y()<=-1000.0){
		f->getRoute()->push_front(r0_3_B);
		f->getRoute()->push_front(r0_2_B);
		f->getRoute()->push_front(r0_1_B);
		f->getRoute()->push_front(r0_0_B);
	}else{
		f->getRoute()->push_front(r0_3_A);
		f->getRoute()->push_front(r0_2_A);
		f->getRoute()->push_front(r0_1_A);
		f->getRoute()->push_front(r0_0_A);
	}
}

void
AirController::AssignAntiStormRoute(Flight *f)
{
		Route r0_0_AT_I, r0_1_AT_I, r0_2_AT_I,r0_0_AT_D, r0_1_AT_D, r0_2_AT_D;
	//Ruta antitormenta izquierda
	Position pos0_0_AT_I(-0.0, -10500.0, 2000.0);
	Position pos0_1_AT_I(-2500.0, -12000.0, 2000.0);
	Position pos0_2_AT_I(-0.0, -14500.0, 2000.0);
	//Ruta antitormenta derecha
	Position pos0_0_AT_D(-0.0, 10500.0, 2000.0);
	Position pos0_1_AT_D(-2500.0, 12000.0, 2000.0);
	Position pos0_2_AT_D(-0.0, 14500.0, 2000.0);

	//Ruta antitormenta izquierda
				r0_0_AT_I.pos = pos0_0_AT_I;
				r0_0_AT_I.speed = 400.0;
				r0_1_AT_I.pos = pos0_1_AT_I;
				r0_1_AT_I.speed = 100.0;
				r0_2_AT_I.pos = pos0_2_AT_I;
				r0_2_AT_I.speed = 400.0;
	//Ruta antitormenta derecha
				r0_0_AT_D.pos = pos0_0_AT_D;
				r0_0_AT_D.speed = 400.0;
				r0_1_AT_D.pos = pos0_1_AT_D;
				r0_1_AT_D.speed = 100.0;
				r0_2_AT_D.pos = pos0_2_AT_D;
				r0_2_AT_D.speed = 400.0;

	f->setLanding(false);
	f->setAvoidingStorm(true);
	f->getRoute()->clear();

	if(f->getPosition().get_y()<= 0 ){
		f->getRoute()->push_back(r0_0_AT_D);
		f->getRoute()->push_back(r0_1_AT_D);
		f->getRoute()->push_back(r0_2_AT_D);
	}
	if(f->getPosition().get_y()> 0) {
		f->getRoute()->push_back(r0_0_AT_I);
		f->getRoute()->push_back(r0_1_AT_I);
		f->getRoute()->push_back(r0_2_AT_I);
	}
}

void
AirController::AssignLanding(Flight *f)
{

	//Aprox. final
				Position pos1_A(4000.0, 0.0, 100.0);
				Position pos1_B(4000.0, -1500, 100.0);
				Position pos1_C(4000.0, 1500, 100.0);
				Position pos2(1500.0, 0.0, 50.0);
				Position pos3(100.0, 0.0, 25.0);
				Position pos4(-750.0, 0.0, 25.0);

	Route r1_A, r1_B, r1_C, r2, r3, r4;

	//Aprox. final
				r1_A.pos = pos1_A;
				r1_A.speed = 500.0;
				r1_B.pos = pos1_B;
				r1_B.speed = 500.0;
				r1_C.pos = pos1_C;
				r1_C.speed = 500.0;
				r2.pos = pos2;
				r2.speed = 400.0;
				r3.pos = pos3;
				r3.speed = 40.0;
				r4.pos = pos4;
				r4.speed = 15.0;


	f->setLanding(true);
	f->setAvoidingStorm(false);
	f->getRoute()->clear();

	if(f->getPosition().get_y()>= 1000.0){
		f->getRoute()->push_back(r1_C);
	}
	else if(f->getPosition().get_y()<=-1000.0){
		f->getRoute()->push_back(r1_B);
	}else{
		f->getRoute()->push_back(r1_A);
	}

	f->getRoute()->push_back(r2);
	f->getRoute()->push_back(r3);
	f->getRoute()->push_back(r4);
}


bool
AirController::CheckStorm(Flight *f, Storm *s)
{
	float radio_storm = s->getRadious();
	float altura_storm = s->getHeight();
	float x_storm = s->getPosition().get_x();
	float y_storm = s->getPosition().get_y();
		float x_flight = f->getPosition().get_x();
		float y_flight = f->getPosition().get_y();
		float distancia = CalcularDistancia(x_flight, y_flight, x_storm, y_storm);
			if(distancia <= radio_storm+MARGENSEGURIDAD){
				return true;
			}else{
				return false;
			}
}


bool
AirController::ClosedRunway(Storm *s)
{
	float radio_storm = s->getRadious();
	float altura_storm = s->getHeight();
	float x_storm = s->getPosition().get_x();
	float y_storm = s->getPosition().get_y();
	bool closed;

	float pos1_A_x = 4000.0;
	float pos1_A_y = 0.0;
	float pos1_B_x = 4000.0;
	float pos1_B_y = -1500.0;
	float pos1_C_x = 4000.0;
	float pos1_C_y = 1500.0;
	float pos2_x = 1500.0;
	float pos2_y = 0.0;
	float pos3_x = 100.0;
	float pos3_y = 0.0;
	float pos4_x = -750.0;
	float pos4_y = 0.0;

	float distancia1_A = CalcularDistancia(pos1_A_x, pos1_A_y, x_storm, y_storm);
	float distancia1_B = CalcularDistancia(pos1_B_x, pos1_B_y, x_storm, y_storm);
	float distancia1_C = CalcularDistancia(pos1_C_x, pos1_C_y, x_storm, y_storm);
	float distancia2 = CalcularDistancia(pos2_x, pos2_y, x_storm, y_storm);
	float distancia3 = CalcularDistancia(pos3_x, pos3_y, x_storm, y_storm);
	float distancia4= CalcularDistancia(pos4_x, pos4_y, x_storm, y_storm);

	if(distancia1_A <= radio_storm+MARGENSEGURIDAD_AIRPORT){
		closed =  true;
	}else if(distancia1_B <= radio_storm+MARGENSEGURIDAD_AIRPORT){
		closed =  true;
	}else if(distancia1_C <= radio_storm+MARGENSEGURIDAD_AIRPORT){
		closed =  true;
	}else if(distancia2 <= radio_storm+MARGENSEGURIDAD_AIRPORT){
		closed =  true;
	}else if(distancia3 <= radio_storm+MARGENSEGURIDAD_AIRPORT){
		closed =  true;
	}else if(distancia4 <= radio_storm+MARGENSEGURIDAD_AIRPORT){
		closed =  true;
	}else{
		closed = false;
	}
	return closed;
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			std::list<Flight*>::iterator it1;
			std::list<Route> route;
			Storm *storm = Airport::getInstance()->getStorm();


	//evitar colisiones
				for(it = flights.begin(); it!=flights.end(); ++it)
				{
					float x_flight1 = (*it)->getPosition().get_x();
					float y_flight1 = (*it)->getPosition().get_y();
					for(it1 = it; it1!=flights.end(); ++it1)
					{
						float x_flight2 = (*it1)->getPosition().get_x();
						float y_flight2 = (*it1)->getPosition().get_y();
						float separacion = CalcularDistancia(x_flight1, y_flight1, x_flight2, y_flight2);
						if(separacion <= ALTURAANTICOLISION && separacion > 0.0){
							(*it1)->setSpeed(VELOCIDADANTICOLISION);
							}
					}
				}
//Asignar ruta de espera si no tienen ruta
			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty()){
					AssignWaiting(*it);
				}
			}

//evitar tormenta
			if(storm != NULL){
				for(it = flights.begin(); it!=flights.end(); ++it){
						if(CheckStorm(*it, storm) &&  not (*it)->getLanding() &&  not (*it)->getAvoidingStorm()){
							AssignAntiStormRoute(*it);
					}
				}
			}
//Comprobar si la pista está ocupada
			ruta_ocupada = false;
			for(it = flights.begin(); it!=flights.end(); ++it){
				if((*it)->getLanding() && (*it)->getPosition().get_z() >= 30){
							ruta_ocupada = true;
				}
			}
//Asignar Aterrizaje

				for(it = flights.begin(); it !=flights.end(); ++it){
					if(not ruta_ocupada && not (*it)->getLanding() && not (*it)->getAvoidingStorm()) {
							if(storm == NULL || (storm != NULL && not ClosedRunway(storm))){
									AssignLanding(*it);
									ruta_ocupada=true;
							}
					}
				}


}
