
#include <iostream>
#include <unistd.h>
#include "PWMDriver.h"
#include <wiringPi.h>
#include <sys/time.h>
#include <cmath>

#include "ServoUpdater.h"


using namespace std;


// ServoUpdater
//
// This class controls the motion for 2 servo axis and drives them
// using a thread from startPosition1,2 to endPosition1,2 at speed.
//
// All positions are doubles in the range of 0.0 - 1.0 representing the
// travel of the servo, which is abstracted and simplified in this class
//
// speed is also a double 0.0 - 1.0 with 1.0 representing the top speed
// of the servo. Both servos will always arrive simultaneously.
//
// Calling goToPos(endPos1, endPos2, speed) will initiate a movement
// which will continue until isMoving = false, indicating the move is complete.




ServoUpdater::ServoUpdater() {
	
	// init pwm driver which will handle both pwm outputs being used
	pwm.initPWM(0x40);			// default i2c hat address
	pwm.setPWMFreq(100);		// run the PWM at 100Hz	
	
	int lowVal = .5/10 * 0xfff;
	int highVal = 2.5/10 * 0xfff;
	cout << "lowVal = " << lowVal << " highVal = " << highVal << endl;
		
	curPosA = 0;
	curPosB = 0;
	destPosA = 0;
	destPosB = 0;
	destSpeed = 3;
	
	pwm.setPWM(0,0x00, lowVal);				// send them back to the beginning to start
	pwm.setPWM(1,0x00, lowVal);
	delayMicroseconds(450000);				// delay 450ms	

}

void ServoUpdater::start() {
	
	// thread is started here via threadHelper
	int err = pthread_create(&myThread, NULL, threadHelper, this);
 
	if (err != 0)
	{
		cout << "Error in thread creation: " << err << endl;
    }
}

void ServoUpdater::stop() {
	
	running = false;
	
}

void* ServoUpdater::threadHelper(void* arg) {
	
	ServoUpdater* thisObject = reinterpret_cast<ServoUpdater*>(arg);
    thisObject->updater();
    
    cout << "ServoUpdater thread stopped" << endl;
    return(0);
	
}

void ServoUpdater::updater() {
	
	struct timeval start, end;

	running = true;
	
	while (running) {
		
		//	cout << ".";
		// grab the time we started the update loop
		gettimeofday(&start, NULL);			// time of the first run
		
		updateServos();
		
		// grab the time again and decide how long we want to sleep
		// pwm writes are significant
		gettimeofday(&end, NULL);
		
		long mtime = ((end.tv_sec) * 1000000000 + end.tv_usec * 1000) - ((start.tv_sec) * 1000000000 + start.tv_usec * 1000);		// number of nanoseconds
		struct timespec tp;
		tp.tv_sec = 0;
		tp.tv_nsec = (1000000000/UPDATER_FREQUENCY_HZ) - mtime;	// 1 billion nano seconds / update frequency - how long it took to run the loop		

		if (tp.tv_nsec < 0) {
			tp.tv_nsec = 1000;	// run time is limited by execution speed. Just wait 1us
		}
		
	//	cout << "Was gone for:" << mtime << " nanoseconds so sleeping for:" << tp.tv_nsec << " nanoseconds." << endl;		
		nanosleep(&tp, NULL);		// updater runs every 1/UPDATE_FREQUENCY_HZ seconds

	}
}

void ServoUpdater::goToPos(double posA, double posB, double speed) {
	destPosA = posA;
	destPosB = posB;
	destSpeed = speed;
	cout << " CALLED posA=" << posA << " destPosA = " << destPosA << "  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
}


void ServoUpdater::updateServos() {
	
	// first, decide which axis has farther to go. It will move at the 
	// commanded speed and the other will scale to arrive at the same time.
	double distA = destPosA - curPosA;
	double distB = destPosB - curPosB;

	cout << "distA =" << distA << "destPosA = " << destPosA << "curPosA = " << curPosA << " distB = " << distB << endl;
	cout << "fabs(distA) = " << fabs(distA) << " fabs(distB) = " << fabs(distB) << endl;
	// if pan has farther to go
	if (fabs(distA) >= fabs(distB)) {
		cout << "A>B ";
		// calculate distance to move this cycle in steps
		int cyclDist = ((STEPS_FASTEST_SPEED - STEPS_SLOWEST_SPEED) * destSpeed) + STEPS_SLOWEST_SPEED;
		int stepA = getStepFromPos(curPosA);
		int stepB = getStepFromPos(curPosB);
		
		if (distA >= 0) {
			// positive direction case - move pan the full amount
			curPosA = getPosFromStep(stepA + cyclDist);
			cout << " curPosA=" << curPosA << " destPosA = " << destPosA << " stepA = " << stepA << "  cyclDist == " << cyclDist << endl;
			// move tilt less by a scaling factor
			curPosB = getPosFromStep(stepB + ((distB/distA)*cyclDist));	// should take care of the sign automatically
		} else {
			// Negative direction case
			curPosA = getPosFromStep(stepA - cyclDist);
			curPosB = getPosFromStep(stepB - ((distB/distA)*cyclDist));	// should take care of the sign automatically
			
		}
	// tilt has farther to go
	} else {
		cout << "B>A";
		int cyclDist = ((STEPS_FASTEST_SPEED - STEPS_SLOWEST_SPEED) * destSpeed) + STEPS_SLOWEST_SPEED;
		int stepA = getStepFromPos(curPosA);
		int stepB = getStepFromPos(curPosB);

		if (distB >= 0) {
			// positive direction case
			curPosB = getPosFromStep(stepB + cyclDist);
			curPosA = getPosFromStep(stepA + ((distA/distB)*cyclDist));	// should take care of the sign automatically
			
		} else {
			// Negative direction case
			curPosB = getPosFromStep(stepB - cyclDist);		
			curPosA = getPosFromStep(stepA - ((distA/distB)*cyclDist));	// should take care of the sign automatically
		}
	}		
	
	// and finally write the corPos in Steps values to the pwm driver
	pwm.setPWM(0,0x00, getStepFromPos(curPosA));				// send them back to the beginning to start
	pwm.setPWM(1,0x00, getStepFromPos(curPosB));

	
		
}


int ServoUpdater::getStepFromPos(double pos) {
	int val = ((MAX_STEP - MIN_STEP)*pos) + MIN_STEP;
//	cout << "step from pos:" << val << endl;
	return(val);
}


double ServoUpdater::getPosFromStep(int step) {
	double val = (step - MIN_STEP) / static_cast<double>(MAX_STEP - MIN_STEP);
//	cout << "pos from step:" << val << endl;
	return(val);
}





