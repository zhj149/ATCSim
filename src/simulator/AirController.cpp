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

using namespace std;

AirController::AirController() {
	// TODO Auto-generated constructor stub
	landing = false;

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::assignWaiting(Flight *f, Route r0, Route r1, Route r2, Route r3)
{
	setLanding(false);
	f->getRoute()->clear();

	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);

}

void
AirController::assignLanding(Flight *f, Route r0, Route r1, Route r2, Route r3, Route r4, Route r5)
{
	setLanding(true);
	f->getRoute()->clear();

	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
	f->getRoute()->push_front(r4);
	f->getRoute()->push_front(r5);

}

void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;

	float z=3000;

/****************GENERAL LANDING ROUTE********************************************/

	Route r0, r1, r2, r3;

	Position pos0(4500.0, 0.0, 100.0);
	Position pos1(1000.0, 0.0, 50.0);
	Position pos2(200.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	r0.pos = pos0;
	r0.speed = 200.0;//100
	r1.pos = pos1;
	r1.speed = 100.0;//75
	r2.pos = pos2;
	r2.speed = 50.0;
	r3.pos = pos3;
	r3.speed = 15.0;

/****************LEFT WING LANDING ROUTE********************************************/

	Route r4_l, r5_l;

	Position pos5_l(8000, -5000.0, 100.0);
	Position pos4_l(6000, -2500.0, 100.0);


	r5_l.pos = pos5_l;
	r5_l.speed = 500.0;
	r4_l.pos = pos4_l;
	r4_l.speed = 400.0;


/****************RIGHT WING LANDING ROUTE*******************************************/

	Route r4_r, r5_r;

	Position pos5_r(8000, 5000.0, 100.0);
	Position pos4_r(6000, 2500.0, 100.0);

	r5_r.pos = pos5_r;
	r5_r.speed = 500.0;
	r4_r.pos = pos4_r;
	r4_r.speed = 400.0;

/**********************WAITING ROUTE 1**************************************/

	Route r11, r12, r13, r14;

	float x_w1 = -8000;
	float y_w1 = -6500;

	Position pos11(x_w1+1000, y_w1, z);
	Position pos12(x_w1, y_w1+1000, z);
	Position pos13(x_w1-1000, y_w1, z);
	Position pos14(x_w1, y_w1-1000, z);

	r11.pos = pos11;
	r11.speed = 200.0;
	r12.pos = pos12;
	r13.pos = pos13;
	r14.pos = pos14;
	r12.speed = r13.speed = r14.speed = r11.speed;

/**********************WAITING ROUTE 2**************************************/

	Route r21, r22, r23, r24;

	float x_w2 = -4000;
	float y_w2 = -2500;

	Position pos21(x_w2+1000, y_w2, z);
	Position pos22(x_w2, y_w2+1000, z);
	Position pos23(x_w2-1000, y_w2, z);
	Position pos24(x_w2, y_w2-1000, z);

	r21.pos = pos21;
	r21.speed = 200.0;
	r22.pos = pos22;
	r23.pos = pos23;
	r24.pos = pos24;
	r22.speed = r23.speed = r24.speed = r21.speed;

/**********************WAITING ROUTE 3**************************************/

	Route r31, r32, r33, r34;

	float x_w3 = -4000;
	float y_w3 = 2500;

	Position pos31(x_w3+1000, y_w3, z);
	Position pos32(x_w3, y_w3+1000, z);
	Position pos33(x_w3-1000, y_w3, z);
	Position pos34(x_w3, y_w3-1000, z);

	r31.pos = pos31;
	r31.speed = 200.0;
	r32.pos = pos32;
	r33.pos = pos33;
	r34.pos = pos34;
	r32.speed = r33.speed = r34.speed = r31.speed;

/**********************WAITING ROUTE 4**************************************/

	Route r41, r42, r43, r44;

	float x_w4 = -8000;
	float y_w4 = 6500;

	Position pos41(x_w4+1000, y_w4, z);
	Position pos42(x_w4, y_w4+1000, z);
	Position pos43(x_w4-1000, y_w4, z);
	Position pos44(x_w4, y_w4-1000, z);

	r41.pos = pos41;
	r41.speed = 200.0;
	r42.pos = pos42;
	r43.pos = pos43;
	r44.pos = pos44;
	r42.speed = r43.speed = r44.speed = r41.speed;



/***************************************************************************************
*****************************CÓDIGO PARA OBTENER MAS PUNTUACION*************************
****************************************************************************************/

	for(it = flights.begin(); it!=flights.end(); ++it)
	{
		if(((*it)->getRoute()->empty()) && (getLanding() == false))
		{
			if((*it)->getPosition().get_y()<=0)
			{
		    		assignLanding ((*it), r0,r1, r2, r3,r4_l,r5_l);

			}else if ((*it)->getPosition().get_y()>0) {

				assignLanding ((*it), r0,r1, r2, r3,r4_r,r5_r);
			}

		}else if(((*it)->getRoute()->empty())&&(getLanding() == true)){

			float x_avion = (*it)->getPosition().get_x();
			float y_avion = (*it)->getPosition().get_y();

			if (y_avion <=-5000)//SECTOR1
			{
				float z=(*it)->getPosition().get_z()-1000.0;

				assignWaiting((*it), r11,  r12, r13, r14);

			}else if((-5000< y_avion)&&(y_avion < 0)){//SECTOR 2

				float z=(*it)->getPosition().get_z()-1000.0;

				assignWaiting((*it), r21, r22, r23, r24);

			}else if((0<= y_avion)&&(y_avion < 5000)){//SECTOR 3

				float z=(*it)->getPosition().get_z()-1000.0;

				assignWaiting((*it), r31, r32, r33, r34);

			}else if(y_avion >=5000){//SECTOR 4

 				float z=(*it)->getPosition().get_z()-1000.0;

				assignWaiting((*it), r41, r42, r43, r44);

			}//ultimo elseif
		}//1º else

	}//1º for
}


