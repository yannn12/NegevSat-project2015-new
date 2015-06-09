/*
 * Antenna.cpp
 *
 *  Created on: 8 ???? 2015
 *      Author: hod amran
 */

#include <hardware2/modules/Antenna.hpp>

Antenna::Antenna() {
	this->status=false;
	this->power=false;
}

void Antenna::Open(){
	this->status=true;

}
void Antenna::Colse(){
	this->status=false;
}
void Antenna::TurnOn(){
	this->power=true;
}
void Antenna::TurnOff(){
	this->power=false;
}
Antenna::~Antenna() {
	// TODO Auto-generated destructor stub
}

