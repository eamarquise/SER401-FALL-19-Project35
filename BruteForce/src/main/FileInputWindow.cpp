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
	Fl_Box *labelIntroduction = new Fl_Box(100,50,300,20,"Student File");
	Fl_File_Input *fileInput_Student = new Fl_File_Input(100,75,300,30);

	window->begin();
	labelIntroduction->box(FL_FRAME_BOX);
	labelIntroduction->color(FL_WHITE);
	window->end();
	window->show();
	Fl::run();

}

FileInputWindow::~FileInputWindow() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
