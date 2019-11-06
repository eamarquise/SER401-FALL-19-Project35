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
		Utility();
		virtual ~Utility();
<<<<<<< HEAD
		void initProjectPool(string filename, Project projectPool[], int numProjects);
		void initStudentPool(string filename, Student studentPool[], int numStudents);
		void initClassSectionPool(string filename, ClassSection classSectionPool[],
                int numClassSections);
		void initProjectStudentSkills(Project projectPool[], Student studentPool[],
				int projectStudentSkills[], int numProjects, int numStudents, int numSkills);
		vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects);
=======

>>>>>>> p35/dev
		int getProjectXskill(Project projectPool[], int i, int k);
		int getSkillXstudent(Student studentPool[], int i, int j);
		int getSizeOfJson(string filename, string key);
<<<<<<< HEAD
		void projectTypePartition(Project projectPool[], int numProjects,
				char t0, char t1, char t2);
=======


		vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects);
		void printIntMatrix(vector<vector<int>> a);
		int** ProjectToSectionPercentages(vector<vector<Student>> studentList, vector <Project> projectList, int numProjects, int NumOfClassSections);

>>>>>>> p35/dev
};

} /* namespace std */

#endif /* SRC_MAIN_UTILITY_H_ */
