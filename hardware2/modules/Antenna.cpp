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
	printf("Module Antenna - Open Antenna\n");

}
void Antenna::Close(){
	this->status=false;
	printf("MODULE ANTENNA - Close Antenna\n");
}
void Antenna::TurnOn(){
	this->power=true;
	printf("Module Antenna - Turn ON\n");
}
void Antenna::TurnOff(){
	this->power=false;
	printf("Module Antenna - Turn OFF\n");
}

bool Antenna::getStatus(){
	return this->status;
}
bool Antenna::getPower(){
	return this->power;
}

Antenna::~Antenna() {
	// TODO Auto-generated destructor stub
}

