

using namespace std;

#include <iostream>
#include <stdlib.h>
#include "ServoUpdater.h"
#include "TerminalUI.h"


TerminalUI::TerminalUI(ServoUpdater sUp) {

	sUpdater = sUp;
	char command = getCommand();
	cout << "Received command:" << command << endl;
	driveToPosition();
	

}


void TerminalUI::driveToPosition() {
	bool running = true;

	system("clear");
	cout << "Use wasd to move the laser into position and then hit Enter to set." << endl;
	
	// Set terminal to raw mode 
	system("stty raw"); 
	sUpdater.goToPos(0.5, 0.5, 1.0); 		// center the laser
	// Loop while the laser is driven around
	while (running) {

		// Wait for single character 
		char input = getchar(); 

		switch (input) 
		{
			
			case 'w':
			
			break;
			
			case 'a':
			
			break;
			
			case 's':
						
			break;
			
			case 'd':
			
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
	system("clear");
		
}




void TerminalUI::printMenu() {
	
	system("clear");
		
	cout << "Main Menu" << endl << endl;
	
	cout << "p - Print profile" << endl;
	cout << "c - Clear profile" << endl;
	cout << "a - Add steps to profile" << endl;
	cout << "e - Edit profile step" << endl;
	cout << "d - Delete profile step" << endl;
	cout << "r - Run profile" << endl;
	cout << "s - Save profile" << endl;
	cout << "l - Load profile" << endl;
	
}

char TerminalUI::getCommand() {
	
	string inText;
	
	printMenu();
	
	
	while (true) {
		
		cout << "Command:";
		cin >> inText;
		if (inText.length() == 1) {
			
		// if input is a proper command return with it. Otherwise call it out and get another.
			if ((inText.front() == 'p') ||
				(inText.front() == 'c') ||
				(inText.front() == 'a') ||
				(inText.front() == 'e') ||
				(inText.front() == 'd') ||
				(inText.front() == 'r') ||
				(inText.front() == 's') ||
				(inText.front() == 'q') ||
				(inText.front() == 'l')) {
				return(inText.front());
			}
		}		
			
		cout << "Invalid command. Valid options are p, c, a, e, d, r, s, q and l" << endl;
			
	}
		
		
}
	
