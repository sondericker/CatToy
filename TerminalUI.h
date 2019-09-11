
#define MANUAL_SPEED 0.2
#define NO_PAUSE 0.0
#define RUNNING_PROFILE_CYCLES 5
#define RUNNING_SLEEP_TIME 120

class TerminalUI {

	public:
	TerminalUI(ServoUpdater* sUp);

	protected:

	private:
	double panPos;
	int panPosTicks;
	double tiltPos;
	int tiltPosTicks;
	
	ServoUpdater* sUpdater;
	MotionProfile mProfile;
	void driveToPosition();
	void printMenu();
	char getCommand();
	void runUI();
	
};
