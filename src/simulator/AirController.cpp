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
#include "Position.h"
#include <list>

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}


void
AirController::assignRuta(Flight* vuelo, Route wait_1, Route wait_2, Route wait_3, Route wait_4, Route wait_5, Route wait_5, Route wait_7)
{
	vuelo->getRoute()->clear();
	vuelo->getRoute()->push_front(wait_1);
	vuelo->getRoute()->push_back(wait_2);
	vuelo->getRoute()->push_back(wait_3);
	vuelo->getRoute()->push_back(wait_4);
	vuelo->getRoute()->push_back(wait_5);
	vuelo->getRoute()->push_back(wait_6);
	vuelo->getRoute()->push_back(wait_7);

//	vuelo->setWaiting(true);
}

void
AirController::assignRuta(Flight* vuelo, Route wait_1, Route wait_2, Route wait_3, Route wait_4, Route wait_5)
{
	vuelo->getRoute()->clear();
	vuelo->getRoute()->push_front(wait_1);
	vuelo->getRoute()->push_back(wait_2);
	vuelo->getRoute()->push_back(wait_3);
	vuelo->getRoute()->push_back(wait_4);
	vuelo->getRoute()->push_back(wait_5);

//	vuelo->setWaiting(true);
}

/*
void
AirController::assignLanding(Flight* vuelo, Route wp_land)
{
	vuelo->getRoute()->push_front(wp_land);
	vuelo->setLanding(false);
}
*/
/*

void
AirController::creaRuta(std::list<Route> ruta, Route wp_1, Route wp_2, Route wp_3, Route wp_4)
{
	ruta.push_front(wp_1);
	ruta.push_back(wp_2);
	ruta.push_back(wp_3);
	ruta.push_back(wp_4);
}
*/


void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;

	Position pos0(3500.0, 0.0, 100.0);
	Position pos1(1500.0, 0.0, 50.0);
	Position pos2(200.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 0.0);

	Position pos_der(10000.0, 10000.0, 100.0);
	Position pos_izq(10000.0, -10000.0, 100.0);
	Position pos_cen(13000.0, 0.0, 100.0);


	Position wp1_wder(16000.0, 10000.0, 100.0);
	Position wp2_wder(16000.0, 16000.0, 100.0);
	Position wp3_wder(8000.0, 16000.0, 100.0);
	Position wp4_wder(8000.0, 10000.0, 100.0);

	Position wp1_wizq(16000.0, -10000.0, 100.0);
	Position wp2_wizq(16000.0, -16000.0, 100.0);
	Position wp3_wizq(8000.0, -16000.0, 100.0);
	Position wp4_wizq(8000.0, -10000.0, 100.0);

	Position wp1_wcen(16000.0, 6000.0, 100.0);
	Position wp2_wcen(16000.0, -6000.0, 100.0);
	Position wp3_wcen(8000.0, -6000.0, 100.0);
	Position wp4_wcen(8000.0, 6000.0, 100.0);

	Position wp1_w2_der(16000.0, 10000.0, 200.0);
	Position wp2_w2_der(16000.0, 16000.0, 200.0);
	Position wp3_w2_der(8000.0, 16000.0, 200.0);
	Position wp4_w2_der(8000.0, 10000.0, 200.0);

	Position wp1_w2_izq(16000.0, -10000.0, 200.0);
	Position wp2_w2_izq(16000.0, -16000.0, 200.0);
	Position wp3_w2_izq(8000.0, -16000.0, 200.0);
	Position wp4_w2_izq(8000.0, -10000.0, 200.0);

	Position wp1_w2_cen(16000.0, 6000.0, 200.0);
	Position wp2_w2_cen(16000.0, -6000.0, 200.0);
	Position wp3_w2_cen(8000.0, -6000.0, 200.0);
	Position wp4_w2_cen(8000.0, 6000.0, 200.0);

	// Inicialización de vectores de niveles
	for (int i=0; i<NUM_FLIGHT_LV; i++)
	{
		setWhere_I(false, i);
		setWhere_C(false, i);
		setWhere_D(false, i);
	}

	Route r0, r1, r2, r3;//, r_der, r_izq, r_cen;

	Route r1_d, r2_d, r3_d, r4_d, r5_d, r6_d, r7_d, r1_i, r2_i, r3_i, r4_i, r5_i, r6_i, r7_i, r1_c, r2_c, r3_c, r4_c, r5_c;

	Route r1_2_d, r2_2_d, r3_2_d, r4_4_d, r5_2_d, r6_2_d, r7_2_d;
	Route r1_2_i, r2_2_i, r3_2_i, r4_2_i, r2_2_i, r3_2_i, r4_2_i;
	Route r1_2_c, r2_2_c, r3_2_c, r4_2_c, r5_2_c;

	r0.pos = pos0;
	r0.speed = 200.0;
	r1.pos = pos1;
	r1.speed = 100.0;
	r2.pos = pos2;
	r2.speed = 19.0;
	r3.pos = pos3;
	r3.speed = 15.0;
