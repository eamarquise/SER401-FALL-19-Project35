/*
 * SimpleGUI.h
 *
 *  Created on: Jan 26, 2020
 *      Author: myles
 */

#ifndef SRC_MAIN_SIMPLEGUI_H_
#define SRC_MAIN_SIMPLEGUI_H_
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;
class SimpleGUI {
public:
	int num_projects;
	int num_students;

	SimpleGUI();
	virtual ~SimpleGUI();
	void new_window();
	void generateTeams_cb(Fl_Widget* o, void*);
	void quit_cb(Fl_Widget* o, void*);
};
#endif /* SRC_MAIN_SIMPLEGUI_H_ */

