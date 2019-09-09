

using namespace std;

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "ServoUpdater.h"
#include "MotionProfile.h"
#include "TerminalUI.h"


TerminalUI::TerminalUI(ServoUpdater* sUp) {

	sUpdater = sUp;	
	runUI();
	
}


void TerminalUI::driveToPosition() {
	bool running = true;

	system("clear");
	cout << "Use wasd to move the laser into position and enter to set. Enter Q when finished." << endl;
	
	// Set terminal to raw mode 
	system("stty raw"); 
	//sUpdater.goToPos(0.5, 0.5, 1.0); 		// center the laser
	// Loop while the laser is driven around
	
	
	
	while (running) {

	//		double distA = sUpdater->destPosA - sUpdater->curPosA;
	//		double distB = sUpdater->destPosB - sUpdater->curPosB;	

		// Wait for single character 
		char input = getchar(); 
		int x;
		switch (input) 
		{
			
			case 's':
			x = sUpdater->getStepFromPos(sUpdater->getdestPosA());
			if (x < MAX_STEP) x = x + ((sUpdater->getdestSpeed() * (STEPS_FASTEST_SPEED - STEPS_SLOWEST_SPEED)) + STEPS_SLOWEST_SPEED); 
//			sUpdater->destPosA = sUpdater->getPosFromStep(x);
			sUpdater->goToPos(sUpdater->getPosFromStep(x), sUpdater->getdestPosB(), MANUAL_SPEED);				
			break;
			
			case 'a':
			x = sUpdater->getStepFromPos(sUpdater->getdestPosB());
			if (x < MAX_STEP) x = x + ((sUpdater->getdestSpeed() * (STEPS_FASTEST_SPEED - STEPS_SLOWEST_SPEED)) + STEPS_SLOWEST_SPEED);
			//sUpdater->destPosB = sUpdater->getPosFromStep(x);	
			sUpdater->goToPos(sUpdater->getdestPosA(), sUpdater->getPosFromStep(x), MANUAL_SPEED);	
			break;
			
			case 'w':
			x = sUpdater->getStepFromPos(sUpdater->getdestPosA());
			if (x > MIN_STEP) x = x - ((sUpdater->getdestSpeed() * (STEPS_FASTEST_SPEED - STEPS_SLOWEST_SPEED)) + STEPS_SLOWEST_SPEED);
//			sUpdater->destPosA = sUpdater->getPosFromStep(x);	
			sUpdater->goToPos(sUpdater->getPosFromStep(x), sUpdater->getdestPosB(), MANUAL_SPEED);	
								
			break;
			
			case 'd':
			x = sUpdater->getStepFromPos(sUpdater->getdestPosB());
			if (x > MIN_STEP) x = x - ((sUpdater->getdestSpeed() * (STEPS_FASTEST_SPEED - STEPS_SLOWEST_SPEED)) + STEPS_SLOWEST_SPEED);
//			sUpdater->destPosB = sUpdater->getPosFromStep(x);	
			sUpdater->goToPos(sUpdater->getdestPosA(), sUpdater->getPosFromStep(x), MANUAL_SPEED);	
				
//			cout << "destPosB = " << sUpdater->destPosB << endl;
			break;
			
			case '\r':
			mProfile.addStep(sUpdater->getcurPosA(), sUpdater->getcurPosB(), 0.2);
			cout << "step added" << endl;
			break;
			
			case 'Q':
				running=false;
			break;
			
		}
		

				
	}

	// Reset terminal to normal "cooked" mode 
	system("stty cooked"); 	
	
	// clean up the screen	
	//	system("clear");
		
}




void TerminalUI::printMenu() {
	
	system("clear");
		
	cout << "Main Menu" << endl << endl;
	
	cout << "m - move laser / add profile points" << endl;
	cout << "p - Print profile" << endl;
	cout << "c - Clear profile" << endl;
	cout << "r - Run profile" << endl;
	cout << "s - Save profile" << endl;
	cout << "l - Load profile" << endl;
	cout << "q - quit program" << endl;
	cout << "1 - Test1" << endl;
	cout << "2 - Test2" << endl;
	cout << "3 - Test3" << endl;
	cout << "4 - Test4" << endl;
	
}

char TerminalUI::getCommand() {
	
	string inText;
	
	printMenu();
	
	
	while (true) {
		
		cout << "Command:";
		cin >> inText;
		
		cout << "inText length = " << inText.length() << endl;
		
		if (inText.length() == 1) {
			
		// if input is a proper command return with it. Otherwise call it out and get another.
		
			if ((inText.front() == 'm') ||
				(inText.front() == 'p') ||
				(inText.front() == 'c') ||
				(inText.front() == 'r') ||
				(inText.front() == 's') ||
				(inText.front() == '1') ||
				(inText.front() == '2') ||
				(inText.front() == '3') ||
				(inText.front() == '4') ||
				
				(inText.front() == 'q') ||
				(inText.front() == 'l')) {
				return(inText.front());
			}
		}		
			
		cout << "Invalid command. Valid options are m, p, c, r, s, q and l" << endl;
			
	}
				
}

void TerminalUI::runUI() {
	
	char command;	
	bool running = true;
	
	while (running) {
		
		command = getCommand();
		
		switch (command) {
			
			case 'm':
				driveToPosition();			// just a way to move the laser
				break;
			
			case 'p':
			
				break;
			
			case 'c':
			
				break;
			case 'r':
			
			struct timespec tp;
				tp.tv_sec = 0;
				tp.tv_nsec = 1000000;
				for (int y=0; y<10; y++) {
					for (int x = 0; x < mProfile.numSteps; x++) {
	//					cout << "Heading into gotopos from TerminalUI\n";
						sUpdater->goToPos(mProfile.pan[x], mProfile.tilt[x], mProfile.speed[x]);
						cout << "Moving to step:" << x << " pan:" << mProfile.pan[x] << " tilt:" << mProfile.tilt[x]  << " at speed:" << mProfile.speed[x] << endl;
						while(!sUpdater->getmoveComplete()) {						
							nanosleep(&tp, NULL);						
						}						
						cout << "Finished move." << endl;				
					}
				}
			
				break;

			case 's':
				break;

			case 'l':
				break;

			case 'q':
				running = false;
				break;
				
			case '1':
				sUpdater->goToPos(0.0, 0.0, 0.5);
					
				break;
				
			case '2':
				sUpdater->goToPos(1.0, 1.0, 0.5);
				break;

			case '3':
				sUpdater->goToPos(0.5, 0.5, 0.8);
				break;
			case '4':
				sUpdater->goToPos(0, 1, 1.0);
				break;
			}
	}
}
	
