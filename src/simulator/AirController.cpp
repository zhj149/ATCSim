/*
 * AirController.cpp
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

#include "AirController.h"
#include "Airport.h"
#include "Flight.h"
#include "Position.h"
#include <list>

AirController::AirController() {
	// TODO Auto-generated constructor stub

}

AirController::~AirController() {
	// TODO Auto-generated destructor stub
}

void
AirController::asignarLanding(Flight *f, Route a, Route b, Route c, Route d)
{

	f->getRoute()->clear();
	f->getRoute()->push_back(d);
	f->getRoute()->push_front(c);
	f->getRoute()->push_front(b);
	f->getRoute()->push_front(a);


//setLanding(true);


}
void
AirController::asignarWaiting(Flight *f, Route a, Route b, Route c, Route d)
{
	f->getRoute()->clear();
	f->getRoute()->push_front(d);
	f->getRoute()->push_front(c);
	f->getRoute()->push_front(b);
	f->getRoute()->push_front(a);
	f->getRoute()->push_front(d);

//setLanding(false);
}

void
AirController::asignarRutaStorm(Flight *f, Route a, Route b, Route c, Route d)
{
	f->getRoute()->clear();
	f->getRoute()->push_front(d);
	f->getRoute()->push_front(c);
	f->getRoute()->push_front(b);
	f->getRoute()->push_front(a);
	f->getRoute()->push_front(d);

}

float
AirController::Distancia(float x1, float x2,float y1, float y2)//,float z1, float z2 )
{
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));// + (z1-z2)*(z1-z2));

}



void
AirController::doWork()
{
			std::list<Flight*> flights = Airport::getInstance()->getFlights();
			std::list<Flight*>::iterator it;
			Storm *storm = Airport::getInstance()->getStorm();

			float R=8700;
			float x0=3000, x1=1500, x2=200, x3=-750;
			float y0=0, y1=0, y2=0, y3=0;
			float x4=R*sin(15*pi/180), x5=R*sin(45*pi/180) ;//x6=R*sin(75*pi/180);
			float x7=R*sin(89*pi/180), x8=R*sin(45*pi/180), x9=R*sin(15*pi/180);
			float y4=-R*cos(15*pi/180), y5=-R*cos(45*pi/180) ;//y6=-R*cos(75*pi/180);
			float y7=R*cos(89*pi/180), y8=R*cos(45*pi/180), y9=R*cos(15*pi/180);

/////////////////////////////////// PUNTOS DE RUTA ////////////////////////
			Position pos0(x0, y0, 100.0);
			Position pos1(x1, y1, 50.0);
			Position pos2(x2, y2, 25.0);
			Position pos3(x3, y3, 25.0);

			Position pos4(x4, y4, 150.0);
			Position pos41(x4, y4+1500.0, 150.0);
			Position pos42(x4-1000.0, y4+1500, 150.0);
			Position pos43(x4-1000.0, y4, 150.0);

			Position pos5(x5, y5, 150.0);
			Position pos51(x5-1220.60, y5+871.85759, 150.0);
			Position pos52(x5-2034.333, y5+290.6237, 150.0);
			Position pos53(x5-813.733, y5-581.2388, 150.0);

			Position pos7(x7, y7, 150.0);
			Position pos71(x7-1500, y7, 150.0);
			Position pos72(x7-1500, y7+3500, 150.0);
			Position pos73(x7, y7+3500, 150.0);

			Position pos8(x8, y8, 150.0);
			Position pos81(x8-1220.60, y8-871.85759, 150.0);
			Position pos82(x8-2034.333, y8-290.6237, 150.0);
			Position pos83(x8-813.733, y8+581.2388, 150.0);

			Position pos9(x9, y9, 150.0);
			Position pos91(x9, y9-1500.0, 150.0);
			Position pos92(x9-1000.0, y9-1500, 150.0);
			Position pos93(x9-1000.0, y9, 150.0);


			Route r0,r1,r2,r3, r4,r41,r42,r43, r5,r51,r52,r53;
			Route r7,r71,r72,r73, r8,r81,r82,r83, r9,r91,r92,r93;

			r0.pos = pos0;
			r0.speed = 180.0;
			r1.pos = pos1;
			r1.speed = 150.0;
			r2.pos = pos2;
			r2.speed = 50.0;
			r3.pos = pos3;
			r3.speed = 15.0;

			r4.pos = pos4;
			r4.speed = 220.0;
			r41.pos = pos41;
			r41.speed = 220.0;
			r42.pos = pos42;
			r42.speed = 220.0;
			r43.pos = pos43;
			r43.speed = 220.0;

			r5.pos = pos5;
			r5.speed = 220.0;
			r51.pos = pos51;
			r51.speed = 220.0;
			r52.pos = pos52;
			r52.speed = 220.0;
			r53.pos = pos53;
			r53.speed = 220.0;

			r7.pos = pos7;
			r7.speed = 220.0;
			r71.pos = pos71;
			r71.speed = 220.0;
			r72.pos = pos72;
			r72.speed = 220.0;
			r73.pos = pos73;
			r73.speed = 220.0;

			r8.pos = pos8;
			r8.speed = 220.0;
			r81.pos = pos81;
			r81.speed = 220.0;
			r82.pos = pos82;
			r82.speed = 220.0;
			r83.pos = pos83;
			r83.speed = 220.0;

			r9.pos = pos9;
			r9.speed = 220.0;
			r91.pos = pos91;
			r91.speed = 220.0;
			r92.pos = pos92;
			r92.speed = 220.0;
			r93.pos = pos93;
			r93.speed = 220.0;

////////////////////////////////////////////////////////////////////////////////

for(it = flights.begin(); it!=flights.end(); ++it)
    {
      float angulo=(atan((*it)->getPosition().get_x()/(*it)->getPosition().get_y()));
      float anguloGrados= angulo/pi*180;

        if (it == flights.begin()&&((*it)->getRoute()->empty()))
        {
            if(((anguloGrados<0) && (anguloGrados>-30)))
            {
              asignarLanding(*it, r0, r1, r2, r3);
              (*it)->getRoute()->push_front(r4);
            }
            else if(((anguloGrados<-30) && (anguloGrados>-60)))
            {
              asignarLanding(*it, r0, r1, r2, r3);
              (*it)->getRoute()->push_front(r5);
            }
            else if(((anguloGrados>0) && (anguloGrados<30)))
            {
              asignarLanding(*it, r0, r1, r2, r3);
              (*it)->getRoute()->push_front(r9);
            }
            else if(((anguloGrados>30) && (anguloGrados<60)))
            {
              asignarLanding(*it, r0, r1, r2, r3);
              (*it)->getRoute()->push_front(r8);
            }
            else if((fabs(anguloGrados)>60))
            {
              asignarLanding(*it, r0, r1, r2, r3);
              (*it)->getRoute()->push_front(r7);
            }

        }
        else if((*it)->getRoute()->empty())
        {
            if(((anguloGrados<0) && (anguloGrados>-30)))
              {
                asignarWaiting(*it, r41, r42, r43, r4);
              }
            else if(((anguloGrados<-30) && (anguloGrados>-60)))
              {
                asignarWaiting(*it, r51, r52, r53, r5);
              }
            else if(((anguloGrados>0) && (anguloGrados<30)))
              {
                asignarWaiting(*it, r91, r92, r93, r9);
              }
            else if(((anguloGrados>30) && (anguloGrados<60)))
              {
                asignarWaiting(*it, r81, r82, r83, r8);
              }
            else if((fabs(anguloGrados)>60))
              {
                asignarWaiting(*it, r71, r72, r73, r7);
              }
          }
        }
///////////////////TORMENTA///////////////////////////////////////////////////

/*
if (storm != NULL)
{
	float X_Strom= storm->getPosition().get_x();
	float Y_Strom= storm->getPosition().get_y();
	float Z_Strom= storm->getPosition().get_z();
	float X_Avion= (*it)->getPosition().get_x();
	float Y_Avion= (*it)->getPosition().get_y();
	float Z_Avion= (*it)->getPosition().get_z();

	float Radio_Strom= storm->getRadious();
	float Altura_Strom= storm->getHeight();
	float Rumbo_Strom= storm->getBearing();//radianes
	float Rumbo_Strom_Grados= Rumbo_Strom*180/pi;
	float Speed_Strom= storm->getSpeed();
	float BEARING_AVION=(*it)->getBearing();


	float Distancia_Av_Strom;
	Distancia_Av_Strom=Distancia(X_Strom, X_Avion, Y_Strom, Y_Avion);//, Z_Strom, Z_Avion);



	float xST1=sin(45*pi/180)*8500;
	float yST1=cos(45*pi/180)*8500;

	Position posST1(-xST1, -yST1, 300);
	Position posST2(-xST1-3500, -yST1, 300);
	Position posST3(-xST1-3500, -yST1-3500, 300);
	Position posST4(-xST1, -yST1-3500, 300);

	Position posST11(-xST1, yST1, 300);
	Position posST21(-xST1-3500, yST1, 300);
	Position posST31(-xST1-3500, yST1+3500, 300);
	Position posST41(-xST1, yST1+3500, 300);

	Route rST1, rST2, rST3, rST4,rST11, rST21, rST31, rST41;

	rST1.pos = posST1;
	rST1.speed = 500.0;
	rST2.pos = posST2;
	rST2.speed = 500.0;
	rST3.pos = posST3;
	rST3.speed = 500.0;
	rST4.pos = posST4;
	rST4.speed = 500.0;

	rST11.pos = posST11;
	rST11.speed = 500.0;
	rST21.pos = posST21;
	rST21.speed = 500.0;
	rST31.pos = posST31;
	rST31.speed = 500.0;
	rST41.pos = posST41;
	rST41.speed = 500.0;

	for(it = flights.begin(); it!=flights.end(); ++it)
	{

		if((Distancia_Av_Strom<Radio_Strom+COLLISION_STORM))
		{
			std::cout << "PELIGRO de TORMENTA" << std::endl;
			if ((X_Strom>0 && Y_Strom<0 && X_Avion>0 && Y_Avion<0)&&((*it)->getRoute()->empty()))
				{
					//std::cout << "Rumbo entre 0 y 90" << std::endl;
					if (Rumbo_Strom_Grados<-45 && Rumbo_Strom_Grados>-135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
					else if(fabs(Rumbo_Strom_Grados)<=45)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if(fabs(Rumbo_Strom_Grados)>=135)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if (Rumbo_Strom_Grados>45 && Rumbo_Strom_Grados<135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
				}
			else if ((X_Strom>0 && Y_Strom>0 && X_Avion>0 && Y_Avion>0)&&((*it)->getRoute()->empty()))
				{
					//std::cout << "Rumbo entre 90 y 180" << std::endl;
					if (Rumbo_Strom_Grados<-45 && Rumbo_Strom_Grados>-135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
					else if(fabs(Rumbo_Strom_Grados)<=45)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if(fabs(Rumbo_Strom_Grados)>=135)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if (Rumbo_Strom_Grados>45 && Rumbo_Strom_Grados<135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
				}
			else if ((X_Strom<0 && Y_Strom>0 && X_Avion<0 && Y_Avion>0)&&((*it)->getRoute()->empty()))
				{
					//std::cout << "Rumbo entre 0 y -90" << std::endl;
					if (Rumbo_Strom_Grados<-45 && Rumbo_Strom_Grados>-135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
					else if(fabs(Rumbo_Strom_Grados)<=45)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if(fabs(Rumbo_Strom_Grados)>=135)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if (Rumbo_Strom_Grados>45 && Rumbo_Strom_Grados<135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
				}
			else if ((X_Strom<0 && Y_Strom<0 && X_Avion<0 && Y_Avion<0)&&((*it)->getRoute()->empty()))
				{
					//std::cout << "Rumbo entre 0 y -180" << std::endl;
					if (Rumbo_Strom_Grados<-45 && Rumbo_Strom_Grados>-135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
					else if(fabs(Rumbo_Strom_Grados)<=45)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if(fabs(Rumbo_Strom_Grados)>=135)
					{
						asignarRutaStorm(*it, rST11, rST21, rST31, rST41);
					}
					else if (Rumbo_Strom_Grados>45 && Rumbo_Strom_Grados<135)
					{
						asignarRutaStorm(*it, rST1, rST2, rST3, rST4);
					}
				}
		}

*/
////////////////////////////////////////////////////////////////////////////////


