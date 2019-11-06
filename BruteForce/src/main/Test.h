/*
 * Test.h
 *
 *  Created on: Oct 27, 2019
 *      Author: myles
 */

#ifndef BRUTEFORCE_SRC_MAIN_TEST_H_
#define BRUTEFORCE_SRC_MAIN_TEST_H_

#include "Project.h"
#include "Student.h"

class Test {
public:
	Test();
	virtual ~Test();
	void PrintProjectPool(Project projectPool[], int numProjects, int numSkills);
	void PrintStudentPool(Student studentPool[], int numStudents, int numSkills);
	void PrintProjectStudentSkills(int projectStudentSkills[], int numProjects, int numStudents);
	void InitializeProjectStudentSkillMatrixTest(int projectXstudent[], int numProjects, int numStudents);
	void StructTest();
};

#endif /* BRUTEFORCE_SRC_MAIN_TEST_H_ */
