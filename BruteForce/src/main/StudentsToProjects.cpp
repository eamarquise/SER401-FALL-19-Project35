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

	/*struct Student {

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

	//int numProjects = 1;
	int numSkills = 7;
	//int numStudents = 50;
	//int teamSize = 5;


	//create numProjects projects
	for(int i = 0; i < numProjects; i++) {
		for(int j = 0; j < numSkills; j++) {
			p.skills[j] = (rand() % 2);
		}
		p.projectID = i+1;
		projects.push_back(p);
		Project p;

	}*/

	/*ifstream ifs("./BruteForce/SampleJsonFiles/60Students.json");
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

	cout << endl;*/

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

		string bitmask(teamSize,1);
		bitmask.resize(numStudents, 0);
		while(std::prev_permutation(bitmask.begin(), bitmask.end())) {
			for (int j = 0; j < numStudents; ++j) {
				if(bitmask[j]) {
					currentTeam.team.push_back(StudentList[j]);
					//for(int k = 0; k < numSkills; k++) {


						//teamskillscore += StudentList[j].Skills[k] * ProjectList[i].Skills[k];
					//}
				}
			} //end j loop

			//negative affinity check

			//call to 3 team score functions
			//TeamScore = func1() + func2() + func3()

			int score1 = ProjectCompareTeamScore(currentTeam.team,  ProjectList[i]);
			int score2 = SkillCompareTeamScore(currentTeam.team);

			teamskillscore = score1 + score2;

			currentTeam.TeamScore = teamskillscore;
			cout << "TeamSkillScore for student skills "  << ": " << teamskillscore <<endl;

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

		}// end while loop

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

// This function returns a score of 0-40 determining
// the quality of the team by comparing the student's skills to eachother
int StudentsToProjects::SkillCompareTeamScore(vector <Student> team){


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

//returns a student to student comparison score of 0 - 4.
//helper function for SkillCompareTeamScore
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
int StudentsToProjects::ProjectCompareTeamScore(vector <Student> team, Project project){

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


StudentsToProjects::~StudentsToProjects() {
	// TODO Auto-generated destructor stub
}

