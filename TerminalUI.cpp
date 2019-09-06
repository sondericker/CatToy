

using namespace std;

#include <iostream>
#include <stdlib.h>
#include "ServoUpdater.h"
#include "TerminalUI.h"


TerminalUI::TerminalUI(ServoUpdater sUp) {

	sUpdater = sUp;
	driveToPosition();

}


void TerminalUI::driveToPosition() {
	
	system("clear");

	cout << "Use wasd to move the laser into position and then hit Enter to set." << endl;
	
	system("stty raw"); 
	bool running = true;
	
	while (running) {
		// Set terminal to raw mode 

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

		// Reset terminal to normal "cooked" mode 
				
	}
	
	system("stty cooked"); 		
	system("clear");
		
}



void TerminalUI::clearTerminal() {
	
	system("CLS");
	
}
