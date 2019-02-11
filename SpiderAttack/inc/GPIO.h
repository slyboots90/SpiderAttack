/*
 * GPIO.h
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
	void setIndex(unsigned int);
	unsigned int getIndex(void);
	void setDirection(gpioDirection);
	gpioDirection getDirection(void);
	int gpioInit(void);
	int setGPIO(bool);
	//TODO bool getGPIO();
	/* Variables */

private:

	/* Methods */
	bool validateIndex(unsigned int);
	int exportGPIO(void);
	int unexportGPIO(void);
	int setDirection();
	/* Variables */
	unsigned int index;
	gpioDirection direction;
	static std::vector<int> usedGpio;

};

#endif /* GPIO_H_ */
