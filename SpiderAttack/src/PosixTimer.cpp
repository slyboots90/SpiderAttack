/*
 * PosixTimer.cpp
 *
 *  Created on: 8 feb. 2019
 *      Author: mateusz.fraszczynski
 */

#include "../inc/PosixTimer.h"
#include "../inc/macrologger.h"
#include <iostream>
#include <algorithm> //std::find

#define CLOCKID CLOCK_REALTIME
#define GETSIGNUMMIN SIGRTMIN
#define GETSIGNUMMAX SIGRTMAX

using namespace std;

std::vector<int> PosixTimer::usedSigNum;

PosixTimer::PosixTimer() : sigNumber(-1), timerid(NULL), freq_nano(0) {

}

PosixTimer::~PosixTimer() {

}

void PosixTimer::setFreq(long long freq) {
	this->freq_nano = freq;
}

int PosixTimer::assignSigNum() {
	for(int idx = GETSIGNUMMIN; idx <= GETSIGNUMMAX; idx++) {
		if(std::find(usedSigNum.begin(), usedSigNum.end(), idx) != usedSigNum.end()) {
			// Already reserved - no action
		} else {
			sigNumber = idx;
			usedSigNum.push_back(sigNumber);
			return 0;
		}
	}
	LOG_ERROR("Warning: No available system SIG for Posix Timer");
	return -1;
}

	/* Establish handler for timer signal */
int PosixTimer::createHandler() {
	if(sigNumber == -1) return -1;
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	//TODO virtual sigHandler - new class with handler
	//sa.sa_sigaction = sigHandler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(sigNumber, &sa, NULL) == -1) {
		LOG_ERROR("Cannot create handler");
		return -1;
	}
	return 0;
}

	/* Block timer signal temporarily */
int PosixTimer::blockSignal() {
	sigemptyset(&mask);
	sigaddset(&mask, sigNumber);
	if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1) {
		LOG_ERROR("Cannot block Signal");
		return -1;
	}
	return 0;
}

	/* Unlock the timer signal, so that timer notification can be delivered */
int PosixTimer::unblockSignal() {
	if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1) {
		LOG_ERROR("Cannot unblock Signal");
		return -1;
	}
	return 0;
}

	/* Create the timer */
int PosixTimer::createTimer() {
	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
 	sev.sigev_signo = sigNumber;
	sev.sigev_value.sival_ptr = &timerid;
 	if (timer_create(CLOCKID, &sev, &timerid) == -1) {
		LOG_ERROR("Cannot create timer");
 		return -1;
 	}
 	return 0;
}
	/* Start the timer */
int PosixTimer::startTimer() {
	if(timerid == NULL || freq_nano == 0) {
		LOG_ERROR("Cannot start Timer : improper init");
		return -1;
	}
	struct itimerspec its;
 	its.it_value.tv_sec = freq_nano / 1000000000;
 	its.it_value.tv_nsec = freq_nano % 1000000000;
 	its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;
	if (timer_settime(timerid, 0, &its, NULL) == -1) {
		LOG_ERROR("Cannot start timer");
		return -1;
	}
	return 0;
}

void timerTest() {

	/* Establish handler for timer signal */

	/* Block timer signal temporarily */

	/* Create the timer */

 	/* Start the timer */

	/* Unlock the timer signal, so that timer notification can be delivered */

}
