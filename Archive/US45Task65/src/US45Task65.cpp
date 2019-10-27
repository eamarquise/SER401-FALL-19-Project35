//============================================================================
// Name        : US45Task65.cpp
// Author      : Sean Rogers
// Description : Algorithm for calculating a student's skill score for a project
//============================================================================

#include <iostream>
#include <vector>
#include "Project.h"
#include "Skills.h"
#include "Student.h"
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

int main() {
	auto start = high_resolution_clock::now();
	PreferredMeetingTimes pmt;
	Affinity affinity;
	Skills skills;
	srand(time(NULL));
	Project project = Project("project", skills, 1);
	Student student = Student("Student", skills, pmt, affinity, 0);
	vector<Project> projects;
	vector<Student> students;
	vector<Student> team;

	int numProjects = 2;
	int numSkills = 6;
	int numStudents = 25;
	int teamSize = 5;



	//create numProjects projects
	for(int i = 0; i < numProjects; i++) {
		for(int j = 0; j < numSkills; j++) {
			skills.skillScoreArray.push_back(rand() % 2);
		}
		project = Project("p" + to_string(i + 1), skills, 0);
		projects.push_back(project);
		skills.skillScoreArray.clear();
	}


	//create numStudents students
	for(int i = 0; i < numStudents; i++) {
		for(int j = 0; j < numSkills; j++) {
			skills.skillScoreArray.push_back(rand() % 5);
		}
		student = Student("Student" + to_string(i+1), skills, pmt, affinity, 0);
		students.push_back(student);
		skills.skillScoreArray.clear();
	}

	//print out to ensure correct
	cout << "project skills" << endl;
	for(int i = 0; i < numProjects; i++) {
		cout << projects.at(i).name + ": ";
		for(int j = 0; j < numSkills; j++) {
			cout << to_string(projects.at(i).projectSkills.skillScoreArray.at(j)) + " ";
		}
		cout << endl;
	}

	cout << endl;

	//print students to ensure
	cout << "student skills" << endl;
	for(int i = 0; i < numStudents; i++) {
		cout << students.at(i).name + ": ";
		for(int j = 0; j < numSkills; j++) {
			cout << to_string(students.at(i).studentSkills.skillScoreArray.at(j)) + " ";
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
				skillscore += students.at(j).studentSkills.skillScoreArray.at(k) * projects.at(i).projectSkills.skillScoreArray.at(k);
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
				teamskillscore += students.at(j).studentSkills.skillScoreArray.at(k) * projects.at(i).projectSkills.skillScoreArray.at(k);
			}

		}
		for(unsigned int j = 0; j < team.size(); j++) {
			cout << team.at(j).name << " ";
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
						teamskillscore += students.at(j).studentSkills.skillScoreArray.at(k) * projects.at(i).projectSkills.skillScoreArray.at(k);
					}
				}
			}
			for(unsigned int j = 0; j < team.size(); j++) {
				cout << team.at(j).name << " ";
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
	return 0;
}
