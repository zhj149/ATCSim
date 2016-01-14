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


	std::list<Route> *getRoute() { return &route;};
	bool routed() { return !route.empty();};
	Position getPosition() { return pos;};
	float getInclination() { return inclination;};
	float getBearing() { return bearing;};
	float getSpeed() { return speed;};
	float getPoints() {return points;};
	float getAssignedHeight () {return assigned_Height;};
	void setAssignedHeight (float height) { assigned_Height = height;};
	std::string getId(){return id;};
	void setFocused(bool state) { focused = state;};
	bool getFocused() { return focused;};

	void setBearing(float bearing_){bearing = bearing_;};

	float getS(float v, float theta1, float theta2, float w_max); //get the minimun distance to bear 
	float getSInclination(float v, float theta1, float theta2, float w_max);
	float updateV(float acc_ideal,float speed, float delta_t);
	float updateW(float ideal_w,float w_max );
	float diffBearing(float goal_bearing,float bearing);
	float diffInclination(float goal_inclination1, float inclination);

	int getSector(){return sector;};
	void setSector(int sector_){sector = sector_;};
	
	bool getLanding() {return landing;};
	void setLanding(bool landing_) {landing=landing_;};

	bool getStormAvoided(){return storm_avoided;};
	void setStormAvoided(bool sA){storm_avoided = sA;};

	bool getInStorm() {return inStorm;};
	void setInStorm(bool in) {inStorm=in;};
	void setStormWarning(bool warning) {storm_warning = warning;};
	bool getStormWarning() {return storm_warning;};

private:
	std::string id;
	Position pos, last_pos;
	float bearing, inclination;
	float speed, w_speed;
	float assigned_Height;
	bool storm_avoided;
	bool storm_warning;
	float s;	//distance
	std::list<Route> route;
	std::list<Route>::iterator it;
	bool focused;

	int sector;

	bool landing;

	bool inStorm;

	float points;
};

#endif /* FLIGHT_H_ */
