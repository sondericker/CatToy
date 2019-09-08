


#include <iostream>
#include <stdlib.h>
#include "MotionProfile.h"

using namespace std;


MotionProfile::MotionProfile() {
	
	numSteps = 0;
	

}


void MotionProfile::addStep(double panPos, double tiltPos, double stepSpeed) {
	cout << "Into add step\n";
	
	pan[numSteps] = panPos;
	tilt[numSteps] = tiltPos;
	speed[numSteps] = stepSpeed;
	numSteps++;
	
}



