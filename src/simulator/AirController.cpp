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
#include "Common.h"
#include <list>

using namespace std;

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::assignWaiting(Flight *f, Route r0, Route r1, Route r2, Route r3)
{
	f->setLanding(false);
	f->getRoute()->clear();

	

	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);

}

void
AirController::assignLanding(Flight *f, Route r0, Route r1, Route r2, Route r3, Route r4, Route r5)
{
	f->setLanding(true);
	f->getRoute()->clear();

	
	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
	f->getRoute()->push_front(r4);
	f->getRoute()->push_front(r5);

}

float 
AirController::selectedHeight(WaitRouteHeight h[])
{
	int i;
	float routeHeight = 0.0;
	WaitRouteHeight temp[MAX_NUM_WAIT_HEIGHT];
	//temp = h;
	
	for (i=0; i<MAX_NUM_WAIT_HEIGHT; i++)
	{
		if(h[i].occuped ==false){

			routeHeight = h[i].selectedHeight;
			h[i].occuped = true;
			i = MAX_NUM_WAIT_HEIGHT;
		}//else{h++;}

	}

	return routeHeight;
	
}

void
AirController::HeightInizialitation(WaitRouteHeight h[])
{
	int i;
	float z_last = MIN_WAIT_HEIGHT;

	for(i=0; i<MAX_NUM_WAIT_HEIGHT;i++)
	{
		h[i].occuped = false;
		h[i].selectedHeight = z_last;
		z_last = z_last + COLLISION_DISTANCE;	
	}
}

bool
AirController::releaseHeight(WaitRouteHeight h[], float z)
{
	int i;
	bool releaseOk = false;

	for(i=0; i<MAX_NUM_WAIT_HEIGHT;i++)
	{
		if(h[i].selectedHeight = z)
		{
			h[i].occuped = false;
			releaseOk = true;
		}
	}
	return releaseOk;
}

void 
AirController::checkFreeRunway(Flight *f, bool *routeState)
{
	float x_avion = f->getPosition().get_x();
	float y_avion = f->getPosition().get_y();

	if (f->getLanding()==true){

		if((x_avion>=0)&&(x_avion<=4000)&&(y_avion>=-100)&&(y_avion<=100))
		{			
			*routeState=false;
			f->setLanding(false);
			
		}else{
			*routeState=true;
		}
	}
}

void 
AirController::avoidStorm(Flight* f, Storm* s)
{


		float x_avion = f->getPosition().get_x();
		float y_avion = f->getPosition().get_y();
		float x_storm = s->getPosition().get_x();
		float y_storm = s->getPosition().get_y();
			
		float dist=sqrt(pow((x_avion - x_storm),2) + pow((y_avion - y_storm),2));
		float aux_bearing;

		if(dist<=s->getRadious()+COLLISION_DISTANCE*3)
		{
			if(f->getBearing()>= 0){
					if(f->getBearing()>= (M_PI/2)){
						 
						float sig_bearing_storm = (s->getBearing()/fabs(s->getBearing()));
						float sig_bearing_flight = (f->getBearing()/fabs(f->getBearing()));
						aux_bearing = (sig_bearing_storm*sig_bearing_flight)*(M_PI/2);

					}else if(f->getBearing()< (M_PI/2)){

						float sig_bearing_storm = (s->getBearing()/fabs(s->getBearing()));
						float sig_bearing_flight = (f->getBearing()/fabs(f->getBearing()));
						aux_bearing = (sig_bearing_storm*sig_bearing_flight)*(-M_PI/2);
					}

			}else if(f->getBearing()< 0){
				if((fabs(s->getBearing())>= M_PI/2)&&(fabs(s->getBearing())< M_PI)){
					aux_bearing = M_PI/2;

				}else if((fabs(s->getBearing())< M_PI/2)&&(fabs(s->getBearing())>= 0.0)){
					aux_bearing = -M_PI/2;
				}
			}
			
			f->setBearing(normalizePi((f->getBearing())+aux_bearing));	
		}
}


