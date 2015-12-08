/*
 * Flight.h
 *
 *  Created on: 15/07/2014
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
#include <string>

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "Position.h"
#include "Common.h"
#include <list>

typedef struct {
	Position pos;
	float speed;
} Route;

class Flight {
public:
	Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed);
	virtual ~Flight();

	void update(float delta_t);
	void draw();

	std::list<Route> *getRoute() { return route;};
	void setRoute(std::list<Route> *ruta) { route = ruta;};

	bool routed() { return route != NULL;};
	Position getPosition() { return pos;};
	float getInclination() { return inclination;};
	float getBearing() { return bearing;};
	float getSpeed() { return speed;};
	float getPoints() {return points;};
	float getS(float velocidad, float theta_0, float theta_1, float w_max);
	/*
		Conseguir el cálculo del tiempo d giro con diferencia de thetas
		entre velocidad de giro máxima, y ese tiempo dividirlo entre la
		velodidad que lleva el avion
	*/
	float updateVel(float acc_buena, float speed, float delta_t);
	float updateOmega(float w_buena);
	float restaAngulos(float goal_bearing, float bearing);
	std::string getId(){return id;};
	void setFocused(bool state) { focused = state;};
	bool getFocused() { return focused;};

	void setLanding (bool land) {aterriza_ = land;};
	bool getLanding () {return aterriza_;};

	void setNivel (int nivel) {nivelVuelo_ = nivel;};
	int getNivel () {return nivelVuelo_;};

/*
	void setWaiting_1 (bool wait1) {espera1_ = wait1;};
	bool getWaiting_1 () {return espera1_;};
	void setWaiting_2 (bool wait2) {espera2_ = wait2;};
	bool getWaiting_2 () {return espera2_;};
*/

private:
	std::string id;
	Position pos, last_pos;
	float bearing, inclination;
	float speed, w_speed;
	std::list<Route> *route; //Esto pasa de ser una lista de puntos de ruta, a ser una lista de punteros a ruta
	bool focused;
	std::list<Route>::iterator it;
	int desfase;  //Variable de prueba para manejar it y su comportamiento en la lista

	bool aterriza_;
	int nivelVuelo_;

	float points;
};

#endif /* FLIGHT_H_ */
