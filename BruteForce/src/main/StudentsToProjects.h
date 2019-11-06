/*
 * StudentsToProjects.h
 *
 *  Created on: Oct 30, 2019
 *      Author: sean
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

#include "Student.h"
#include "Project.h"

#ifndef BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_
#define BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_

class StudentsToProjects {
public:

	StudentsToProjects();
	void StudentsToProjectsAssignment(Student StudentList[], Project Projectlist[],int numProjects, int numStudents );
	constexpr int toConstInt(int constInt);
	// 3 functions to evaluate a team's score
	int AvailabilityTeamScore(Student team[5]);
	int SkillCompareTeamScore(Student team[5]);
	int ProjectCompareTeamScore(Student team[5], Project project);

	int StudentToStudentSkill(Student s1, Student s2);      //helper function for SkillCompareTeamScore
	int StudentToStudentAvailibility(Student s1, Student s2);   //helper function for AvailabilityTeamScore

	virtual ~StudentsToProjects();
};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_ */