void
AirController::doWork()
{
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	Storm *storm = Airport::getInstance()->getStorm();
	std::list<Flight*>::iterator it;
	std::list<Flight*>::iterator it2;


	//WaitRouteHeight z1 [MAX_NUM_WAIT_HEIGHT];
	//WaitRouteHeight z2 [MAX_NUM_WAIT_HEIGHT];
	//WaitRouteHeight z3 [MAX_NUM_WAIT_HEIGHT];
	//WaitRouteHeight z4 [MAX_NUM_WAIT_HEIGHT];

	float z=1000;

//****************GENERAL LANDING ROUTE********************************************

	Route r0, r1, r2, r3;

	Position pos0(4500.0, 0.0, 100.0);
	Position pos1(1000.0, 0.0, 50.0);
	Position pos2(200.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	r0.pos = pos0;
	r0.speed = 300.0;//100
	r1.pos = pos1;
	r1.speed = 100.0;//75
	r2.pos = pos2;
	r2.speed = 50.0;
	r3.pos = pos3;
	r3.speed = 15.0;

//****************LEFT WING LANDING ROUTE********************************************

	Route r4_l, r5_l;

	Position pos5_l(8000, -5000.0, 100.0);
	Position pos4_l(6000, -2500.0, 100.0);


	r5_l.pos = pos5_l;
	r5_l.speed = 500.0;
	r4_l.pos = pos4_l;
	r4_l.speed = 400.0;


//****************RIGHT WING LANDING ROUTE*******************************************

	Route r4_r, r5_r;

	Position pos5_r(8000, 5000.0, 100.0);
	Position pos4_r(6000, 2500.0, 100.0);

	r5_r.pos = pos5_r;
	r5_r.speed = 500.0;
	r4_r.pos = pos4_r;
	r4_r.speed = 400.0;

//**********************WAITING ROUTE 1**************************************
	
	Route r11, r12, r13, r14;

	float x_w1 = -8000;
	float y_w1 = -6500;


//**********************WAITING ROUTE 2**************************************

	Route r21, r22, r23, r24;

	float x_w2 = -4000;
	float y_w2 = -2500;

	

//**********************WAITING ROUTE 3**************************************

	Route r31, r32, r33, r34;

	float x_w3 = -4000;
	float y_w3 = 2500;


//**********************WAITING ROUTE 4**************************************

	Route r41, r42, r43, r44;

	float x_w4 = -8000;
	float y_w4 = 6500;


//Asignación de rutas

	for(it = flights.begin(); it!=flights.end(); ++it)
	{
		if(storm != NULL)
		{
			avoidStorm(*it, storm);
		}

		if(((*it)->getRoute()->empty()) && (routeState==false))
		{
			if((*it)->getPosition().get_y()<=0)
			{
				//if ((*it)->getSector() == 1){

					//releaseHeight(z1, (*it)->getPosition().get_z());
				//}else if((*it)->getSector() == 2){

					//releaseHeight(z2, (*it)->getPosition().get_z());
				//}	
		    		assignLanding ((*it), r0,r1, r2, r3,r4_l,r5_l);

			}else if ((*it)->getPosition().get_y()>0){

				//if ((*it)->getSector() == 3){

					//releaseHeight(z3, (*it)->getPosition().get_z());
				//}else if((*it)->getSector() == 4){

					//releaseHeight(z4, (*it)->getPosition().get_z());
				//}
				assignLanding ((*it), r0,r1, r2, r3,r4_r,r5_r);
			}
			
					
		}else if(((*it)->getRoute()->empty()) && (routeState==true)){
					
			
			float x_avion = (*it)->getPosition().get_x();
			float y_avion = (*it)->getPosition().get_y();
	            
			if (y_avion <=-5000)//SECTOR1
			{
				//HeightInizialitation(z1);
				//z = selectedHeight(z1);
				//float z = (*it)->getPosition().get_z()-1000.0;
				//(*it)->setSector(1);
	
				/*float z1=0;
				if(zlast1>=3000.0 ){
					zlast1 = 1000.0;

				}else if ((*zlast1<3000.0)&&(*zlast1>=1000.0)){
					zlast1 =zlast1 +COLLISION_DISTANCE;
				}

				z1 = zlast1;*/

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

				assignWaiting((*it), r11,  r12, r13, r14);
				

			}else if((-5000< y_avion)&&(y_avion < 0)){//SECTOR 2

				//HeightInizialitation(z2);
				//z = selectedHeight(z2);	

				//(*it)->setSector(2);

				//float z=(*it)->getPosition().get_z()-1000.0;
				//cout<<*zlast2<<endl;
				
				/*float z2=0;
				if(zlast2>=3000.0 ){
					zlast2 = 1000.0;

				}else if ((zlast2<3000.0)&&(zlast2>=1000.0)){
					zlast2 =zlast2 +COLLISION_DISTANCE;
				}
				
				z2 = zlast2; */

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
				
				assignWaiting((*it), r21, r22, r23, r24);

			}else if((0<= y_avion)&&(y_avion < 5000)){//SECTOR 3
			
				//HeightInizialitation(z3);
				//z = selectedHeight(z3);

				//float z=(*it)->getPosition().get_z()-1000.0;

				//(*it)->setSector(3);

				//cout<<*zlast3<<endl;
				
				/*float z3=0;

				if(zlast3>=3000.0 ){
					zlast3 = 1000.0;

				}else if ((zlast3<3000.0)&&(zlast3>=1000.0)){
					zlast3 =zlast3 +COLLISION_DISTANCE;
				}
				
				z3 = zlast3; */


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

				
				assignWaiting((*it), r31, r32, r33, r34);

			}else if(y_avion >=5000){//SECTOR 4

 				//HeightInizialitation(z4);
				//z = selectedHeight(z4);

				//float z=(*it)->getPosition().get_z()-1000.0;

				//(*it)->setSector(4);

				
				//cout<<*zlast4<<endl;
				/*float z4=0;

				if(zlast4>=3000.0 ){
					zlast4 = 1000.0;

				}else if ((zlast4<3000.0)&&(zlast4>=1000.0)){
					zlast4 =zlast4 +COLLISION_DISTANCE;
				}
				
				
				z4 = zlast4;*/
				

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


				assignWaiting((*it), r41, r42, r43, r44);

			}//ultimo elseif
			
		}//1º else

		checkFreeRunway((*it), &routeState);
		//cout<<routeState<<endl;
	}//1º for

	int counter =0;

	for(it = flights.begin(); it!=flights.end(); ++it)
	{
		if((*it)->getLanding()==true)
			counter++;
	}

	if(counter == 0)
		routeState=false;
		
		


}


