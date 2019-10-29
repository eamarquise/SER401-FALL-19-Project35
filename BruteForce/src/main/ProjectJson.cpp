/*
 * ProjectJson.cpp
 *
 *  Created on: Oct 29, 2019
 *      Author: myles
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

ProjectJson::ProjectJson() {
	// TODO Auto-generated constructor stub

}

ProjectJson::~ProjectJson() {
	// TODO Auto-generated destructor stub
}

void ProjectJson::ProjectWriter(string filename){

}

void ProjectJson::ProjectReader(string filename){

	//read file named profile.json, then parse it as json, then store that parse into obj
		ifstream ifs(filename);
		Json::Reader reader;
		Json::Value obj;
		reader.parse(ifs, obj);


		//all projects
		vector<Project> allProjects;


		cout <<endl;
			cout<<"STUDENT JSON FILE READER TEST"<<endl;
		//get the size of the "projects" array in the json file, then store that into numberOfProjects
		const int numberOfProjects = obj["projects"].size();
		cout << "number of Projects: " << numberOfProjects << endl;

		int skills[7];
		int numberOfSkills = 0;
		int ProjectID;
		int Priority = 0;
		char Type;

//Json File Reader Test
//*********************************************
		// for each project in the json file, store the information into a Project object, then push that object to vector<Project> projects
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
//End - Json File Reader Test

}

