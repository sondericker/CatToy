
#define MANUAL_SPEED 0.1

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
