/*
 * FileInputWindow.cpp
 *
 *  Created on: Jan. 28, 2020
 *      Author: mcilibra
 */


#include "FileInputWindow.h"

namespace std {

Fl_Input *fileInput_Student = NULL;
Fl_Input *fileInput_Project = NULL;

void chooseStudentFile_cb(Fl_Widget*, void*){
	Fl_Native_File_Chooser fileChooser;
	fileChooser.title("Choose File");
	fileChooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fileChooser.preset_file(fileInput_Student->value());
	switch ( fileChooser.show() ) {
		default:
			if ( fileChooser.filename() ) {
				fileInput_Student->value(fileChooser.filename());
			} else {
				fileInput_Student->value("NULL");
			}
			break;
	}
}

void chooseProjectFile_cb(Fl_Widget*, void*){
	Fl_Native_File_Chooser fileChooser;
	fileChooser.title("Choose File");
	fileChooser.type(Fl_Native_File_Chooser::BROWSE_FILE);
	fileChooser.preset_file(fileInput_Project->value());
	switch ( fileChooser.show() ) {
		default:
			if ( fileChooser.filename() ) {
				fileInput_Project->value(fileChooser.filename());
			} else {
				fileInput_Project->value("NULL");
			}
			break;
	}
}

FileInputWindow::FileInputWindow() {

	Fl_Window *window = new Fl_Window(500,500,"Capstone Team Assignment File Selection" );
	window->begin();

	Fl_Box *labelStudentFile = new Fl_Box(75,50,300,20,"Student File");
	labelStudentFile->box(FL_FRAME_BOX);
	labelStudentFile->color(FL_WHITE);

	fileInput_Student = new Fl_Input(75,70,300,35);
	fileInput_Student->value(".");

	Fl_Box *labelProjectFile = new Fl_Box(75,150,300,20,"Project File");
	labelProjectFile->box(FL_FRAME_BOX);
	labelProjectFile->color(FL_WHITE);

	fileInput_Project = new Fl_Input(75,170,300,35);
	fileInput_Project->value(".");

	Fl_Button *studentFileChooserButton = new Fl_Button(375, 50, 55,55, "@+3fileopen");
	studentFileChooserButton->callback(chooseStudentFile_cb, 0);

	Fl_Button *projectFileChooserButton = new Fl_Button(375,150, 55,55, "@+3fileopen");
	projectFileChooserButton->callback(chooseProjectFile_cb, 0);

	window->end();
	window->show();
	Fl::run();

}

FileInputWindow::~FileInputWindow() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
