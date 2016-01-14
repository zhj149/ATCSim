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
#include "Airport.h"


class AirController: public Singleton<AirController> {
public:
	AirController();
	virtual ~AirController();

	void doWork();
	void asignarLanding(Flight *f);

	void asignarWaitingR(Flight *f);
	void asignarWaitingL(Flight *f);
	void asignarWaitingCenter1(Flight *f);
	void asignarWaitingCenter2(Flight *f);
	void asignarWaiting(Flight *f);

	float DistanciaAv_Punto(Flight *f,float x2,float y2, float z2 );
	float DistanciaAv_Av(Flight *f1,Flight *f2 );
	float DistanciaStorm_Aeropuerto(Storm *s);
	float DistanciaStorm_Av(Storm *s,Flight *f);
	float DistanciaAvion_WayPoint(Flight *f);
	float GetAnguloGiro(Storm *s,Flight *f);

	void TCAS_System(Flight *f1, Flight *f2 );
	void EvitarStorm(Storm *s,Flight *f);

private:

};

#endif /* AIRCONTROLLER_H_ */
