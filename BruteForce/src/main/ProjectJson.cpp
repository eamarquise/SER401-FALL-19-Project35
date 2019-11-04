/*
 * ProjectJson.cpp
 *
 *  Created on: Oct 29, 2019
 *      Revised by: Myles Colina
 *
 *      File revised from archive the file: SecondProject.cpp
 *      Author:Sean Rogers
 *
 *      Description:
 *      A class to store all the functions for Project Json data.
 *      Includes reading in Project Json Files.
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

#include "Project.h"
#include "json/json.h"
#include "ProjectJson.h"

#define NUM_PROJECTS 3

ProjectJson::ProjectJson() {
	// TODO Auto-generated constructor stub
}
/*
ProjectJson::ProjectJson(string filename) {
	// TODO Auto-generated constructor stub
	numProjects = getSizeOfJson(filename);
}*/

ProjectJson::~ProjectJson() {
	// TODO Auto-generated destructor stub
}

void ProjectJson::ProjectWriter(string filename){
	//to be implemented in a later sprint.
}

// Returns a pointer to Project struct
Project ProjectJson::ProjectReader(string filename, int i){

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	Project project;

	project.ProjectID = (char)obj["projects"].get((int)i, "")["ProjectID"].asInt();

	string temp;
	temp = obj["projects"].get((int)i, "")["Type"].asString();
	project.Type = temp[0];

	project.Priority = (char)obj["projects"].get((int)i, "")["Priority"].asInt();

	int numSkills = obj["projects"].get((int)i, "")["Skills"].size();

	for (int j = 0; j < numSkills; j++) {
		project.Skills[j] = (obj["projects"].get((int)i, "")["Skills"][j].asInt());
	}

	return project;
}

