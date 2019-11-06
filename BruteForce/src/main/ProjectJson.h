/*
 * ProjectJson.h
 *
 *  Created on: Oct 29, 2019
 *      Author: myles
 */

#ifndef BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_
#define BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_

#include "Project.h"

#include <string>
#include <array>

using namespace std;

class ProjectJson {
	public:
		int numProjects;
		vector <Project> allProjects;
		ProjectJson();
		virtual ~ProjectJson();
		int getSizeOfJson(string filename);
		Project getProjectJsonObject(string filename, int i);
		void ProjectWriter(string filename);
		void ProjectReaderVector(string filename);
};

#endif /* BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_ */
