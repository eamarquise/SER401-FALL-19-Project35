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
#include <array>
#include <chrono>
#include <algorithm>
#include <fstream>
#include "json/json.h"
using namespace std;
using namespace std::chrono;

StudentsToProjects::StudentsToProjects() {

}

void StudentsToProjects::StudentsToProjectsAssignment(vector <Student> StudentList, vector <Project> ProjectList) {

	auto start = high_resolution_clock::now();
	srand(time(NULL));

	int numProjects = ProjectList.size();
	int numStudents = StudentList.size();
	int numSkills = 7;
	int teamSize = 5;

	struct Team {

				vector <Student> team;
				int TeamScore;
			};

    struct ProjectSet {

				vector <Team> teams;
				int ProjectSetScore;
			};

	Team currentTeam;
	ProjectSet currentSet, bestSet, bestSetWithDuplicates;

   //used to store the top 10 teams for every project.
	Team temp;

	 vector <Team> currentTopTeams;
	 for(int j = 0; j < 10; j++) {
		 currentTopTeams.push_back(temp);
	 }


	//Team currentTopTeams[10];
	vector<vector<Team>> topTeams;

    int top1 = 0;
    int top2 = 0;
    int top3 = 0;
    int top4 = 0;
    int top5 = 0;
    int top6 = 0;
    int top7 = 0;
    int top8 = 0;
    int top9 = 0;
    int top10 = 0;

	//calculate each team combination skillscore for each project
	int teamskillscore = 0;

	cout << "STUDENTS TO PROJECTS ASSIGNMENT RUNNING..." << endl;
	for(int i = 0; i < numProjects; i++) {

		//new combination process
		int studentIndexes[teamSize];
		for(int i = 0; i < teamSize; i++) {
			studentIndexes[i] = i+1;
		}
		int indexToIncrement = teamSize - 1;
		bool permuting = true;
		numStudents = 60;

		while(permuting) {
			for(int j = 0; j < teamSize; j++) {
				currentTeam.team.push_back(StudentList[studentIndexes[j] - 1]);
				for(int k = 0; k < numSkills; k++) {
					teamskillscore += StudentList[studentIndexes[j] - 1].Skills[k] * ProjectList[i].Skills[k];
				}
			}
			for(unsigned int j = 0; j < currentTeam.team.size(); j++) {
				//cout << currentTeam.team[j].StudentID << " ";
			}

			currentTeam.TeamScore = teamskillscore;

			if (currentTeam.TeamScore >= top1 ){
				top1 = currentTeam.TeamScore;
				currentTopTeams[0] = currentTeam;
			}else if (currentTeam.TeamScore >= top2 ){
				top2 = currentTeam.TeamScore;
				currentTopTeams[1] = currentTeam;
			}else if (currentTeam.TeamScore >= top3 ){
				top3 = currentTeam.TeamScore;
				currentTopTeams[2] = currentTeam;
			}else if (currentTeam.TeamScore >= top4 ){
				top4 = currentTeam.TeamScore;
				currentTopTeams[3] = currentTeam;
			}else if (currentTeam.TeamScore >= top5 ){
				top5 = currentTeam.TeamScore;
				currentTopTeams[4] = currentTeam;
			}else if (currentTeam.TeamScore >= top6 ){
				top6 = currentTeam.TeamScore;
				currentTopTeams[5] = currentTeam;
			}else if (currentTeam.TeamScore >= top7 ){
				top7 = currentTeam.TeamScore;
				currentTopTeams[6] = currentTeam;
			}else if (currentTeam.TeamScore >= top8 ){
				top8 = currentTeam.TeamScore;
				currentTopTeams[7] = currentTeam;
			}else if (currentTeam.TeamScore >= top9 ){
				top9 = currentTeam.TeamScore;
				currentTopTeams[8] = currentTeam;
			}else if (currentTeam.TeamScore >= top10 ){
				top10 = currentTeam.TeamScore;
				currentTopTeams[9] = currentTeam;}

			teamskillscore = 0;
			currentTeam.team.clear();
			currentTeam.TeamScore = 0;


			studentIndexes[indexToIncrement]++;
			while(studentIndexes[indexToIncrement] == numStudents - ((teamSize - 1) - (indexToIncrement + 1))){
				indexToIncrement--;
				if(indexToIncrement < 0) {
					permuting = false;
					break;
				} else {
					studentIndexes[indexToIncrement]++;
				}
			}
			while(indexToIncrement < teamSize - 1 && permuting) {
				indexToIncrement++;
				studentIndexes[indexToIncrement] = studentIndexes[indexToIncrement - 1] + 1;
			}
		}

		//old combination calculation process
		/*string bitmask(teamSize,1);
		bitmask.resize(numStudents, 0);
		while(std::prev_permutation(bitmask.begin(), bitmask.end())) {
			for (int j = 0; j < numStudents; ++j) {
				if(bitmask[j]) {
					currentTeam.team.push_back(StudentList[j]);
					for(int k = 0; k < numSkills; k++) {

						teamskillscore += StudentList[j].Skills[k] * ProjectList[i].Skills[k];
					}
				}
			} //end j loop
			for(unsigned int j = 0; j < currentTeam.team.size(); j++) {
				//cout << currentTeam.team[j].StudentID << " ";
			}

			//call to 3 team score functions
			//TeamScore = func1() + func2() + func3()

			currentTeam.TeamScore = teamskillscore;
			//cout << "TeamSkillScore for project " << i+1 << ": " << currentTeam.TeamScore<<endl;



			if (currentTeam.TeamScore >= top1 ){
				top1 = currentTeam.TeamScore;
				currentTopTeams[0] = currentTeam;
			}else if (currentTeam.TeamScore >= top2 ){
				top2 = currentTeam.TeamScore;
				currentTopTeams[1] = currentTeam;
			}else if (currentTeam.TeamScore >= top3 ){
				top3 = currentTeam.TeamScore;
				currentTopTeams[2] = currentTeam;
			}else if (currentTeam.TeamScore >= top4 ){
				top4 = currentTeam.TeamScore;
				currentTopTeams[3] = currentTeam;
			}else if (currentTeam.TeamScore >= top5 ){
				top5 = currentTeam.TeamScore;
				currentTopTeams[4] = currentTeam;
			}else if (currentTeam.TeamScore >= top6 ){
				top6 = currentTeam.TeamScore;
				currentTopTeams[5] = currentTeam;
			}else if (currentTeam.TeamScore >= top7 ){
				top7 = currentTeam.TeamScore;
				currentTopTeams[6] = currentTeam;
			}else if (currentTeam.TeamScore >= top8 ){
				top8 = currentTeam.TeamScore;
				currentTopTeams[7] = currentTeam;
			}else if (currentTeam.TeamScore >= top9 ){
				top9 = currentTeam.TeamScore;
				currentTopTeams[8] = currentTeam;
			}else if (currentTeam.TeamScore >= top10 ){
				top10 = currentTeam.TeamScore;
				currentTopTeams[9] = currentTeam;}

			teamskillscore = 0;
			currentTeam.team.clear();
			currentTeam.TeamScore = 0;

		} // end while loop*/

		topTeams.push_back(currentTopTeams);
            top1 = 0;
            top2 = 0;
            top3 = 0;
            top4 = 0;
            top5 = 0;
            top6 = 0;
            top7 = 0;
            top8 = 0;
            top9 = 0;
            top10 = 0;

		cout << "Project # " + to_string(ProjectList[i].ProjectID) + "  team combinations complete. " << endl;


	} // end i loop



	// Do Project Set combinations here

	// End Project Set combinations


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "time in milliseconds: ";
	cout << duration.count() << endl;
	//cout << "Number of iterations: ";
	cout << endl;
	cout<< "Top 10 teams for each project"<<endl;
	cout << "Size of top teams: " + to_string(topTeams.size())<<endl;

	for(int i = 0; i < numProjects; i++) {

		cout<< "Projects #" + to_string(ProjectList[i].ProjectID) + " Student Teams:"<<endl;
		cout << "Size of top teams in top teams: " + to_string(topTeams[i].size())<<endl;
		for(int j = 0; j < topTeams[i].size(); j++) {

		  cout << "Team #" + to_string(j) + " ";
		  for(int k = 0; k < teamSize; k++) {

			 cout<< to_string(topTeams[i][j].team[k].StudentID) + " ";

		  }
		  cout << endl;
		  cout<< "TeamScore: " + to_string(topTeams[i][j].TeamScore)<<endl;
		}
		 cout << endl;
	}


}
//Task#120
int StudentsToProjects::AvailabilityTeamScore(vector <Student> team){
	//to-do
	return 0;

}

//Task#118
int StudentsToProjects::SkillCompareTeamScore(vector <Student> team){
	//to-do
	return 0;

}

//Task#120
int StudentsToProjects::ProjectCompareTeamScore(vector <Student> team, Project project){
	//to-do
	return 0;

}


StudentsToProjects::~StudentsToProjects() {
	// TODO Auto-generated destructor stub
}

