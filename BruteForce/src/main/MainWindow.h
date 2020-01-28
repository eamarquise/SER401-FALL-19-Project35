#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

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


using namespace std;

class MainWindow {

	//generate teams 'static' callback function
	//this function calls the real TeamsButtonClick callback function.
	static void static_TeamsButtonClick(Fl_Widget* w, void * data) {
		((MainWindow*)data)->TeamsButtonClick(w);
	}

	// generate teams callback function
	void TeamsButtonClick(Fl_Widget* w);

    public:
		int num_projects;
		int num_students;

		Fl_Window *windowMain;
		Fl_Box *boxHeader;
		Fl_Button *buttonNewProject;
		Fl_Button *buttonOpenProject;
		Fl_Button *generateTeams;
		Fl_Int_Input* inputprojects;
		Fl_Int_Input* inputstudents;
        MainWindow();
        ~MainWindow();

};

#endif /*SRC_MAIN_MAINWINDOW_H_*/
