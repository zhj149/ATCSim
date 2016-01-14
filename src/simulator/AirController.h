/*
 * AirController.h
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

#ifndef AIRCONTROLLER_H_
#define AIRCONTROLLER_H_

#include "Singleton.h"
#include "Airport.h"
#include "Flight.h"
#include <list>

class AirController: public Singleton<AirController> {
public:
	AirController();
	virtual ~AirController();

	void doWork();
	void assignLanding(Flight *f);
	void assignWaiting(Flight *f);

	void checkFreeRunway(Flight *f, bool *routeState);
	float giveFreeHeight (int sector);
	void releaseHeight (int sector, float height);

	void avoidStorm(Flight* f, Storm* s);
	void avoidFlightsCollisions (Flight* f1, Flight* f2);

private:	

	bool routeState; //It will be false if Runway is free
	bool free_Height [NUMBER_OF_SECTORS][MAX_NUMBER_OF_HEIGHTS_BY_SECTOR];
	
};

#endif /* AIRCONTROLLER_H_ */
