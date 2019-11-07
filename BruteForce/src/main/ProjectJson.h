/*
 * ProjectJson.h
 *
 *  Created on: Oct 29, 2019
 *      Author: myles
 */

#ifndef PROJECTJSON_H_
#define PROJECTJSON_H_

#include "Project.h"

#include <array>
#include <vector>
#include <string>

using namespace std;

class ProjectJson {
	public:
		int numProjects;
		vector<Project> allProjects;
		ProjectJson();
		~ProjectJson();
		Project getProjectJsonObject(string filename, int i);
		void ProjectWriter(string filename);
		void ProjectReaderVector(string filename);
};

#endif /* BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_ */