/*
		/////////////////////////TRAZAS///////////////////////////////////////


		float Lado_Objetivo=Radio_Strom+COLLISION_STORM;
		float Seno_Rumbo_Storm= sin(Rumbo_Strom);
		float Distancia_Av_PtoObjetivo=Distancia(X_Strom+Lado_Objetivo, X_Avion, Y_Strom, Y_Avion, Z_Strom, Z_Avion);
		float Incrmento_Rumbo=asin((Lado_Objetivo*Seno_Rumbo_Storm)/Distancia_Av_PtoObjetivo);

		std::cout << "Rumbo_Strom_Grados: " <<Rumbo_Strom_Grados<< std::endl;
		std::cout << "Incrmento_Rumbo: " <<Incrmento_Rumbo*180/pi<< std::endl;
		std::cout << "Distancia_Av_Strom: " <<Distancia_Av_Strom<< std::endl;
		std::cout << "BEARING_AVION: " <<BEARING_AVION*180/pi<<" "<<(*it)->getId()<< std::endl;
		std::cout << "X strom:  "<<X_Strom << std::endl;
		std::cout << "Y strom:  "<<Y_Strom << std::endl;
		std::cout << "Z strom:  "<<Z_Strom << std::endl;
		std::cout << "Radio strom:  "<<Radio_Strom << std::endl;
		std::cout << "Altura strom:  "<<Altura_Strom << std::endl;
		std::cout << "Rumbo strom:  "<<Rumbo_Strom*180/pi << std::endl;
		std::cout << "Speed strom:  "<<Speed_Strom << std::endl;
*/








	


}
