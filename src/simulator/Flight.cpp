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
	inStorm = false;

	focused = false;
	landing = false;
	girando = false;
	points = INIT_FLIGHT_POINTS;
	ord = 0;

	w_speed = 0.0f;
}

float
Flight::getS(float v, float theta0, float theta1, float wmax)
{
	float thetad, t, S;

	//theta0 = normalizePi(theta0 + M_PI);
	//theta1 = normalizePi(theta1 + M_PI);

	thetad = fabs(theta1-theta0);

	t = thetad/wmax;

	S = t * v;

	return S;
}

void
Flight::proceedLanding()
{
		Route r0, r1, r2, r3, r4;

		Position pos0(5000.0, 0.0, 400.0);
		Position pos1(3500.0, 0.0, 200.0);
		Position pos2(1500.0, 0.0, 50.0);
		Position pos3(200.0, 0.0, 25.0);
		Position pos4(-750.0, 0.0, 25.0);

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

		if(getRoute()->empty()){
				getRoute()->clear();
				getRoute()->push_front(r0);
				getRoute()->push_back(r1);
				getRoute()->push_back(r2);
				getRoute()->push_back(r3);
				getRoute()->push_back(r4);
		}
}

void
Flight::avoidFromEast()
{
		Route r0, r1, r2, r3, r4, r5, r6, r7;
		Position pos0(10000.0, 0.0, 400.0);
		Position pos1(8000.0, 3000.0, 400.0);
		Position pos2(6000.0, 6000.0, 400.0);
		Position pos3(4000.0, 3000.0, 200.0);
		Position pos4(2000.0, 0.0, 200.0);
		Position pos5(1500.0, 0.0, 50.0);
		Position pos6(200.0, 0.0, 25.0);
		Position pos7(-750.0, 0.0, 25.0);

		r0.pos = pos0;
		r0.speed = 400.0;
		r1.pos = pos1;
		r1.speed = 400.0;
		r2.pos = pos2;
		r2.speed = 400.0;
		r3.pos = pos3;
		r3.speed = 400.0;
		r4.pos = pos4;
		r4.speed = 300.0;
		r5.pos = pos5;
		r5.speed = 200.0;
		r6.pos = pos6;
		r6.speed = 25.0;
		r7.pos = pos7;
		r7.speed = 15.0;

		if(getRoute()->empty()){
			getRoute()->clear();
			getRoute()->push_back(r2);
			getRoute()->push_back(r3);
			getRoute()->push_back(r4);
			getRoute()->push_back(r5);
			getRoute()->push_back(r6);
			getRoute()->push_back(r7);
		}
}

void
Flight::avoidFromWest()
{
	Route r0, r1, r2, r3, r4, r5, r6, r7;

	Position pos0(10000.0, 0.0, 400.0);
	Position pos1(8000.0, -3000.0, 400.0);
	Position pos2(6000.0, -6000.0, 400.0);
	Position pos3(4000.0, -3000.0, 200.0);
	Position pos4(2000.0, 0.0, 200.0);
	Position pos5(1500.0, 0.0, 50.0);
	Position pos6(200.0, 0.0, 25.0);
	Position pos7(-750.0, 0.0, 25.0);

	r0.pos = pos0;
	r0.speed = 400.0;
	r1.pos = pos1;
	r1.speed = 400.0;
	r2.pos = pos2;
	r2.speed = 400.0;
	r3.pos = pos3;
	r3.speed = 400.0;
	r4.pos = pos4;
	r4.speed = 300.0;
	r5.pos = pos5;
	r5.speed = 200.0;
	r6.pos = pos6;
	r6.speed = 25.0;
	r7.pos = pos7;
	r7.speed = 15.0;

	if(getRoute()->empty()){
			getRoute()->clear();
			getRoute()->push_front(r0);
			getRoute()->push_back(r1);
			getRoute()->push_back(r2);
			getRoute()->push_back(r3);
			getRoute()->push_back(r4);
			getRoute()->push_back(r5);
			getRoute()->push_back(r6);
			getRoute()->push_back(r7);
	}
}