/*
	r_der.pos = pos_der;
	r_der.speed = 500.0;
	r_izq.pos = pos_izq;
	r_izq.speed = 500.0;
	r_cen.pos = pos_cen;
	r_cen.speed = 500.0;
*/

	r1_d.pos = wp1_wder;
	r1_d.speed = LAND_VEL;
	r2_d.pos = wp2_wder;
	r2_d.speed = LAND_VEL;
	r3_d.pos = wp3_wder;
	r3_d.speed = LAND_VEL;
	r4_d.pos = wp4_wder;
	r4_d.speed = LAND_VEL;

	r1_i.pos = wp1_wizq;
	r1_i.speed = LAND_VEL;
	r2_i.pos = wp2_wizq;
	r2_i.speed = LAND_VEL;
	r3_i.pos = wp3_wizq;
	r3_i.speed = LAND_VEL;
	r4_i.pos = wp4_wizq;
	r4_i.speed = LAND_VEL;

	r1_c.pos = wp1_wcen;
	r1_c.speed = LAND_VEL;
	r2_c.pos = wp2_wcen;
	r2_c.speed = LAND_VEL;
	r3_c.pos = wp3_wcen;
	r3_c.speed = LAND_VEL;
	r4_c.pos = wp4_wcen;
	r4_c.speed = LAND_VEL;


	r1_2_d.pos = wp1_w2_der;
	r1_2_d.speed = LAND_VEL;
	r2_2_d.pos = wp2_w2_der;
	r2_2_d.speed = LAND_VEL;
	r3_2_d.pos = wp3_w2_der;
	r3_2_d.speed = LAND_VEL;
	r4_2_d.pos = wp4_w2_der;
	r4_2_d.speed = 300.0;

	r1_2_i.pos = wp1_w2_izq;
	r1_2_i.speed = LAND_VEL;
	r2_2_i.pos = wp2_w2_izq;
	r2_2_i.speed = LAND_VEL;
	r3_2_i.pos = wp3_w2_izq;
	r3_2_i.speed = LAND_VEL;
	r4_2_i.pos = wp4_w2_izq;
	r4_2_i.speed = LAND_VEL;

	r1_2_c.pos = wp1_w2_cen;
	r1_2_c.speed = LAND_VEL;
	r2_2_c.pos = wp2_w2_cen;
	r2_2_c.speed = LAND_VEL;
	r3_2_c.pos = wp3_w2_cen;
	r3_2_c.speed = LAND_VEL;
	r4_2_c.pos = wp4_w2_cen;
	r4_2_c.speed = LAND_VEL;

	/*
	std::list<Route> ruta_land, ruta_w1_d, ruta_w1_c, ruta_w1_i, ruta_w2_d, ruta_w2_c, ruta_w2_i;

	creaRuta(ruta_land, r0, r1, r2, r3);

	creaRuta(ruta_w1_d, r1_d, r2_d, r3_d, r4_d);
	creaRuta(ruta_w1_c, r1_c, r2_c, r3_c, r4_c);
	creaRuta(ruta_w1_i, r1_i, r2_i, r3_i, r4_i);

	creaRuta(ruta_w2_d, r1_2_d, r2_2_d, r3_2_d, r4_2_d);
	creaRuta(ruta_w2_c, r1_2_c, r2_2_c, r3_2_c, r4_2_c);
	creaRuta(ruta_w2_i, r1_2_i, r2_2_i, r3_2_i, r4_2_i);
*/
	it = flights.begin();
	std::list<Flight*>::iterator aux = it;
	aux++;

	for(it == flights.begin(); it!=flights.end(); ++it)
	{
		if((*it)->getRoute()->empty())
		{
			if ( it == flights.begin() )
			{
				assignRuta(*it, r0, r1, r2, r3);
				(*it)->setLanding(true);
			}
			else
			{
				if ( (*it)->getPosition().get_y() > DIST_DECISION )
				{
					if ( getWhere_D(0) == false )
					{
						assignRuta(*it, r1_d, r2_d, r3_d, r4_d);
						setWhere_D(true, 0);
					}
					else
					{
						assignRuta(*it, r1_2_d, r2_2_d, r3_2_d, r4_2_d);
						setWhere_D(true, 1);
					}
				}
				else if (  (*it)->getPosition().get_y() < -DIST_DECISION )
				{
					if ( getWhere_I(0) == false )
					{
						assignRuta(*it, r1_i, r2_i, r3_i, r4_i);
						setWhere_I(true, 0);
					}
					else
					{
						assignRuta(*it, r1_2_i, r2_2_i, r3_2_i, r4_2_i);
						setWhere_I(true, 1);
					}
				}
				else
				{
					if ( getWhere_C(0) == false )
					{
						assignRuta(*it, r1_c, r2_c, r3_c, r4_c);
						setWhere_C(true, 0);
					}
					else
					{
						assignRuta(*it, r1_2_c, r2_2_c, r3_2_c, r4_2_c);
						setWhere_C(true, 1);
					}
				}
			}

		} else //if (!(*it)->getRoute()->empty())
		{
//			std::cout<<"Empieza reorganización de rutas"<<std::endl;
			if ( ( (*it)->getLanding() == true) && ( (*it)->getPosition().get_x() < DIST_UMBRAL) )
			{
				assignRuta(*aux, r0, r1, r2, r3);
				(*aux)->setLanding(true);

				if ( (*aux)->getPosition().get_y() > DIST_DECISION )
				{
					if ( getWhere_D(0)==true ) setWhere_D(false, 0);

					else if ( getWhere_D(1)==true ) setWhere_D(false, 1);
				}
				else if ( (*aux)->getPosition().get_y() < -DIST_DECISION )
				{
					if ( getWhere_I(0)==true ) setWhere_I(false, 0);

					else if ( getWhere_I(1)==true ) setWhere_I(false, 1);
				}
				else
				{
					if ( getWhere_C(0)==true ) setWhere_C(false, 0);

					else if ( getWhere_C(1)==true ) setWhere_C(false, 1);
				}
			}
/*			else if (( (*it)->getLanding() == false))
			{
				assignRuta(*aux, r0, r1, r2, r3);
				(*aux)->setLanding(true);
			}
*/
		}



//	}	//	fin del for de vuelos

/*
	it = flights.begin();
	std::list<Flight*>::iterator aux = it;
	aux++;

// A partir de aquí, el cambio realizado es que los aux pasar a ser it; añadido el clear de las rutas
	for(it == flights.begin() ; it!=flights.end(); ++it)
	{
		std::cout<<"Empieza reorganización de rutas"<<std::endl;
		if ( ( (*it)->getLanding() == true) && ( (*it)->getPosition().get_x() < DIST_UMBRAL) )
		{
			assignRuta(*aux, r0, r1, r2, r3);
			(*aux)->setLanding(true);

			if ( (*aux)->getPosition().get_y() > DIST_DECISION )
			{
				if ( getWhere_D(0)==true ) setWhere_D(false, 0);

				else if ( getWhere_D(1)==true ) setWhere_D(false, 1);
			}
			else if ( (*aux)->getPosition().get_y() < -DIST_DECISION )
			{
				if ( getWhere_I(0)==true ) setWhere_I(false, 0);

				else if ( getWhere_I(1)==true ) setWhere_I(false, 1);
			}
			else
			{
				if ( getWhere_C(0)==true ) setWhere_C(false, 0);

				else if ( getWhere_C(1)==true ) setWhere_C(false, 1);
			}
		}
//		else if (( (*it)->getLanding() == false))
//		{
//			assignRuta(*it, r0, r1, r2, r3);
//			(*it)->setLanding(true);
//		}
*/
//		std::cout<<"Termina reorganización de rutas";
//		std::cout<<"======================================"<<std::endl;
		aux++;
	}


