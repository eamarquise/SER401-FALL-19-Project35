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
#include <chrono>

#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "Skills.h"
#include "Affinity.h"
#include "PreferredMeetingTimes.h"
#include "Student.h"
#include "Project.h"
#include "ProjectGroup.h"
#include "Team.h"
#include <math.h>
#include <bits/stdc++.h>

using namespace std;
//using namespace std::chrono;

// GLOBAL VARIABLES
// Important Numbers
int numStudents = 6;
int numProjects = 2;
int numSkills = 7;
int teamSize = 5;
int possibilityCount = 0;
int teamIDincrementor = 0;

///global list of students
vector <Student> allStudents;

///global list of projects
vector <Project> allProjects;

//global list of project groups
vector <ProjectGroup> allProjectGroups;

vector<vector<Team> > allProjectsallTeams(numProjects, vector<Team>());

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
void getCombinations(int a[], int sizeofteam, int startIndex, int currentTeamSize, bool assignedStudents[], int totalNumStudents, Project& p){
	Team tempTeam(teamIDincrementor, p.pId);
	tempTeam.studentIDs.clear();
	// Return if the currentTeamSize is more than the required length.
	if(currentTeamSize > sizeofteam){
		return;
	}
	// If currentTeamSize is equal to required length then print the sequence.
	else if (currentTeamSize == sizeofteam) {
		cout<<"\t";
		for (int i = 0; i < totalNumStudents; i++) {
			if (assignedStudents[i] == true) {
				tempTeam.studentIDs.push_back(allStudents[i].sId);
				cout << allStudents[i].sId << " ";
				//cout<<a[i]<<" ";
			}
		}
		cout << endl;
		possibilityCount++;
		int score = 0;
		for (unsigned int i = 0; i < tempTeam.studentIDs.size(); i++){
			score += allStudents[tempTeam.studentIDs[i]].skillScores[p.pId];
		}
		tempTeam.teamScore = score;
		tempTeam.teamID = teamIDincrementor;
		tempTeam.projectID = p.pId;
        p.teams.push_back(tempTeam);
        allProjectsallTeams[p.pId].push_back(tempTeam);
		teamIDincrementor++;
		return;
	}
	// If startIndex equals to totalNumStudents then return. No elements left.
	if (startIndex == totalNumStudents){
		//teamIDincrementor=0;
		return;
	}
	// If we select the student, put true into assignedStudents, increment our currentTeamSize and startIndex.
	assignedStudents[startIndex] = true;
	getCombinations(a, sizeofteam, startIndex + 1, currentTeamSize + 1, assignedStudents, totalNumStudents, p);
	// If we dont select the student, put false in the assignedStudents and increment our startIndex.
	assignedStudents[startIndex] = false;
	getCombinations(a, sizeofteam, startIndex + 1, currentTeamSize, assignedStudents, totalNumStudents, p);
}

// function to print combinations that contain
// one element from each of the given arrays
void projectCombos(vector<vector<Team>>& arr) {
    // number of arrays
    int n = arr.size();

    // to keep track of next element in each of
    // the n arrays
    int* indices = new int[n];

    // initialize with first element's index
    for (int i = 0; i < n; i++)
        indices[i] = 0;

    while (1) {
        // print current combination
        for (int i = 0; i < n; i++){
        	//arr[i][indices[i]];
            cout << "projectID: "<< arr[i][indices[i]].projectID<< " Score: "<<to_string(arr[i][indices[i]].teamScore) << " ";
        }
        cout << endl;
        // find the rightmost array that has more
        // elements left after the current element
        // in that array
        int next = n - 1;
        while (next >= 0 &&
              (indices[next] + 1 >= (signed)arr[next].size()))
            next--;

        // no such array is found so no more
        // combinations left
        if (next < 0)
            return;

        // if found move to next element in that
        // array
        indices[next]++;

        // for all arrays to the right of this
        // array current index again points to
        // first element
        for (int i = next + 1; i < n; i++)
            indices[i] = 0;
    }
}



int main()
{
	clock_t start, end;
	start = clock();
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
	}// End create Students


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
	} // End create projects

	allStudents=studentList.allStudentList;


	cout << endl << "working 1 " << endl;
	bool assignedStudents[numStudents];
	int students[numStudents];
	for (int i = 0; i < numStudents; i++){
		assignedStudents[i]= false;
		students[i] = i;
	}
    for (int i=0; i< numProjects; i++){
    	getCombinations(students, teamSize, 0, 0, assignedStudents, numStudents, projectList.allProjectList[i]);
    }
    // print teams, project ID, teamScore and students in team
    cout << endl;
    for (int i = 0; i < (signed)allProjectsallTeams.size(); i++){
    	for (int j = 0 ; j < (signed)allProjectsallTeams.at(i).size(); j++){
    		cout << "TeamID: " << allProjectsallTeams.at(i).at(j).teamID
    				<< "\tProjectID: " << allProjectsallTeams.at(i).at(j).projectID
    				<< "\tTeamScore: " << allProjectsallTeams.at(i).at(j).teamScore
					<< "\tStudents: ";
    		for (int k = 0; k < (signed)allProjectsallTeams.at(i).at(j).studentIDs.size(); k++){
    			cout << allProjectsallTeams.at(i).at(j).studentIDs.at(k) << ", ";
    		}
    		cout << endl;
    	}
    }
    //project groupings
//    cout << endl << "working 2 " << endl;
//    allProjects = projectList.allProjectList;
//    projectCombos(allProjectsallTeams);

    //vector<vector<Project> > allProjectsallTeams(numProjects, vector<Project>());

/*
    bool assignedTeams[projectList.allProjectList[0].teams.size()];
    	int projects[numProjects];
    	for (int i = 0; i < numProjects; i++){
    		assignedTeams[i]= false;
    		projects[i] = i;
    	}

    getProjectCombos(projects, numProjects, 0, 0, projectList.allProjectList[0].teams.size(), assignedTeams, projectList.allProjectList[0].teams.size());
*/

	//cout << endl << "possiblities: " << possibilityCount/numProjects;
	//cout << endl << "working 3 ";

	/*Prints all teams and team scores for a given project.
	cout << endl << "Project #2: all Team combinations and Team scores." << endl;
	for (int i=0; i< projectList.allProjectList[2].teams.size(); i++){
           cout << "Team # " + to_string(i) + " ";
		for (int j=0; j<5; j++){
			cout <<  to_string(projectList.allProjectList[2].teams[i].studentIDs[j])+ " ";

		}
			cout << " Score: " + to_string(projectList.allProjectList[2].teams[i].teamScore) << endl;
	}*/
	end = clock();


	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	    cout << "Time taken by program is : " << fixed
	         << time_taken << setprecision(5);
	    cout << " sec " << endl;
	return 0;
}
