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
#include "Flight.h"

class AirController: public Singleton<AirController> {
public:
	AirController();
	virtual ~AirController();

	void doWork();
	void assignLanding(Flight *f, Route r12, Route r11, Route r10);
	void assignWaiting(Flight *f, Route r0, Route r3, Route r2, Route r1, Route r5, Route r6, Route r4, Route r7,
			             Route r18, Route r19, Route r20, Route r16, Route r24, Route r21, Route r23, Route r22);
	bool setLanding(bool state) { landing = state;};
	bool getLanding() {return landing;};
        void assignRoute(Flight *f, Route r14, Route r13, Route r15, Route r9, Route r8, Route r17);


private:
	bool landing;
};

#endif /* AIRCONTROLLER_H_ */
