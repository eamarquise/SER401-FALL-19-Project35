/*
 * StudentsToProjects.cpp
 *
 *  Created on: Oct 30, 2019
 *      Author: sean
 */

#include "StudentsToProjects.h"
#include "Project.h"
#include "Student.h"
#include "ClassSection.h"
#include "json/json.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <chrono>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

StudentsToProjects::StudentsToProjects() {
}

StudentsToProjects::~StudentsToProjects() {
}

constexpr int StudentsToProjects::toConstInt(int constInt) {
	return constInt;
}

void StudentsToProjects::ArrayStudentsToProjectsAssignment(Student studentPool[],
		Project projectPool[], int numStudents, int numProjects, int numSkills,
		const int teamSize, int numTopTeams) {

    auto start = high_resolution_clock::now();
	srand(time(NULL));

	  const int TOP_TEAMS = toConstInt(numTopTeams);
	 //const int TEAM_SIZE = toConstInt(teamSize);
	//const int NUM_STUDENTS = toConstInt(numStudents);

	struct Team {

    	Student Team[5];
		int TeamScore;
	};

    struct ProjectSet {
		//Team Teams[NUM_PROJECTS];
		int ProjectSetScore;
	};

	Team currentTeam;
	ProjectSet currentSet, bestSet, bestSetWithDuplicates;

   //used to store the top 10 teams for every project.
	Team temp;
	Team currentTopTeams[TOP_TEAMS];

	//array to store checks for the top scores.
	int topscores[TOP_TEAMS];

	 for(int j = 0; j < TOP_TEAMS; j++) {
			 currentTopTeams[j]=temp;
			 topscores[j] = 0;
		 }

	Team topTeams[numStudents][TOP_TEAMS];

    //calculate each team combination skillscore for each project
    	int teamskillscore = 0;

        int num =0;

        	cout << "STUDENTS TO PROJECTS ASSIGNMENT RUNNING..." << endl;
        	for(int i = 0; i < numProjects; i++) {

        		//new combination process
        		int studentIndexes[teamSize];
        		for(int i = 0; i < teamSize; i++) {
        			studentIndexes[i] = i+1;
        		}
        		int indexToIncrement = teamSize - 1;
        		bool permuting = true;

        		while(permuting) {
        			for(int j = 0; j < teamSize; j++) {
        				currentTeam.Team[num] = studentPool[studentIndexes[j] - 1];
        				num++;
        				for(int k = 0; k < numSkills; k++) {
        					teamskillscore += studentPool[studentIndexes[j] - 1].Skills[k] * projectPool[i].Skills[k];
        				}
        			}

        			            //negative affinity check
        						//check returns true if there is negative affinity on the team,
        						//and false if there is no negative affinity.
        						if (negativeAffinityCheck(currentTeam.Team) == false){

        						//call to 3 team score functions
        						//TeamScore = func1() + func2() + func3()

        						 teamskillscore = ProjectCompareTeamScore(currentTeam.Team,  projectPool[i]) + SkillCompareTeamScore(currentTeam.Team) + AvailabilityTeamScore(currentTeam.Team);

        						currentTeam.TeamScore = teamskillscore;
        						//debugging: cout for seeing the teamscores.
        						//cout << "TeamScore: "+ to_string(score1) +" " + to_string(score2) +" " + to_string(score3) +" " << " = " << teamskillscore <<endl;


        						for(int k = 0; k < TOP_TEAMS; k++) {

        						    if (k == 0){
        						    	if (currentTeam.TeamScore > topscores[k] ){
        						    	topscores[k] = currentTeam.TeamScore;
        						        currentTopTeams[k] = currentTeam;
        						        break;

        						    	}
        						    }else{
        						    	if ( currentTeam.TeamScore == topscores[k-1] | currentTeam.TeamScore > topscores[k] ){
        						        		topscores[k] = currentTeam.TeamScore;
        						        	    currentTopTeams[k] = currentTeam;
        						        	    break;
        								 }
        						}}

        				  }//end affinity check

        						num = 0;
        						teamskillscore = 0;
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

        		 for(int j = 0; j < TOP_TEAMS; j++) {
        				 topTeams[i][j] = currentTopTeams[j];
        				 topscores[j] = 0;
        				 }

        				cout << "Project # " + to_string(projectPool[i].ProjectID) + "  team combinations complete. " << endl;

        	} // end i loop


	// Do Project Set combinations here
	// End Project Set combinations


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);

	cout << "time in milliseconds: ";
	cout << duration.count() << endl;
	//cout << "Number of iterations: ";
	cout << endl;
	cout<< "Top "<<TOP_TEAMS<<" teams for each project"<<endl;

	for(int i = 0; i < numProjects; i++) {
		Project project = *(projectPool + i);
		cout<< "Projects #" + to_string(project.ProjectID) + " Student Teams:"<<endl;
		for(int j = 0; j < TOP_TEAMS; j++) {

			cout << "Team #" + to_string(j) + " ";
			for(int k = 0; k < teamSize; k++) {

				cout<< to_string(topTeams[i][j].Team[k].StudentID) + " ";

			}
			cout << endl;
			cout<< "TeamScore: " + to_string(topTeams[i][j].TeamScore)<<endl;
		}
		cout << endl;
	}
}

