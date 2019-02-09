/*
 * GPIO.cpp
 *
 *  Created on: 8 feb. 2019
 *      Author: mateusz.fraszczynski
 */

#include "../inc/GPIO.h"
#include <iostream>
#include <fstream>

using namespace std;

GPIO::GPIO() : index(0), direction(gpioDirection::out) {

}

GPIO::GPIO(unsigned int idx, gpioDirection dir) {
	if(validateIndex()) {
		cout << "GPIO index %d is not available" << idx <<endl;
	} else {
		this->setIndex(idx);
		this->setDirection(dir);
	}
}

GPIO::~GPIO() {

}

bool GPIO::validateIndex() {
	//TODO
	// 1. Acording to GPIO list on Raspberry
	// 2. Check if GPIO is used already
	return 0;
}

void GPIO::setIndex(unsigned int idx) {
	this->index = idx;
}

unsigned int GPIO::getIndex() {
	return this->index;
}

void GPIO::setDirection(gpioDirection value) {
	this->direction = value;
}

gpioDirection GPIO::getDirection() {
	return direction;
}

int GPIO::gpioInit() {
	if(!index) return -1;
	exportGPIO();
	setDirection();
	return 0;
}

//TODO
//Investigate: this method should be static for timer
//But static in class means something else
//static int setValueGPIO7(bool)
int GPIO::setGPIO(bool val) {
	//TODO This method should be moved to GPIOController class, then index check not needed
	if(!index) return -1;
	string setval_path = "/sys/class/gpio/gpio" + std::to_string(index) + "/value";
	ofstream setvalgpio(setval_path.c_str());
	if(!setvalgpio.is_open()) {
		cout << "FAILED to set value for GPIO%d" << index << endl;
		return -1;
	}
	setvalgpio << to_string((int) val);
	setvalgpio.close();
	return 0;
}

int GPIO::exportGPIO() {
	string export_path = "/sys/class/gpio/export";
	ofstream exportgpio(export_path.c_str());
	if(!exportgpio.is_open()) {
		cout << "FAILED to export GPIO%d" << this->index << endl;
		return -1;
	}
	//TODO
	//Check if c_str() needed - never know..
	exportgpio << std::to_string(index).c_str();
	exportgpio.close();
	return 0;
}

// Better not to use since it unexport all GPIO
// Keeping just in case
int GPIO::unexportGPIO() {
	string unexport_path = "/sys/class/gpio/unexport";
	ofstream unexportgpio(unexport_path.c_str());
	if(!unexportgpio.is_open()) {
		cout << "FAILED to unexport GPIO%d" << this->index << endl;
		return -1;
	}
	return 0;
}

int GPIO::setDirection() {
	string setdir_path = "/sys/class/gpio/gpio" + std::to_string(index) + "/direction";
	ofstream setdirgpio(setdir_path.c_str());
	if(!setdirgpio.is_open()) {
		cout << "FAILED to set direction for GPIO%d" << index << endl;
		return -1;
	}
	if(direction == gpioDirection::out) {
		setdirgpio << "out";
	}
	if(direction == gpioDirection::in) {
		setdirgpio << "in";
	}
	setdirgpio.close();
	return 0;
}
