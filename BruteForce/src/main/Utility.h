/*
 * Utility.h
 *
 *  Created on: Oct. 29, 2019
 *      Author: mcilibra
 */

#ifndef SRC_MAIN_UTILITY_H_
#define SRC_MAIN_UTILITY_H_
#include <vector>
#include "Student.h"
#include "Project.h"
namespace std {

class Utility {
public:
	int numOfClassSections;
	Utility();
	virtual ~Utility();
	//vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects);
	int** ProjectToSectionPercentages(Student *studentList[], Project projectList[], int numProjects, int NumOfClassSections, int ClassSize[]);
};

} /* namespace std */

#endif /* SRC_MAIN_UTILITY_H_ */
