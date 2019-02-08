//============================================================================
// Name        : SpiderAttack.cpp
// Author      : Skynet
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <pthread.h>
#include <stdio.h>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#include <sys/time.h>

//Timers
//#include <stdlib.h>
//#include <unistd.h>
//#include <stdio.h>
#include <signal.h>
#include <time.h>

using namespace std;

/* Xenomai
#define TASK_STKSZ 32768
#define TASK_PRIO 99 SIG
#define TASK_MODE T_FPU|T_CPU(1)

RT_TASK task1;
RT_TASK task2;
RT_TASK task3;
*/

int setValueGPIO8(string val);

/* ===== INTERRUPTS ======= */

#define CLOCKID CLOCK_REALTIME
#define SIG SIGRTMIN

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

static void print_siginfo(siginfo_t *si) {

	timer_t *tidp;
	int ort;

	*tidp = si->si_value.sival_ptr;

	printf(" sival_ptr = %p; ", si->si_value.sival_ptr);
	printf(" *sival_ptr = 0x%1x\n", (long) *tidp);

	ort = timer_getoverrun(*tidp);
	if(ort == -1) {
		errExit("timer_getoverrun");
	} else {
		printf(" overrun count = %d\n", ort);
	}
}

static void handler(int sig, siginfo_t *si, void *uc) {
           /* Note: calling printf() from a signal handler is not safe
              (and should not be done in production programs), since
              printf() is not async-signal-safe; see signal-safety(7).
              Nevertheless, we use printf() here as a simple way of
              showing that the handler was called. */

	printf("Caught signal %d\n", sig);
	//print_siginfo(si);

	static int cnt = 0;
	if(cnt % 2) {
			setValueGPIO8("1");
}
	else {
		setValueGPIO8("0");
}

	cnt++;
	signal(sig, SIG_IGN);

	if(cnt == 65000) {
		exit(EXIT_FAILURE);
	}
}

void timerTest(long long freq_nanosecs) {
	timer_t timerid;
	struct sigevent sev;
	struct itimerspec its;
	sigset_t mask;
	struct sigaction sa;

	/* Establish handler for timer signal */

	printf("Establishing handler for signal %d\n", SIG);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIG, &sa, NULL) == -1)
		errExit("sigaction");

	/* Block timer signal temporarily */

	printf("Blocking signal %d\n", SIG);
	sigemptyset(&mask);
	sigaddset(&mask, SIG);
	if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
		errExit("sigprocmask");

	/* Create the timer */

	sev.sigev_notify = SIGEV_SIGNAL;
 	sev.sigev_signo = SIG;
	sev.sigev_value.sival_ptr = &timerid;
 	if (timer_create(CLOCKID, &sev, &timerid) == -1)
		errExit("timer_create");

	printf("timer ID is 0x%lx\n", (long) timerid);

 	/* Start the timer */

 	its.it_value.tv_sec = freq_nanosecs / 1000000000;
 	its.it_value.tv_nsec = freq_nanosecs % 1000000000;
  its.it_interval.tv_sec = its.it_value.tv_sec;
	its.it_interval.tv_nsec = its.it_value.tv_nsec;

	if (timer_settime(timerid, 0, &its, NULL) == -1)
		errExit("timer_settime");

	/* Unlock the timer signal, so that timer notification can be delivered */

	printf("Unblocking signal %d\n", SIG);
	if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
 		errExit("sigprocmask");
}



/* ===== CODE ======= */


int exportGPIO(void) {
	string tmp1 = "/sys/class/gpio/export";
	ofstream exportgpio7(tmp1.c_str());
	if(!exportgpio7.is_open()) {
		cout << "FAILED to export GPIO7" << endl;
		return -1;
	}
	exportgpio7 << "7";
	exportgpio7.close();

	string tmp2 = "/sys/class/gpio/export";
	ofstream exportgpio8(tmp2.c_str());
	if(!exportgpio8.is_open()) {
		cout << "FAILED to export GPIO78" << endl;
		return -1;
	}
	exportgpio8 << "8";
	exportgpio8.close();

	string tmp3 = "/sys/class/gpio/export";
	ofstream exportgpio9(tmp3.c_str());
	if(!exportgpio9.is_open()) {
		cout << "FAILED to export GPIO9" << endl;
		return -1;
	}
	exportgpio9 << "9";
	exportgpio9.close();

	return 0;
}

int unexportGPIO(void) {
	string unexport_str = "/sys/class/gpio/unexport";
	ofstream unexportgpio(unexport_str.c_str());
	if(!unexportgpio.is_open()) {
		cout << "FAILED to unexport GPIO" << endl;
		return -1;
	}
	return 0;
}

int setDirection(string gpioNr) {
	//string setdir_str = "/sys/class/gpio/gpio" + gpioNr + "/direction";
	string tmp1 = "/sys/class/gpio/gpio7/direction";
	ofstream setdirgpio7(tmp1.c_str());
	if(!setdirgpio7.is_open()) {
		cout << "FAILED to set direction for GPIO7" << endl;
		return -1;
	}
	setdirgpio7 << "out";
	setdirgpio7.close();

	string tmp2 = "/sys/class/gpio/gpio8/direction";
	ofstream setdirgpio8(tmp2.c_str());
	if(!setdirgpio8.is_open()) {
		cout << "FAILED to set direction for GPIO8" << endl;
		return -1;
	}
	setdirgpio8 << "out";
	setdirgpio8.close();

	string tmp3 = "/sys/class/gpio/gpio9/direction";
	ofstream setdirgpio9(tmp3.c_str());
	if(!setdirgpio9.is_open()) {
		cout << "FAILED to set direction for GPIO9" << endl;
		return -1;
	}
	setdirgpio9 << "out";
	setdirgpio9.close();
	return 0;
}

