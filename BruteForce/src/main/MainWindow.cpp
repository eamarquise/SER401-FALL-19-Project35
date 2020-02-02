/*
 * MainWindow.cpp
 *
 * Description:  Contains functions relating to the creation and user
 * interaction with the main window of the GUI/application.
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
#include "main.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Widget.H>


using namespace std;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}


/*****************************************************************************
 * TeamsButtonClick
 *
 * Author(s): Myles,
 *
 * Description:
 *		When the Generate Teams button is clicked, this callback function
 *	    takes the inputs from the int text input boxes, and passes them
 *	    to the main Team assignment function (main_run).
 *
 * Arguments:
 *		Fl_Widget* w
 *
 * Returns:
 *		nothing
 */
void MainWindow::TeamsButtonClick(Fl_Widget* w) {

	num_projects = atol(inputprojects->value());
	num_students = atol(inputstudents->value());

	cout <<"'Generate Teams' button clicked" <<endl;
	cout << num_projects<<endl;
	cout<< num_students<<endl;
	cout<<endl;

	//call to main.cpp function main_run, to run the team assignment system.
	main m;
	m.main_run(num_projects, num_students);

}

// CONSTRUCTOR
MainWindow::MainWindow() {
    // MAIN WINDOW
	num_students=0;
	num_projects=0;
    const int windowMainW = 400;
    const int windowMainH = 400;
    const char windowMainStr[] = "Project 35";

    // HEADER BOX
    const int boxHeaderX = 20;
    const int boxHeaderY = 20;
    const int boxHeaderW = toConstInt(windowMainW - (boxHeaderX * 2));
    const int boxHeaderH = 75;
    const char boxHeaderStr[] = "CAPSTONE TEAM ASSIGNMENT SYSTEM";

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

    // PROJECT INPUT
    const int InputProjectX = toConstInt(buttonNewProjectX + buttonNewProjectW + 20);
    const int InputProjectY = toConstInt(buttonNewProjectY + 70);
    const int InputProjectW = toConstInt(buttonNewProjectW);
    const int InputProjectH = toConstInt(buttonNewProjectH);
    const char InputPStr[] = "#Projects";

    // STUDENT INPUT
    const int InputStudentX = toConstInt(buttonNewProjectX + buttonNewProjectW + 20);
    const int InputStudentY = toConstInt(buttonNewProjectY + 140);
    const int InputStudentW = toConstInt(buttonNewProjectW);
    const int InputStudentH = toConstInt(buttonNewProjectH);
    const char InputSStr[] = "#Students";

     // GENERATE TEAMS BUTTON
    const int generateTeamsX = toConstInt(buttonNewProjectX + buttonNewProjectW + 130);
    const int generateTeamsY = toConstInt(buttonNewProjectY + 140);
    const int generateTeamsW = toConstInt(buttonNewProjectW);
    const int generateTeamsH = toConstInt(buttonNewProjectH);
    const char generateTeamsStr[] = "Generate Teams";


    // INITIALIZE COMPONENTS
    windowMain = new Fl_Window(windowMainW, windowMainH, windowMainStr);
    boxHeader = new Fl_Box(boxHeaderX, boxHeaderY, boxHeaderW,
        boxHeaderH, boxHeaderStr);
    buttonNewProject = new Fl_Button(buttonNewProjectX, buttonNewProjectY,
        buttonNewProjectW, buttonNewProjectH, buttonNewProjectStr);
    buttonOpenProject = new Fl_Button(buttonOpenProjectX, buttonOpenProjectY,
        buttonOpenProjectW, buttonOpenProjectH, buttonOpenProjectStr);

    inputprojects = new Fl_Int_Input(InputProjectX, InputProjectY,
    		InputProjectW, InputProjectH, InputPStr );

    inputstudents = new Fl_Int_Input(InputStudentX, InputStudentY,
    		InputStudentW, InputStudentH, InputSStr );

     generateTeams = new Fl_Button(generateTeamsX, generateTeamsY,
    		 generateTeamsW, generateTeamsH, generateTeamsStr);

    generateTeams->callback(static_TeamsButtonClick, this);

    boxHeader->box(FL_UP_BOX);
    boxHeader->labelfont(FL_BOLD + FL_ITALIC);
    boxHeader->labelsize(18);
    boxHeader->labeltype(_FL_SHADOW_LABEL);
    boxHeader->labelcolor(FL_BLUE);

    windowMain->show();
    windowMain->end();

    //buttonNewProject->callback(newProjectButtonClick);

    Fl::run();
}

// DESTRUCTOR
MainWindow::~MainWindow() {

}



