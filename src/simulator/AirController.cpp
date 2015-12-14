/*
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
#include "Storm.h"
#include <list>

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void AirController::WaitingRoute(Flight *f)
{
	f->SetLanding(false);
	//Right side Waiting Routes
	//route at height 2000m
	Position waitr1(5000.0,12000.0,2000.0);
	Position waitr2(10000.0,12000.0,2000.0);
	Position waitr3(5000.0,18000.0,2000.0);
	Position waitr4(10000.0,18000.0,2000.0);

	Route wait1,wait2,wait3,wait4;

	wait1.pos=waitr1;
	wait1.speed=200.0;
	wait2.pos=waitr2;
	wait2.speed=200.0;
	wait3.pos=waitr3;
	wait3.speed=200.0;
	wait4.pos=waitr4;
	wait4.speed=200.0;

	//route at height 3500m
	Position waitr5(5000.0,12000.0,3500.0);
	Position waitr6(10000.0,12000.0,3500.0);
	Position waitr7(5000.0,18000.0,3500.0);
	Position waitr8(10000.0,18000.0,3500.0);

	Route wait5,wait6,wait7,wait8;

	wait5.pos=waitr5;
	wait5.speed=200.0;
	wait6.pos=waitr6;
	wait6.speed=200.0;
	wait7.pos=waitr7;
	wait7.speed=200.0;
	wait8.pos=waitr8;
	wait8.speed=200.0;

	Position waitrn1(5000.0,12000.0,5000.0);
	Position waitrn2(10000.0,12000.0,5000.0);
	Position waitrn3(5000.0,18000.0,5000.0);
	Position waitrn4(10000.0,18000.0,5000.0);

	Route waitn1,waitn2,waitn3,waitn4;

	waitn1.pos=waitrn1;
	waitn1.speed=200.0;
	waitn2.pos=waitrn2;
	waitn2.speed=200.0;
	waitn3.pos=waitrn3;
	waitn3.speed=200.0;
	waitn4.pos=waitrn4;
	waitn4.speed=200.0;
	//Left side waiting routes

	Position waitl1(5000.0,-12000.0,2000.0);
	Position waitl2(10000.0,-12000.0,2000.0);
	Position waitl3(5000.0,-18000.0,2000.0);
	Position waitl4(10000.0,-18000.0,2000.0);

	Route wait9,wait10,wait11,wait12;

	wait9.pos=waitl1;
	wait9.speed=200.0;
	wait10.pos=waitl2;
	wait10.speed=200.0;
	wait11.pos=waitl3;
	wait11.speed=200.0;
	wait12.pos=waitl4;
	wait12.speed=200.0;

	//route at height 2500m
	Position waitl5(5000.0,-12000.0,3500.0);
	Position waitl6(10000.0,-12000.0,3500.0);
	Position waitl7(5000.0,-18000.0,3500.0);
	Position waitl8(10000.0,-18000.0,3500.0);

	Route wait13,wait14,wait15,wait16;

	wait13.pos=waitl5;
	wait13.speed=250.0;
	wait14.pos=waitl6;
	wait14.speed=200.0;
	wait15.pos=waitl7;
	wait15.speed=200.0;
	wait16.pos=waitl8;
	wait16.speed=200.0;

	Position waitln1(5000.0,-12000.0,5000.0);
	Position waitln2(10000.0,-12000.0,5000.0);
	Position waitln3(5000.0,-18000.0,5000.0);
	Position waitln4(10000.0,-18000.0,5000.0);

	Route waitn9,waitn10,waitn11,waitn12;

	waitn9.pos=waitln1;
	waitn9.speed=200.0;
	waitn10.pos=waitln2;
	waitn10.speed=200.0;
	waitn11.pos=waitln3;
	waitn11.speed=200.0;
	waitn12.pos=waitln4;
	waitn12.speed=200.0;


		if(f->getPosition().get_y()>=0.0 &&  f->getPosition().get_z()<2000.0)
			{
				f->getRoute()->push_back(wait4);
				f->getRoute()->push_front(wait2);
				f->getRoute()->push_front(wait1);
				f->getRoute()->push_front(wait3);
		}else  if(f->getPosition().get_y()>=0.0 && f->getPosition().get_z()>2000.0  && f->getPosition().get_z()<2500.0){
				f->getRoute()->push_back(wait8);
				f->getRoute()->push_front(wait6);
				f->getRoute()->push_front(wait5);
				f->getRoute()->push_front(wait7);
		}else  if(f->getPosition().get_y()>=0.0 && f->getPosition().get_z()>2500.0){
				f->getRoute()->push_back(waitn4);
				f->getRoute()->push_front(waitn2);
				f->getRoute()->push_front(waitn1);
				f->getRoute()->push_front(waitn3);
		}else if(f->getPosition().get_y()<0.0 && f->getPosition().get_z()<2000.0){
				f->getRoute()->push_back(wait12);
				f->getRoute()->push_front(wait10);
				f->getRoute()->push_front(wait9);
				f->getRoute()->push_front(wait11);
		}else if(f->getPosition().get_y()<0.0 && f->getPosition().get_z()>2000.0 && f->getPosition().get_z()<2500.0){
				f->getRoute()->push_back(wait16);
				f->getRoute()->push_front(wait14);
				f->getRoute()->push_front(wait13);
				f->getRoute()->push_front(wait15);
		}else if(f->getPosition().get_y()<0.0 && f->getPosition().get_z()>2500.0){
				f->getRoute()->push_back(waitn12);
				f->getRoute()->push_front(waitn10);
				f->getRoute()->push_front(waitn9);
				f->getRoute()->push_front(waitn11);
		}
}

void AirController::LandingRoute(Flight *f)
{
		f->SetLanding(true);
		Position pos0(3500.0, 0.0, 100.0);
		Position prueba(8000.0,-10000.0,100.0);
		Position pos1(1500.0, 0.0, 100.0);
		Position pos2(200.0, 0.0, 100.0);
		Position pos3(-700.0, 0.0, 25.0);
		Position prueba2(8000.0,10000.0,100.0);
		Position medio(6000.0,0.0,100.0);

		Route r0, r1, r2, r3,r4,r5,r6;

			r0.pos = pos0;
			r0.speed = 450.0;
			r1.pos = pos1;
			r1.speed = 300.0;
			r2.pos = pos2;
			r2.speed = 100.0;
			r3.pos = pos3;
			r3.speed = 50.0;
			r4.pos=prueba;
			r4.speed=700.0;
			r5.pos=prueba2;
			r5.speed=700.0;
			r6.pos=medio;
			r6.speed=700.0;

			if(f->getPosition().get_y()<=-10000.0)
					{

						f->getRoute()->push_back(r3);
						f->getRoute()->push_front(r2);
						f->getRoute()->push_front(r1);
						f->getRoute()->push_front(r0);
						f->getRoute()->push_front(r4);
					}
					else if(f->getPosition().get_y()>=10000.0)
					{

						f->getRoute()->push_back(r3);
						f->getRoute()->push_front(r2);
						f->getRoute()->push_front(r1);
						f->getRoute()->push_front(r0);
						f->getRoute()->push_front(r5);
					}
					else
					{

						f->getRoute()->push_back(r3);
						f->getRoute()->push_front(r2);
						f->getRoute()->push_front(r1);
						f->getRoute()->push_front(r0);
						f->getRoute()->push_front(r6);
					}
}

bool AirController::CheckMinimumDist(Storm s,Flight *f)
{
		float dist,radstorm;
		dist=s.getPosition().distance(f->getPosition());
		radstorm=s.getRadious();

		if(dist<=1.7*radstorm){
			return true;
		}else {
			return false;
		}
}

void AirController::AvoidStorm(Storm s,Flight *f)
{
		float radstorm;
		radstorm=s.getRadious();
		Position avoid1(s.getPosition().get_x()+radstorm*2.0,s.getPosition().get_y()+radstorm*2.0,s.getPosition().get_z()+radstorm*2.0);

		Route a1;

		a1.pos=avoid1;
		a1.speed=900.0;

			f->SetLanding(false);
			f->getRoute()->push_front(a1);


}


void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();

			std::list<Flight*>::iterator it;

			Position LandingP(0,0,25);

			bool isLanding=false;

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getLand()==true) isLanding=true;
			}

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if(((*it)->getPosition().distance(LandingP)<=900.0) && ((*it)->getPosition().distance(LandingP)>=500.0)) isLanding=false;
			}

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty())
				{
					if(isLanding==false ){
						LandingRoute((*it));


					}else{
						WaitingRoute((*it));
					}

				}
			}

			Storm s=Airport::getInstance()->getStorm();
			float x,y;
			x = s.getPosition().get_x();
			y = s.getPosition().get_y();

			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if(sqrt(x*x+y*y)<(AIRPORT_DISTANCE_MAX*1.3)){
						bool danger;
					danger=CheckMinimumDist(s,(*it));
					if(danger==true) AvoidStorm(s,(*it));
				}
			}
}
