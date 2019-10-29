/*
 * P35Driver.cpp
 *
 *  Created on: Oct. 23, 2019
 *      Author: mcilibra
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
//#include "Global.h"
using namespace std;


int main(){
	cout << "Hi Team 35" << endl;

	// Task#97 Testing for
	     Test t;
	    t.StructTest();

	//Task#99 testing Student Json file reader
    // To use, you need to copy-paste the location of the Json file on your Computer.
	// To get it, find the file through the (files) app in the virtual box.
	// Then right-click properties, and copy the path next to (parent folder).

	  StudentJson SJson;
	   SJson.StudentReader("/home/myles/git/project35/SER401-FALL-19-Project35/BruteForce/SampleJsonFiles/students.json");

	  ProjectJson PJson;
	   PJson.ProjectReader("/home/myles/git/project35/SER401-FALL-19-Project35/BruteForce/SampleJsonFiles/projects.json");

	// Drivers to read in Json
	// ex - readJSon("filename.json");

	// Drivers to convert Json into data structures
	// ex - jsonToDataStructures(someKindofJSonObject);

	// Drivers to read in rules, like class section definitions
	// ex - getRules(capStoneCourseDefinitions);

	// Drivers to crunch stuff
	// ex - mapProjectsToClasses(rules);

	// Drivers to write Json
	// ex - composeReport();

	// Drivers to convert Json into some kind of report, like excel or json to pdf?
	// ex - writeReport();

	return 0;
}




