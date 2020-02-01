/*
 * FileInputWindow.h
 *
 *  Created on: Jan. 28, 2020
 *      Author: mcilibra
 */

#ifndef SRC_MAIN_FILEINPUTWINDOW_H_
#define SRC_MAIN_FILEINPUTWINDOW_H_

#include <stdio.h>
#include <string.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Multiline_Input.H>


namespace std {


class FileInputWindow {
public:

	FileInputWindow();
	virtual ~FileInputWindow();

};

} /* namespace std */

#endif /* SRC_MAIN_FILEINPUTWINDOW_H_ */
