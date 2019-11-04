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
	void StudentsToProjectsAssignment(vector <Student> studentlist, vector <Project> projectlist);
	virtual ~StudentsToProjects();
};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_ */
