/*
 * Utility.cpp
 *
 *  Created on: Oct. 29, 2019
 *      Author: mcilibra
 */
#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>

#include <string>
#include <vector>
#include <iterator>

#include "json/json.h"
#include "Student.h"
#include "Utility.h"

using namespace std;

Utility::Utility() {
	// TODO Auto-generated constructor stub

}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}


int Utility::getSizeOfJson(string filename, string key) {
	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	return obj[key].size();
}

int Utility::getProjectXskill(Project projectPool[], int i, int j){
	Project project;
	project = *(projectPool + i);
	return project.Skills[j];
}

int Utility::getSkillXstudent(Student studentPool[], int i, int j){
	Student student;
	student = *(studentPool + i);
	return student.Skills[j];
}

long Utility::getProjectVsStudentSkill(Project projectPool[], int numProjects,
		Student studentPool[], int numStudents, int numSkills, int projectXstudentScore, int i, int j) {

	int projectXskill = 0;
	int skillXstudent = 0;

	Utility u;

	for (int k = 0; k < numSkills; k++){
		projectXskill = u.getProjectXskill(projectPool, i, k);
		skillXstudent = u.getSkillXstudent(studentPool, j, k);

		projectXstudentScore =
				projectXstudentScore +  projectXskill * skillXstudent;
	}

	return projectXstudentScore;
}


vector<vector<int>> Utility::calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects){
	int numStudents = students.size();
	int numProjects = projects.size();
	int numSkills = (sizeof(students.at(0).Skills)/sizeof(*students.at(0).Skills));
	vector<vector<int>> projectXstudentMatrix;
	// create projectXskill matrix
	int projectXskill[numProjects][numSkills] = {0};
	for (int i = 0; i < numProjects; i++){
		for (int j = 0; j < numSkills; j++){
			projectXskill[i][j] = projects.at(i).Skills[j];
		}
	}
	// create skillXstudent matrix transposing skills and students
	int skillXstudent[numSkills][numStudents] = {0};
	for (int i = 0; i < numSkills; i++){
		for (int j = 0; j < numStudents; j++){
			skillXstudent[i][j] = students.at(j).Skills[i];
		}
	}
	//cout << "\t";
	for (int i = 0; i < numStudents ; i++ ){
		//cout << "st" << students.at(i).StudentID << "\t";
	}
	cout<< endl;
	int projectXstudent[numProjects][numStudents];
	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		//string p = to_string(rows);
		//cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectXstudent[rows][cols] = {0};
			for (int inner = 0; inner < numSkills; inner++){
				projectXstudent[rows][cols] = projectXstudent[rows][cols] +  projectXskill[rows][inner] * skillXstudent[inner][cols];

			}
			//cout << projectXstudent[rows][cols] << "\t\t";
		}
		//cout << "\n";
	}
	for (int i = 0; i < numProjects; i++){
		vector<int> currProject;
		for (int j= 0; j < numStudents; j++){
			int studentScore = projectXstudent[i][j];
			currProject.push_back(studentScore);
		}
		projectXstudentMatrix.push_back(currProject);
	}
	return projectXstudentMatrix;
} // end calcProjectXStudentMatrix

void Utility::printIntMatrix(vector<vector<int>> a){
	cout << endl;
	for (int i = 0; i < a.size() ; i++){
		for (int j = 0 ; j < a.at(i).size() ; j++){
			cout << a.at(i).at(j) << "\t";
		}
		cout << endl;
	}
}


/*  ProjectToSectionPercentages(vector<vector<Student>> studentList, vector<Project> projectList)
 *
 *    Function returns a 2d array [number of projects] [ number of class sections]
 *   containing the percentages, 0-100, of how the students in a class section compare to that project
 *
 *      Author: Myles Colina
 */
