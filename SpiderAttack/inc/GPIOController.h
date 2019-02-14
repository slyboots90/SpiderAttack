/*
 * GPIOController.h
 *
 *  Created on: 9 lut 2019
 *      Author: mateu
 */

#ifndef GPIOCONTROLLER_H_
#define GPIOCONTROLLER_H_

#include "GPIO.h"

class GPIOController : public GPIO {
public:
	GPIOController(unsigned int, gpioDirection = gpioDirection::out);
	virtual ~GPIOController();

	int setGPIO();
	int unsetGPIO();
	//TODO bool readGPIO();

private:

};

#endif /* GPIOCONTROLLER_H_ */
