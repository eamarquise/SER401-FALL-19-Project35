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

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

Fl_Window *windowMain;
Fl_Box *boxTitle;
Fl_Button *buttonNewProject;
Fl_Button *buttonOpenProject;
Fl_Input *input;
Fl_Output *output;

using namespace std;

// CONSTRUCTOR
MainWindow::MainWindow() {
    // MAIN WINDOW
    const int windowMainW = 400;
    const int windowMainH = 400;
    const string windowMainStr = "Project 35"

    // HEADER BOX
    int boxHeaderX = 20;
    int boxHeaderY = 20;
    int boxHeaderW = windowMainW - (boxTitleX * 2);
    int boxHeaderH = 75;
    string boxHeaderStr = "Main Window Header"

    // NEW PROJECT BUTTON
    int buttonNewProjectX = boxHeaderX;
    int buttonNewProjectY = boxHeaderY + 20;
    int buttonNewProjectW = 100;
    int buttonNewProjectH = 50;
    string buttonNewProjectStr = "New Project";

    // OPEN PROJECT BUTTON
    int buttonOpenProjectX = buttonNewProjectX + 20;
    int buttonOpenProjectY = buttonNewProjectY;
    int buttonOpenProjectW = buttonNewProjectW;
    int buttonOpenProjectH = buttonNewProjectH;
    string buttonOpenProjectStr = "Open Project";

    // INITIALIZE COMPONENTS
    windowMain = new Fl_Window(windowMainW, windowMainH, windowMainStr);
    boxTitle = new Fl_Box(boxHeaderX, boxHeaderY, boxHeaderW,
        boxHeaderH, boxHeaderStr);
    buttonNewProject = new Fl_Button(buttonNewProjectX, buttonNewProjectY,
        buttonNewProjectW, buttonNewProjectH, buttonNewProjectStr);
    buttonOpenProject = new Fl_Button(buttonOpenProjectX, buttonOpenProjectY,
        buttonOpenProjectW, buttonOpenProjectH, buttonOpenProjectStr);

    boxTitle->box(FL_UP_BOX);
    boxTitle->labelfont(FL_BOLD + FL_ITALIC);
    boxTitle->labelsize(36);
    boxTitle->labeltype(FL_SHADOW_LABEL);

    windowMain->show();
    windowMain->end();

    buttonNewProject->callback(dobut);

    Fl::run();
}

// DESTRUCTOR
MainWindow::~MainWindow() {
    // TODO
}

//
