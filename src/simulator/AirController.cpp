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

void assignLanding(Flight* f)
{
	if((*f).getLanding() == false){
		(*f).getRoute()->clear();
	}
	f->setLanding(true);
}

bool checkStormBearing(Storm s, Route r)
{
	float x, y, ang;
	x = s.getPosition().get_x() - r.pos.get_x();
	y = s.getPosition().get_y() - r.pos.get_y();
	ang = atan2(y,x);

	if(fabs(s.getBearing()) < fabs(ang + 0.09) || fabs(s.getBearing()) > fabs(ang - 0.09))
	{
		return true;
	}
}

bool checkStormDist(Storm& s, Route r)
{
	float x, y, dist;
	x = s.getPosition().get_x() - r.pos.get_x();
	y = s.getPosition().get_y() - r.pos.get_y();
	dist = sqrt(x*x+y*y);

	if(dist < 1.5*s.getRadious())
	{
		return true;
	}
}

void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			Storm* storm = Airport::getInstance()->getStorm();

			Position pos0(5000.0, 0.0, 400.0);
			Position pos1(3500.0, 0.0, 200.0);
			Position pos2(1500.0, 0.0, 50.0);
			Position pos3(200.0, 0.0, 25.0);
			Position pos4(-750.0, 0.0, 25.0);

			Position posaec(15000, -10000.0, 200.0);
			Position posaoc(15000.0, 10000.0, 200.0);
			Position posc(15000.0, 0.0, 500.0);

			Position poswe1(10000.0, -7500.0, 500.0);
			Position poswe2(5000.0, -5000.0, 800.0);
			Position poswe3(1500.0, -10000.0, 1100.0);
			Position poswe4(8000.0, -12500.0, 1400.0);
			Position poswe5(10000.0, -7500.0, 1700.0);
			Position poswe6(5000.0, -5000.0, 2000.0);
			Position poswe7(1500.0, -10000.0, 2300.0);
			Position poswe8(8000.0, -12500.0, 2600.0);
			Position poswe9(10000.0, -7500.0, 2900.0);
			Position poswe10(5000.0, -5000.0, 3200.0);
			Position poswe11(1500.0, -10000.0, 3500.0);
			Position poswe12(8000.0, -12500.0, 3800.0);
			Position poswe13(10000.0, -7500.0, 4100.0);
			Position poswe14(5000.0, -5000.0, 4400.0);
			Position poswe15(1500.0, -10000.0, 4700.0);
			Position poswe16(8000.0, -12500.0, 5000.0);

			Position poswo1(10000.0, 7500.0, 500.0);
			Position poswo2(5000.0, 5000.0, 800.0);
			Position poswo3(1500.0, 10000.0, 1100.0);
			Position poswo4(8000.0, 12500.0, 1400.0);
			Position poswo5(10000.0, 7500.0, 1700.0);
			Position poswo6(5000.0, 5000.0, 2000.0);
			Position poswo7(1500.0, 10000.0, 2300.0);
			Position poswo8(8000.0, 12500.0, 2600.0);
			Position poswo9(10000.0, 7500.0, 2900.0);
			Position poswo10(5000.0, 5000.0, 3200.0);
			Position poswo11(1500.0, 10000.0, 3500.0);
			Position poswo12(8000.0, 12500.0, 3800.0);
			Position poswo13(10000.0, 7500.0, 4100.0);
			Position poswo14(5000.0, 5000.0, 4400.0);
			Position poswo15(1500.0, 10000.0, 4700.0);
			Position poswo16(8000.0, 12500.0, 5000.0);

			Route rac, raec, raoc, rwe1, rwe2, rwe3, rwe4, rwo1, rwo2, rwo3, rwo4, r0, r1, r2, r3, r4;
			Route rwe5, rwe6, rwe7, rwe8, rwe9, rwe10, rwe11, rwe12, rwe13, rwe14, rwe15, rwe16;
			Route rwo5, rwo6, rwo7, rwo8, rwo9, rwo10, rwo11, rwo12, rwo13, rwo14, rwo15, rwo16;

			r0.pos = pos0;
			r0.speed = 500.0;
			r1.pos = pos1;
			r1.speed = 400.0;
			r2.pos = pos2;
			r2.speed = 200.0;
			r3.pos = pos3;
			r3.speed = 100.0;
			r4.pos = pos4;
			r4.speed = 15.0;

			raec.pos = posaec;
			raec.speed = 700.0;
			raoc.pos = posaoc;
			raoc.speed = 700.0;
			rac.pos = posc;
			rac.speed = 600.0;

			rwe1.pos = poswe1;
			rwe1.speed = 400.0;
			rwe2.pos = poswe2;
			rwe2.speed = 400.0;
			rwe3.pos = poswe3;
			rwe3.speed = 400.0;
			rwe4.pos = poswe4;
			rwe4.speed = 400.0;
			rwe5.pos = poswe5;
			rwe5.speed = 400.0;
			rwe6.pos = poswe6;
			rwe6.speed = 400.0;
			rwe7.pos = poswe7;
			rwe7.speed = 400.0;
			rwe8.pos = poswe8;
			rwe8.speed = 400.0;
			rwe9.pos = poswe9;
			rwe9.speed = 400.0;
			rwe10.pos = poswe10;
			rwe10.speed = 400.0;
			rwe11.pos = poswe11;
			rwe11.speed = 400.0;
			rwe12.pos = poswe12;
			rwe12.speed = 400.0;
			rwe13.pos = poswe13;
			rwe13.speed = 400.0;
			rwe14.pos = poswe14;
			rwe14.speed = 400.0;
			rwe15.pos = poswe15;
			rwe15.speed = 400.0;
			rwe16.pos = poswe16;
			rwe16.speed = 400.0;

			rwo1.pos = poswo1;
			rwo1.speed = 400.0;
			rwo2.pos = poswo2;
			rwo2.speed = 400.0;
			rwo3.pos = poswo3;
			rwo3.speed = 400.0;
			rwo4.pos = poswo4;
			rwo4.speed = 400.0;
			rwo5.pos = poswo5;
			rwo5.speed = 400.0;
			rwo6.pos = poswo6;
			rwo6.speed = 400.0;
			rwo7.pos = poswo7;
			rwo7.speed = 400.0;
			rwo8.pos = poswo8;
			rwo8.speed = 400.0;
			rwo9.pos = poswo9;
			rwo9.speed = 400.0;
			rwo10.pos = poswo10;
			rwo10.speed = 400.0;
			rwo11.pos = poswo11;
			rwo11.speed = 400.0;
			rwo12.pos = poswo12;
			rwo12.speed = 400.0;
			rwo13.pos = poswo13;
			rwo13.speed = 400.0;
			rwo14.pos = poswo14;
			rwo14.speed = 400.0;
			rwo15.pos = poswo15;
			rwo15.speed = 400.0;
			rwo16.pos = poswo16;
			rwo16.speed = 400.0;

			if(storm == NULL)
			{
				assignLanding(*flights.begin());
			}else{
				if(!checkStormDist(*storm, r3))
				{
					assignLanding(*flights.begin());
				}
			}


			for(it = flights.begin(); it!=flights.end(); ++it)
			{
				if((*it)->getRoute()->empty())
				{
					if((*it)->getPosition().get_y() < 0.0)
					{
						if(checkStormDist(*storm, rwe1) || checkStormDist(*storm, rwe2) || checkStormDist(*storm, rwe3) || checkStormDist(*storm, rwe4))
						{
							if((*it)->getLanding()){
								if(!checkStormDist(*storm, raec)){
									(*it)->getRoute()->push_back(raec);
									(*it)->getRoute()->push_back(rac);
								}
								if(checkStormDist(*storm, r0))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos0.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos0.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r0);
								if(checkStormDist(*storm, r1))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos1.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos1.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r1);
								if(checkStormDist(*storm, r2))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos2.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos2.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r2);
								(*it)->getRoute()->push_back(r3);
								(*it)->getRoute()->push_back(r4);
							}else{
								(*it)->getRoute()->push_back(raec);
								(*it)->getRoute()->push_back(raoc);
								(*it)->getRoute()->push_back(rwo1);
								(*it)->getRoute()->push_back(rwo2);
								(*it)->getRoute()->push_back(rwo3);
								(*it)->getRoute()->push_back(rwo4);
								(*it)->getRoute()->push_back(rwo5);
								(*it)->getRoute()->push_back(rwo6);
								(*it)->getRoute()->push_back(rwo7);
								(*it)->getRoute()->push_back(rwo8);
								(*it)->getRoute()->push_back(rwo9);
								(*it)->getRoute()->push_back(rwo10);
								(*it)->getRoute()->push_back(rwo11);
								(*it)->getRoute()->push_back(rwo12);
								(*it)->getRoute()->push_back(rwo13);
								(*it)->getRoute()->push_back(rwo14);
								(*it)->getRoute()->push_back(rwo15);
								(*it)->getRoute()->push_back(rwo16);
							}
						}else{
							if((*it)->getLanding()){
								if(checkStormDist(*storm, r0))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos0.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos0.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r0);
								if(checkStormDist(*storm, r1))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos1.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos1.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r1);
								if(checkStormDist(*storm, r2))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos2.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos2.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r2);
								(*it)->getRoute()->push_back(r3);
								(*it)->getRoute()->push_back(r4);
							}else{
								(*it)->getRoute()->push_front(raec);
								(*it)->getRoute()->push_back(rwe1);
								(*it)->getRoute()->push_back(rwe2);
								(*it)->getRoute()->push_back(rwe3);
								(*it)->getRoute()->push_back(rwe4);
								(*it)->getRoute()->push_back(rwe5);
								(*it)->getRoute()->push_back(rwe6);
								(*it)->getRoute()->push_back(rwe7);
								(*it)->getRoute()->push_back(rwe8);
								(*it)->getRoute()->push_back(rwe9);
								(*it)->getRoute()->push_back(rwe10);
								(*it)->getRoute()->push_back(rwe11);
								(*it)->getRoute()->push_back(rwe12);
								(*it)->getRoute()->push_back(rwe13);
								(*it)->getRoute()->push_back(rwe14);
								(*it)->getRoute()->push_back(rwe15);
								(*it)->getRoute()->push_back(rwe16);
							}
						}
				  }else{
						if(checkStormDist(*storm, rwo1) || checkStormDist(*storm, rwo2) || checkStormDist(*storm, rwo3) || checkStormDist(*storm, rwo4))
						{
							if((*it)->getLanding()){
								if(!checkStormDist(*storm, raoc)){
									(*it)->getRoute()->push_back(raoc);
									(*it)->getRoute()->push_back(rac);
								}
								if(checkStormDist(*storm, r0))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos0.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos0.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r0);
								if(checkStormDist(*storm, r1))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos1.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos1.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r1);
								if(checkStormDist(*storm, r2))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos2.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos2.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r2);
								(*it)->getRoute()->push_back(r3);
								(*it)->getRoute()->push_back(r4);
							}else{
								(*it)->getRoute()->push_back(raoc);
								(*it)->getRoute()->push_back(raec);
								(*it)->getRoute()->push_back(rwe1);
								(*it)->getRoute()->push_back(rwe2);
								(*it)->getRoute()->push_back(rwe3);
								(*it)->getRoute()->push_back(rwe4);
								(*it)->getRoute()->push_back(rwe5);
								(*it)->getRoute()->push_back(rwe6);
								(*it)->getRoute()->push_back(rwe7);
								(*it)->getRoute()->push_back(rwe8);
								(*it)->getRoute()->push_back(rwe9);
								(*it)->getRoute()->push_back(rwe10);
								(*it)->getRoute()->push_back(rwe11);
								(*it)->getRoute()->push_back(rwe12);
								(*it)->getRoute()->push_back(rwe13);
								(*it)->getRoute()->push_back(rwe14);
								(*it)->getRoute()->push_back(rwe15);
								(*it)->getRoute()->push_back(rwe16);
							}
						}else{
							if((*it)->getLanding()){
								if(checkStormDist(*storm, r0))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos0.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos0.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r0);
								if(checkStormDist(*storm, r1))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos1.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos1.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r1);
								if(checkStormDist(*storm, r2))
								{
									if(storm->getPosition().get_y() < 0.0)
									{
										pos2.set_x(storm->getPosition().get_x() + storm->getRadious() + 500.0);
									}else{
										pos2.set_x(storm->getPosition().get_x() - storm->getRadious() - 500.0);
									}
								}
								(*it)->getRoute()->push_back(r2);
								(*it)->getRoute()->push_back(r3);
								(*it)->getRoute()->push_back(r4);
							}else{
								(*it)->getRoute()->push_front(raoc);
								(*it)->getRoute()->push_back(rwo1);
								(*it)->getRoute()->push_back(rwo2);
								(*it)->getRoute()->push_back(rwo3);
								(*it)->getRoute()->push_back(rwo4);
								(*it)->getRoute()->push_back(rwo5);
								(*it)->getRoute()->push_back(rwo6);
								(*it)->getRoute()->push_back(rwo7);
								(*it)->getRoute()->push_back(rwo8);
								(*it)->getRoute()->push_back(rwo9);
								(*it)->getRoute()->push_back(rwo10);
								(*it)->getRoute()->push_back(rwo11);
								(*it)->getRoute()->push_back(rwo12);
								(*it)->getRoute()->push_back(rwo13);
								(*it)->getRoute()->push_back(rwo14);
								(*it)->getRoute()->push_back(rwo15);
								(*it)->getRoute()->push_back(rwo16);
							}
						}
					}
				}

			}
}
