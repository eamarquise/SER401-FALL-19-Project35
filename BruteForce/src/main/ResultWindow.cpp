/*
 * ResultWindow.cpp
 *
 * Description:  prints out the team assignment results for the user to review
 *
 *
 * Created on:   01/29/2020
 *
 * Authors:   M. Cilibra, M. Colina, C. DeLeo, E. Marquise, S. Rogers
 *
 * List of functions:
 *
 */

#include "ResultWindow.h"
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
#include <FL/Fl_Text_Display.H>



using namespace std;

//Function to convert integers into constant expressions.
constexpr int toConstInt(int constInt) {
	return constInt;
}

// CONSTRUCTOR
ResultWindow::ResultWindow() {

    // MAIN WINDOW
    const int windowResultW = 640;
    const int windowResultH = 480;
    const char windowResultStr[] = "Project 35";
    windowResult = new Fl_Window(windowResultW, windowResultH, windowResultStr);

    /* HEADER BOX
    const int boxHeaderX = 20;
    const int boxHeaderY = 20;
    const int boxHeaderW = toConstInt(windowResultW - (boxHeaderX * 2));
    const int boxHeaderH = 75;
    const char boxHeaderStr[] = "Hi Team 35!";
    boxHeader = new Fl_Box(boxHeaderX, boxHeaderY, boxHeaderW,
        boxHeaderH, boxHeaderStr);
    boxHeader->box(FL_UP_BOX);
    boxHeader->labelfont(FL_BOLD + FL_ITALIC);
    boxHeader->labelsize(18);
    boxHeader->labeltype(_FL_SHADOW_LABEL);
    boxHeader->labelcolor(FL_BLUE);*/

    // Text Box
    buffer = new Fl_Text_Buffer();
    textDisplay = new Fl_Text_Display(20,20,640-40,480-40, "Results:");
    textDisplay->buffer(buffer);
    windowResult->resizable(textDisplay);


    // INITIALIZE COMPONENTS


    windowResult->show();
    windowResult->end();

    Fl::run();
}

// DESTRUCTOR
ResultWindow::~ResultWindow() {
    // TODO
}
