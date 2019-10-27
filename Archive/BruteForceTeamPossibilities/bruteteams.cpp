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
int teamSize = 3;
int numSkills = 7;
long long possibilityCount = 0;
long long teamIDincrementor = 0;
long long groupCounter = 0;

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

///global list of students
vector <Student> allStudents;

///global list of projects
vector <Project> allProjects;

//global list of project groups
vector <ProjectGroup> allProjectGroups;
vector <ProjectGroup> allUniqueProjectGroups;
vector<vector<Team> > allProjectsallTeams(numProjects, vector<Team>());


int roll(int min, int max){
	int value = rand() % (max-min +1) + min;
	return value;
}

bool sortGroupsDescending(const ProjectGroup &a, const ProjectGroup &b){
	return a.groupScore > b.groupScore;
}

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
    long long n = arr.size();

    // to keep track of next element in each of
    // the n arrays
    long long* indices = new long long[n];

    // initialize with first element's index
    for (long long i = 0; i < n; i++)
        indices[i] = 0;

    while (1) {
    	int projectScore = 0;
    	vector<int> teamIDsInProjectGroup;
    	teamIDsInProjectGroup.clear();
        // print current combination
        for (long long i = 0; i < n; i++){
        	cout << "\tPID: " << arr[i][indices[i]].projectID
        			<< "\tTID: " <<  arr[i][indices[i]].teamID
					<< "\tTS: " << arr[i][indices[i]].teamScore
					<< "\t|";
        	projectScore += arr[i][indices[i]].teamScore;
        	teamIDsInProjectGroup.push_back(arr[i][indices[i]].teamID);
        }
        cout << endl;
        ProjectGroup projectGroup(groupCounter);
        projectGroup.groupScore = projectScore / numProjects;
        projectGroup.teamIDsInGroup = teamIDsInProjectGroup;
        allProjectGroups.push_back(projectGroup);
        groupCounter++;

        // find the rightmost array that has more
        // elements left after the current element
        // in that array
        long long next = n - 1;
        while (next >= 0 &&
              (indices[next] + 1 >= arr[next].size()))
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
        for (long long i = next + 1; i < n; i++)
            indices[i] = 0;
    }
}

// The main function that receives a vector of studentID vectors as parameter and
// returns a vector containing intersection of all sets
vector <int> getIntersectionOfStudents(vector < vector <int> > &studentTeams)
{
	vector <int> duplicateStudentsVector; // To store the duplicate student vector
	unsigned smallSetInd = 0; // Initialize index of smallest set
	unsigned minSize = studentTeams[0].size(); // Initialize size of smallest set

	// sort all the sets, and also find the smallest set
	for (unsigned i = 1 ; i < studentTeams.size() ; i++)
	{
		// sort this set
		sort(studentTeams[i].begin(), studentTeams[i].end());

		// update minSize, if needed
		if (minSize > studentTeams[i].size())
		{
			minSize = studentTeams[i].size();
			smallSetInd = i;
		}
	}

	map<int,int> studentMap;

	// Add all the students of smallest vector to a map, if already present,
	// update the frequency
	for (unsigned i = 0; i < studentTeams[smallSetInd].size(); i++)
	{
		if (studentMap.find( studentTeams[smallSetInd][i] ) == studentMap.end())
			studentMap[ studentTeams[smallSetInd][i] ] = 1;
		else
			studentMap[ studentTeams[smallSetInd][i] ]++;
	}

	// iterate through the map students to see if they are present in
	// remaining studentTeams
	map<int,int>::iterator it;
	for (it = studentMap.begin(); it != studentMap.end(); ++it)
	{
		int currentStudentID = it->first;
		int studentIDFrequency = it->second;

		bool bFound = true;

		// Iterate through all studentTeams
		for (unsigned j = 0 ; j < studentTeams.size() ; j++)
		{
			// If this vector is not the smallest vector, then do binary search in it
			if (j != smallSetInd)
			{
				// If the element is found in this vector, then find its frequency
				if (binary_search( studentTeams[j].begin(), studentTeams[j].end(), currentStudentID ))
				{
				int lInd = lower_bound(studentTeams[j].begin(), studentTeams[j].end(), currentStudentID)
															- studentTeams[j].begin();
				int rInd = upper_bound(studentTeams[j].begin(), studentTeams[j].end(), currentStudentID)
															- studentTeams[j].begin();

				// Update the minimum frequency, if needed
				if ((rInd - lInd) < studentIDFrequency)
					studentIDFrequency = rInd - lInd;
				}
				// If the student is not present in any vector, then no need
				// to proceed for this student.
				else
				{
					bFound = false;
					break;
				}
			}
		}

		// If student was found in all vector, then add it to result 'freq' times
		if (bFound)
		{
			for (int k = 0; k < studentIDFrequency; k++)
				duplicateStudentsVector.push_back(currentStudentID);
		}
	}
	return duplicateStudentsVector;
}

