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
#include <thread>
#include <cstdlib>
#include <bits/stdc++.h>


#include "Student.h"
#include "Project.h"
#include "ClassSection.h"
#include "Test.h"
#include "json/json.h"
#include "StudentJson.h"
#include "ProjectJson.h"
#include "StudentsToProjects.h"

#include "Utility.h"


using namespace std;


//INFORMATION THAT WE WILL ASSUME WILL BE READ IN FROM THE GUI
int numClassSections = 4;

constexpr int toConstInt(int constInt) {
	return constInt;
}

int main(){
	cout << "Hi Team 35" << endl;


	    const string projectFilename = "./SampleJsonFiles/20Projects.json";
		const string studentFilename = "./SampleJsonFiles/60Students.json";

	    const int NUM_SKILLS = 7;
		const int TEAM_SIZE = 5;
		const int NUM_CLASS_SECTIONS = 4;

		Utility util;

		int tempNumStudents = util.getSizeOfJson(studentFilename, "students");
		int tempNumProjects = util.getSizeOfJson(projectFilename, "projects");

		const int NUM_STUDENTS = toConstInt(tempNumStudents);
		const int NUM_PROJECTS = toConstInt(tempNumProjects);

	Project PROJECT_POOL[NUM_PROJECTS];
	Student STUDENT_POOL[NUM_STUDENTS];

	const int numProjects = util.getSizeOfJson(projectFilename, "projects");
	const int numStudents = util.getSizeOfJson(studentFilename, "students");
	const int numSkills = 7;


	StudentJson SJson;
	ProjectJson PJson;



	// INITIALIZE PROJECT POOL
	for (int i = 0; i < numProjects; i++) {
		PROJECT_POOL[i] = PJson.ProjectReader(projectFilename, i);
	}

	// INITIALIZE STUDENT POOL
	for (int i = 0; i < numStudents; i++) {
		STUDENT_POOL[i] = SJson.getStudentJsonObject(studentFilename, i);
	}



//TASK#144 TESTS.=====================================


	  	  SJson.StudentReader(studentFilename);
          PJson.ProjectReaderVector(projectFilename);

	        //This is just to create a vector of vectors for use in the percent matrix.
	        //the function will take in the vector of vectors of students sorted by class section
	        vector<vector<Student>> studentlist(numClassSections);
            Student s;
	    	for (int i = 0; i < numClassSections; ++i)
	    	  	    {

	    	  	        for (int j = 0; j < numStudents; j++)
	    	  	        {
	    	  	            studentlist[i].push_back(SJson.allStudents[j]);
	    	  	        }}


            //function call to create the percent matirx
	    	int** percentMatrix = util.ProjectToSectionPercentages(studentlist, PJson.allProjects, numProjects, numClassSections);

                   cout << "PERCENT MATRIX, ROWS=projects, COLUMNS=Class Sections"<<endl;
	    		  	//print the resulting percent matrix
	    		  	for (int i = 0; i < numProjects; ++i)
	    		  	    {
	    		  	        for (int j = 0; j < numClassSections; j++)
	    		  	        {
	    		  	            cout << percentMatrix[i][j] << ' ';
	    		  	        }
	    		  	        cout <<endl;
	    		  	    }
//End -TASK#144 TESTS =================================

//STUDENTS TO PROJECTS ASSIGNMENT
	    		  	//Threads for each class section will start here
	    		  	//Students will be partitioned here by skill averages
	    		  	//projects will be partitioned by priority

	StudentsToProjects x;
	x.StudentsToProjectsAssignment(STUDENT_POOL, PROJECT_POOL, NUM_PROJECTS, NUM_STUDENTS);


	                //join threads

	//Tests
	// Test t;
	//t.StructTest();
	//t.InitializeProjectPoolTest(projectPool, numProjects);
	//t.InitializeStudentPoolTest(studentPool, numStudents);
	//t.InitializeProjectStudentSkillMatrixTest(projectXstudent, numProjects, numStudents);

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





