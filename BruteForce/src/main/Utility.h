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

		int getProjectXskill(Project projectPool[], int i, int k);
		int getSkillXstudent(Student studentPool[], int i, int j);
		long getProjectVsStudentSkill(Project projectPool[], int numProjects,
				Student studentPool[], int numStudents, int numSkills, int projectXstudentScore, int i, int j);
		int getSizeOfJson(string filename, string key);
		void makeProjectJSON(int numProj, int numSkill);

		vector<vector<int>> calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects);
		void printIntMatrix(vector<vector<int>> a);
		int** ProjectToSectionPercentages(vector<vector<Student>> studentList, vector <Project> projectList, int numProjects, int NumOfClassSections);

};

} /* namespace std */

#endif /* SRC_MAIN_UTILITY_H_ */
