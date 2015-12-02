/*
 * Flight.cpp
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

#include "Flight.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "Common.h"

#include <iostream>
#include <string>
#include <math.h>

Flight::~Flight() {
	// TODO Auto-generated destructor stub
}

Flight::Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed)
{
	id = _id;
	pos = _pos;
	bearing = _bearing;
	inclination = _inclination;
	speed = _speed;
	route.clear();

	focused = false;
	points = INIT_FLIGHT_POINTS;

	w_speed = 0.0f;
}

float Flight::getS(float v,float bear,float w_max)
{
	float T;
	float A;
	T = fabs(bear)/w_max;
	A = T*v;
	return A;
}

float Flight::updateV(float speed1,float speed0,float t)
{
	float new_speed,diff_speed,acc;

	diff_speed = speed1-speed0;
	acc = diff_speed;

	if(fabs(acc) > MAX_ACELERATION)
		acc = (acc/fabs(acc))*MAX_ACELERATION;
	else{
		acc = acc;
	}
	return new_speed = speed + acc*t;
}

float Flight::updateW(float w)
{
	float new_w;

	if(fabs(w) > MAX_FLIFGT_W)
			new_w = (fabs(w)/w)*MAX_FLIFGT_W;
	else{
			new_w = w;
	}
	return new_w;
}

void
Flight::update(float delta_t)
{
	float trans;
	Position CPpos;
	float s;
	float new_bearing,new_speed;

	if(routed())
	{
	float goal_bearing, diff_bearing, new_w;

	CPpos = route.front().pos;
	pos.angles(CPpos, goal_bearing, inclination);

	goal_bearing = normalizePi(goal_bearing + M_PI);
	diff_bearing = normalizePi(goal_bearing - bearing);
	new_w = diff_bearing;
	if(fabs(new_w)>MAX_FLIFGT_W) new_w = (fabs(new_w)/new_w) * MAX_FLIFGT_W;
	new_bearing = new_w;
	//std::cout<<"["<<id<<"]angle = "<<bearing<<"\tnew = "<<goal_bearing<<"\t["<<diff_bearing<<"]\tideal w = "<<new_w<<" -> "<<new_w_b<<std::endl;

	bearing = bearing + new_w*delta_t;

	float goal_speed, diff_speed, acc;

	goal_speed = route.front().speed;
	acc = (goal_speed - speed);

	if(fabs(acc)>MAX_ACELERATION) acc = (acc/fabs(acc))*MAX_ACELERATION;

	speed = speed + acc*delta_t;
	new_speed = speed;
	//std::cout<<"["<<id<<"]speed = "<<speed<<"\tnew = "<<goal_speed<<"\t["<<acc<<"]\t"<<std::endl;

}else
	inclination = 0.0;

last_pos = pos;

trans = speed * delta_t;


pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
pos.set_z(pos.get_z() + ( trans * sin(inclination)));

s = getS(new_speed,new_bearing,MAX_FLIFGT_W);
//std::cout<<"pos ="<< s << std::endl;
if(pos.distance(CPpos)< s)
	route.pop_front();

points = points - delta_t;

}
/*	if(routed())
	{
		float w_0,acc,diff_bear,bear1,bear2,inc1,inc2;
		std::list<Route>::iterator it;
		Route r1,r2;
		it = route.begin();
		r1 = *it;
		pos.angles(r1.pos, bear1, inc1);
		it++;
		r2 = *it;
		r1.pos.angles(r2.pos, bear2 , inc2);
		diff_bear = normalizePi(bear2-bear1);
		float omega = diff_bear;
		float new_w = updateW(omega);

		s = getS(speed,diff_bear,MAX_FLIFGT_W);
	//std::cout<<"position =  "<< s << std::endl;
		if(pos.distance(r1.pos) < s)
		{
			route.pop_front();
			w_0 = std::min(omega,MAX_FLIFGT_W);
		}
		if(fabs(omega) > 0.001)
			acc = 0;

	}else

	last_pos = pos;

	trans = speed * delta_t;


	pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
	pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
	pos.set_z(pos.get_z() + ( trans * sin(inclination)));

	speed0 = getSpeed();
	speed1 = route.front().speed;
	updateV(speed1,speed0,delta_t);


//std::cout <<"angle = "<< diff_bear << std::endl;


	points = points - delta_t;
}
*/

