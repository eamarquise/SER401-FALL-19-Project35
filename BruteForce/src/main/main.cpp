/*************************************************************************************
 * main.cpp
 *
 *  Created on: 10/27/2019
 *      Created by: Team#35 (Sean, Myles, Cristi, Matthew, Elizabeth)
 *
 *
 * Description:
 *		This class is the main driver for the skills based assignment of Capstone project teams.
 *	    The algorithm takes in all the projects via Json files, and assigns them to each student
 *	    class section. The class sections are either Online, or Ground. The algorithm, then partitions each
 *	    class sections, projects and students into 3 separate pools, and performs the assignment of student teams
 *	    to projects for each pool. This takes into account negative affinity between students, insuring that
 *	    students who do not want to work with each other will not be assigned to the same team. It scores each team
 *	    assignment based on student to student skills, and availability, and finds the best combination of student teams
 *	    to projects for a given pool.
 *
 * List of Functions:
 *
 *
 *		int main(void)  -The main driver for the skills based assignment of Capstone project teams.
 *
 *	 	void threadFunction(Student studentPool[],
 *		Project projectPool[], const int numStudents, const int numProjects, const int numSkills,
 *		const int teamSize, const int numTopTeams, string results[], int classSection)
 *
 *		int parseLine(char* line) - a function to monitor system memory usage
 *
 *		int getValuePhy() - a function to monitor system memory usage
 *
 *		int getValueVirt() - a function to monitor system memory usage
 *
 *		constexpr int toConstInt(int constInt) - a function to convert an int to a constant
 *
 */
//#include "Student.h"
//#include "Project.h"
//#include "ClassSection.h"
//#include "Test.h"
//#include "json/json.h"
//#include "StudentJson.h"
//#include "ProjectJson.h"
//#include "ClassSectionJson.h"
//#include "Utility.h"
//#include "StudentsToProjects.h"


#include <iostream>
#include <utility>
#include <array>
#include <algorithm>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <chrono>

#include <bits/stdc++.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>

#include "FLTKExample1.h"

using namespace std;
using namespace std::chrono;


int main(){

	FLTKExample1 example;


	return 0;
}
