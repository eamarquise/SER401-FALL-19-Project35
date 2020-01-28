/*
 * FileInputWindow.h
 *
 *  Created on: Jan. 28, 2020
 *      Author: mcilibra
 */

#ifndef SRC_MAIN_FILEINPUTWINDOW_H_
#define SRC_MAIN_FILEINPUTWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>

namespace std {

class FileInputWindow {
public:
	FileInputWindow();
	virtual ~FileInputWindow();
};

} /* namespace std */

#endif /* SRC_MAIN_FILEINPUTWINDOW_H_ */
