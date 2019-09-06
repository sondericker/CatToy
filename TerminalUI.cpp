

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


void printMenu() {
	
	clearTerminal();
	
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

char getCommand() {
	
	bool gotCommand = false;
	string inText;
	
	printMenu();
	
	
	while (!gotCommand) {
		
		cout << "Command:";
		cin >> inText;
		if (inText.length==1) {
			
		// got a single character
		if ((intext.front == 'p') ||
			(intext.front == 'c') ||
			(intext.front == 'a') ||
			(intext.front == 'e') ||
			(intext.front == 'd') ||
			(intext.front == 'r') ||
			(intext.front == 's') ||
			(intext.front == 'l')) {
			return(inText.front);
		}
			
		cout << "Invalid command. Valid options are p, c, a, e, d, r, s and l" << endl;
			
	}
		
		
		
		
		
		
		
	}
	
