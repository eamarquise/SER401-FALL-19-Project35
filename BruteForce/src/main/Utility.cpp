/*
 * Utility.cpp
 *
 *  Created on: Oct. 29, 2019
 *      Author: mcilibra
 */
#include "json/json.h"
#include "ProjectJson.h"
#include "StudentJson.h"
#include "Project.h"
#include "Student.h"
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

namespace std {

Utility::Utility() {
	// TODO Auto-generated constructor stub
}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

void Utility::initProjectPool(string filename, Project projectPool[], int numProjects) {
	ProjectJson PJson;
	for (int i = 0; i < numProjects; i++) {
		*(projectPool + i) = PJson.getProjectJsonObject(filename, i);
	}
}

void Utility::initStudentPool(string filename, Student studentPool[], int numStudents) {
	StudentJson SJson;
	for (int i = 0; i < numStudents; i++) {
		*(studentPool + i) = SJson.getStudentJsonObject(filename, i);
	}
}

void Utility::initClassSectionPool(string filename, ClassSection classSectionPool[],
        int numClassSections) {
	ClassSectionJson CSJson;
    for (int i = 0; i < numClassSections; i++) {
        *(classSectionPool + i) = CSJson.getClassSectionJsonObject(filename, i);
    }
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

void Utility::initProjectStudentSkills(Project projectPool[], Student studentPool[],
		int projectStudentSkills[], int numProjects, int numStudents, int numSkills) {

	int score = 0;

	for (int i = 0; i < numProjects; i++) {
		Project project;
		project = *(projectPool + i);
		for (int j = 0; j < numStudents; j++) {
			Student student;
			student = *(studentPool + j);
			score = 0;
			for (int k = 0; k < numSkills; k++) {
				score += project.Skills[k] * student.Skills[k];
			}

			*(projectStudentSkills + (i * numStudents) + j) = score;
		}
	}
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
	cout << "\t";
	for (int i = 0; i < numStudents ; i++ ){
		cout << "st" << students.at(i).StudentID << "\t";
	}
	cout<< endl;
	int projectXstudent[numProjects][numStudents];
	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		string p = to_string(rows);
		cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectXstudent[rows][cols] = {0};
			for (int inner = 0; inner < numSkills; inner++){
				projectXstudent[rows][cols] = projectXstudent[rows][cols] +  projectXskill[rows][inner] * skillXstudent[inner][cols];

			}
			cout << projectXstudent[rows][cols] << "\t\t";
		}
		cout << "\n";
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

// TASK: 107 AUTHOR: CRISTI DELEO
// PARTITION BY PROJECT TYPE (PRIMARY = O | SECONDARY = G | TERTIARY = H
void Utility::projectTypePartition(Project projectPool[], int numProjects,
		char t0, char t1, char t2) {

	int start = 0;
	int end = numProjects - 1;
	int t0Index = 0;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Type == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Type != t0) {
			swap(projectPool[i], projectPool[end--]);
	    } else {
	    	i++;
	    };
	}

	t0Index = 0;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Type == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = numProjects - 1;

	for (int i = t0Index; i <=end; ) {
		if (projectPool[i].Type == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Type != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}
}

} /* namespace std */
