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

/*
 * 1. Establish handler for timer signal
 * 2. Block timer signal temporarily
 * 3. Create the timer
 * 4. Start the timer
 * 5. Unlock the timer signal, so that timer notification can be delivered
 */

class PosixTimer {
public:
	PosixTimer();
	virtual ~PosixTimer();

private:

	void setFreq(long long);
	int assignSigNum(void);
	//virtual void sigHandler(void);
	int blockSignal(void);
	int unblockSignal(void);
	int createTimer(void);


	int sigNumber;
	timer_t timerid;
	static std::vector<int> usedSigNum;
	sigset_t mask;
	long long freq_nano;

protected:

	virtual int timerInit(void);
	int createHandler(void);
	int startTimer(void);
};

#endif /* POSIXTIMER_H_ */
