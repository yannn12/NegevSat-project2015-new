/*
 * ISensor.hpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef ISENSOR_HPP_
#define ISENSOR_HPP_
#include <string>
using namespace std;
class ISensor
{
	private:
	int status;
	string name;

public:

	ISensor(string _name){
			name = _name;
	}

  virtual int getSample(bool useI2C)=0;
  virtual void setValue(int val)=0;
  void setStatus(int _status) {
		status = _status;
  }

  int getStatus(){
		return status;
  }

  void setName(string _name){
  		name = _name;
  	}

  	string getName(){
  		return name;
  	}

  virtual ~ISensor() { }
};


#endif /* ISENSOR_HPP_ */