//Team Score Calculating Functions

// This function returns a score of 0-20 determining
// the quality of the team by comparing the Availability of students
// on a team to each other.

int StudentsToProjects::AvailabilityTeamScore(Student team[5]){

	int timeCompareScore = 0;

	timeCompareScore += StudentToStudentAvailibility(team[0], team[1]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[2]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[2]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[2], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[2], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[3], team[4]);

	    //score 0-40
		return timeCompareScore;

		//configure the score from 0-40 to 0-20
		float percent= 0;
		float max = 40;
		percent = timeCompareScore/ max;
		percent = percent * 20;
		percent = (int)percent;

		//return the score 0-20
		return percent;
//>>>>>>> p35/ArraysTest
}

//helper function for AvailabilityTeamScore, compares 2 students
//returns an Availability comparison score of 0 - 4.
int StudentsToProjects::StudentToStudentAvailibility(Student s1, Student s2){

	int score = 0;

	//checks preferred weekday selections
	if(s1.Availability[0] == s2.Availability[0]){
		score += 2;
	}else if ((s1.Availability[1] == s2.Availability[1]) | (s1.Availability[1] == s2.Availability[0]) |(s1.Availability[0] == s2.Availability[1])){
		score += 1;
	}

	//checks preferred weekend selections
	if(s1.Availability[2] == s2.Availability[2]){
			score += 2;
		}else if ((s1.Availability[3] == s2.Availability[3]) | (s1.Availability[3] == s2.Availability[2]) |(s1.Availability[2] == s2.Availability[3])){
			score += 1;
		}

	return score;
}

// This function returns a score of 0-40 determining
// the quality of the team by comparing the student's skills to each other
int StudentsToProjects::SkillCompareTeamScore(Student team[5]){

int teamCompareScore = 0;

teamCompareScore += StudentToStudentSkill(team[0], team[1]);
teamCompareScore += StudentToStudentSkill(team[0], team[2]);
teamCompareScore += StudentToStudentSkill(team[0], team[3]);
teamCompareScore += StudentToStudentSkill(team[0], team[4]);
teamCompareScore += StudentToStudentSkill(team[1], team[2]);
teamCompareScore += StudentToStudentSkill(team[1], team[3]);
teamCompareScore += StudentToStudentSkill(team[1], team[4]);
teamCompareScore += StudentToStudentSkill(team[2], team[3]);
teamCompareScore += StudentToStudentSkill(team[2], team[4]);
teamCompareScore += StudentToStudentSkill(team[3], team[4]);

	return teamCompareScore;

}

