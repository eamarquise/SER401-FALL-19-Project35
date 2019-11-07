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
#include "StudentsToProjects.h"

#include "Utility.h"


using namespace std;


//INFORMATION THAT WE WILL ASSUME WILL BE READ IN FROM THE GUI
int numClassSections = 4;




int main(){
	cout << "Hi Team 35" << endl;

	const string projectFilename = "./SampleJsonFiles/20Projects.json";
	const string studentFilename = "./SampleJsonFiles/60Students.json";


	Utility u;

	const int numProjects = u.getSizeOfJson(projectFilename, "projects");
	const int numStudents = u.getSizeOfJson(studentFilename, "students");
	const int numSkills = 7;


	StudentJson SJson;
	ProjectJson PJson;


	Project *projectPool = new Project[numProjects];
	Student *studentPool = new Student[numStudents];

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


/***** SORTING STUDENTS BASED ON SKILL *****/
	//creating student skill average
	for(int i=0; i<numStudents; i++) {
		double average1=0;
		for(int m=0; m < numSkills; m++) {
			average1 += studentPool[i].Skills[m];
		}
		average1 = average1/numSkills;
		studentPool[i].skillAverage = average1;
	}


	//Averaging student skills into a sorted array
	for(int i=0; i < numStudents; i++){
		Student temp;
		for(int j=(i+1); j < numStudents; j++){
			if (studentPool[j].skillAverage > studentPool[i].skillAverage) {
				temp = studentPool[i];
				studentPool[i] = studentPool[j];
				studentPool[j] = temp;
			}
		}
	 }


	//Counting project priority
	int count2=0, count1=0;
	for(int i=0; i<numProjects; i++){
		if(projectPool[i].Priority ==2) { count2++; }
		if(projectPool[i].Priority ==1) { count1++; }
	}
	count2 = count2*5;
	count1 = count1*5;

	//Pushing students onto project priority vectors
	Student *priority2 = new Student[count2];
	Student *priority1 = new Student[count1];
	Student *priority0 = new Student[numStudents-count2-count1];
	std::copy(studentPool +0, studentPool+(count2-1), priority2);
	std::copy(studentPool +(count2), studentPool +(count2+count1-1), priority1);
	std::copy(studentPool +(count2+count1), studentPool +(numStudents), priority0);


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
	    	int** percentMatrix = u.ProjectToSectionPercentages(studentlist, PJson.allProjects, numProjects, numClassSections);

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
	x.StudentsToProjectsAssignment(SJson.allStudents, PJson.allProjects);


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


	delete[] projectXstudent;
	delete[] studentPool;
	delete[] projectPool;

	return 0;
}