int setValueGPIO7(string val) {
	string tmp1 = "/sys/class/gpio/gpio7/value";
	ofstream setvalgpio7(tmp1.c_str());
	if(!setvalgpio7.is_open()) {
		cout << "FAILED to set value for GPIO7" << endl;
		return -1;
	}
	setvalgpio7 << val;
	setvalgpio7.close();
	return 0;
}

int setValueGPIO8(string val) {
	string tmp1 = "/sys/class/gpio/gpio8/value";
	ofstream setvalgpio8(tmp1.c_str());
	if(!setvalgpio8.is_open()) {
		cout << "FAILED to set value for GPIO8" << endl;
		return -1;
	}
	setvalgpio8 << val;
	setvalgpio8.close();
	return 0;
}

int setValueGPIO9(string val) {
	string tmp1 = "/sys/class/gpio/gpio9/value";
	ofstream setvalgpio9(tmp1.c_str());
	if(!setvalgpio9.is_open()) {
		cout << "FAILED to set value for GPIO9" << endl;
		return -1;
	}
	setvalgpio9 << val;
	setvalgpio9.close();
	return 0;
}

void delayMicroSec(unsigned int ms) {
	struct timeval tCurrent;
	struct timeval tDelay;
	struct timeval tEnd;

	gettimeofday(&tCurrent, NULL);

	tDelay.tv_sec = ms / 1000000;
	tDelay.tv_usec = ms % 1000000;

	timeradd(&tCurrent, &tDelay, &tEnd);

	while(timercmp(&tCurrent, &tEnd, <)) {
		gettimeofday(&tCurrent, NULL);
	}

}

/*
int init_rt_tasks(void) {
	int err;
	err = rt_task_create(&task1, "PWM1", TASK_STKSZ, TASK_PRIO, TASK_MODE);
	if(!err) {
		rt_task_start(&task1, &gpio7, NULL);
	} else {
		cout << "FAILED to create task1" << endl;
	}
	err = rt_task_create(&task2, "PWM2", TASK_STKSZ, TASK_PRIO, TASK_MODE);
	if(!err) {
		rt_task_start(&task2, &gpio8, NULL);
	} else {
		cout << "FAILED to create task2" << endl;
	}
	err = rt_task_create(&task3, "PWM1", TASK_STKSZ, TASK_PRIO, TASK_MODE);
	if(!err) {
		rt_task_start(&task3, &gpio9, NULL);
	} else {
		cout << "FAILED to create task3" << endl;
	}
	return 0;
}
*/

void *gpio7(void *thread_id) {
	cout << "Hello gpio7" << endl;
	while(1) {
		setValueGPIO7("1");
		/*usleep(200000); */
		delayMicroSec(200000);
		setValueGPIO7("0");
		delayMicroSec(200000);
		/*usleep(200000); */
	}
}

void *gpio8(void *thread_id) {
	cout << "Hello gpio8" << endl;
	while(1) {
		setValueGPIO8("1");
		delayMicroSec(500000);
		/*usleep(500000);*/
		setValueGPIO8("0");
		delayMicroSec(500000);
		/*usleep(500000);*/
	}
}

void *gpio9(void *thread_id) {
	cout << "Hello gpio9" << endl;
	while(1) {
		setValueGPIO9("1");
		/*usleep(200000);*/
		delayMicroSec(200000);
		setValueGPIO9("0");
		delayMicroSec(500000);
		/*usleep(500000);*/
	}
}


int init_tasks(void) {

	pthread_t pwmGPIO7;
	pthread_t pwmGPIO8;
	pthread_t pwmGPIO9;


	pthread_attr_t attrHP;
	pthread_attr_t attrLP;
	pthread_attr_init(&attrHP);
	pthread_attr_init(&attrLP);
	int sched_policy = SCHED_FIFO;
	int priomax = sched_get_priority_max(sched_policy);
	int priomin = sched_get_priority_min(sched_policy);
	struct sched_param spLP;
	struct sched_param spHP;
	pthread_attr_setinheritsched(&attrLP, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setinheritsched(&attrHP, PTHREAD_EXPLICIT_SCHED);
	pthread_attr_setschedpolicy(&attrLP, sched_policy);
	pthread_attr_setschedpolicy(&attrHP, sched_policy);
	spLP.sched_priority = priomax / 2;
	spHP.sched_priority = priomax;
	pthread_attr_setschedparam(&attrLP, &spLP);
	pthread_attr_setschedparam(&attrHP, &spHP);

	pthread_create(&pwmGPIO7, &attrHP, gpio7, (void *)0);
	pthread_create(&pwmGPIO8, &attrHP, gpio8, (void *)0);
	pthread_create(&pwmGPIO9, &attrHP, gpio9, (void *)0);

	return 0;
}


int main(int argc, const char *argv[]) {
	cout << "Off we go :)" << endl;
	if(exportGPIO()) return 0;
	if(setDirection("currently ignored arg")) return 0;
	for(int i=0; i < 5; i++) {
		setValueGPIO7("1");
		setValueGPIO8("1");
		setValueGPIO9("1");
		usleep(500000); //0.5 s
		setValueGPIO7("0");
		setValueGPIO8("0");
		setValueGPIO9("0");
		usleep(500000); //0.5 s
	}

	//init_tasks();

	timerTest(1000000000);
	//timerTest(1000);

	while(true) {

 	}
	return 0;
}