//helper function for SkillCompareTeamScore
//returns a student to student comparison score of 0 - 4.
int StudentsToProjects::StudentToStudentSkill(Student s1, Student s2){

	  int skillsum1 = 0;
	  int skillsum2 = 0;
	  int score = 0;

	  for(int i = 0; i < 7; i++){

		 skillsum1 += s1.Skills[i];
		 skillsum2 += s2.Skills[i];
	  }

	  score = skillsum1 - skillsum2;
	  score = abs(score);

	  if (score == 0 || score == 1){
	  	return 4;

	  	}else if(score == 2 || score == 3){
	  	return 3;

	  	}else if(score == 4 || score == 5){
	  	return 2;

	  	}else if(score > 5 && score < 9){
	  	return 1;

	  	}else if(score >= 9){
	  	return 0;

	  	}

}

// This function returns a score of 0-40 determining
// the quality of the team by comparing the max skills a team could have
// on a certain project, to the team's overall skills.
int StudentsToProjects::ProjectCompareTeamScore(Student team[5], Project project){

	int numSkills = 7;
	int teamSize = 5;
	int maxProjectScore = 0;
	int teamSkillSum = 0;

	//find the maximum score a team could get on this project
	for( int i = 0; i < numSkills ; i++ ){

		maxProjectScore += project.Skills[i] * 4;
	}
	maxProjectScore = maxProjectScore * teamSize;

	//find the sum of the team's skills for this project
	for( int i = 0; i < teamSize ; i++ ){
		for( int j = 0; j < numSkills ; j++ ){
			teamSkillSum += team[i].Skills[j] * project.Skills[j];
	}}

    //calculate percentage
	float percent= 0;
	float max = 0;
	max = maxProjectScore;
	percent = teamSkillSum/ max;
	percent = percent * 40;
	percent = (int)percent;

    //return the score 0-40
	return percent;

}

/*
 * Utility::negativeAffinityCheck
 * currently takes in a vector of students, which represents a possible team combination.
 * function checks to see if any students have negative affinity toward one another.
 * If negative affinity between team members IS NOT found, function will return a boolean value of false,
 * If negative affinity between team member IS found, function will return a boolean value of true.
 */
bool StudentsToProjects::negativeAffinityCheck(Student team[5]){
	// start of with negativeAffinity being false - meaning we have not found negative affinity.
	// We will return true if we find an instance of negative affinity in this team combination.
	bool negativeAffinity = false;
	// We begin with an outer loop of that will examine each student in the team
	for (int studentTeamCounter = 0; studentTeamCounter < 5; studentTeamCounter++){
		// Create a temporary student object for ease of use
		//Student currentStudent = team[studentTeamCounter];
		// if the current student's affinity list is empty - we don't need about comparing any other students - so on to the next iteration
		if (team[studentTeamCounter].StudentAffinity.empty()){
			continue;
		} else {
			// lets take a look at the current students affinity list
			for (int currentStudentAffinityCounter = 0; currentStudentAffinityCounter < team[studentTeamCounter].StudentAffinity.size(); currentStudentAffinityCounter++){
				// next we will loop through all other students comparing the current students affinity to other students, checking for negative affinity.
				for (int otherStudentsCounter = 0; otherStudentsCounter < 5; otherStudentsCounter++){
					// create a temporary student object for the other student we are examining in this loop.
					//Student otherStudent = team[otherStudentsCounter];
					// because we are looping, if the current student happens to be the other student, lets continue to the next iteration.
					if (team[studentTeamCounter].StudentID == team[otherStudentsCounter].StudentID){
						continue;
						// next for each student id in the current students affinity list, lets see if the other student has the same Student ID
						// and if the affinity boolean value is false, meaning negative affinity. The current student doesn't want to work with
						// the other student. In this case we will change our negativeAffinity flag to true. We can break out of this function with
						// one instance of negative affinity. The team won't work.
					} else {
						if ((team[studentTeamCounter].StudentAffinity.at(currentStudentAffinityCounter).first == team[otherStudentsCounter].StudentID) && (team[studentTeamCounter].StudentAffinity.at(currentStudentAffinityCounter).second == false)){
							negativeAffinity = true;
							break;
						}
					} // end otherStudentsCounter loop
				}
				if (negativeAffinity == true){
					break;
				}
			} // end currentStudentAffinityCounter loop
		}
		if (negativeAffinity == true){
			break;
		}
	} // end studentTeamCounter loop
	return negativeAffinity;
}
