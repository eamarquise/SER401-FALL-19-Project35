/*
 * MainWindow.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the main window of the GUI/application.
 *
 * Created on:   01/25/2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 * List of functions:
 *    - TODO
 *
 */

#include "MainWindow.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

Fl_Window *windowMain;
Fl_Box *boxHeader;
Fl_Button *buttonNewProject;
Fl_Button *buttonOpenProject;
Fl_Input *input;
Fl_Output *output;

using namespace std;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}

// NEW PROJECT BUTTON CLICK
void newProjectButtonClick(Fl_Widget *) {
	bool validNumber = true;
	cout << input->value() << endl;
	string str = input->value();
	if(str.length() == 0) {
			validNumber = false;
	} else if(str.at(0) > 48 && str.at(0) <= 57) {
		for(int i = 1; i < str.length(); i++) {
			if(str.at(i) < 48 || str.at(i) > 57) {
				validNumber = false;
			}
		}
	} else {
		validNumber = false;
	}

	if(validNumber) {
		output->value(input->value());
		cout << "valid number" << endl;
	} else {
		cout << "Invalid number" << endl;
	}
}

// CONSTRUCTOR
MainWindow::MainWindow() {
    // MAIN WINDOW
    const int windowMainW = 400;
    const int windowMainH = 400;
    const char windowMainStr[] = "Project 35";

    // HEADER BOX
    const int boxHeaderX = 20;
    const int boxHeaderY = 20;
    const int boxHeaderW = toConstInt(windowMainW - (boxHeaderX * 2));
    const int boxHeaderH = 75;
    const char boxHeaderStr[] = "Main Window Header";

    // NEW PROJECT BUTTON
    const int buttonNewProjectX = toConstInt(boxHeaderX);
    const int buttonNewProjectY = toConstInt(boxHeaderY + boxHeaderH + 20);
    const int buttonNewProjectW = 100;
    const int buttonNewProjectH = 50;
    const char buttonNewProjectStr[] = "New Project";

    // OPEN PROJECT BUTTON
    const int buttonOpenProjectX = toConstInt(buttonNewProjectX + buttonNewProjectW + 20);
    const int buttonOpenProjectY = toConstInt(buttonNewProjectY);
    const int buttonOpenProjectW = toConstInt(buttonNewProjectW);
    const int buttonOpenProjectH = toConstInt(buttonNewProjectH);
    const char buttonOpenProjectStr[] = "Open Project";

    // INITIALIZE COMPONENTS
    windowMain = new Fl_Window(windowMainW, windowMainH, windowMainStr);
    boxHeader = new Fl_Box(boxHeaderX, boxHeaderY, boxHeaderW,
        boxHeaderH, boxHeaderStr);
    buttonNewProject = new Fl_Button(buttonNewProjectX, buttonNewProjectY,
        buttonNewProjectW, buttonNewProjectH, buttonNewProjectStr);
    buttonOpenProject = new Fl_Button(buttonOpenProjectX, buttonOpenProjectY,
        buttonOpenProjectW, buttonOpenProjectH, buttonOpenProjectStr);

    boxHeader->box(FL_UP_BOX);
    boxHeader->labelfont(FL_BOLD + FL_ITALIC);
    boxHeader->labelsize(18);
    boxHeader->labeltype(FL_SHADOW_LABEL);

    windowMain->show();
    windowMain->end();

    //buttonNewProject->callback(newProjectButtonClick);

    Fl::run();
}

// DESTRUCTOR
MainWindow::~MainWindow() {
    // TODO
}
