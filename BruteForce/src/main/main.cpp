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

	   //test to make sure all the students can be accessed in other files.
	   cout<<"MAIN.CPP TEST"<<endl;
	   cout<< "Number of students read in: " + to_string(SJson.allStudents.size())<<endl;

	 //Task#100 testing Project Json file reader
	 // To use, you need to copy-paste the location of the Json file on your Computer.
	 // To get it, find the file through the (files) app in the virtual box.
	 // Then right-click properties, and copy the path next to (parent folder).
	   ProjectJson PJson;
	   PJson.ProjectReader("/home/myles/git/project35/SER401-FALL-19-Project35/BruteForce/SampleJsonFiles/projects.json");

	   //test to make sure all the projects can be accessed in other files.
	    cout<<"MAIN.CPP TEST"<<endl;
	  	cout<< "Number of projects read in: " + to_string(PJson.allProjects.size())<<endl;

	  						float percent= 0;
	  		  				float x = 0;
	  		  				int pxskills=6;
	  		  				int pXsection=80;
	  		  				int sl=15;
	  		  				x = (pxskills * sl);
	  		  				percent = pXsection/ x;
	  		  				percent = percent * 100;
	  		  			    percent = (int)percent;
	  		  			    cout<<percent<<endl;

	  		  				//float p, number, base;
	  		  				//p=(number/base)*100;

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


int NumOfClassSections = 4;


/*  ProjectToSectionPercentages(vector<vector<Student>> studentList, vector<Project> projectList)
 *
 *    Function returns a 2d array [number of projects] [ number of class sections]
 *   containing the percentages, 0-100, of how the students in a class section compare to that project
 *
 *      Author: Myles Colina
 */
 int** ProjectToSectionPercentages(vector<vector<Student>> studentList, vector<Project> projectList){


	 //create a 2d array containing the sum of all the students skills, for each skill.
	 int SectionSkills[NumOfClassSections][7] = {0};

	 for(int i = 0; i < NumOfClassSections; i++){

	 //number of students in class sections
	 int numStudents = studentList[i].size();

	 	 for(int j = 0; j < numStudents; j++){

	 		 for(int k = 0; k < 7; k++){
	 			 SectionSkills[i][k] += studentList[i][j].Skills[k];
	 }}}

	 // create skillXproject matrix
	    int numProjects = projectList.size();
	  	int skillXproject[numProjects][7] = {0};
	  	for (int i = 0; i < 7; i++){
	  		for (int j = 0; j < numProjects; j++){
	  			skillXproject[i][j] = projectList[i].Skills[j];
	  		}
	  	}

	  	   // Calculate Project x Section skills Matrix
	  		int projectXsection[numProjects][NumOfClassSections];
	  		for (int rows = 0; rows < NumOfClassSections; rows++){

	  			// do the multiplication
	  			for (int cols = 0; cols < numProjects; cols++){
	  				projectXsection[rows][cols] = {0};
	  				for (int inner = 0; inner < 7; inner++){
	  					projectXsection[rows][cols] = projectXsection[rows][cols] +  SectionSkills[rows][inner] * skillXproject[inner][cols];

	  				}
	  			}
	  		}



          //create a 2d array for the projects, containing the maximum
	  	   //skill score sum a student could have on that project.
	  		int ProjectSkills[numProjects][1] = {0};
	  			  	for (int i = 0; i < numProjects; i++){
	  			  		int sum = 0;
	  			  		for (int j = 0; j < 7; j++){
	  			  		  sum  = sum + projectList[i].Skills[j];
	  			  		}
	  			  	   ProjectSkills[i][0] = sum * 4;
	  			  	}

         //gets the percentages and stores them in a new 2d matrix.
	  		int** percentMatrix = new int *[NumOfClassSections];
	  		//int percentMatrix[numProjects][NumOfClassSections] = {0};

	  		for (int i = 0; i < numProjects; i++){

	  			 for (int j = 0; j < NumOfClassSections; j++){
	  				float percent= 0;
	  				float x = 0;
	  				x = (ProjectSkills[i][0] * studentList[j].size());
	  				percent = projectXsection[j][i]/ x;
	  				percent = percent * 100;
	  			    percent = (int)percent;
	  			    //store percentage in matrix as int, so if 88.8, it will be 88.
	  			  	percentMatrix[i][j] = percent ;

	  			 }}


	  		return  percentMatrix;
 }
 void deleteFunction(int *arr){

	 delete[] arr;
 }


