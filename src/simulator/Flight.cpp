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

float
Flight::updateW(float ideal_w)
{
	float new_w;
	if(fabs(ideal_w)>MAX_FLIFGT_W)
	{
		 new_w = (fabs(ideal_w)/ideal_w)*MAX_FLIFGT_W;
	}
	else
	{
		 new_w = ideal_w;
	}

return new_w;
}

float
Flight::updateVel(float acc_inst,float speed, float delta_t)
{
	float new_speed,acceleration;
	if(fabs(acc_inst)>MAX_ACELERATION)
  {
		acceleration = (fabs(acc_inst)/acc_inst)*MAX_ACELERATION;
	}
	else
	{
		acceleration = acc_inst;
	}
return new_speed = speed + acceleration*delta_t;
}


float
Flight::getS(float V0, float Diferencia)
{
	float A, tiempo;
	tiempo=((Diferencia)/MAX_FLIFGT_W);
	A=tiempo*V0;
return A;
};

void
Flight::update(float delta_t)
{
	float trans;
	Position CPpos, CPpos1;

	if(routed())
	{
		float goal_bearing,goal_bearing1, diff_bearing,diff_bearing1, diff_diff_bearing, new_w;
		float goal_inclination,goal_inclination1, diff_inclination,diff_inclination1, diff_diff_inclination, new_wi;
		float S;
		float Si;
		float goal_speed, goal_speed1,diff_speed, acc_ideal;



		it=route.begin();
		CPpos = it->pos;
		goal_speed = it->speed;

		it++;
		CPpos1 = it->pos;
		goal_speed1 = it->speed;

		pos.angles(CPpos, goal_bearing, goal_inclination);//Rumbo que queremos mantener
		pos.angles(CPpos1, goal_bearing1, goal_inclination1);//Rumbo objetivo

		goal_bearing = normalizePi(goal_bearing + M_PI);
		goal_bearing1 = normalizePi(goal_bearing1 + M_PI);

		diff_bearing = normalizePi(goal_bearing - bearing);
		diff_bearing1 = normalizePi(goal_bearing1 - bearing);

		diff_diff_bearing= fabs(diff_bearing1-diff_bearing);

		diff_inclination = normalizePi(goal_inclination - inclination);
		diff_inclination1 = normalizePi(goal_inclination1 - inclination);

		diff_diff_inclination= fabs(diff_inclination1-diff_inclination);


    float w = diff_bearing/delta_t;
		new_w = updateW(w);
		bearing = bearing + new_w*delta_t;

		float wi = diff_inclination/delta_t;
		new_wi = updateW(wi);
		inclination = inclination + new_wi*delta_t;

		acc_ideal = (goal_speed - speed)*delta_t;
		speed = updateVel(acc_ideal,speed, delta_t);


		//std::cout << "\nAvión ["<<id<<"]" << std::endl;
		//std::cout<<"\nBEARING ACTUAL = "<<bearing*180/pi<<std::endl;
		//std::cout<<"BEARING A SEGUIR = "<<goal_bearing*180/pi<<std::endl;
		//std::cout<<"BEARING A CAMBIAR = "<<goal_bearing1*180/pi<<std::endl;
		//std::cout<<"DIFERENCIA ENTRE BEARING QUE TENEMOS Y BEARING QUE SEGUIMOS = "<<diff_bearing*180/pi<<std::endl;///IDEAL ES QUE SEA 0
		//std::cout<<"DIFERENCIA ENTRE BEARING QUE TENEMOS Y BEARING QUE QUEREMOS CAMBIAR = "<<diff_bearing1*180/pi<<std::endl;
		//std::cout<<"Diferencia BEARINGS = "<<diff_diff_bearing*180/pi<<std::endl;



		S = getS(speed, diff_diff_bearing);
		Si = getS(speed, diff_diff_inclination);

		if((pos.distance(CPpos)<S)||(pos.distance(CPpos)<Si))
		{
			  new_w = fabs(diff_diff_bearing)/delta_t;
				new_wi = fabs(diff_diff_inclination)/delta_t;

				route.pop_front();
		}

		//std::cout<<"Distancia S = "<<S<<" metros"<<std::endl;

		std::cout<<"VELOCIDAD ACTUAL = "<<speed<<std::endl;
		//std::cout<<"VELOCIDAD EN EL WAYPOINT = "<<goal_speed<<std::endl;
		//std::cout<<"VELOCIDAD EN EL WAYPOINT+1 = "<<goal_speed1<<std::endl;


}else{inclination = 0.0;}


		last_pos = pos;

		trans = speed * delta_t;

		pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
		pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
		pos.set_z(pos.get_z() + ( trans * sin(inclination)));


		if(pos.distance(CPpos) < DIST_POINT){
	  	route.pop_front();
		}

		//if(pos.distance(last_pos) > pos.distance(CPpos))
			//route.pop_front();

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
