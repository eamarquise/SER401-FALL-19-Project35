/*
 * Utility.cpp
 *
 *  Created on: Oct. 29, 2019
 *      Author: mcilibra
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include "Student.h"
#include "Utility.h"

namespace std {

Utility::Utility() {
	// TODO Auto-generated constructor stub

}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects){
	int numStudents = students.size();
	int numProjects = projects.size();
	int numSkills = (sizeof(students.at(0).Skills)/sizeof(*students.at(0).Skills));
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



}


} /* namespace std */
