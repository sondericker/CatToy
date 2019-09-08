

using namespace std;

#include <iostream>
#include <stdlib.h>
#include "ServoUpdater.h"
#include "TerminalUI.h"


TerminalUI::TerminalUI(ServoUpdater sUp) {

	
	sUpdater = sUp;
	
	runUI();
	
}


void TerminalUI::driveToPosition() {
	bool running = true;

	system("clear");
	cout << "Use wasd to move the laser into position and then hit Enter to set." << endl;
	
	// Set terminal to raw mode 
	system("stty raw"); 
	//sUpdater.goToPos(0.5, 0.5, 1.0); 		// center the laser
	// Loop while the laser is driven around
	while (running) {

			double distA = sUpdater.destPosA - sUpdater.curPosA;
			double distB = sUpdater.destPosB - sUpdater.curPosB;	

		// Wait for single character 
		char input = getchar(); 
		int x;
		switch (input) 
		{
			
			case 'w':
			x = sUpdater.getStepFromPos(sUpdater.destPosA);
			if (x < MAX_STEP) x = x + sUpdater.destSpeed; 
			sUpdater.destPosA = sUpdater.getPosFromStep(x);
			cout << "step from destA = " << x << endl;
			cout << "destPosA = " << sUpdater.destPosA << endl;
			cout << "curPosA = " << sUpdater.curPosA << endl;
			cout << "destSpeed = " << sUpdater.destSpeed << endl;
			cout << "distA = " << distA << " distB = " << distB << endl;		
			
			break;
			
			case 'd':
			x = sUpdater.getStepFromPos(sUpdater.destPosB);
			if (x < MAX_STEP) x = x + sUpdater.destSpeed;
			sUpdater.destPosB = sUpdater.getPosFromStep(x);			
			break;
			
			case 's':
			x = sUpdater.getStepFromPos(sUpdater.destPosA);
			if (x > MIN_STEP) x = x - sUpdater.destSpeed;
			sUpdater.destPosA = sUpdater.getPosFromStep(x);						
			break;
			
			case 'a':
			x = sUpdater.getStepFromPos(sUpdater.destPosB);
			if (x > MIN_STEP) x = x - sUpdater.destSpeed;
			sUpdater.destPosB = sUpdater.getPosFromStep(x);		
			cout << "destPosB = " << sUpdater.destPosB << endl;

			break;
			
			case '\r':
				running=false;
			break;
			
			default:
			
			break;
		}
		
		// Echo input:
		// cout << "--" << input << "--";
				
	}

	// Reset terminal to normal "cooked" mode 
	system("stty cooked"); 	
	// clean up the screen	
//	system("clear");
		
}




void TerminalUI::printMenu() {
	
//	system("clear");
		
	cout << "Main Menu" << endl << endl;
	
	cout << "m - move laser to a position" << endl;
	cout << "p - Print profile" << endl;
	cout << "c - Clear profile" << endl;
	cout << "a - Add steps to profile" << endl;
	cout << "e - Edit profile step" << endl;
	cout << "d - Delete profile step" << endl;
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
		if (inText.length() == 1) {
			
		// if input is a proper command return with it. Otherwise call it out and get another.
		
			if ((inText.front() == 'm') ||
				(inText.front() == 'p') ||
				(inText.front() == 'c') ||
				(inText.front() == 'a') ||
				(inText.front() == 'e') ||
				(inText.front() == 'd') ||
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
			
		cout << "Invalid command. Valid options are m, p, c, a, e, d, r, s, q and l" << endl;
			
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
				
			case 'a':
				break;

			case 'e':
				break;

			case 'd':
				break;

			case 'r':
				break;

			case 's':
				break;

			case 'l':
				break;

			case 'q':
				running = false;
				break;
				
			case '1':
				sUpdater.goToPos(0.0, 0.0, 3.0);
				cout << "1 typed" << endl;				
				cout << "destPosA = " << sUpdater.destPosA << endl;
				cout << "curPosA = " << sUpdater.curPosA << endl;
				cout << "destSpeed = " << sUpdater.destSpeed << endl;
			//	cout << "distA = " << distA << " distB = " << distB << endl;						
				break;
				
			case '2':
				sUpdater.goToPos(1.0, 1.0, 0.2);
				cout << "2 typed" << endl;				
				cout << "destPosA = " << sUpdater.destPosA << endl;
				cout << "curPosA = " << sUpdater.curPosA << endl;
				cout << "destSpeed = " << sUpdater.destSpeed << endl;
			//	cout << "distA = " << distA << " distB = " << distB << endl;						
				break;

			case '3':
				sUpdater.goToPos(1, 0, 2);
				break;
			case '4':
				sUpdater.goToPos(0, 1, 4);
				break;


			}

	}
	
	
	
}
	
