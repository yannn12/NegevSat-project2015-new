/*
 * ISensor.hpp
 *
 *  Created on: 3 ???? 2015
 *      Author: hod amran
 */

#ifndef ISENSOR_HPP_
#define ISENSOR_HPP_
#include <string>

class ISensor
{
public:

  virtual int getSample()=0;
  virtual ~ISensor() { }
};


#endif /* ISENSOR_HPP_ */
