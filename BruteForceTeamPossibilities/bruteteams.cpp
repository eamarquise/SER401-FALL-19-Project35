/*
 * bruteteams.cpp
 *
 *  Created on: Oct. 14, 2019
 *      Author: mcilibra
 *
 *      edited by: mcolina
 *      On: Oct. 17 2019.
 *
 */


#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "Skills.h"
#include "Affinity.h"
#include "PreferredMeetingTimes.h"
#include "Student.h"
#include "Project.h"
#include "Team.h"
#include <math.h>

using namespace std;

// GLOBAL VARIABLES
// Important Numbers
int numStudents = 15;
int numProjects = 3;
int numSkills = 7;
int teamSize = 5;
int possibilityCount = 0;
int teamIDincrementor = 0;

///global list of students
vector <Student> allStudents;

int roll(int min, int max){
	int value = rand() % (max-min +1) + min;
	return value;
}

class StudentList {
	public:
		vector<Student> allStudentList;

};


class ProjectList {
	public:
		vector<Project> allProjectList;
};




class TeamList {
	public:
	vector<Team> allTeams;
};


// A function to print all combination of a given length from the given array.
void getCombinations(int a[], int sizeofteam, int startIndex, int currentTeamSize, bool assignedStudents[], int totalNumStudents, Project& p)
{

	Team tempTeam(teamIDincrementor, p.pId);
	tempTeam.studentIDs.clear();
	// Return if the currLen is more than the required length.
	if(currentTeamSize > sizeofteam)
	return;
	// If currLen is equal to required length then print the sequence.
	else if (currentTeamSize == sizeofteam)
	{
		cout<<"\t";
		for (int i = 0; i < totalNumStudents; i++)
		{
			if (assignedStudents[i] == true)
			{
				int x= allStudents[i].sId;
               tempTeam.studentIDs.push_back(x);
				//cout<<a[i]<<" ";
			}
		}
		possibilityCount++;

		//cout<<endl;
		int score = 0;
		for (int i = 0; i < tempTeam.studentIDs.size(); i++){

			score += allStudents[tempTeam.studentIDs[i]].skillScores[p.pId];

				}

		tempTeam.teamScore = score;

		tempTeam.teamID = teamIDincrementor;
		tempTeam.projectID = p.pId;
        p.teams.push_back(tempTeam);
        teamIDincrementor++;

		return;
	}
	// If startIndex equals to totalNumStudents then return. No elements left.
	if (startIndex == totalNumStudents)
	{
		teamIDincrementor=0;


		return;
	}

	// If we select the student, put true into assignedStudents, increment our currentTeamSize and startIndex.
	assignedStudents[startIndex] = true;
	getCombinations(a, sizeofteam, startIndex + 1, currentTeamSize + 1, assignedStudents, totalNumStudents, p);
	// If we dont select the student, put false in the assignedStudents and increment our startIndex.
	assignedStudents[startIndex] = false;
	getCombinations(a, sizeofteam, startIndex + 1, currentTeamSize, assignedStudents, totalNumStudents, p);
}






int main()
{

		int numMeetingTimesAvailable = 6;
		int numOfMeetingTimesToSelect = 3;
		srand(time(0));

		StudentList studentList; // using randomly generated students
		ProjectList projectList; // using randomly generated projects

		// Create randomly generated Students and put them in StudentList2
		for (int i = 0; i < numStudents ; i++){
			string studentName = "st" + to_string(i);
			int sID = i;
			Skills tempSkills;
			for (int j = 0 ; j < numSkills; j++){
				int skillScore = roll(0, 4);
				tempSkills.skillScoreArray.push_back(skillScore);
			}
			PreferredMeetingTimes times;
			bool uniquetimes = false;
			do {
				for (int i = 0 ; i < numOfMeetingTimesToSelect ; i++){
					int time = roll(0, (numMeetingTimesAvailable - 1));
					times.meetingTimes.push_back(time);
				}
				if (times.meetingTimes.at(0) == times.meetingTimes.at(1)
						|| times.meetingTimes.at(0) == times.meetingTimes.at(2)
						|| times.meetingTimes.at(1) == times.meetingTimes.at(2)) {
					times.meetingTimes.clear();
					continue;
				} else {
					uniquetimes = true;
				}
			} while (uniquetimes == false);
			bool online = (bool)roll(0,1);
					Affinity affinity;
					int chanceForPositiveAffinity = roll(1,100);
					int chanceForNegativeAffinity = roll(1,100);
					int chanceForPreferredStudent = roll(1,20);
					int chanceForAvoidedStudent = roll(1,20);
					if (chanceForPreferredStudent >= chanceForPositiveAffinity){
						int numPreferredStudents = roll(1,3);
						for (int i = 0; i < numPreferredStudents; i++){
							int preferredStudent = roll(0, (numStudents-1));
							if (preferredStudent == i){
								continue;
							}
							string preferredStudentName = "st" + to_string(preferredStudent);
							affinity.preferredStudents.push_back(preferredStudentName);
						}
					}
					if (chanceForAvoidedStudent >= chanceForNegativeAffinity){
						int numAvoidedStudents = roll(1,3);
						for (int i = 0; i < numAvoidedStudents; i++){
							int avoidedStudent = roll(0, (numStudents-1));
							if (avoidedStudent == i){
								continue;
							}
							string avoidedStudentName = "st" + to_string(avoidedStudent);
							if (find(affinity.preferredStudents.begin(), affinity.preferredStudents.end(), avoidedStudentName) != affinity.preferredStudents.end()){
								continue;
							} else {
								affinity.avoidedStudents.push_back(avoidedStudentName);
							}
						}
					}
					vector <int> skillscores;
					for (int i=0; i < numProjects; i++){

						int x = roll(0,35);
						skillscores.push_back(x);

					}


					Student tempStudent(studentName, sID, tempSkills, times, affinity, online, skillscores);
					studentList.allStudentList.push_back(tempStudent);
				}


	// Create randomly generated Projects and put them in ProjectList2
		for (int i = 0; i < numProjects ; i++){
			int pId = i;
			string projectName = "p" + to_string(i);
			Skills tempSkills;
			for (int j = 0 ; j < numSkills; j++){
				int skillScore = roll(0, 4);
				tempSkills.skillScoreArray.push_back(skillScore);
			}
			bool online = (bool)roll(0,1);
			Project tempProject(projectName, pId, tempSkills, online);
			projectList.allProjectList.push_back(tempProject);
		}


		allStudents=studentList.allStudentList;


	bool assignedStudents[numStudents];
	int students[numStudents];
	for (int i = 0; i < numStudents; i++){
		assignedStudents[i]= false;
		students[i] = i;
	}

    for (int i=0; i< numProjects; i++){

	getCombinations(students, teamSize, 0, 0, assignedStudents, numStudents, projectList.allProjectList[i]);

    }

	cout << endl << "possiblities: " << possibilityCount/numProjects;
	cout << endl << "working ";

	//Prints all teams and team scores for a given project.
	cout << endl << "Project #2: all Team combinations and Team scores.";
	for (int i=0; i< projectList.allProjectList[2].teams.size(); i++){
           cout << "Team #" + to_string(projectList.allProjectList[2].teams[i].teamID) + " ";
		for (int j=0; j<5; j++){
			cout <<  to_string(projectList.allProjectList[2].teams[i].studentIDs[j])+ " ";

		}
			cout << " Score: " + to_string(projectList.allProjectList[2].teams[i].teamScore) << endl;
	}



	return 0;
}