//
//void
//Flight::draw()
//{
//
//
//
//	glPushMatrix();
//
//	//Draw Aeroplane
//	glTranslatef(pos.get_x(), pos.get_y(), pos.get_z());
//	glRotatef(toDegrees(bearing), 0.0f, 0.0f, 1.0f);
//	glRotatef(toDegrees(-inclination), 0.0f, 1.0f, 0.0f);
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f,0.0f,0.0f);
//
//	glVertex3f( 30.0f, 0.0f, 0.0f);
//	glVertex3f( -30.0f, 32.0f, 0.0f);
//	glVertex3f( -30.0f, -32.0f, 0.0f);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f,0.0f,1.0f);
//
//	glVertex3f( -10.0f, 0.0f, 0.0f);
//	glVertex3f( -30.0f, 0.0f, 0.0f);
//	glVertex3f( -30.0f, 0.0f, 21.0f);
//	glEnd();
//
//
//	//Draw Collision sphere
//
//	if(focused)
//		glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
//	else
//		glColor4f(1.0f,1.0f,1.0f, 0.2f);
//
//
//	GLUquadric *quadratic = gluNewQuadric();
//	gluQuadricNormals(quadratic, GLU_SMOOTH);
//	gluQuadricTexture(quadratic, GL_TRUE);
//	gluSphere( quadratic, COLLISION_DISTANCE/2.0f, 32, 32);
//	glPopMatrix();
//
//	if(focused)
//	{
//		std::list<Route>::iterator it;
//
//		TextDisplay *textDisplay = TextDisplay::getInstance();
//		char pos_str[255];
//
//		textDisplay->displayText((char*)id.c_str(), 15, 75, GUI::win_width, GUI::win_height, LIGHTBLUE, GLUT_BITMAP_HELVETICA_18);
//		snprintf(pos_str, 255, "Points: %5.5lf ", points);
//		textDisplay->displayText(pos_str, 15, 95, GUI::win_width, GUI::win_height, YELLOW, GLUT_BITMAP_HELVETICA_12);
//
//		snprintf(pos_str, 255, "Position: (%lf, %lf, %lf) m", pos.get_x(), pos.get_y(), pos.get_z());
//		textDisplay->displayText(pos_str, 15, 115, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//		snprintf(pos_str, 255, "Bearing: %lf deg", toDegrees(bearing));
//		textDisplay->displayText(pos_str, 15, 135, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//		snprintf(pos_str, 255, "Inclination: %lf deg", toDegrees(inclination));
//		textDisplay->displayText(pos_str, 15, 155, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//		snprintf(pos_str, 255, "Speed: %lf m/sec", speed);
//		textDisplay->displayText(pos_str, 15, 175, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//
//
//		if(!route.empty())
//		{
//
//			glColor4f(0.0f,0.0f,1.0f, 1.0f);
//			glBegin(GL_LINES);
//
//			glVertex3f(pos.get_x(), pos.get_y(), pos.get_z());
//			for(it = route.begin(); it!=route.end(); ++it)
//			{
//				glVertex3f((*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
//				glVertex3f((*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
//			}
//			glEnd();
//
//			for(it = route.begin(); it!=route.end(); ++it)
//			{
//				glPushMatrix();
//				glTranslatef((*it).pos.get_x(), (*it).pos.get_y(),(*it).pos.get_z());
//				GLUquadric *quadratic = gluNewQuadric();
//				gluQuadricNormals(quadratic, GLU_SMOOTH);
//				gluQuadricTexture(quadratic, GL_TRUE);
//				gluSphere( quadratic, 50.0f, 32, 32);
//				glPopMatrix();
//			}
//
//
//			textDisplay->displayText((char *)"Route", 15, 230, GUI::win_width, GUI::win_height, BLUE, GLUT_BITMAP_HELVETICA_12);
//
//			int c = 0;
//			for(it = route.begin(); it!=route.end(); ++it)
//			{
//				snprintf(pos_str, 255, "Position: (%lf, %lf, %lf) m", (*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
//				textDisplay->displayText(pos_str, 25, 250+(20*c), GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//				c++;
//			}
//
//		}
//
//	}
//
//
//
//
//}
