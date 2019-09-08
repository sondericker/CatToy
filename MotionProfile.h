

#define default speed 0.8

class MotionProfile {
	
	public:
	MotionProfile();
	void addStep(double panPos, double tiltPos, double stepSpeed);
	int numSteps;
	double pan[100] = {0.0};
	double tilt[100] = {0.0};
	double speed[100] = {0.0};
	
	protected:
	
	private:

	
};
