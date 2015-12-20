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
AirController::assignLanding(Flight* f)
{
	f->setLanding(true);
	f->setReRuted(false);
	f->getRoute()->clear();

	Position pos0(3500.0, 0.0, 100.0);
	Position pos1(1500.0, 0.0, 50.0);
	Position pos2(200.0, 0.0, 25.0);
	Position pos3(-750.0, 0.0, 25.0);

	Route r0, r1, r2, r3;

	r0.pos = pos0;
	r0.speed = 600.0;
	r1.pos = pos1;
	r1.speed = 300.0;
	r2.pos = pos2;
	r2.speed = 25.0;
	r3.pos = pos3;
	r3.speed = 15.0;


	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
}

void
AirController::assignDescend(Flight* f)
{
	f->setLanding(false);	
	f->setReRuted(false);
	f->getRoute()->clear();

	Position pos0(6500.0, 0.0, 150.0);
	Position pos1(4000.0, 0.0, 100.0);

	Route r0, r1;

	r0.pos = pos0;
	r0.speed = 200.0;
	r1.pos = pos1;
	r1.speed = 100.0;

	f->getRoute()->push_back(r1);
	f->getRoute()->push_front(r0);
}



void
AirController::assignWaiting(Flight* f)
{
	
	f->setLanding(false);
	f->setReRuted(false);
	f->getRoute()->clear();

	Position pos1_3(13000.0, -700.0, 1300.0);
	Position pos1_0(13000.0, -10000.0, 1300.0);
	Position pos1_1(10000.0, -10000.0, 1300.0);
	Position pos1_2(10000.0, -700.0, 1300.0);


	Position pos2_3(10000.0, -700.0 , 1100.0);
	Position pos2_2(7000.0, -700.0, 1100.0);
	Position pos2_1(7000.0, -11000.0,1100.0);
	Position pos2_0(10000.0, -11000.0, 1100.0);


	Position pos3_3(7000.0, -700.0, 1000.0);
	Position pos3_0(7000.0, -12000.0, 1000.0);
	Position pos3_1(5000.0, -12000.0, 1000.0);
	Position pos3_2(5000.0, -700.0, 1000.0);

	Position pos4_3(13000.0, 10000.0, 1300.0);
	Position pos4_0(13000.0, 700.0, 1300.0);
	Position pos4_1(10000.0, 700.0, 1300.0);
	Position pos4_2(10000.0, 10000.0, 1300.0);


	Position pos5_3(10000.0, 11000.0 , 1100.0);
	Position pos5_2(7000.0, 11000.0, 1100.0);
	Position pos5_1(7000.0, 700.0, 1100.0);
	Position pos5_0(10000.0, 700.0, 1100.0);


	Position pos6_3(7000.0, 12000.0, 1000.0);
	Position pos6_0(7000.0, 700.0, 1000.0);
	Position pos6_1(5000.0, 700.0, 1000.0);
	Position pos6_2(5000.0, 12000.0, 1000.0);


	Route r0, r1, r2, r3;

	if(f->getwaitRoute()==0){
	   if(f->getPosition().get_x()<=12000){

		if(f->getPosition().get_y()<=0)
			{f->setwaitRoute(1);}
		else
			{f->setwaitRoute(2);}
	   }else{

		if( f->getPosition().get_y()<-16000)
			{f->setwaitRoute(3);}

		else if(f->getPosition().get_y()>16000)
			{f->setwaitRoute(4);}
			
	 	else if(f->getPosition().get_y()<16000 && f->getPosition().get_y()>0)
			{f->setwaitRoute(5);}
		
		else
			{f->setwaitRoute(6);}
	   }
	}
	

	if(f->getwaitRoute()==1)
		{
			r0.pos = pos3_1;
			r1.pos = pos3_0;
			r2.pos = pos3_3;
			r3.pos = pos3_2;
			
			if(f->getPosition().get_z()>=2000)
				{r0.pos.set_z(2000);}
		}	
		else if(f->getwaitRoute()==2)
		{
			r0.pos = pos6_2;
			r1.pos = pos6_1;
			r2.pos = pos6_0;
			r3.pos = pos6_3;
			if(f->getPosition().get_z()>=2000)
				{r0.pos.set_z(2000);}
		}	
		else if(f->getwaitRoute()==3)
		{
			r0.pos = pos2_1;
			r1.pos = pos2_0;
			r2.pos = pos2_3;
			r3.pos = pos2_2;
			if(f->getPosition().get_z()>=2000)
				{r0.pos.set_z(2100);}
		}	
		else if(f->getwaitRoute()==4)
		{
			r0.pos = pos5_2;
			r1.pos = pos5_1;
			r2.pos = pos5_0;
			r3.pos = pos5_3;
			if(f->getPosition().get_z()>=2000)
				{r0.pos.set_z(2100);}
		}	
		else if(f->getwaitRoute()==5)
		{
			r0.pos = pos4_3;
			r1.pos = pos4_2;
			r2.pos = pos4_1;
			r3.pos = pos4_0;
			if(f->getPosition().get_z()>=2000)
				{r0.pos.set_z(2200);}
		}	
		else if(f->getwaitRoute()==6)
		{
			r0.pos = pos1_0;
			r1.pos = pos1_3;
			r2.pos = pos1_2;
			r3.pos = pos1_1;
			if(f->getPosition().get_z()>=2000)
				{r0.pos.set_z(2200);}
		}else {std::cerr<<"error:ruta no asignada"<<std::endl;}
	
	r0.speed = 300.0;
	r1.speed = 300.0;
	r2.speed = 300.0;
	r3.speed = 300.0;


	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
}

