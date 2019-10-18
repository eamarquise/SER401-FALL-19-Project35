/*
 * ProjectGroup.h
 *
 *  Created on: Oct 18, 2019
 *      Author: myles
 */

#ifndef PROJECTGROUP_H_
#define PROJECTGROUP_H_


#include <string>
#include <vector>
#include "Skills.h"
#include "Team.h"
#include "Project.h"

using namespace std;
class ProjectGroup {
	public:

		int pgroupId;        //Project id
		int groupScore;
		vector <Project> projects;
		vector <Team> teams;

		//Methods
		ProjectGroup(int x);
		bool operator==(const ProjectGroup &projectToCompare) const;

};


#endif /* PROJECTGROUP_H_ */
