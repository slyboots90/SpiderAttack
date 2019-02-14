/*
 * PosixTimer.h
 *
 *  Created on: 8 feb. 2019
 *      Author: mateusz.fraszczynski
 */

#ifndef POSIXTIMER_H_
#define POSIXTIMER_H_

#include <vector>
#include <signal.h>
#include <time.h>

class PosixTimer {
public:
	PosixTimer();
	virtual ~PosixTimer();

private:

	void setFreq(long long);
	int createHandler(void);
	int assignSigNum(void);
	//virtual void sigHandler(void);
	int blockSignal(void);
	int unblockSignal(void);
	int createTimer(void);
	int startTimer(void);

	int sigNumber;
	timer_t timerid;
	static std::vector<int> usedSigNum;
	sigset_t mask;
	long long freq_nano;
};

#endif /* POSIXTIMER_H_ */
