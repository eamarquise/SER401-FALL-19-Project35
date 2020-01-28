/*
 * FileInputWindow.cpp
 *
 *  Created on: Jan. 28, 2020
 *      Author: mcilibra
 */

#include "FileInputWindow.h"

namespace std {

FileInputWindow::FileInputWindow() {


	Fl_Window *window = new Fl_Window(1000,500,"Capstone Team Assignment File Selection" );
	Fl_Box *labelStudentFile = new Fl_Box(100,50,300,20,"Student File");
	Fl_File_Input *fileInput_Student = new Fl_File_Input(100,71,300,35);
	Fl_Box *labelProjectFile = new Fl_Box(100,150,300,20,"Project File");
	Fl_File_Input *fileInput_Project = new Fl_File_Input(100,171,300,35);

	window->begin();
	labelStudentFile->box(FL_FRAME_BOX);
	labelStudentFile->color(FL_WHITE);
	labelProjectFile->box(FL_FRAME_BOX);
	labelProjectFile->color(FL_WHITE);
	window->end();
	window->show();
	Fl::run();

}

FileInputWindow::~FileInputWindow() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
