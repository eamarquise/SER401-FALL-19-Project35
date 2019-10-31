/*
 * Filename: main.cpp
 * Created On: 10/27/2019
 * Purpose: driver for BruteForce prototype.
 */

#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Student.h"
#include "Project.h"
#include "ClassSection.h"
#include "Test.h"
#include "json/json.h"
#include "StudentJson.h"
#include "ProjectJson.h"

#include "Utility.h"
//#include "Global.h"

#define NUM_PROJECTS 3

using namespace std;

int main(){
	cout << "Hi Team 35" << endl;

	//Tests
	Test t;
	t.StructTest();
	t.InitializeProjectPoolTest();

	//Testing Student Json file reader
	/*StudentJson SJson;
	SJson.StudentReader("./SampleJsonFiles/students.json");

	//Verify all Student source data can be accessed from other files
	cout << "MAIN.CPP TEST" << endl;
	cout << "Number of students read in: "
			+ to_string(SJson.allStudents.size())
			<< endl;

	//Verify all Project source data can be accessed from other files
	cout << "MAIN.CPP TEST" << endl;
	//cout << "Number of projects read in: " + to_string(PJson.allProjects.size())
	//		<< endl;

	// Drivers to read in rules, like class section definitions
	// ex - getRules(capStoneCourseDefinitions);

	// Drivers to crunch stuff
	// ex - mapProjectsToClasses(rules);
	Utility u;
	//vector<vector<int>> projectxstudent = u.calcProjectXStudentMatrix(
	//		SJson.allStudents, PJson.allProjects);

	// Drivers to write Json
	// ex - composeReport();

	// Drivers to convert Json into some kind of report, like excel or json to pdf?
	// ex - writeReport();
*/
	return 0;
}