void
Flight::proceedWaitingEast()
{
	Route rwe1, rwe2, rwe3, rwe4;
	float speed = 300.0;

	Position poswe1(14000.0, -10000.0, 400.0);
	Position poswe2(10000.0, -14000.0, 400.0);
	Position poswe3(6000.0, -10000.0, 400.0);
	Position poswe4(10000.0, -6000.0, 400.0);

	rwe1.pos = poswe1;
	rwe1.speed = speed;
	rwe2.pos = poswe2;
	rwe2.speed = speed;
	rwe3.pos = poswe3;
	rwe3.speed = speed;
	rwe4.pos = poswe4;
	rwe4.speed = speed;

	if(getRoute()->empty()){
		if(getPosition().get_x() > 10000.0){
			if(ord > 0){
				rwe1.pos.set_z(rwe1.pos.get_z()+1000.0*ord);
				rwe2.pos.set_z(rwe2.pos.get_z()+1000.0*ord);
				rwe3.pos.set_z(rwe3.pos.get_z()+1000.0*ord);
				rwe4.pos.set_z(rwe4.pos.get_z()+1000.0*ord);
				getRoute()->clear();
				getRoute()->push_back(rwe1);
				getRoute()->push_back(rwe2);
				getRoute()->push_back(rwe3);
				getRoute()->push_back(rwe4);
			}else{
				getRoute()->clear();
				getRoute()->push_front(rwe1);
				getRoute()->push_back(rwe2);
				getRoute()->push_back(rwe3);
				getRoute()->push_back(rwe4);
			}
		}else{
			if(ord > 0){
				rwe1.pos.set_z(rwe1.pos.get_z()+1000.0*ord);
				rwe2.pos.set_z(rwe2.pos.get_z()+1000.0*ord);
				rwe3.pos.set_z(rwe3.pos.get_z()+1000.0*ord);
				rwe4.pos.set_z(rwe4.pos.get_z()+1000.0*ord);
				getRoute()->clear();
				getRoute()->push_back(rwe3);
				getRoute()->push_back(rwe4);
				getRoute()->push_back(rwe1);
				getRoute()->push_back(rwe2);
			}else{
				getRoute()->clear();
				getRoute()->push_front(rwe3);
				getRoute()->push_back(rwe4);
				getRoute()->push_back(rwe1);
				getRoute()->push_back(rwe2);
			}
		}
	}
}

void
Flight::proceedWaitingWest()
{
	Route rwo1, rwo2, rwo3, rwo4;
	float speed = 300.0;

	Position poswo1(14000.0, 10000.0, 400.0);
	Position poswo2(10000.0, 14000.0, 400.0);
	Position poswo3(6000.0, 10000.0, 400.0);
	Position poswo4(10000.0, 6000.0, 400.0);

	rwo1.pos = poswo1;
	rwo1.speed = speed;
	rwo2.pos = poswo2;
	rwo2.speed = speed;
	rwo3.pos = poswo3;
	rwo3.speed = speed;
	rwo4.pos = poswo4;
	rwo4.speed = speed;

	if(getRoute()->empty()){
		if(getPosition().get_x() > 10000.0){
			if(ord > 0){
				rwo1.pos.set_z(rwo1.pos.get_z()+1000.0*ord);
				rwo2.pos.set_z(rwo2.pos.get_z()+1000.0*ord);
				rwo3.pos.set_z(rwo3.pos.get_z()+1000.0*ord);
				rwo4.pos.set_z(rwo4.pos.get_z()+1000.0*ord);
				getRoute()->clear();
				getRoute()->push_front(rwo1);
				getRoute()->push_back(rwo2);
				getRoute()->push_back(rwo3);
				getRoute()->push_back(rwo4);
			}else{
				getRoute()->clear();
				getRoute()->push_front(rwo1);
				getRoute()->push_back(rwo2);
				getRoute()->push_back(rwo3);
				getRoute()->push_back(rwo4);
			}
		}else{
			if(ord > 0){
				rwo1.pos.set_z(rwo1.pos.get_z()+1000.0*ord);
				rwo2.pos.set_z(rwo2.pos.get_z()+1000.0*ord);
				rwo3.pos.set_z(rwo3.pos.get_z()+1000.0*ord);
				rwo4.pos.set_z(rwo4.pos.get_z()+1000.0*ord);
				getRoute()->clear();
				getRoute()->push_front(rwo3);
				getRoute()->push_back(rwo4);
				getRoute()->push_back(rwo1);
				getRoute()->push_back(rwo2);
			}else{
				getRoute()->clear();
				getRoute()->push_front(rwo3);
				getRoute()->push_back(rwo4);
				getRoute()->push_back(rwo1);
				getRoute()->push_back(rwo2);
			}
		}
  }
}


