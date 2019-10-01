/*
 * Project.cpp
 *
 *  Created on: Sep 30, 2019
 *      Author: sean
 */

#include "Project.h"
#include <iostream>
#include <string>
using namespace std;

Project::Project(int projectSkillsLength) {
	STUDENTS_LENGTH = 5;
	PROJECT_SKILLS_LENGTH = projectSkillsLength;

	//initialize students array
	students = new int[STUDENTS_LENGTH];
	for(int i = 0; i < STUDENTS_LENGTH; i++) {
		students[i] = 0;
	}
	//initialize the skills required array
	projectSkills = new int[PROJECT_SKILLS_LENGTH];
	for(int i = 0; i < PROJECT_SKILLS_LENGTH; i++) {
		projectSkills[i] = 0;
	}
}

Project::~Project() {
	// TODO Auto-generated destructor stub
}