int** Utility::ProjectToSectionPercentages(vector<vector<Student>> studentList, vector <Project> projectList, int numProjects, int NumOfClassSections){


	 //create a 2d array containing the sum of all the students skills, for each skill.
	 int SectionSkills[NumOfClassSections][7] = {0};

	 int numStudentsByClass[NumOfClassSections];
     Student student;
     Project project;

	 for(int i = 0; i < NumOfClassSections; i++){

	 //number of students in class sections
	 int numStudents = studentList[i].size();
	 numStudentsByClass[i] = numStudents;


	 	 for(int j = 0; j < numStudents; j++){
	 		 student = studentList[i][j];

	 		 for(int k = 0; k < 7; k++){

				SectionSkills[i][k] += student.Skills[k];
	 }}}

	 //Print out to make sure Section Skills is correct.
	 /*cout <<endl;
	 cout<<"Class Section Skills Matrix"<<endl;
		for (int i = 0; i < NumOfClassSections; ++i)
		  	    {
		  	        for (int j = 0; j < 7; j++)
		  	        {
		  	            cout << SectionSkills[i][j] << ' ';
		  	        }
		  	        cout <<endl;
		  	    }*/

	 //create skillXproject matrix
	  	int skillXproject[numProjects][7] = {0};
	  	for (int i = 0; i < 7; i++){
	  		for (int j = 0; j < numProjects; j++){

	  			skillXproject[i][j] = projectList[j].Skills[i];
	  		}
	  	}

	  	//Print out to make sure skillXproject is correct
	  	/*cout <<endl;
	  	cout<<"Project Skills Matrix"<<endl;
	  			for (int i = 0; i < 7; ++i)
	  			  	    {
	  			  	        for (int j = 0; j < numProjects; j++)
	  			  	        {
	  			  	            cout << skillXproject[i][j] << ' ';
	  			  	        }
	  			  	        cout <<endl;
	  			  	    }*/


	  	   // Calculate Project x Section skills Matrix
	  		int projectXsection[numProjects][NumOfClassSections];
	  		for (int rows = 0; rows < numProjects; rows++){

	  			// do the multiplication
	  			for (int cols = 0; cols < NumOfClassSections; cols++){
	  				projectXsection[rows][cols] = {0};
	  				for (int inner = 0; inner < 7; inner++){
	  					projectXsection[rows][cols] = projectXsection[rows][cols] +  SectionSkills[cols][inner] * skillXproject[inner][rows];

	  				}
	  			}
	  		}

	  		//Print out to make sure projectXsection is correct
	  		    /* cout <<endl;
	  			 cout<<"projectXsection Matrix"<<endl;
	  				for (int i = 0; i < numProjects; ++i)
	  				  	    {
	  				  	        for (int j = 0; j < NumOfClassSections; j++)
	  				  	        {
	  				  	            cout << projectXsection[i][j] << ' ';
	  				  	        }
	  				  	        cout <<endl;
	  				  	    }*/


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

            //Print out to make sure ProjectSkills is correct
	  		/*	  cout <<endl;
	  			cout<<"ProjectSkills Matrix"<<endl;
	  				for (int i = 0; i < numProjects; ++i){

	  			  cout << ProjectSkills[i][0] << ' ';
	  			  cout <<endl;
	  				  }*/


          //gets the percentages and stores them in a new 2d matrix.
	  	   int** percentMatrix = 0;
	  	   percentMatrix = new int *[numProjects];

	  		for (int i = 0; i < numProjects; i++){

	  			percentMatrix[i] = new int [NumOfClassSections];

	  			 for (int j = 0; j < NumOfClassSections; j++){
	  				float percent= 0;
	  				float x = 0;
	  				x = (ProjectSkills[i][0] * numStudentsByClass[j]);
	  				percent = projectXsection[i][j]/ x;
	  				percent = percent * 100;
	  			    percent = (int)percent;
	  			    //store percentage in matrix as int, so if 88.8, it will be 88.
	  			  	percentMatrix[i][j] = percent;

	  			 }}


	  		return  percentMatrix;
 }//end ProjectToSectionPercentages



