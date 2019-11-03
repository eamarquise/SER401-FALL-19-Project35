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
	void InitializeProjectPoolTest(Project projectPool[], int numProjects);
	void InitializeStudentPoolTest(Student studentPool[], int numStudents);
	void StructTest();
};

#endif /* BRUTEFORCE_SRC_MAIN_TEST_H_ */