void
AirController::reRute(Storm* s, Flight* f)
{
		
	f->getRoute()->clear();
	f->setReRuted(true);
	
	float p_x, p_y, p_z, bearing;

	if (f->getBearing()<=pi || f->getBearing()>(0*pi))
		{bearing= f->getBearing() + s->getBearing();}
	else	
		{bearing= f->getBearing() - s->getBearing();} 
		
	bearing=normalizePi(bearing + M_PI);

	p_x=(f->getPosition().get_x() + 2*s->getRadious()* cos(bearing) );
	p_y=(f->getPosition().get_y() + 2*s->getRadious()* sin(bearing)) ;
	p_z=f->getPosition().get_z();
	
	Position p(p_x, p_y , p_z);
	Route r;

	r.pos = p;
	r.speed = 300.0;

	
	f->getRoute()->push_front(r);
	std::cout<<"reruted"<<std::endl;
	
}

bool
AirController::stormInLanding(Storm* s)
{
	float pos0_x=3500.0, pos0_y=0.0, pos0_z=100.0;
	float pos1_x=1500.0, pos1_y=0.0, pos1_z=50.0;
	float pos2_x=200.0, pos2_y=0.0, pos2_z=25.0;
	float pos3_x=-750.0, pos3_y=0.0, pos3_z=25.0;
	
	float dist0, dist1, dist2, dist3, xs, ys, zs;

	xs = s->getPosition().get_x();
	ys = s->getPosition().get_y();
	zs = s->getPosition().get_z();

	dist0 = sqrt((pos0_x-xs)*(pos0_x-xs)+(pos0_y-ys)*(pos0_y-ys));
	dist1 = sqrt((pos1_x-xs)*(pos1_x-xs)+(pos1_y-ys)*(pos1_y-ys));
	dist2 = sqrt((pos2_x-xs)*(pos2_x-xs)+(pos2_y-ys)*(pos2_y-ys));		
	dist3 = sqrt((pos3_x-xs)*(pos3_x-xs)+(pos3_y-ys)*(pos3_y-ys));

	if (dist0 < s->getRadious() && fabs(zs-pos0_z)<s->getHeight())
		{return true;}
	else if(dist1 < s->getRadious() && fabs(zs-pos1_z)<s->getHeight())
		{return true;}
	else if(dist2 < s->getRadious() && fabs(zs-pos2_z)<s->getHeight())
		{return true;}
	else if(dist3 < s->getRadious() && fabs(zs-pos3_z)<s->getHeight())
		{return true;}
	else{return false;}

}

bool
AirController::stormInView(Storm* s, Flight* f)
{
		
		float xf,yf, zf, xs, ys, zs;
		float dist;

		xf = f->getPosition().get_x();
		yf = f->getPosition().get_y();
		zf = f->getPosition().get_z();
		xs = s->getPosition().get_x();
		ys = s->getPosition().get_y();
		zs = s->getPosition().get_z();

		dist = sqrt((xf-xs)*(xf-xs)+(yf-ys)*(yf-ys));


		if(dist< 2500+s->getRadious() )//&& fabs(zs-zf)<s->getHeight())
			{return true; std::cout<<"tormenta en vista"<<std::endl;}
		else 
			{return false;}
		

}

void
AirController::doWork()
{
			
	std::list<Flight*> flights = Airport::getInstance()->getFlights();
	std::list<Flight*>::iterator it;
			
	Storm* storm= Airport::getInstance()->getStorm();
		

	int counter;
	counter=0;


		for(it = flights.begin(); it!=flights.end(); ++it)

		{
  			
			   std::list<Flight*>::iterator it2;


			   if ((*it)->getRoute()->empty())
			     {
				assignWaiting(*it);
			     }
	

			   for(it2 = flights.begin(); it2!=flights.end(); ++it2)
				{
				   if((*it2)->getLanding()) 
					counter=counter+1;
				}
			
		
		//std::list<Flight*>::iterator it3;

		//it3=flights.begin();
		
			   if(counter==0)
			   {
				  if(storm==NULL || (storm!=NULL && stormInLanding(storm)==false))
					assignLanding(flights.front());
					
			  }

		//it3++;
		//	   if(flights.size()>1 && counter==1)
		//		assignDescend(*it3);

				
			  

				
			   if(storm!=NULL)
			   {
 				   if(stormInView(storm , *it) && (*it)->getReRuted()==false)
					{if (not (*it)->getLanding())
				              reRute(storm , *it);
					}
			   }


		} 
}


