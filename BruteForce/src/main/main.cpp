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




/***** SORTING STUDENTS BASED ON SKILL *****/
	//creating student skill average
	for(int i=0; i<numStudents; i++) {
		double average1=0;
		for(int m=0; m < numSkills; m++) {
			average1 += STUDENT_POOL[i].Skills[m];
		}
		average1 = average1/numSkills;
		STUDENT_POOL[i].skillAverage = average1;
	}


	//Averaging student skills into a sorted array
	for(int i=0; i < numStudents; i++){
		Student temp;
		for(int j=(i+1); j < numStudents; j++){
			if (STUDENT_POOL[j].skillAverage > STUDENT_POOL[i].skillAverage) {
				temp = STUDENT_POOL[i];
				STUDENT_POOL[i] = STUDENT_POOL[j];
				STUDENT_POOL[j] = temp;
			}
		}
	 }


	//Counting project priority
	int count2=0, count1=0;
	for(int i=0; i<numProjects; i++){
		if(PROJECT_POOL[i].Priority ==2) { count2++; }
		if(PROJECT_POOL[i].Priority ==1) { count1++; }
	}
	count2 = count2*5;
	count1 = count1*5;

	//Pushing students onto project priority vectors
	Student *priority2 = new Student[count2];
	Student *priority1 = new Student[count1];
	Student *priority0 = new Student[numStudents-count2-count1];
	std::copy(STUDENT_POOL +0, STUDENT_POOL+(count2-1), priority2);
	std::copy(STUDENT_POOL +(count2), STUDENT_POOL +(count2+count1-1), priority1);
	std::copy(STUDENT_POOL +(count2+count1), STUDENT_POOL +(numStudents), priority0);


//TASK#144 TESTS.=================================



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





