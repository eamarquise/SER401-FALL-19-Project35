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
	Fl_Box *box = new Fl_Box(10,10,480,100,"This is a box");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labelsize(36);
	box->labeltype(FL_NORMAL_LABEL);
	Fl_Box *box2 = new Fl_Box(510,10,480,100);
	box2->box(FL_UP_BOX);
	box2->label("@+5fileopen");
	Fl_Button *button = new Fl_Button(10,120,50,50,"@+5fileopen");
	button->color(FL_YELLOW);
	Fl_Input *input1 = new Fl_Input(10,180,480,20);
	input1->value("Now is the time for all good men...");
	window->end();
	window->show();
	Fl::run();

}

FileInputWindow::~FileInputWindow() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
