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

	

	points = INIT_FLIGHT_POINTS;

	w_speed = 0.0f;
}

float
Flight::getS(float v, float theta1, float theta2, float w_max)
{
	double t = fabs((theta2-theta1)) /w_max;
  	s = v*t;
	return s;	
}

float 
Flight:: getSInclination(float v, float alpha1, float alpha2, float w_max)
{
	double t = fabs((alpha2-alpha1)) /w_max;
  	s = v*t;
	return s;
}


float
Flight::updateV(float acc_ideal,float speed, float delta_t)
{
	float new_speed,acc;
	
	if(fabs(acc_ideal)>MAX_ACELERATION)
        {
		acc = (acc_ideal/fabs(acc_ideal))*MAX_ACELERATION;
	}else{
		acc = acc_ideal;
	}

	return new_speed = speed + acc*delta_t;
		   	
}
float
Flight::updateW(float ideal_w,float w_max )
{
	float new_w;
	
		if(fabs(ideal_w)>w_max)
			{
				 new_w = (fabs(ideal_w)/ideal_w) * MAX_FLIFGT_W; //limitaciones de velocidad angular
			}else{
				 new_w = ideal_w;
			}
			
		return new_w;	
}

float
Flight::diffBearing(float goal_bearing,float bearing)
{
		float diff_bearing;
		diff_bearing = normalizePi(goal_bearing - bearing);
		return diff_bearing;
}

float
Flight::diffInclination(float goal_inclination, float inclination)
{
	float diff_inclination;
	diff_inclination = normalizePi(goal_inclination - inclination);

	return diff_inclination;
}

void
Flight::update(float delta_t)
{
	float trans;
	Position CPpos1;

	if(routed())
	{
			it = route.begin();  // cambie el route.front()
			
			CPpos1 = (*it).pos;	//Creamos la posicion del waypoint 1
			float goal_speed1 = (*it).speed;
			it++;
			Position CPpos2 = it->pos;	//Creamos la posicion del waypoint 2
			float goal_speed2 = it->speed;
			
			float goal_bearing1, goal_bearing2;
			float goal_inclination1, goal_inclination2;

			pos.angles(CPpos1, goal_bearing1, goal_inclination1);
			pos.angles(CPpos2, goal_bearing2, goal_inclination2);	
						
			float alpha1 = diffInclination(goal_inclination1, inclination);
			float alpha2 = diffInclination(goal_inclination2, inclination);
			
			goal_bearing1 = normalizePi(goal_bearing1 + M_PI);
			goal_bearing2 = normalizePi(goal_bearing2 + M_PI);
						
			float theta1 = diffBearing(goal_bearing1, bearing);
			float theta2 = diffBearing(goal_bearing2, bearing);
			
			float ideal_w = theta1; //w ideal para girar todo el rumbo de golpe
			float w_max = MAX_FLIFGT_W;
			float new_w = updateW(ideal_w, w_max);

			float ideal_w_inclination = alpha1; //w ideal para girar todo el rumbo de golpe
			float w_max_inclination = 0.2;//maxima w que podemos tener en descenso
			float new_w_inclination = updateW(ideal_w_inclination,w_max_inclination);

			

			bearing = bearing + new_w*delta_t;
			inclination = inclination + new_w_inclination*delta_t;
		
			float acc_ideal = (goal_speed1 - speed);

			speed = updateV(acc_ideal,speed, delta_t); 
				

			float s = getS(speed, theta1,theta2,w_max);
			float s_inclination = getSInclination(speed, alpha1,alpha2,w_max_inclination);  

/********************************TRAZAS PARA COMPROBAR RESULTADOS*************************************
			//std::cout<<"inclinacion = "<<inclination<<"\tnew = "<<goal_inclination1<<"\t["<<goal_inclination2<<"\talpha1=  " <<alpha1<<"\talpha2=  " <<alpha2<<"]\tideal w = "<<new_w_inclination<<std::endl;

			//std::cout<<"S="<<s<<"   wmax="<<w_max<<"  speed="<<speed<<"  tetha1: "<<theta1<<"  tetha2: "<<theta2<<std::endl;

			//std::cout<<"INCLINACION="<<goal_inclination1<<"	S inclinacion="<<s_inclination<<"		z=   "<<pos.get_z()<<std::endl;
			
			//std::cout<<"x: "<<pos.get_x() <<"  y= "<<pos.get_y()<<"   z=   "<<pos.get_z()<<std::endl;		

****************************************************************************************************/
			
			if((pos.distance(CPpos1)<s)||(pos.distance(CPpos1)<s_inclination))
			{
				new_w = fabs(theta1-theta2)/delta_t;			
				new_w_inclination = fabs(alpha2-alpha1)/delta_t;
				route.pop_front();				
			}
			
	

	}else	
		inclination = 0.0;

	last_pos = pos;

	trans = speed * delta_t;

	pos.set_x(pos.get_x() + trans * cos(bearing)* cos(inclination));
	pos.set_y(pos.get_y() + trans * sin(bearing)* cos(inclination));
	pos.set_z(pos.get_z() + ( trans * sin(inclination)));

        if(pos.distance(CPpos1)<DIST_POINT)
        {
		//std::cout<<pos.distance(CPpos1)<<std::endl;
		route.pop_front();
	}

	if(inStorm)
	{
		//std::cout<<"["<<id<<"]In Storm"<<std::endl;
		points = points - 2*delta_t;
	}
	else
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
