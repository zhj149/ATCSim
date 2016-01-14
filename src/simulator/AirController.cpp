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

	Position pos4_r1(4500.0, -900.0, 300.0);
	Position pos4_r2(4500.0 , 900.0, 300.0);


	Route r0, r1, r2, r3, r4;

	r0.pos = pos0;
	r0.speed = 500.0;
	r1.pos = pos1;
	r1.speed = 100.0;
	r2.pos = pos2;
	r2.speed = 19.0;
	r3.pos = pos3;
	r3.speed = 15.0;


	if(f->getwaitRoute()==1)
		{r4.pos=pos4_r1;}
	else {r4.pos=pos4_r2;}

	r4.speed = 600.0;

	f->getRoute()->push_back(r3);
	f->getRoute()->push_front(r2);
	f->getRoute()->push_front(r1);
	f->getRoute()->push_front(r0);
	f->getRoute()->push_front(r4);

}

void
AirController::assignAdap(Flight* f)
{

	f->setLanding(false);
	f->setReRuted(false);
	f->getRoute()->clear();

	double z;
 	z=f->getPosition().get_z()-200;

	Position adap1(5000.0, -16000.0, z);
	Position adap2(15000.0, -16000.0, z);
	Position adap3(16000.0, -15000.0, z);
	Position adap4(16000.0, -5000.0, z);
	Position adap5(16000.0, 5000.0, z);
	Position adap6(16000.0, 15000.0, z);
	Position adap7(15000.0, 16000.0, z);
	Position adap8(5000.0, 16000.0, z);

	Position adap_r1(8000.0, -3000.0, 1600.0);
	Position adap_r2(8000.0, 3000.0, 1600.0);


	Route adap, adap_r;

	adap.speed = 350.0;
	adap_r.speed = 350.0;

  if(f->getPosition().get_y()<=-10000)
	{
			if(f->getPosition().get_x()<=10000)
					{	f->setwaitRoute(1);
				 		adap.pos= adap1;	}

			else if(f->getPosition().get_x()<=20000 && f->getPosition().get_x()>10000)
					{	f->setwaitRoute(1);
			 			adap.pos= adap2;	}

			else
					{	f->setwaitRoute(1);
						adap.pos= adap3;	}
	}
	else if(f->getPosition().get_y()>-10000 && f->getPosition().get_x()<=0)
	{
					f->setwaitRoute(1);
					adap.pos= adap4;
	}
	else if(f->getPosition().get_y()>0 && f->getPosition().get_x()<=10000)
	{
					f->setwaitRoute(2);
					adap.pos= adap5;
	}
	else
	{
		if(f->getPosition().get_x()<=10000)
				{	f->setwaitRoute(2);
					adap.pos= adap8;	}

		else if(f->getPosition().get_x()<=20000 && f->getPosition().get_x()>10000)
				{	f->setwaitRoute(2);
					adap.pos= adap7;	}

		else
				{	f->setwaitRoute(2);
					adap.pos= adap6;}
  }

	if(f->getwaitRoute()==1)
			{adap_r.pos=adap_r1;}
	else
			{adap_r.pos=adap_r2;}


		f->getRoute()->push_back(adap_r);
		f->getRoute()->push_front(adap);
}


void
AirController::assignWaiting(Flight* f)
{

		f->setLanding(false);
		f->setReRuted(false);
		f->getRoute()->clear();

		double z;

		z=f->getPosition().get_z()-200;

		Position pos2_3(7000.0, 15000.0 , z);
		Position pos2_2(16000.0, 15000.0, z);
		Position pos2_1(16000.0, 1000.0, z);
		Position pos2_0(7000.0, 1000.0, z);

		Position pos1_3(7000.0, -15000.0, z);
		Position pos1_2(16000.0, -15000.0, z);
		Position pos1_1(16000.0, -1000.0, z);
		Position pos1_0(7000.0, -1000.0, z);

		Route r0, r1, r2, r3 ;

		r0.speed = 300.0;
		r1.speed = 300.0;
		r2.speed = 300.0;
		r3.speed = 300.0;

	if(f->getwaitRoute()==1)
		{
			r0.pos = pos1_0;
			r1.pos = pos1_1;
			r2.pos = pos1_2;
			r3.pos = pos1_3;
		}
	else
		{
			r0.pos = pos2_0;
			r1.pos = pos2_1;
			r2.pos = pos2_2;
			r3.pos = pos2_3;
		}

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

	int signo;

	signo=bearing/fabs(bearing);

	bearing= s->getBearing()-((pi/3)*signo);
	bearing=normalizePi(bearing + M_PI);



	p_x=(f->getPosition().get_x()+ 15000*cos(bearing));
	p_y=(f->getPosition().get_y()+ 15000*sin(bearing)) ;
	p_z=f->getPosition().get_z();

 std::cout << s->getRadious()<< std::endl;
 std::cout << s->getBearing()<< std::endl;


	Position p(p_x, p_y , p_z);
	Route r;

	r.pos = p;
	r.speed = 400;

	 Position p(p_x, p_y , p_z);
	 Route r;

	 r.pos = p;
	 r.speed = 400;

	/*
	Position p1_1(10000, -10000, f->getPosition().get_z());
	Position p2_1 (10000, -4000, f->getPosition().get_z());

	Position p1_2(10000, 10000, f->getPosition().get_z());
	Position p2_2 (10000, 4000, f->getPosition().get_z());

	Route r1, r2;

	 if (f->getPosition().get_y()<=0)
	 {		r1.pos = p1_1;
			 r2.pos = p2_1;
	 }
	 else
	 {		r1.pos = p1_2;
			 r2.pos = p2_2;
	 }

	 r1.speed = 400;
	 r2.speed = 400;

	 f->getRoute()->push_back(r1);
	 f->getRoute()->push_front(r2);
	*/

	f->getRoute()->push_front(r);

	std::cerr<<"Flight "<<f->getId()<<"reruted"<<std::endl;
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

		if(dist< 1000+s->getRadious() )//&& fabs(zs-zf)<s->getHeight())
			{return true;}
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
		std::list<Flight*>::iterator it3;

		 if ((*it)->getRoute()->empty())
		 {
			 	if((*it)->getwaitRoute()==0)
					{assignAdap(*it);}

				else {assignWaiting(*it);}
		 }

		for(it2 = flights.begin(); it2!=flights.end(); ++it2)
		{
			  if((*it2)->getLanding())
						counter=counter+1;
		}

		it3=flights.begin();

	  if(storm==NULL || (storm!=NULL &&  !stormInLanding(storm)))
		{

					if (counter==0)
							{assignLanding(*it3);}
					else if (counter==1 && (*it3)->getPosition().get_x()<500.0 && flights.size()>1)
							{	it3++;
								assignLanding(*it3);}
		}

		if(storm!=NULL)
		{
 			   if(stormInView(storm, *it) &&  !(*it)->getReRuted())
				 {
					 	if (!(*it)->getLanding())
				          reRute(storm , *it);
					}
		}

	}
}
