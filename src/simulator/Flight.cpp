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

using namespace std;

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
	route = NULL;

	focused = false;
	points = INIT_FLIGHT_POINTS;

	aterriza_ = false;
	nivelVuelo_ = 0;
	desfase = 0; // Inicialización de la variable de prueba

	w_speed = 0.0f;
}

float Flight::getS(float velocidad, float theta_0, float theta_1, float w_max)
{	
	float time, s_decision;
	
	time = (fabs(theta_0 - theta_1))/w_max;
	s_decision = time * velocidad;
	
	return s_decision;
}

float
Flight::updateVel(float acc_buena, float speed, float delta_t)
{
	float n_speed, acc;
	
	if (fabs(acc_buena)> MAX_ACELERATION)
	{
		acc = (fabs(acc_buena)/ acc_buena ) * MAX_ACELERATION;
	} 
	else
	{
		acc = acc_buena;
	}
	
	return n_speed = speed + acc*delta_t;
}

float
Flight::updateOmega(float w_buena)
{
   float new_w;
	if ( fabs(w_buena)>MAX_FLIFGT_W )
	{
		new_w = ( fabs(w_buena)/w_buena ) * MAX_FLIFGT_W;
	} 
	else
	{
		new_w = w_buena;
	}
	
	return new_w;
}

float
Flight::restaAngulos(float goal_bearing, float bearing)
{
   float resta_rumbo = normalizePi(goal_bearing - bearing);
   
   return resta_rumbo;
}


void
Flight::update(float delta_t)
{
	float trans;
	
	float goal_bearing_0, goal_bearing_1;
	float acc_buena, S, goal_speed_0;
	
	it = route->begin();

	if(routed())
	{
	   std::list<Route>::iterator aux = it;
	   for (int j=0; j<desfase; j++)
	   {
		   aux++;
	   }
	   if (aux!=route->end())
	   {	
	   	   Position CPpos_0, CPpos_1;

		   CPpos_0 = aux->pos;
		   goal_speed_0 = aux->speed;
		
		   aux++;
		   CPpos_1 = aux->pos;
		   
		   pos.angles(CPpos_0, goal_bearing_0, inclination);
		   pos.angles(CPpos_1, goal_bearing_1, inclination);
		   		   
		   goal_bearing_0 = normalizePi(goal_bearing_0 + M_PI);
		   goal_bearing_1 = normalizePi(goal_bearing_1 + M_PI);
		   
	       float resta_rumbo_0 = restaAngulos(goal_bearing_0, bearing);
		   float resta_rumbo_1 = restaAngulos(goal_bearing_1, bearing);
		   
		   float w_buena = resta_rumbo_0/delta_t;
		
		   float new_w = updateOmega(w_buena);
		   		   
 		   bearing = bearing + new_w*delta_t;
		   
		   acc_buena = (goal_speed_0 - speed);
		   
		   speed = updateVel(acc_buena, speed, delta_t);
		   
		   float omega_max = MAX_FLIFGT_W;	
		      
		   S = getS(speed, resta_rumbo_0, resta_rumbo_1, omega_max);
		   		
		   if (pos.distance(CPpos_0) < S)
		   {
		   	new_w = fabs(resta_rumbo_0 - resta_rumbo_1)/delta_t;
//			route->pop_front();
		   	desfase++;
		   } 
		   
		   
	   }
	   else
	   {
		   desfase = 0;
	   }
		

	}
	else
	{
		inclination = 0.0;
		
		it = route->begin();
		
		goal_speed_0 = it->speed;
		
		acc_buena = (goal_speed_0 - speed);
		   
		speed = updateVel(acc_buena, speed, delta_t);

		desfase = 0;

	}
	
	last_pos = pos;

	trans = speed * delta_t;


	pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
	pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
	pos.set_z(pos.get_z() + ( trans * sin(inclination)));

	points = points - delta_t;

	//std::cout<<"["<<id<<"]speed = "<<speed<<"\tnew = "<<goal_speed_0<<"\t["<<acc_buena<<"]\t"<<std::endl;
			
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
