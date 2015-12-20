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

typedef struct {
	float selectedHeight;
	bool occuped;

} WaitRouteHeight;

class AirController: public Singleton<AirController> {
public:
	AirController();
	virtual ~AirController();

	void doWork();
	void assignLanding(Flight *f, Route r0, Route r1, Route r2, Route r3, Route r4, Route r5);
	void assignWaiting(Flight *f, Route r0, Route r1, Route r2, Route r3);

	void checkFreeRunway(Flight *f, bool *routeState);
	float selectedHeight(WaitRouteHeight h[]);
	void HeightInizialitation(WaitRouteHeight h[]);
	bool releaseHeight(WaitRouteHeight h[],float z);

	void avoidStorm(Flight* f, Storm* s);

private:

	

	bool routeState; //It will be false if Runway is free
	
};

#endif /* AIRCONTROLLER_H_ */
