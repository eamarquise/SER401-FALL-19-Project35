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

#include "ProjectJson.h"
#include "Project.h"
#include "json/json.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <array>

using namespace std;

ProjectJson::ProjectJson() {
	// TODO Auto-generated constructor stub
}

ProjectJson::~ProjectJson() {
	// TODO Auto-generated destructor stub
}

void ProjectJson::ProjectWriter(string filename){
	//to be implemented in a later sprint.
}

// Returns a pointer to Project struct
Project ProjectJson::getProjectJsonObject(string filename, int i){

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

void ProjectJson::ProjectReaderVector(string filename){
	//read file named profile.json, then parse it as json, then store that parse into obj
		ifstream ifs(filename);
		Json::Reader reader;
		Json::Value obj;
		reader.parse(ifs, obj);

		//get the size of the "projects" array in the json file, then store that into numberOfProjects
		const int numberOfProjects = obj["projects"].size();

		int numberOfSkills = 0;
		int skills[7];
		int ProjectID;
		int Priority = 0;
		char Type;

		// for each project in the json file, store the information into a Project object,
		//then push that object to vector<Project> allProjects
		for(int i = 0; i < numberOfProjects; i++) {

			// read in the ProjectID
			ProjectID = (char)obj["projects"].get((int)i, "")["ProjectID"].asInt();

			// read in the priority
			Priority = (char)obj["projects"].get((int)i, "")["Priority"].asInt();

			//read in the skills
			numberOfSkills = obj["projects"].get((int)i, "")["Skills"].size();
						for(int j = 0; j < numberOfSkills; j++) {
							skills[j] = (obj["projects"].get((int)i, "")["Skills"][j].asInt());
						}

			// read in the type
            string temp;
			temp = obj["projects"].get((int)i, "")["Type"].asString();
			Type = temp[0];

			//create the project object
		    Project p( ProjectID, Type, Priority, skills);
			allProjects.push_back(p);
		}
//Json File Reader Test
//*********************************************
		/*
		cout <<endl;
	    cout <<"PROJECT JSON FILE READER TEST"<<endl;
	    cout <<endl;
	    cout << "Number of Projects: " + to_string(allProjects.size())<<endl;
	    cout <<endl;
		// for each Project object, print its information to ensure success
		    for(unsigned int i = 0; i < allProjects.size(); i++) {
			cout << "Project ";
			cout << allProjects.at(i).ProjectID<< endl;
			cout << "Skills: ";
			for (unsigned int j = 0; j < 7; j++) {
				cout << to_string(allProjects.at(i).Skills[j]);
				cout << " ";
			}
			cout << endl;
			cout << "Priority: ";
			cout << allProjects.at(i).Priority << endl;
			cout << "Type:  " ;
		    cout.put(allProjects.at(i).Type);
			cout << endl;
			cout << endl;
		}
//*********************************************
//End - Json File Reader Test*/
}

