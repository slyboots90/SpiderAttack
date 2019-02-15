/*
 * TimerHandler.h
 *
 *  Created on: 14 feb. 2019
 *      Author: mateusz.fraszczynski
 */

#ifndef TIMERHANDLER_H_
#define TIMERHANDLER_H_

#include "PosixTImer.h"

class TimerHandler : private PosixTimer {
public:
	TimerHandler();
	virtual ~TimerHandler();

private:
	int timerInit(void);
};

#endif /* TIMERHANDLER_H_ */
