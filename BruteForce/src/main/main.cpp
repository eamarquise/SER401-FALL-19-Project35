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

#include "Utility.h"


using namespace std;

//INFORMATION THAT WE WILL ASSUME WILL BE READ IN FROM THE GUI
int numClassSections = 4;



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
	   SJson.StudentReader("./SampleJsonFiles/60Students.json");


	   //test to make sure all the students can be accessed in other files.
	   cout<<"MAIN.CPP TEST"<<endl;
	   cout<< "Number of students read in: " + to_string(SJson.allStudents.size())<<endl;

	 //Task#100 testing Project Json file reader
	 // To use, you need to copy-paste the location of the Json file on your Computer.
	 // To get it, find the file through the (files) app in the virtual box.
	 // Then right-click properties, and copy the path next to (parent folder).
	   ProjectJson PJson;
	   PJson.ProjectReader("./SampleJsonFiles/20Projects.json");

	   //test to make sure all the projects can be accessed in other files.
	    cout<<"MAIN.CPP TEST"<<endl;
	  	cout<< "Number of projects read in: " + to_string(PJson.allProjects.size())<<endl;
        int numProjects = PJson.allProjects.size();

        const int numprojects = PJson.allProjects.size();
        const int numstudents = SJson.allStudents.size();

        cout<<"Working"<<endl;

        Project *projectPool = new Project[numprojects];
        int *classSize = new int[numClassSections];
        Student** studentList =0;
        studentList = new Student*[numClassSections];

        vector<vector<Student>> studentlist(numClassSections);


        cout<<"Working"<<endl;
    	for (int i = 0; i < numClassSections; ++i)
    	  	    { studentList[i] = new Student[numstudents];
    	  	      classSize[i]= SJson.allStudents.size();

    	  	        for (int j = 0; j < numstudents; j++)
    	  	        {
    	  	        	studentlist[i].push_back(SJson.allStudents[j]);
    	  	            studentList[i][j] = SJson.allStudents[j];
                        cout<<to_string(studentList[i][j].StudentID)<<endl;

    	  	        }}

    	for (int i = 0; i < numProjects; ++i){

    		projectPool[i]=PJson.allProjects[i];
    	}

    	cout<<"Working"<<endl;

	  	//US#88 task#114 test.
	  	Utility u;
	  	int** percentMatrix = u.ProjectToSectionPercentages(studentList, projectPool, numProjects, numClassSections, classSize);


	  	//print the resulting percent matrix
	  	for (int i = 0; i < numProjects; ++i)
	  	    {
	  	        for (int j = 0; j < numClassSections; j++)
	  	        {
	  	            cout << percentMatrix[i][j] << ' ';
	  	        }
	  	        cout <<endl;
	  	    }




	// Drivers to read in rules, like class section definitions
	// ex - getRules(capStoneCourseDefinitions);

	// Drivers to crunch stuff
	// ex - mapProjectsToClasses(rules);

	  	//vector<vector<int>> projectxstudent = u.calcProjectXStudentMatrix(SJson.allStudents, PJson.allProjects);



	// Drivers to write Json
	// ex - composeReport();

	// Drivers to convert Json into some kind of report, like excel or json to pdf?
	// ex - writeReport();

	return 0;
}





