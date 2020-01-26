/*
 * SimpleGUI.cpp
 *
 *  Created on: Jan 26, 2020
 *      Author: myles
 */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Output.H>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

#include "SimpleGUI.h"

using namespace std;

SimpleGUI::SimpleGUI() {
	// TODO Auto-generated constructor stub

}

SimpleGUI::~SimpleGUI() {
	// TODO Auto-generated destructor stub
}



void SimpleGUI::new_window(){

	Fl_Window* win = new Fl_Window(300, 200, "Capstone Team Assignment");
	win->begin();
	Fl_Button* generateTeams = new Fl_Button( 10, 150, 70, 30, "Generate Teams");  //child 0 1st Widget
	Fl_Button* quit = new Fl_Button( 100, 150, 70, 30, "Quit");
	Fl_Input* projects = new Fl_Input( 50, 50, 140, 30, "Projects");
	Fl_Input* students = new Fl_Input( 100, 150, 70, 30, "Students"); //child 3 4th Widget
	win->end();
	generateTeams->callback( generateTeams_cb );
	quit->callback( quit_cb );
	win->show();

}

void SimpleGUI::generateTeams_cb(Fl_Widget* o, void*){

Fl_Button *b = (Fl_Button*)o;
Fl_Input* proj = (Fl_Input*)b->parent()->child(2);
Fl_Input* stud = (Fl_Input*)b->parent()->child(3);

strcpy (input->ival = atoi(input->))

num_projects = (int)proj->value();
num_students = (int)stud->value();


cout << endl << num_projects << endl;
cout << endl << num_students << endl;


}

void SimpleGUI::quit_cb(Fl_Widget* o, void*){

exit 0;

}


