/*
 * StudentsToProjects.h
 *
 *  Created on: Oct 30, 2019
 *      Author: sean
 */

#ifndef STUDENTSTOPROJECTS_H_
#define STUDENTSTOPROJECTS_H_

#include<vector>

#include "Student.h"
#include "Project.h"
#include "ClassSection.h"

using namespace std;

class StudentsToProjects {
	public:
		StudentsToProjects();
		~StudentsToProjects();

		//void StudentsToProjectsAssignment(vector <Student> studentlist,
		//	vector <Project> projectlist);
		void ArrayStudentsToProjectsAssignment(Student studentPool[],
				Project projectPool[], int numStudents, int numProjects, int numSkills,
				const int teamSize, int numTopTeams);

		bool negativeAffinityCheck(Student team[5]);

		int AvailabilityTeamScore(Student team[5]);
		int SkillCompareTeamScore(Student team[5]);
		int ProjectCompareTeamScore(Student team[5], Project project);
		int StudentToStudentSkill(Student s1, Student s2);      //helper function for SkillCompareTeamScore
		int StudentToStudentAvailibility(Student s1, Student s2);   //helper function for AvailabilityTeamScore
		constexpr int toConstInt(int constInt);
};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_ */
