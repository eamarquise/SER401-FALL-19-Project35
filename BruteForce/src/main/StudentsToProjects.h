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

namespace std{

class StudentsToProjects {
	public:
		StudentsToProjects();
		~StudentsToProjects();
		void StudentsToProjectsAssignment(vector <Student> studentlist,
			vector <Project> projectlist);
		void arrayStudentsToProjectsAssignment(Project projectPool[],
		        Student studentPool[], ClassSection classSectionPool[], int numProjects,
				int numStudents, int numClassSections,
				int numSkills, int teamSize);

		// 3 functions to evaluate a team's score
		int AvailabilityTeamScore(vector <Student> team);
		int SkillCompareTeamScore(vector <Student> team);
		int ProjectCompareTeamScore(vector <Student> team, Project project);
};
}
#endif /* BRUTEFORCE_SRC_MAIN_STUDENTSTOPROJECTS_H_ */