// A utility function to print a set of elements
void printset(vector <int> set)
{
	for (unsigned i = 0 ; i < set.size() ; i++)
		cout<<set[i]<<" ";
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

	// Start Calculations
	allStudents=studentList.allStudentList;

	// Display all student team combinations
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
    int combinations = possibilityCount/numProjects;
	cout << endl << "student combination possibilities per project: " << combinations << endl;

    // print teams, project ID, teamScore and students in team
    cout << endl << "working 2 " << endl;
    for (int i = 0; i < (signed)allProjectsallTeams.size(); i++){
    	for (int j = 0 ; j < (signed)allProjectsallTeams.at(i).size(); j++){
    		cout << "teamID: " << allProjectsallTeams.at(i).at(j).teamID
    				<< "\tprojectID: " << allProjectsallTeams.at(i).at(j).projectID
    				<< "\tteamScore: " << allProjectsallTeams.at(i).at(j).teamScore
					<< "\tStudentsIDs: ";
    		for (int k = 0; k < (signed)allProjectsallTeams.at(i).at(j).studentIDs.size(); k++){
    			cout << allProjectsallTeams.at(i).at(j).studentIDs.at(k) << ", ";
    		}
    		cout << endl;
    	}
    }
    //project groupings
    cout << endl << "working 3 " << endl;
    allProjects = projectList.allProjectList;
    projectCombos(allProjectsallTeams);

    // project group scores
    cout << endl << "working 4 " << endl;
    for (unsigned i = 0 ; i < allProjectGroups.size() ; i++){
    	cout << "\tGroupID: "<< allProjectGroups.at(i).pgroupId
    			<< "\t GroupScore: " << allProjectGroups.at(i).groupScore
				<< "\t TeamsInGroup: ";
    	for (unsigned j = 0 ; j < allProjectGroups.at(i).teamIDsInGroup.size() ; j++){
    		cout << allProjectGroups.at(i).teamIDsInGroup.at(j) << ", ";
    	}
    	cout << endl;
    }

    // Sort all the group projects according to group score.
    sort(allProjectGroups.begin(), allProjectGroups.end(), sortGroupsDescending);

    cout << endl << "working 4 sort" << endl;
    for (unsigned i = 0 ; i < allProjectGroups.size() ; i++){
    	cout << "\tGroupID: "<< allProjectGroups.at(i).pgroupId
    			<< "\t GroupScore: " << allProjectGroups.at(i).groupScore
				<< "\t TeamsInGroup: ";
    	for (unsigned j = 0 ; j < allProjectGroups.at(i).teamIDsInGroup.size() ; j++){
    		cout << allProjectGroups.at(i).teamIDsInGroup.at(j) << ", ";
    	}
    	cout << endl;
    }

    cout << endl << "working task 86" << endl;
    // create project groups with unique combinations per project

//    cout << "Group 0 ID: " << allProjectGroups.at(0).pgroupId << endl;
//    cout << "Group 0 Teams: " << allProjectGroups.at(0).teamIDsInGroup.at(0) << " "<< allProjectGroups.at(0).teamIDsInGroup.at(1) <<  endl;
//    cout << "allProjectsallTeams teamID at 1,4: " << allProjectsallTeams.at(1).at(4).teamID;
//    cout << endl;

    int teamIDToFind;
    teamIDToFind = 2;
    vector<vector<int>> studentsInTeamsVector;
    vector<ProjectGroup> uniqueProjectGroups;
    uniqueProjectGroups.clear();
    // iterate through each project group
    for (unsigned projectGroupCounter = 0 ; projectGroupCounter < allProjectGroups.size(); projectGroupCounter++){
    	cout << endl << "ProjectGroup #" << allProjectGroups.at(projectGroupCounter).pgroupId << endl;
    	studentsInTeamsVector.clear();
    	// iterate through each project groups teamIDs
    	for (unsigned projectGroupTeamCounter = 0; projectGroupTeamCounter < allProjectGroups.at(projectGroupCounter).teamIDsInGroup.size(); projectGroupTeamCounter++){
    		cout << "\tTeam #" << allProjectGroups.at(projectGroupCounter).teamIDsInGroup.at(projectGroupTeamCounter) << " Students: ";
    		teamIDToFind = allProjectGroups.at(projectGroupCounter).teamIDsInGroup.at(projectGroupTeamCounter);
			// return studentsID in team #teamIDToFind
			for (unsigned projectCounter = 0; projectCounter < allProjectsallTeams.size() ; projectCounter++){
				for (unsigned teamCounter = 0 ; teamCounter < allProjectsallTeams.at(projectCounter).size() ; teamCounter++){
					if (allProjectsallTeams.at(projectCounter).at(teamCounter).teamID == teamIDToFind){
						for (unsigned studentIDCounter = 0 ; studentIDCounter < allProjectsallTeams.at(projectCounter).at(teamCounter).studentIDs.size(); studentIDCounter++){
							cout << allProjectsallTeams.at(projectCounter).at(teamCounter).studentIDs.at(studentIDCounter) << ", ";
							studentsInTeamsVector.push_back(allProjectsallTeams.at(projectCounter).at(teamCounter).studentIDs);
						}
					}
				}
			} // end return studentsID in team #teamIDToFind
    	} // end iterate through each project groups teamIDs
    	// find intersection in studentsInTeamsVector
    	vector<int> dupStudents = getIntersectionOfStudents(studentsInTeamsVector);
    	cout << endl;
    	if (dupStudents.empty()){
    		cout << "******** Unique Student Group ********";
    		uniqueProjectGroups.push_back(allProjectGroups.at(projectGroupCounter));
    	} else {
        	cout << "\tDuplicate Students: ";
        	printset(dupStudents);
    	}
    } // end iterate through each project group



	cout << endl;
	// Display unique Project Groups
	cout << endl << "Unique Project Groups" << endl;
	cout << "*********************" << endl;
	for (unsigned projectGroupCounter = 0; projectGroupCounter < uniqueProjectGroups.size(); projectGroupCounter++){
		cout << "ProjectGroup #" << uniqueProjectGroups.at(projectGroupCounter).pgroupId
				<< "\tScore: " << uniqueProjectGroups.at(projectGroupCounter).groupScore
				<< "\tTeams: ";
		for (unsigned projectGroupTeamCounter = 0; projectGroupTeamCounter < uniqueProjectGroups.at(projectGroupCounter).teamIDsInGroup.size(); projectGroupTeamCounter++){
			cout << uniqueProjectGroups.at(projectGroupCounter).teamIDsInGroup.at(projectGroupTeamCounter) << ", ";
		}
		cout << endl;
	}



    // End keeping track of time
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	    cout << "Time taken by program is : " << fixed
	         << time_taken << setprecision(5);
	    cout << " sec " << endl;
	return 0;
}