void
Flight::update(float delta_t)
{
	float trans;
	Position CPpos, CPpos2;

	if(routed())
	{
		float theta_goal, theta0, theta1, goal_bearing, diff_bearing, new_w, S, inclination2;
		int gir;
		Route r,s;

		S = 0.0;

		std::list<Route>::iterator it;
		it = route.begin();
		it++;
		r = *it;

		CPpos = route.front().pos;
		pos.angles(CPpos, theta0, inclination);
		CPpos2 = r.pos;
		pos.angles(CPpos2, theta1, inclination2);
		////////////////////////////////////////////////----v

		S = getS(speed, theta0, theta1, MAX_FLIFGT_W);

		if(pos.distance(CPpos)<S && (fabs(theta1-theta0)>0.01) ){
				setGirando(true);
				theta_goal = theta1;
				route.pop_front();
		}

		if(getGirando()){
			if(toDegrees(fabs(inclination)) > CRASH_INC ){
				inclination = (fabs(inclination)/inclination) * toRadians(CRASH_INC-0.5);
			}
			if(theta1-theta0 >=0)
			{
				new_w = MAX_FLIFGT_W;
			}else{
				new_w = -MAX_FLIFGT_W;
			}
//			std::cout<<theta0<<std::endl;
	//		std::cout<<theta1<<std::endl;
			bearing = bearing + new_w*delta_t;
			if(fabs(theta0) < (fabs(theta_goal) + 0.01) || fabs(theta0) > (fabs(theta_goal) - 0.01) ){
				setGirando(false);
			}
		}else{

		if(toDegrees(fabs(inclination)) > CRASH_INC ){
			inclination = (fabs(inclination)/inclination) * toRadians(CRASH_INC);
		}

		theta0 = normalizePi(theta0 + M_PI);
		diff_bearing = normalizePi(theta0 - bearing);
		new_w = diff_bearing;

		//std::cout<<new_w<<std::endl;

		if(fabs(new_w)>MAX_FLIFGT_W) new_w = (fabs(new_w)/new_w) * MAX_FLIFGT_W;

		//std::cout<<"["<<id<<"]angle = "<<bearing<<"\tnew = "<<goal_bearing<<"\t["<<diff_bearing<<"]\tideal w = "<<new_w<<" -> "<<new_w_b<<std::endl;

		bearing = bearing + new_w*delta_t;

		float goal_speed, diff_speed, acc;

		goal_speed = route.front().speed;

		//if(new_w > 0.01){
		//	acc = 0.0;
		//}else{
		acc = (goal_speed - speed);
		//}

		if(fabs(acc)>MAX_ACELERATION) acc = (acc/fabs(acc))*MAX_ACELERATION;

		speed = speed + acc*delta_t;
	}


		//std::cout<<"["<<id<<"]speed = "<<speed<<"\tnew = "<<goal_speed<<"\t["<<acc<<"]\t"<<std::endl;

	}else

		inclination = 0.0;

	last_pos = pos;

	trans = speed * delta_t;

	if(toDegrees(fabs(inclination)) > CRASH_INC ){
		inclination = (fabs(inclination)/inclination) * toRadians(CRASH_INC-0.5);
	}

	pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
	pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
	pos.set_z(pos.get_z() + ( trans * sin(inclination)));

//	if(pos.distance(last_pos) > pos.distance(CPpos))
//		route.pop_front();

	if(pos.distance(CPpos)<DIST_POINT)
		route.pop_front();

	if(inStorm)
	{
		//std::cout<<"["<<id<<"]In Storm"<<std::endl;
		points = points - 2*delta_t;
	}
	else
		points = points - delta_t;


	points = points - delta_t;

}
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
