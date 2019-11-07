/*
 * Utility.h
 *
 *  Created on: Oct. 29, 2019
 *      Author: mcilibra
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "Student.h"
#include "Project.h"
#include "ClassSection.h"

#include <string>
#include <vector>
#include <array>

using namespace std;

class Utility {
    public:
		Utility();

		void initProjectPool(string filename, Project projectPool[], int numProjects);
		void initStudentPool(string filename, Student studentPool[], int numStudents);
		void initClassSectionPool(string filename, ClassSection classSectionPool[],
                int numClassSections);
		void initProjectStudentSkills(Project projectPool[], Student studentPool[],
				int projectStudentSkills[], int numProjects, int numStudents, int numSkills);
		int getSizeOfJson(string filename, string key);
		int getProjectXskill(Project projectPool[], int i, int j);
		int getSkillXstudent(Student studentPool[], int i, int j);
		vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects);
		void projectTypePartition(Project projectPool[], int numProjects,
				char t0, char t1, char t2);
		void printIntMatrix(vector<vector<int>> a);
		int** ProjectToSectionPercentages(vector<vector<Student>> studentList,
				vector<Project> projectList, int numProjects, int NumOfClassSections);
		void arrayProjectToSectionPercentages(Project projectPool[],
		        Student studentPool[], int percentMatrix[], int numProjects, int numStudents, int numClassSections,
				int numSkills);
		~Utility();
};

#endif /* SRC_MAIN_UTILITY_H_ */
