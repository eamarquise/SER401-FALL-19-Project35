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
#include <stdio.h>

#include <bits/stdc++.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

using namespace std;



int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}
int getValuePhy(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int getValueVirt(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

//StudentsToProjectsAssignments will run in this method. This method is called by the threads.
void threadFunction(Student studentPool[],
		Project projectPool[], const int numStudents, const int numProjects, const int numSkills,
		const int teamSize, const int numTopTeams, string results[], int classSection) {
	StudentsToProjects x;
	results[classSection] = x.StudentsToProjectsAssignment(studentPool, projectPool,
			numStudents, numProjects, numSkills, teamSize, numTopTeams);
}


constexpr int toConstInt(int constInt) {
	return constInt;
}

int main(){
	cout << "Hi Team 35" << endl;

	//reading in inputs
	int tempProj, tempStud;
	cout << "#Projects: ";
	cin >> tempProj;
	cout << "#Students: ";
	cin >> tempStud;

	const int NUM_PROJECTS = toConstInt(tempProj);
	const int NUM_STUDENTS = toConstInt(tempStud);
	const int NUM_SKILLS = 7;
	const int NUM_CLASS_SECTIONS = 4;

	Utility util;

	util.makeProjectJSON(NUM_PROJECTS, NUM_SKILLS);
	util.makeStudentJSON(NUM_STUDENTS, NUM_SKILLS);

	const string PROJECT_FILE = "./newProjects.json";
	const string STUDENT_FILE = "./newStudents.json";
	const string CLASS_SECTION_FILE = "./SampleJsonFiles/4ClassSections.json";

	//Change this value to change the number of top teams stored.
    int tempNumTopTeams = 5;
    int tempTeamSize = 5;

	const int NUM_TOP_TEAMS = toConstInt(tempNumTopTeams);
	const int TEAM_SIZE = toConstInt(tempTeamSize);

	StudentJson SJson;
	ProjectJson PJson;
	ClassSectionJson CSJson;

	Project *PROJECT_POOL = new Project[NUM_PROJECTS];
	Student *STUDENT_POOL = new Student[NUM_STUDENTS];
	ClassSection CLASS_SECTION_POOL[NUM_CLASS_SECTIONS];

	int PROJECT_STUDENT_SKILLS[NUM_PROJECTS * NUM_STUDENTS];

	Test t;

	// INITIALIZE POOLS
	util.initProjectPool(PROJECT_FILE, PROJECT_POOL, NUM_PROJECTS);
	util.initStudentPool(STUDENT_FILE, STUDENT_POOL, NUM_STUDENTS);
	util.initClassSectionPool(CLASS_SECTION_FILE, CLASS_SECTION_POOL, STUDENT_POOL,
            NUM_CLASS_SECTIONS, NUM_STUDENTS);
	util.initProjectStudentSkills(PROJECT_POOL, STUDENT_POOL,
			PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS, NUM_SKILLS);

	// PARTITION POOLS BY TYPE (ONLINE/GROUND/HYBRID)
	util.projectTypePartition(PROJECT_POOL, NUM_PROJECTS, 'O', 'G', 'H');
	util.classSectionTypePartition(CLASS_SECTION_POOL, NUM_CLASS_SECTIONS, 'O', 'G');

	// ASSIGN EACH PROJECT TO A CLASS SECTION BASED ON STUDENT-PROJECT SCORE
	util.projectToSectionAssignment(PROJECT_POOL, STUDENT_POOL, CLASS_SECTION_POOL,
				NUM_PROJECTS, NUM_STUDENTS, NUM_CLASS_SECTIONS, NUM_SKILLS);

	cout << endl << "After Project to Class Section Assignment: " << endl ;
	t.PrintProjectPool(PROJECT_POOL, NUM_PROJECTS, NUM_SKILLS);

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

	cout << to_string(getValuePhy() + getValueVirt()) << " KB total memory usage" << endl;

// BEGIN - STUDENTS TO PROJECTS ASSIGNMENT

    //Threads for each class section will start here
    //Students will be partitioned here by skill averages
    //projects will be partitioned by priority

	//THREADS FOR EACH CLASS SECTION...Sean Rogers

	string *results = new string[NUM_CLASS_SECTIONS]; //Stores the results the assignment of students to projects each class section
	int *studentsInSections = new int[NUM_CLASS_SECTIONS]; //stores the number of students in each class section

	//initialize to 0
	for(int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		studentsInSections[i] = 0;
	}

	//set the number of students in each class section to the indexes of studentsInSections[]
	for(int i = 0; i < NUM_STUDENTS; i++) {
		for(int j = 0; j < NUM_CLASS_SECTIONS; j++) {
			if(STUDENT_POOL[i].ClassID == j) {
				studentsInSections[j]++;
			}
		}
	}

	cout << "StudentID|ClassID: ";

	//Print out for testing
	for(int i = 0; i < NUM_STUDENTS; i++) {
		cout << STUDENT_POOL[i].StudentID << "|" << STUDENT_POOL[i].ClassID << "  ";
	}

	cout << endl;

	//create a thread for each class section. store each thread in threads[]
	thread threads[NUM_CLASS_SECTIONS];

	for(int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		//store students in a single class section to *STUDENT_POOL_SECTION_X
		Student *STUDENT_POOL_SECTION_X = new Student[studentsInSections[i]];
		int indexToAddStudent = 0; //used to add a student to STUDENT_POOL_SECTION_X[] from STUDENT_POOL[]

		cout << "StudentIDs in Class Section " << to_string(i) << ": ";

		for(int j = 0; j < NUM_STUDENTS; j++) {
			if(STUDENT_POOL[j].ClassID == i) {
				STUDENT_POOL_SECTION_X[indexToAddStudent] = STUDENT_POOL[j];
				indexToAddStudent++;
			}
		}

		for(int j = 0; j < studentsInSections[i]; j++) {
			cout << STUDENT_POOL_SECTION_X[j].StudentID << " ";
		}

		cout << "Total: " + to_string(studentsInSections[i]) << endl;

		//threads[i] = thread (threadFunction, STUDENT_POOL, PROJECT_POOL, NUM_STUDENTS, NUM_PROJECTS, NUM_SKILLS, TEAM_SIZE, NUM_TOP_TEAMS);
		threads[i] = thread (threadFunction, STUDENT_POOL_SECTION_X, PROJECT_POOL, studentsInSections[i], NUM_PROJECTS, NUM_SKILLS, TEAM_SIZE, NUM_TOP_TEAMS, results, i);
	}

    //join threads
	for(int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		threads[i].join();

	}
	for(int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		cout << results[i] << endl;
	}
	//END THREADS FOR EACH CLASS SECTION...Sean Rogers

//END -STUDENTS TO PROJECTS ASSIGNMENT


    //Tests
	//Test t;
	//t.StructTest();
	//t.PrintProjectPool(PROJECT_POOL, NUM_PROJECTS, NUM_SKILLS);
	//t.PrintStudentPool(STUDENT_POOL, NUM_STUDENTS, NUM_SKILLS);
	//t.PrintProjectStudentSkills(PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS);

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
