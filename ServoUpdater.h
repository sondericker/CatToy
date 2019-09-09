

#define UPDATER_FREQUENCY_HZ	   	50		// frequency the updater runs at
#define PWM_HAT_ADDRESS 		0x40		// address of PWM hat hardware
#define PWM_FREQ				100

#include <pthread.h>
#include "PWMDriver.h"

#define STEPS_SLOWEST_SPEED 0.2
#define STEPS_FASTEST_SPEED 15.0
#define MIN_STEP 300
#define MAX_STEP 1078

class ServoUpdater {
	
	public:
	ServoUpdater();
	void start();
	void stop();
	void goToPos(double posA, double posB, double speed);	
	int getStepFromPos(double pos);
	double getPosFromStep(int step);

	double getdestPosA();		// 0.0 - 1.0 pan destination position
	double getdestPosB();		// 0.0 - 1.0 tilt destination position
	double getdestSpeed();		// 0.0 - 1.0 representing slowest to fastest speed
	double getcurPosA();			// pan current position
	double getcurPosB();			// tilt current position	
	bool getmoveComplete();	
	
	protected:
	
	private:
	void updater();							// looping thread method
	static void* threadHelper(void* arg);	// static method to launch thread
	void updateServos();					// method to actually update servo pwms
	pthread_t myThread;
	PWMDriver pwm;	
	bool running;
	pthread_mutex_t lock;
	
	double destPosA;		// 0.0 - 1.0 pan destination position
	double destPosB;		// 0.0 - 1.0 tilt destination position
	double destSpeed;		// 0.0 - 1.0 representing slowest to fastest speed
	double curPosA;			// pan current position
	double curPosB;			// tilt current position	
	bool moveComplete;	

};
