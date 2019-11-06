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
#include "Utility.h"

#include <iostream>
#include <utility>
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

	const string PROJECT_FILE = "./SampleJsonFiles/projects.json";
	const string STUDENT_FILE = "./SampleJsonFiles/students.json";

	const int NUM_SKILLS = 7;
	const int TEAM_SIZE = 5;
	const int NUM_CLASS_SECTIONS = 4;

	Utility util;

	int tempNumStudents = util.getSizeOfJson(STUDENT_FILE, "students");
	int tempNumProjects = util.getSizeOfJson(PROJECT_FILE, "projects");

	const int NUM_STUDENTS = toConstInt(tempNumStudents);
	const int NUM_PROJECTS = toConstInt(tempNumProjects);

	Project PROJECT_POOL[NUM_PROJECTS];
	Student STUDENT_POOL[NUM_STUDENTS];
	//ClassSection CLASS_SECTION_POOL[NUM_CLASS_SECTIONS];
	// classID & type

	int PROJECT_STUDENT_SKILLS[NUM_PROJECTS * NUM_STUDENTS];

	// INITIALIZE POOLS
	util.initProjectPool(PROJECT_FILE, PROJECT_POOL, NUM_PROJECTS);
	util.initStudentPool(STUDENT_FILE, STUDENT_POOL, NUM_STUDENTS);
	util.initClassSectionPool(CLASS_SECTION_FILE, CLASS_SECTION_POOL, NUM_CLASS_SECTIONS);
	util.initProjectStudentSkills(PROJECT_POOL, STUDENT_POOL,
			PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS, NUM_SKILLS);

	// PARTITION POOLS BY TYPE (ONLINE/GROUND/HYBRID)
	util.projectTypePartition(PROJECT_POOL, NUM_PROJECTS, 'O', 'G', 'H');

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

	return 0;
}