//	std::cout<<"Termina un segundo de tiempo"<<std::endl;

}


// Borrador de posible uso de las rutas de forma genérica en función del nivel de vuelo
/*
(*it)->setRoute(&ruta_w1_d);
bool final = false;
int j=0;
do {
	if ( getWhere_D(j) == false )
	{
		(*it)->setNivel(j);
		setWhere_D(true, j);
		final = true;
	}
	else
	{
		j++;
//							(*it)->setRoute(&())
		//Aquí habra que gestionar la subida de altura
	}

} while ( (final == false) && (j<NUM_FLIGHT_LV)) ;
*/


/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	for(it = flights.begin(); it!=flights.end(); ++it)
	{
		if((*it)->getRoute() == NULL)
		{
			(*it)->setRoute(&ruta_land);
		}

		if ( ( (*it)->getPosition().get_y() > DIST_DECISION) && ((*it)->getLanding() == false) )
		{

			if ( (*it)->getWaiting_1() == false )
			{
				(*it)->setRoute(&ruta_w1_d);
				(*it)->setWaiting_1(true);
			}
			//else
			//{
				//(*it)->setRoute(&ruta_w1_d);
				//(*it)->setWaiting_2(true);
			//}
		}
		else if ( ( (*it)->getPosition().get_y() < -DIST_DECISION) && ((*it)->getLanding() == false) )
		{
			if ( (*it)->getWaiting_1() == false )
			{
				(*it)->setRoute(&ruta_w1_i);
				(*it)->setWaiting_1(true);
			}
			//else
			//{
				//assignWaiting(*it, r1_2_i, r2_2_i, r3_2_i, r4_2_i);
				//(*it)->setWaiting_2(true);
			//}
		}
		else
		{
			if ( (*it)->getWaiting_1() == false )
			{
				(*it)->setRoute(&ruta_w1_c);
				(*it)->setWaiting_1(true);
			}
			//else
			//{
				//assignWaiting(*it, r1_2_c, r2_2_c, r3_2_c, r4_2_c);
				//(*it)->setWaiting_2(true);
			//}
		}

		if ( it != flights.begin() )
		{
			(*it)->setLanding(false);
		}

	}

}
*/

