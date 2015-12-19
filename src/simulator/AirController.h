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

//	void creaRuta(std::list<Route> ruta, Route wp_1, Route wp_2, Route wp_3, Route wp_4);

	void doWork();

	void assignRuta(Flight* vuelo, Route wait_1, Route wait_2, Route wait_3, Route wait_4);
//	void assignLanding(Flight* vuelo, Route wp_land);
	void setWhere_I (bool ocupado, int index) {where_i[index] = ocupado;};
	bool getWhere_I (int index) {return where_i[index];};
	void setWhere_C (bool ocupado, int index) {where_c[index] = ocupado;};
	bool getWhere_C (int index) {return where_c[index];};
	void setWhere_D (bool ocupado, int index) {where_d[index] = ocupado;};
	bool getWhere_D (int index) {return where_d[index];};


private:
	//Variables privadas que son los vectores de niveles
	bool where_i[NUM_FLIGHT_LV];
	bool where_c[NUM_FLIGHT_LV];
	bool where_d[NUM_FLIGHT_LV];

};

#endif /* AIRCONTROLLER_H_ */
