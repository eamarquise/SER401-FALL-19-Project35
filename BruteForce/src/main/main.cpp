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

	const string PROJECT_FILE = "./SampleJsonFiles/10Projects.json";
	const string STUDENT_FILE = "./SampleJsonFiles/60Students.json";
	const string CLASS_SECTION_FILE = "./SampleJsonFiles/4ClassSections.json";



	const int NUM_SKILLS = 7;
	const int NUM_CLASS_SECTIONS = 4;

	Utility util;

	int tempNumStudents = util.getSizeOfJson(STUDENT_FILE, "students");
	int tempNumProjects = util.getSizeOfJson(PROJECT_FILE, "projects");
	//Change this value to change the number of top teams stored.
    int tempNumTopTeams = 5;

    int tempTeamSize = 5;

	const int NUM_STUDENTS = toConstInt(tempNumStudents);
	const int NUM_PROJECTS = toConstInt(tempNumProjects);
	const int NUM_TOP_TEAMS = toConstInt(tempNumTopTeams);
	const int TEAM_SIZE = toConstInt(tempTeamSize);

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

	// PARTITION POOLS BY TYPE (ONLINE/GROUND/HYBRID)
	util.projectTypePartition(PROJECT_POOL, NUM_PROJECTS, 'O', 'G', 'H');

/***** SORTING STUDENTS BASED ON SKILL *****/
	//creating student skill average
	for(int i=0; i<NUM_STUDENTS; i++) {
		double average1=0;
		for(int m=0; m < NUM_SKILLS; m++) {
			average1 += STUDENT_POOL[i].Skills[m];
		}
		average1 = average1/NUM_SKILLS;
		STUDENT_POOL[i].skillAverage = average1;
	}

	//Averaging student skills into a sorted array
	for(int i=0; i < NUM_STUDENTS; i++){
		Student student;
		for(int j=(i+1); j < NUM_STUDENTS; j++){
			if (STUDENT_POOL[j].skillAverage > STUDENT_POOL[i].skillAverage) {
				student = STUDENT_POOL[i];
				STUDENT_POOL[i] = STUDENT_POOL[j];
				STUDENT_POOL[j] = student;
			}
		}
	 }

	//Counting project priority
	int count1 = 0;
	int count2 = 0;

	for(int i=0; i<NUM_PROJECTS; i++){
		if(PROJECT_POOL[i].Priority ==2) { count2++; }
		if(PROJECT_POOL[i].Priority ==1) { count1++; }
	}

	count1 = count1*5;
	count2 = count2*5;

	const int COUNT_1 = toConstInt(count1);
	const int COUNT_2 = toConstInt(count2);

	//Pushing students onto project priority arrays
	Student priority1[COUNT_1];
	Student priority2[COUNT_2];
	Student priority0[NUM_STUDENTS - COUNT_2 - COUNT_1];

	std::copy(STUDENT_POOL + 0, STUDENT_POOL+(COUNT_2-1), priority2);
	std::copy(STUDENT_POOL +(COUNT_2), STUDENT_POOL +(COUNT_2+COUNT_1-1), priority1);
	std::copy(STUDENT_POOL +(COUNT_2+COUNT_1), STUDENT_POOL +(NUM_STUDENTS), priority0);


//START -STUDENTS TO PROJECTS ASSIGNMENT
    //Threads for each class section will start here
    //Students will be partitioned here by skill averages
    //projects will be partitioned by priority
    StudentsToProjects x;
    x.StudentsToProjectsAssignment(STUDENT_POOL, PROJECT_POOL,
    		NUM_STUDENTS, NUM_PROJECTS, NUM_SKILLS, TEAM_SIZE, NUM_TOP_TEAMS);

    //join threads
//END -STUDENTS TO PROJECTS ASSIGNMENT

    //Tests
	Test t;
	//t.StructTest();
	//t.PrintProjectPool(PROJECT_POOL, NUM_PROJECTS, NUM_SKILLS);
	//t.PrintStudentPool(STUDENT_POOL, NUM_STUDENTS, NUM_SKILLS);
	//t.PrintProjectStudentSkills(PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS);
	//t.PrintPercentMatrix(percentMatrix, NUM_PROJECTS, NUM_CLASS_SECTIONS);

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