/*
void
AirController::assignWaiting(Flight* vuelo, Route wait_1, Route wait_2, Route wait_3)
{
	if ( vuelo->getPosition().get_y() > DIST_DECISION )
	{
		vuelo->getRoute()->push_front(pt_1);
	}
	else if ( vuelo->getPosition().get_y() < -DIST_DECISION )
	{
		vuelo->getRoute()->push_front(pt_2);
	}
	else
	{
		vuelo->getRoute()->push_front(pt_3);
	}


}


void
AirController::assignLanding(Flight* vuelo, Route pt_1, Route pt_2, Route pt_3)
{
	if ( vuelo->getPosition().get_y() > DIST_DECISION )
	{
		vuelo->getRoute()->push_front(pt_1);
	}
	else if ( vuelo->getPosition().get_y() < -DIST_DECISION )
	{
		vuelo->getRoute()->push_front(pt_2);
	}
	else
	{
		vuelo->getRoute()->push_front(pt_3);
	}
	vuelo->setLanding(false);
}*/


//Anterior versión del código, exceso de memoria utilizada, mas o menos correcta
/*
if ( (*it)->getPosition().get_y() > DIST_DECISION )
{
	if( (*it)->getLanding() == true)
	{
		assignLanding(*it, r_der);
	}
	else
	{
		if ( (*it)->getWaiting_1() == false )
		{
			assignWaiting(*it, r1_d, r2_d, r3_d, r4_d);
			(*it)->setWaiting_1(true);
		}
		else
		{
			assignWaiting(*it, r1_2_d, r2_2_d, r3_2_d, r4_2_d);
			(*it)->setWaiting_2(true);
		}
	}
}
else if ( (*it)->getPosition().get_y() < -DIST_DECISION )
{
	if( (*it)->getLanding() == true)
	{
		assignLanding(*it, r_izq);
	}
	else
	{
		if ( (*it)->getWaiting_1() == false )
		{
			assignWaiting(*it, r1_i, r2_i, r3_i, r4_i);
			(*it)->setWaiting_1(true);
		}
		else
		{
			assignWaiting(*it, r1_2_i, r2_2_i, r3_2_i, r4_2_i);
			(*it)->setWaiting_2(true);
		}
	}

}
else
{
	if( (*it)->getLanding() == true)
	{
		assignLanding(*it, r_cen);
	}
	else
	{
		if ( (*it)->getWaiting_1() == false )
		{
			assignWaiting(*it, r1_c, r2_c, r3_c, r4_c);
			(*it)->setWaiting_1(true);
		}
		else
		{
			assignWaiting(*it, r1_2_c, r2_2_c, r3_2_c, r4_2_c);
			(*it)->setWaiting_2(true);
		}
	}

}
*/

