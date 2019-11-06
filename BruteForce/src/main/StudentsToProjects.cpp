/*
 * StudentsToProjects.cpp
 *
 *  Created on: Oct 30, 2019
 *      Author: sean
 */

#include "StudentsToProjects.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <fstream>
#include "json/json.h"
using namespace std;
using namespace std::chrono;



StudentsToProjects::StudentsToProjects() {
	auto start = high_resolution_clock::now();
	srand(time(NULL));
	struct Student {

		int studentID;
		int classID;
		int projectID;

		int skills[7];
		int studentAffinity[128][2];

		int availability[4];
	};

	struct Project {

		int projectID;
		int sponsorID;
		int classID;

		char type;
		int priority;

		int skills[7];
	};
	Project p;

	p.sponsorID = 4;
	p.classID = 1;
	p.type = 1;
	p.priority = 1;



	vector<Project> projects;
	vector<Student> students;
	vector<Student> team;

	int numProjects = 1;
	int numSkills = 7;
	int numStudents = 50;
	int teamSize = 5;


	/*//create numProjects projects
	for(int i = 0; i < numProjects; i++) {
		for(int j = 0; j < numSkills; j++) {
			p.skills[j] = (rand() % 2);
		}
		p.projectID = i+1;
		projects.push_back(p);
		Project p;

	}*/

	ifstream ifs("./BruteForce/SampleJsonFiles/60Students.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

    const Json::Value& numberOfStudents = obj["students"];
    numStudents = numberOfStudents.size();


    //for loop that iterates of the number of students in the Json file
    //and stores them as Student objects vector <Student> allStudents.
	for(int i = 0; i < numberOfStudents.size(); i++) {
		Student s;


		//reading in Student Skills
		numSkills = obj["students"].get((int)i, "")["Skills"].size();
		for(int j = 0; j < numSkills; j++) {
			s.skills[j] = (obj["students"].get((int)i, "")["Skills"][j].asInt());
		}

		//Creating the student, and adding the student to the student list
		s.studentID = obj["students"].get((int)i, "")["StudentID"].asInt();
		students.push_back(s);

	}

	ifs.close();
	ifstream ifs2("./BruteForce/SampleJsonFiles/20Projects.json");
	Json::Reader reader2;
	Json::Value obj2;
	reader.parse(ifs2, obj2);
    const Json::Value& numberOfProjects = obj2["projects"];

    numProjects = numberOfProjects.size();


    //for loop that iterates of the number of students in the Json file
    //and stores them as Student objects vector <Student> allStudents.
	for(int i = 0; i < numberOfProjects.size(); i++) {
		Project p;


		//reading in Student Skills
		numSkills = obj2["projects"].get((int)i, "")["Skills"].size();
		for(int j = 0; j < numSkills; j++) {
			p.skills[j] = (obj2["projects"].get((int)i, "")["Skills"][j].asInt());
		}

		//Creating the student, and adding the student to the student list
		p.projectID = obj2["projects"].get((int)i, "")["ProjectID"].asInt();
		projects.push_back(p);

	}
	ifs2.close();
	//print out to ensure correct
	cout << "project skills" << endl;
	for(int i = 0; i < numProjects; i++) {
		cout << to_string(projects.at(i).projectID) + ": ";
		for(int j = 0; j < numSkills; j++) {
			cout << to_string(projects.at(i).skills[j]) + " ";
		}
		cout << endl;
	}

	cout << endl;

	//print students to ensure
	cout << "student skills" << endl;
	cout << to_string(numStudents);
	for(int i = 0; i < numStudents; i++) {
		cout << to_string(students.at(i).studentID) + ": ";
		for(int j = 0; j < numSkills; j++) {
			cout << to_string(students.at(i).skills[j]) + " ";
		}
		cout << endl;
	}

	cout << endl;

	//calculate each student's skillscore for each project
	int skillscore = 0;
	for(int i = 0; i < numProjects; i++) {
		for(int j = 0; j < numStudents; j++) {
			cout << "Student" + to_string(j+1) + " skillscore for Project" + to_string(i + 1) + ": ";
			for(int k = 0; k < numSkills; k++) {
				skillscore += students.at(j).skills[k] * projects.at(i).skills[k];
			}// end k

			cout << to_string(skillscore) << endl;
			skillscore = 0;
		}// end j
	}// end i

	cout << endl;


	//calculate each team combination skillscore for each project
	int teamskillscore = 0;

	for(int i = 0; i < numProjects; i++) {
		for(int j = 0; j < teamSize; j++) {
			team.push_back(students.at(j));
			for(int k = 0; k < numSkills; k++) {
				teamskillscore += students.at(j).skills[k] * projects.at(i).skills[k];
			}

		}
		for(unsigned int j = 0; j < team.size(); j++) {
			cout << team.at(j).studentID << " ";
		}
		cout << "TeamSkillScore for project " << i+1 << ": " << teamskillscore;
		teamskillscore = 0;
		team.clear();
		cout << endl;

		string bitmask(teamSize,1);
		bitmask.resize(numStudents, 0);
		while(std::prev_permutation(bitmask.begin(), bitmask.end())) {
			for (int j = 0; j < numStudents; ++j) {
				if(bitmask[j]) {
					team.push_back(students.at(j));
					for(int k = 0; k < numSkills; k++) {
						teamskillscore += students.at(j).skills[k] * projects.at(i).skills[k];
					}
				}
			}
			for(unsigned int j = 0; j < team.size(); j++) {
				cout << team.at(j).studentID << " ";
			}
			cout << "TeamSkillScore for project " << i+1 << ": " << teamskillscore;
			teamskillscore = 0;
			team.clear();
			cout << endl;
		} // end j loop
		cout << endl;
	} // end i loop

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "time in milliseconds: ";
	cout << duration.count() << endl;
	cout << "Number of iterations: ";

}

StudentsToProjects::~StudentsToProjects() {
	// TODO Auto-generated destructor stub
}

