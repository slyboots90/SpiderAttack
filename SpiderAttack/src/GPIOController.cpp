/*
 * GPIOController.cpp
 *
 *  Created on: 9 lut 2019
 *      Author: mateu
 */

#include "../inc/GPIOController.h"
#include "../inc/macrologger.h"
#include <iostream>
#include <fstream>

using namespace std;

GPIOController::GPIOController(unsigned int idx, gpioDirection dir) : GPIO(idx, dir) {
	if(!gpioInit()) {
		LOG_ERROR("Cannot initialize GPIO ", to_string(idx));
	}
}

GPIOController::~GPIOController() {

}

//TODO
//Investigate: this method should be static for timer
//But static in class means something else
//static int setValueGPIO7()
int GPIOController::setGPIO() {
	string setval_path = "/sys/class/gpio/gpio" + to_string(index) + "/value";
	ofstream setvalgpio(setval_path.c_str());
	//TODO move open/close out of this method
	if(!setvalgpio.is_open()) {
		LOG_ERROR("FAILED to set value for GPIO ", to_string(index));
		return -1;
	}
	setvalgpio << "1";
	setvalgpio.close();
	return 0;
}

int GPIOController::unsetGPIO() {
	string setval_path = "/sys/class/gpio/gpio" + std::to_string(index) + "/value";
	//TODO move open/close out of this method
	ofstream setvalgpio(setval_path.c_str());
	if(!setvalgpio.is_open()) {
		LOG_ERROR("FAILED to set value for GPIO ", to_string(index));
		return -1;
	}
	setvalgpio << "0";
	setvalgpio.close();
	return 0;
}
