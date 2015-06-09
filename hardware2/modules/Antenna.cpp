/*
 * Antenna.cpp
 *
 *  Created on: 8 ???? 2015
 *      Author: hod amran
 */

#include <stdio.h>
#include <hardware2/modules/Antenna.hpp>

Antenna::Antenna() {
	this->status=false;
	this->power=false;
}

void Antenna::Open(){
	this->status=true;
	printf("Module Antenna - Open Antenna");

}
void Antenna::Close(){
	this->status=false;
	printf("MODULE ANTENNA - Close Antenna");
}
void Antenna::TurnOn(){
	this->power=true;
	printf("Module Antenna - Turn ON");
}
void Antenna::TurnOff(){
	this->power=false;
	printf("Module Antenna - Turn OFF");
}
Antenna::~Antenna() {
	// TODO Auto-generated destructor stub
}

