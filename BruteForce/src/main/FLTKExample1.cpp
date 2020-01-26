/*
 * FLTKExample1.cpp
 *
 *  Created on: Jan. 26, 2020
 *      Author: mcilibra
 */

#include "FLTKExample1.h"

namespace std {

FLTKExample1::FLTKExample1() {
	Fl_Window *window = new Fl_Window(340,180);
	Fl_Box *box = new Fl_Box(20,40,300,100,"Hello, World!");
	box->box(FL_UP_BOX);
	box->labelfont(FL_BOLD+FL_ITALIC);
	box->labelsize(36);
	box->labeltype(FL_NORMAL_LABEL);
	window->end();
	window->show();
	Fl::run();
}

FLTKExample1::~FLTKExample1() {
	// TODO Auto-generated destructor stub
}



} /* namespace std */
