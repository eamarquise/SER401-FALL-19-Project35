/*
 * FileInputWindow.cpp
 *
 *  Created on: Jan. 28, 2020
 *      Author: mcilibra
 */

#include "FileInputWindow.h"

namespace std {
char filename[256]="";
int changedValue = 0;

void beepcb(Fl_Widget *, void *){
	fl_beep();
	fflush(stdout);
}


FileInputWindow::FileInputWindow() {


	Fl_Window *window = new Fl_Window(500,500,"Capstone Team Assignment File Selection" );
	Fl_Box *labelStudentFile = new Fl_Box(50,50,300,20,"Student File");
	Fl_File_Input *fileInput_Student = new Fl_File_Input(50,70,300,35);
	Fl_Box *labelProjectFile = new Fl_Box(50,150,300,20,"Project File");
	Fl_File_Input *fileInput_Project = new Fl_File_Input(50,170,300,35);
	Fl_Button *studentFileChooserButton = new Fl_Button(350, 50, 55,55, "@+3fileopen");
	Fl_Button *projectFileChooserButton = new Fl_Button(350,150, 55,55, "@+3fileopen");

	window->begin();
	labelStudentFile->box(FL_FRAME_BOX);
	labelStudentFile->color(FL_WHITE);
	labelProjectFile->box(FL_FRAME_BOX);
	labelProjectFile->color(FL_WHITE);

	studentFileChooserButton->callback(beepcb, 0);

	window->end();
	window->show();
	Fl::run();

}

FileInputWindow::~FileInputWindow() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
