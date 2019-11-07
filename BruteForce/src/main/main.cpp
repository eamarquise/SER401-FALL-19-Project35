/*
 * Filename: main.cpp
 * Created On: 10/27/2019
 * Purpose: driver for BruteForce prototype.
 */

#include "Student.h"
#include "Project.h"
#include "ClassSection.h"
#include "Test.h"
#include "json/json.h"
#include "StudentJson.h"
#include "ProjectJson.h"
#include "ClassSectionJson.h"
#include "Utility.h"
#include "StudentsToProjects.h"

#include <iostream>
#include <utility>
#include <array>
#include <algorithm>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

constexpr int toConstInt(int constInt) {
	return constInt;
}

int main(){
	cout << "Hi Team 35" << endl;

	const string PROJECT_FILE = "./SampleJsonFiles/20Projects.json";
	const string STUDENT_FILE = "./SampleJsonFiles/60Students.json";
	const string CLASS_SECTION_FILE = "./SampleJsonFiles/4ClassSections.json";

	const int NUM_SKILLS = 7;
	const int TEAM_SIZE = 5;
	const int NUM_CLASS_SECTIONS = 4;

	Utility util;

	int tempNumStudents = util.getSizeOfJson(STUDENT_FILE, "students");
	int tempNumProjects = util.getSizeOfJson(PROJECT_FILE, "projects");

	const int NUM_STUDENTS = toConstInt(tempNumStudents);
	const int NUM_PROJECTS = toConstInt(tempNumProjects);

	StudentJson SJson;
	ProjectJson PJson;
	ClassSectionJson CSJson;

	Project PROJECT_POOL[NUM_PROJECTS];
	Student STUDENT_POOL[NUM_STUDENTS];
	ClassSection CLASS_SECTION_POOL[NUM_CLASS_SECTIONS];

	int PROJECT_STUDENT_SKILLS[NUM_PROJECTS * NUM_STUDENTS];
	int percentMatrix[NUM_PROJECTS * NUM_CLASS_SECTIONS];

	// INITIALIZE POOLS
	util.initProjectPool(PROJECT_FILE, PROJECT_POOL, NUM_PROJECTS);
	util.initStudentPool(STUDENT_FILE, STUDENT_POOL, NUM_STUDENTS);
	util.initClassSectionPool(CLASS_SECTION_FILE, CLASS_SECTION_POOL, STUDENT_POOL,
            NUM_CLASS_SECTIONS, NUM_STUDENTS);
	util.initProjectStudentSkills(PROJECT_POOL, STUDENT_POOL,
			PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS, NUM_SKILLS);
	util.arrayProjectToSectionPercentages(PROJECT_POOL, STUDENT_POOL, CLASS_SECTION_POOL,
			percentMatrix, NUM_PROJECTS, NUM_STUDENTS, NUM_CLASS_SECTIONS, NUM_SKILLS);

	 //print the resulting percent matrix
	 for (int i = 0; i < NUM_PROJECTS; ++i) {
	     for (int j = 0; j < NUM_CLASS_SECTIONS; j++) {
	         cout << percentMatrix[(i * NUM_CLASS_SECTIONS) + j] << ' ';
	     }
	     cout <<endl;
	 }

	// PARTITION POOLS BY TYPE (ONLINE/GROUND/HYBRID)
	util.projectTypePartition(PROJECT_POOL, NUM_PROJECTS, 'O', 'G', 'H');

//TASK#144 TESTS.=================================
    SJson.StudentReader(STUDENT_FILE);			// Equivalent to util.initStudentPool
    PJson.ProjectReaderVector(PROJECT_FILE);	// Equivalent to util.initProjectPool

    //This is just to create a vector of vectors for use in the percent matrix.
    //the function will take in the vector of vectors of students sorted by class section
    vector<vector<Student>> studentlist(NUM_CLASS_SECTIONS);

    Student s;

    for (int i = 0; i < NUM_CLASS_SECTIONS; ++i) {
        for (int j = 0; j < NUM_STUDENTS; j++) {
            studentlist[i].push_back(SJson.allStudents[j]);
        }
    }

    //function call to create the percent matirx
    int** percentMatrix1 = util.ProjectToSectionPercentages(studentlist,
            PJson.allProjects, NUM_PROJECTS, NUM_CLASS_SECTIONS);

    cout << "PERCENT MATRIX, ROWS=projects, COLUMNS=Class Sections"<<endl;

    //print the resulting percent matrix
    for (int i = 0; i < NUM_PROJECTS; ++i) {
        for (int j = 0; j < NUM_CLASS_SECTIONS; j++) {
            cout << percentMatrix1[i][j] << ' ';
        }
        cout <<endl;
    }
//End -TASK#144 TESTS =================================

//STUDENTS TO PROJECTS ASSIGNMENT
    //Threads for each class section will start here
    //Students will be partitioned here by skill averages
    //projects will be partitioned by priority
    StudentsToProjects x;
    //x.StudentsToProjectsAssignment(SJson.allStudents, PJson.allProjects);

    x.arrayStudentsToProjectsAssignment(PROJECT_POOL, STUDENT_POOL, CLASS_SECTION_POOL,
			NUM_PROJECTS, NUM_STUDENTS, NUM_CLASS_SECTIONS, NUM_SKILLS, TEAM_SIZE);

    //join threads

    //Tests
	Test t;
	t.StructTest();
	t.PrintProjectPool(PROJECT_POOL, NUM_PROJECTS, NUM_SKILLS);
	t.PrintStudentPool(STUDENT_POOL, NUM_STUDENTS, NUM_SKILLS);
	t.PrintProjectStudentSkills(PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS);

	// Drivers to read in rules, like class section definitions
	// ex - getRules(capStoneCourseDefinitions);

	// Drivers to crunch stuff
	// ex - mapProjectsToClasses(rules);

	// Drivers to write Json
	// ex - composeReport();

	// Drivers to convert Json into some kind of report, like excel or json to pdf?
	// ex - writeReport();
    delete[] percentMatrix1;
	return 0;
}