/***********************************************************************************
**************************CODIGO PARA QUE LOS AVIONES ATERRICEN EN ORDEN************
************************************************************************************/

/*
void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;

	float z=3000;

//****************GENERAL LANDING ROUTE********************************************

	Route r0, r1, r2, r3;

	Position pos0(2000.0, 0.0, 100.0);
	Position pos1(1000.0, 0.0, 50.0);
	Position pos2(200.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	r0.pos = pos0;
	r0.speed = 200.0;//100
	r1.pos = pos1;
	r1.speed = 100.0;//75
	r2.pos = pos2;
	r2.speed = 50.0;
	r3.pos = pos3;
	r3.speed = 15.0;

//****************LEFT WING LANDING ROUTE********************************************

	Route r4_l, r5_l;

	Position pos5_l(6000, -2000.0, 100.0);
	Position pos4_l(4500, -1000.0, 100.0);


	r5_l.pos = pos5_l;
	r5_l.speed = 500.0;
	r4_l.pos = pos4_l;
	r4_l.speed = 400.0;


//****************RIGHT WING LANDING ROUTE*******************************************

	Route r4_r, r5_r;

	Position pos5_r(6000, 2000.0, 100.0);
	Position pos4_r(4500, 1000.0, 100.0);

	r5_r.pos = pos5_r;
	r5_r.speed = 500.0;
	r4_r.pos = pos4_r;
	r4_r.speed = 400.0;

//**********************WAITING ROUTE 1*********************************************

	Route r11, r12, r13, r14;

	float x_w1 = -4000;
	float y_w1 = -6500;

	Position pos11(x_w1+1000, y_w1, z);
	Position pos12(x_w1, y_w1+1000, z);
	Position pos13(x_w1-1000, y_w1, z);
	Position pos14(x_w1, y_w1-1000, z);

	r11.pos = pos11;
	r11.speed = 200.0;
	r12.pos = pos12;
	r13.pos = pos13;
	r14.pos = pos14;
	r12.speed = r13.speed = r14.speed = r11.speed;

//**********************WAITING ROUTE 2*********************************************

	Route r21, r22, r23, r24;

	float x_w2 = -2000;
	float y_w2 = -2500;

	Position pos21(x_w2+1000, y_w2, z);
	Position pos22(x_w2, y_w2+1000, z);
	Position pos23(x_w2-1000, y_w2, z);
	Position pos24(x_w2, y_w2-1000, z);

	r21.pos = pos21;
	r21.speed = 200.0;
	r22.pos = pos22;
	r23.pos = pos23;
	r24.pos = pos24;
	r22.speed = r23.speed = r24.speed = r21.speed;

//**********************WAITING ROUTE 3********************************************

	Route r31, r32, r33, r34;

	float x_w3 = -2000;
	float y_w3 = 2500;

	Position pos31(x_w3+1000, y_w3, z);
	Position pos32(x_w3, y_w3+1000, z);
	Position pos33(x_w3-1000, y_w3, z);
	Position pos34(x_w3, y_w3-1000, z);

	r31.pos = pos31;
	r31.speed = 200.0;
	r32.pos = pos32;
	r33.pos = pos33;
	r34.pos = pos34;
	r32.speed = r33.speed = r34.speed = r31.speed;

//**********************WAITING ROUTE 4********************************************

	Route r41, r42, r43, r44;

	float x_w4 = -4000;
	float y_w4 = 6500;

	Position pos41(x_w4+1000, y_w4, z);
	Position pos42(x_w4, y_w4+1000, z);
	Position pos43(x_w4-1000, y_w4, z);
	Position pos44(x_w4, y_w4-1000, z);

	r41.pos = pos41;
	r41.speed = 200.0;
	r42.pos = pos42;
	r43.pos = pos43;
	r44.pos = pos44;
	r42.speed = r43.speed = r44.speed = r41.speed;



	for(it = flights.begin(); it!=flights.end(); ++it)
	{

		if (it == flights.begin()){

			if(((*it)->getRoute()->empty()))
			{
				if((*it)->getPosition().get_y()<=0)
				{
			    		assignLanding ((*it), r0,r1, r2, r3,r4_l,r5_l);

				}else if ((*it)->getPosition().get_y()>0) {

					assignLanding ((*it), r0,r1, r2, r3,r4_r,r5_r);

					(*it)->getRoute()->push_back(r3);
					(*it)->getRoute()->push_front(r2);
					(*it)->getRoute()->push_front(r1);
					(*it)->getRoute()->push_front(r0);

				}
			}
		
		}else{
			
			if(((*it)->getRoute()->empty()))
			{
					
				float x_avion = (*it)->getPosition().get_x();
				float y_avion = (*it)->getPosition().get_y();
				            
				if (y_avion <=-5000)//SECTOR1
				{
					float z=(*it)->getPosition().get_z()-1000.0;

					assignWaiting((*it), r11,  r12, r13, r14);

				}else if((-5000< y_avion)&&(y_avion < 0)){//SECTOR 2
					
					float z=(*it)->getPosition().get_z()-1000.0;
				
					assignWaiting((*it), r21, r22, r23, r24);

				}else if((0<= y_avion)&&(y_avion < 5000)){//SECTOR 3
			
					float z=(*it)->getPosition().get_z()-1000.0;
				
					assignWaiting((*it), r31, r32, r33, r34);

				}else if(y_avion >=5000){//SECTOR 4

 					float z=(*it)->getPosition().get_z()-1000.0;
				
					assignWaiting((*it), r41, r42, r43, r44);

				}//ultimo elseif
			}

		}//1º else
	
	}//1º for		

		}else{

			if(((*it)->getRoute()->empty()))
			{

				float x_avion = (*it)->getPosition().get_x();
				float y_avion = (*it)->getPosition().get_y();

				if (y_avion <=-5000)//SECTOR1
				{
					float z=(*it)->getPosition().get_z()-1000.0;

					assignWaiting((*it), r11,  r12, r13, r14);

				}else if((-5000< y_avion)&&(y_avion < 0)){//SECTOR 2

					float z=(*it)->getPosition().get_z()-1000.0;

					assignWaiting((*it), r21, r22, r23, r24);

				}else if((0<= y_avion)&&(y_avion < 5000)){//SECTOR 3

					float z=(*it)->getPosition().get_z()-1000.0;

					assignWaiting((*it), r31, r32, r33, r34);

				}else if(y_avion >=5000){//SECTOR 4

 					float z=(*it)->getPosition().get_z()-1000.0;

					assignWaiting((*it), r41, r42, r43, r44);

				}//ultimo elseif
			}

		}//1º else

	}//1º for

}
*/
