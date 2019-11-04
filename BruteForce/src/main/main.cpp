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

using namespace std;

int main(){
	cout << "Hi Team 35" << endl;

	const string projectFilename = "./SampleJsonFiles/projects.json";
	const string studentFilename = "./SampleJsonFiles/students.json";

	Utility u;

	const int numProjects = u.getSizeOfJson(projectFilename, "projects");
	const int numStudents = u.getSizeOfJson(studentFilename, "students");
	const int numSkills = 7;

	Project *projectPool = new Project[numProjects];
	Student *studentPool = new Student[numStudents];

	ProjectJson PJson;
	StudentJson SJson;

	int *projectXstudent  = new int[(numProjects * numStudents)];

	// INITIALIZE PROJECT POOL
	for (int i = 0; i < numProjects; i++) {
		projectPool[i] = PJson.ProjectReader(projectFilename, i);
	}

	// INITIALIZE STUDENT POOL
	for (int i = 0; i < numStudents; i++) {
		studentPool[i] = SJson.getStudentJsonObject(studentFilename, i);
	}

	// INITIALIZE PROJECT X STUDENT SKILL MATRIX
	for (int i = 0; i < (numProjects); i++) {
		for (int j = 0; j < numStudents; j++) {
			int currentProjectXstudent = 0;
			projectXstudent[(i * numStudents) + j] = u.getProjectVsStudentSkill(projectPool, numProjects,
				studentPool, numStudents, numSkills, currentProjectXstudent, i, j);
		}
	}

	//Tests
	Test t;
	t.StructTest();
	t.InitializeProjectPoolTest(projectPool, numProjects);
	t.InitializeStudentPoolTest(studentPool, numStudents);
	t.InitializeProjectStudentSkillMatrixTest(projectXstudent, numProjects, numStudents);

	// Drivers to read in rules, like class section definitions
	// ex - getRules(capStoneCourseDefinitions);

	// Drivers to crunch stuff
	// ex - mapProjectsToClasses(rules);

	// Drivers to write Json
	// ex - composeReport();

	// Drivers to convert Json into some kind of report, like excel or json to pdf?
	// ex - writeReport();

	delete[] projectXstudent;
	delete[] studentPool;
	delete[] projectPool;

	return 0;
}




