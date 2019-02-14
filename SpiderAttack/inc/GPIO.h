/*
 * GPIO.h
 *
 * LIMITS: Cant use GPIO 0
 *
 *  Created on: 8 feb. 2019
 *      Author: mateusz.fraszczynski
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <vector>

#define RPI3B 1;

enum gpioDirection {
	out,
	in
	//TODO
	//both
};

class GPIO {

public:

	GPIO();
	GPIO(unsigned int, gpioDirection = gpioDirection::out);
	virtual ~GPIO();

	/* Methods */
	unsigned int getIndex(void);
	void setDirection(gpioDirection);
	gpioDirection getDirection(void);
	//int setGPIO(bool);
	/* Variables */

private:

	/* Methods */
	void setIndex(unsigned int);
	bool validateIndex(unsigned int);
	int exportGPIO(void);
	int unexportGPIO(void);
	int setDirection();
	/* Variables */
	gpioDirection direction;
	static std::vector<int> usedGpio;

protected:

	int gpioInit(void);
	unsigned int index;

};

#endif /* GPIO_H_ */
