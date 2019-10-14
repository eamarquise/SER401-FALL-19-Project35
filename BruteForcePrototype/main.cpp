#include "Skills.h"
#include "Affinity.h"
#include "PreferredMeetingTimes.h"
#include "Student.h"
#include "Project.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

/*
 * main.cpp
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *      Description:
 *      A brute force draft attempt at student to project allocation
 *
 *  Revised on: 10/14/2019
 *  By: Cristi DeLeo
 *  Revision description: Testing algorithm for assigning Project Pools to
 *  Class Sections.
 */

// Begin External Functions

/* Roll function will return a random number between and including
 * the supplied min and max.
 * for example roll(0,4) will return 0,1,2,3,or 4.
 */
int roll(int min, int max){
	int value = rand() % (max-min +1) + min;
	return value;
}

bool sortPairsDescending(const pair<string,int> &a, const pair<string, int> &b){
	return a.second > b.second;
}
// End External Functions

// calc_min_team_size Function
// Task #36 - Cristi DeLeo
// Calculates the minimum team size.
int calc_min_team_size(int teamSize){
    int minTeamSize;
    double percentFactor = 0.80; // 80%

    minTeamSize = floor(percentFactor * teamSize);

    return minTeamSize;
}

// calc_projects Function
// Task #7 - Cristi DeLeo
// Calculates the number of projects required for any given
// number of students with a specified minimum team size.
int calc_projects(int numStudents, int teamSize, int minTeamSize){
    int numProjects;
    int numStudentsModTeamSize;
    int currentProjectCount;
    int numStudentsNeeded;

    numStudentsModTeamSize = numStudents % teamSize;

    if(numStudentsModTeamSize == 0) {
        numProjects = numStudents / teamSize;
    } else if (numStudentsModTeamSize >= minTeamSize) {
        numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
    } else if (numStudentsModTeamSize < minTeamSize) {
        // Calculation to determine number of projects needed when
        // more than one team will be set at the minimum team size.
        currentProjectCount = numStudents / teamSize;
        numStudentsNeeded = minTeamSize - numStudentsModTeamSize;

        // Determines whether there are enough students to evenly
        // distribute projects based on the minimum team size
        if(numStudentsNeeded > currentProjectCount){
            if(teamSize > minTeamSize){
                teamSize--;
            } else if(teamSize == minTeamSize){
                teamSize--;
                minTeamSize--;
            } else{
                // Error catch
            }
            calc_projects(numStudents, teamSize, minTeamSize);
        } else if(numStudentsNeeded <= currentProjectCount){
            numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
        }
    }

    return numProjects;
}

// calc_projects Function
// Task #7 - Cristi DeLeo
// Calculates the number of projects required for any given
// number of students.
int calc_projects(int numStudents, int teamSize){
    int numProjects;
    int numStudentsModTeamSize;
    int minTeamSize;
    int currentProjectCount;
    int numStudentsNeeded;

    minTeamSize = calc_min_team_size(teamSize);

    numStudentsModTeamSize = numStudents % teamSize;

    if(numStudentsModTeamSize == 0) {
        numProjects = numStudents / teamSize;
    } else if (numStudentsModTeamSize >= minTeamSize) {
        numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
    } else if (numStudentsModTeamSize < minTeamSize) {
        // Calculation to determine number of projects needed when
        // more than one team will be set at the minimum team size.
        currentProjectCount = numStudents / teamSize;
        numStudentsNeeded = minTeamSize - numStudentsModTeamSize;

        // Determines whether there are enough students to evenly
        // distribute projects based on the minimum team size
        if(numStudentsNeeded > currentProjectCount){
            if(teamSize > minTeamSize){
                teamSize--;
            } else if(teamSize == minTeamSize){
                teamSize--;
                minTeamSize--;
            } else{
                // Error catch
            }
            calc_projects(numStudents, teamSize, minTeamSize);
        } else if(numStudentsNeeded <= currentProjectCount){
            numProjects = ((numStudents - numStudentsModTeamSize) / teamSize) + 1;
        }
    }

    return numProjects;
}

class StudentList {
	public:
		vector<Student> allStudentList;
		vector<Student> assignedStudentList; //not used yet - using <vector>assignedStudents down below for the time being
};

class ProjectList {
	public:
		vector<Project> allProjectList;
};
// End Classes

int main(){
	cout << "brute force project x student matrix application for student-project team allocation" << endl;
	cout << "************************************************************************************" << endl;

	// Important Numbers
	int numStudents = 100;
	int numProjects = 35;
	int numSkills = 5;
	int teamSize = 5;
	int numMeetingTimesAvailable = 6;
	int numOfMeetingTimesToSelect = 3;
	srand(time(0));

	StudentList studentList2; // using randomly generated students
	ProjectList projectList2; // using randomly generated projects

	// Create randomly generated Students and put them in StudentList2
	for (int i = 0; i < numStudents ; i++){
		string studentName = "st" + to_string(i);
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
		Student tempStudent(studentName, tempSkills, times, affinity, online);
		studentList2.allStudentList.push_back(tempStudent);
	}

	// Create randomly generated Projects and put them in ProjectList2
	for (int i = 0; i < numProjects ; i++){
		string projectName = "p" + std::to_string(i);
		Skills tempSkills;
		for (int j = 0 ; j < numSkills; j++){
			int skillScore = roll(0, 4);
			tempSkills.skillScoreArray.push_back(skillScore);
		}
		bool online = (bool)roll(0,1);
		Project tempProject(projectName, tempSkills, online);
		projectList2.allProjectList.push_back(tempProject);
	}

	// display random students to console for testing; can delete later
	cout << endl << "Random students in studentList2" << endl;
	for (int i = 0; i < numStudents; i++){
		string studentString = studentList2.allStudentList.at(i).name + "\t";
		for (int j = 0; j < numSkills; j++){
			studentString += "Skill" + to_string(j)+ ": " + to_string(studentList2.allStudentList.at(i).studentSkills.skillScoreArray.at(j)) + "\t";
		}
		studentString += "Times Available: ";
		for (int j = 0; j < numOfMeetingTimesToSelect; j++){
			studentString += to_string(studentList2.allStudentList.at(i).timesAvailable.meetingTimes.at(j)) + ", ";
		}
		studentString += "\t";
		studentString += "PreferredStudents: ";
		if(!studentList2.allStudentList.at(i).affinity.preferredStudents.empty()){
			for (int j = 0; j < studentList2.allStudentList.at(i).affinity.preferredStudents.size(); j++){
				studentString += studentList2.allStudentList.at(i).affinity.preferredStudents.at(j) + ", ";
			}
		} else {
			studentString += "None\t\t";
		}
		studentString += "\t";
		studentString += "AvoidedStudents: ";
		if(!studentList2.allStudentList.at(i).affinity.avoidedStudents.empty()){
			for (int j = 0; j < studentList2.allStudentList.at(i).affinity.avoidedStudents.size(); j++){
				studentString += studentList2.allStudentList.at(i).affinity.avoidedStudents.at(j) + ", ";
			}
		} else {
			studentString += "None\t\t";
		}
		studentString += "\t";
		studentString += "Online: " + to_string(studentList2.allStudentList.at(i).online);
		cout << studentString << endl;
	}
	// display random projects to console for testing; can delete later
	cout << endl << "Random projects in projectList2" << endl;
	for (int i = 0; i < numProjects ; i++){
		string projectString = projectList2.allProjectList.at(i).name + "\t";
		for (int j = 0; j < numSkills; j++){
			projectString += "Skill" + to_string(j)+ ": " + to_string(projectList2.allProjectList.at(i).projectSkills.skillScoreArray.at(j)) + "\t";
		}
		projectString += "Online: " + to_string(projectList2.allProjectList.at(i).online);
		cout << projectString << endl;
	}

	// Fill in ProjectxSkillScore2 Matrix Automatically
	int projectxskill2[numProjects][numSkills] = {0};
	for (int i = 0; i < numProjects; i++){
		for (int j = 0; j < numSkills; j++){
			projectxskill2[i][j] = projectList2.allProjectList.at(i).projectSkills.skillScoreArray.at(j);
		}
	}
	// Fill in SkillxStudent2 Matrix Automatically
	int skillxstudent2[numSkills][numStudents] = {0};
	for (int i = 0; i < numSkills; i++){
		for (int j = 0; j < numStudents; j++){
			skillxstudent2[i][j] = studentList2.allStudentList.at(j).studentSkills.skillScoreArray.at(i);
		}
	}

	// Print student name across top of projectxstudent matrix
	cout << endl;
	cout << "\t";
	for (int i = 0; i < numStudents ; i++ ){
		cout << "st" + to_string(i) + "\t";
	}
	cout<< endl;

	// Calculate Project x Student Matrix
	// (Project x SkillScore Matrix) x (SkillScore x Student Matrix)
	// (4x5)x(5x20)
	// porjectxstudent2 is keeping track of the randomized students and projects
	int projectxstudent2[numProjects][numStudents];
	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		string p = to_string(rows);
		cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectxstudent2[rows][cols] = {0};
			for (int inner = 0; inner < numSkills; inner++){
				projectxstudent2[rows][cols] = projectxstudent2[rows][cols] +  projectxskill2[rows][inner] * skillxstudent2[inner][cols];

			}
			cout << projectxstudent2[rows][cols] << "\t";
		}
		cout << "\n";
	}
	cout << endl;

	// Assign Students to Projects 2
	// take projectxstudent2[][] and put it into a vector<vector<pair<string,int>>>
	// This will allow us to sort each vector<pair<string,int>> representing the values of
	// each students score to a given project. The pair<string,int> will be the students name
	// and the students score for that project.
	pair<string,int> studentPair;
	vector<pair<string,int>> projectVector;
	vector<vector<pair<string,int>>> vectorOfProjects;
	vector<vector<pair<string,int>>> vectorOfProjectsSortedStudents;
	vector<Student> studentTeam;
	vector<vector<Student>> projectTeams;

	for (int i = 0; i < numProjects; i++){
		for (int j = 0; j < numStudents ; j++){
			studentPair.first = "st" + to_string(j);
			studentPair.second = projectxstudent2[i][j];
			projectVector.push_back(studentPair);
		}
		vectorOfProjects.push_back(projectVector);
		projectVector.clear();
	}

	// sort project vectors based on student score (second value stored in the studentPair)
	for (int i = 0 ; i < numProjects ; i++){
		projectVector = vectorOfProjects.at(i);
		sort(projectVector.begin(), projectVector.end(), sortPairsDescending);
		vectorOfProjectsSortedStudents.push_back(projectVector);
	}
	// print sorted students scores per project to console for testing - can delete later
	cout << endl;
	int projectPrintCounter = 0;
	for (vector<vector<pair<string,int>>>::iterator it = vectorOfProjectsSortedStudents.begin(); it != vectorOfProjectsSortedStudents.end();++it){
		cout << "p" << projectPrintCounter << ": ";
		projectVector = *it;
		for (vector<pair<string,int>>::iterator it2 = projectVector.begin(); it2 != projectVector.end(); ++it2){
			studentPair = *it2;
			cout << "(" << studentPair.first << "," << studentPair.second << ") ;";
		}
		cout << '\n';
		projectPrintCounter++;
	}

	// Assign Teams 2 - new method to select student teams - can delete 'Assign Students To Projects' below, after tested.
	// For every Project
	for (int projectCounter = 0; projectCounter < numProjects; projectCounter++){
		projectVector = vectorOfProjectsSortedStudents.at(projectCounter);
		studentTeam.clear();
		// For every student
		for (int studentCounter = 0; studentCounter < numStudents; studentCounter++ ){
			Student * cStudent;
			bool assignStudentToTeam = false;
			studentPair = projectVector.at(studentCounter);
			// capture current student as Student object. Loop below will break and transfer control back
			// to studentCounter loop once it pairs up the studentPair.first string with a Student.name string.
			for (int studentMatchCounter = 0 ; studentMatchCounter < numStudents; studentMatchCounter++){
				cStudent = &studentList2.allStudentList.at(studentMatchCounter);
				if (cStudent->name.compare(studentPair.first) == 0){
					break;
				}
			}
			// check if student on this iteration has already been assigned to a project if so, go to next student.
			bool studentAssigned = false;
			for (int i = 0; i < studentList2.assignedStudentList.size(); i++){
				if (cStudent->name.compare(studentList2.assignedStudentList.at(i).name) == 0){
					studentAssigned = true;
					break;
				}
			}
			if (studentAssigned){
				continue;
			}
			// check if the current iteration's project is local and if the current student is online.
			// if project local and student is online, go to next student.
			// presumption that an online project can be accomplished by local students too.
			if (projectList2.allProjectList.at(projectCounter).online == false && cStudent->online == true){
				// cout << cStudent->name << " is an online student and can't work local project." << endl;
				continue;
			}

			// if this is our first sorted student, place them in the studentTeam and to the assignedStudentList
			// else we need to do some checks for meeting times and affinity.
			Student copyStudent(cStudent->name, cStudent->studentSkills, cStudent->timesAvailable, cStudent->affinity, cStudent->online);
			//cout << "copyStudent: " << copyStudent.name << endl;
			if (studentTeam.empty()){
				assignStudentToTeam = true;
			} else {
				// 1) check for negative affinity toward copyStudent by students already assigned to the studentTeam.
				bool negativeAffinity = false;
				for (int studentTeamCounter = 0; studentTeamCounter < studentTeam.size(); studentTeamCounter++){
					if (studentTeam.at(studentTeamCounter).affinity.avoidedStudents.empty()){
						continue;
					} else {
						for (int studentNegAffinityCounter = 0; studentNegAffinityCounter < studentTeam.at(studentTeamCounter).affinity.avoidedStudents.size(); studentNegAffinityCounter++ ){
							if (studentTeam.at(studentTeamCounter).affinity.avoidedStudents.at(studentNegAffinityCounter).compare(copyStudent.name) == 0){
								cout << studentTeam.at(studentTeamCounter).name << " , a current team member, wants to avoid s" << copyStudent.name << endl;
								negativeAffinity = true;
							}
						}
					}
				}
				// 1.5 check for negative affinity by copyStudent toward any member of current team
				if (!(copyStudent.affinity.avoidedStudents.empty())){
					for (int i = 0; i < copyStudent.affinity.avoidedStudents.size(); i++){
						for (int j = 0; j < studentTeam.size(); j++){
							if (copyStudent.affinity.avoidedStudents.at(i).compare(studentTeam.at(j).name) == 0){
								cout << copyStudent.name << " wants to avoid a current team member, " << studentTeam.at(j).name << endl;
								negativeAffinity = true;
							}
						}
					}
				}
				// if negative affinity is found between a student assigned to the studentTeam and the currentStudent
				// we will continue on to the next student in our sorted vector.
				if (negativeAffinity){
					continue;
				}
				// 2) check for matching meeting times
				bool preferredTimeMatch = false;
				for (int i = 0 ; i < copyStudent.timesAvailable.meetingTimes.size(); i++) {
					if (preferredTimeMatch == true){
						break;
					}
					int preferredMeetingTime = copyStudent.timesAvailable.meetingTimes.at(i);
					for (int j = 0; j < studentTeam.at(0).timesAvailable.meetingTimes.size(); j++){
						if (preferredMeetingTime == studentTeam.at(0).timesAvailable.meetingTimes.at(j)){
							preferredTimeMatch = true;
							break;
						}
					}
				}
				if (preferredTimeMatch){
					assignStudentToTeam = true;
				} else {
					cout << copyStudent.name << " couldn't find a matching meeting time with team captain, " << studentTeam.at(0).name << endl;
					continue;
				}
			}
			if (assignStudentToTeam){
				studentTeam.push_back(copyStudent);
			}
			// if our student team is full for this project break out and go to next project.
			if (studentTeam.size() == teamSize){
				for (int i = 0; i < teamSize; i++){
					studentList2.assignedStudentList.push_back(studentTeam.at(i));
				}
				projectTeams.push_back(studentTeam);
				break;
			}
		}

		if (studentTeam.empty() || studentTeam.size() < teamSize){
			cout << "p" << projectCounter << " could not be filled by a full student team." << endl;
			studentTeam.clear();
			projectTeams.push_back(studentTeam);
		} else {
			cout << endl << "p" << projectCounter << " results: ";
			for (int count = 0; count < teamSize; count++){
				cout << projectTeams.at(projectCounter).at(count).name << ", ";
			}
			cout << endl;
		}
	}




	// Assign Students to Projects
	// firstStudent, secondStudent, thirdStudent, and fourthStudent will be Student name.
	// 0 will be for st0, 12 for st12.
	// first, second, third, and fourth will store the values of the [teamSize=5 currently] highest scoring students per project.
	// Students already selected for a previous project will be skipped and we will look at the next student.
//	cout << "*************Beginning-of-Project-Team Report*************" << endl;
//	cout << endl;
//	int firstStudent, secondStudent, thirdStudent, fourthStudent, fifthStudent;
//	int first, second, third, fourth, fifth;
//
//	// For each project
//	for (int i = 0; i < numProjects; i++){
//		firstStudent = secondStudent = thirdStudent = fourthStudent = fifthStudent = first = second = third = fourth = fifth = -1;
//		// For each Student
//		for (int j = 0 ; j < numStudents; j++){
//			// check if student on this iteration has already been assigned to a project if so, go to next student.
//			vector<Student>::iterator assignedStudentIterator;
//			assignedStudentIterator = find(studentList2.assignedStudentList.begin(), studentList2.assignedStudentList.end(), studentList2.allStudentList.at(j));
//			if (assignedStudentIterator != studentList2.assignedStudentList.end()){
//				continue;
//			}
//			// check if the current iteration's project is local and if the current student is online.
//			// if project local and student is online, go to next student.
//			// presumption that an online project can be accomplished by local students too.
//			if (projectList2.allProjectList.at(i).online == false && studentList2.allStudentList.at(j).online == true){
//				continue;
//			}
//
//			if (projectxstudent2[i][j] > first){
//				fifth = fourth;
//				fifthStudent = fourthStudent;
//				fourth = third;
//				fourthStudent = thirdStudent;
//				third = second;
//				thirdStudent = secondStudent;
//				second = first;
//				secondStudent = firstStudent;
//				first = projectxstudent2[i][j];
//				firstStudent = j;
//			}
//			else if (projectxstudent2[i][j] > second){
//				fifth = fourth;
//				fifthStudent = fourthStudent;
//				fourth = third;
//				fourthStudent = thirdStudent;
//				third = second;
//				thirdStudent = secondStudent;
//				second = projectxstudent2[i][j];
//				secondStudent = j;
//			}
//			else if (projectxstudent2[i][j] > third){
//				fifth = fourth;
//				fifthStudent = fourthStudent;
//				fourth = third;
//				fourthStudent = thirdStudent;
//				third = projectxstudent2[i][j];
//				thirdStudent = j;
//			}
//			else if (projectxstudent2[i][j] > fourth){
//				fifth = fourth;
//				fifthStudent = fourthStudent;
//				fourth = projectxstudent2[i][j];
//				fourthStudent = j;
//			}
//			else if (projectxstudent2[i][j] > fifth){
//				fifth = projectxstudent2[i][j];
//				fifthStudent = j;
//			}
//		} // end student loop
//
//		// if a project team of 5 could not be filled out with available students, move on to next project.
//		if ((fifthStudent == -1) || (fourthStudent == -1) || (thirdStudent == -1) || (secondStudent == -1) || (firstStudent == -1))
//		{
//			cout << "Project" + to_string(i)+  " can not be filled by " + to_string(teamSize) + " Students, moving on to next project" << endl;
//			cout << endl;
//			continue;
//		}
//
//		// these students have been assigned to the current project. We will push them
//		// into a vector so we can compare already assigned students while iterating through the next project.
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(firstStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(secondStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(thirdStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(fourthStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(fifthStudent));
//
//		// print project team to console
//		cout << "p" + to_string(i) + "\tStudent\tOnline:" + to_string(projectList2.allProjectList.at(i).online) << endl;
//		cout << "1)\t" + studentList2.allStudentList.at(firstStudent).name + "\tScore: " + to_string(first)   << endl;
//		cout << "2)\t" + studentList2.allStudentList.at(secondStudent).name + "\tScore: " + to_string(second)  << endl;
//		cout << "3)\t" + studentList2.allStudentList.at(thirdStudent).name + "\tScore: " + to_string(third)  << endl;
//		cout << "4)\t" + studentList2.allStudentList.at(fourthStudent).name + "\tScore: " + to_string(fourth)   << endl;
//		cout << "5)\t" + studentList2.allStudentList.at(fifthStudent).name + "\tScore: " + to_string(fifth) << endl;
//		cout << endl;
//
//	}//end project loop
//
	// check if all students assigned
	vector<Student>::iterator assignedStudentIterator;
	for (int i = 0 ; i < numStudents; i++){
		bool foundAssignedStudent = false;
		for (int j = 0; j < studentList2.assignedStudentList.size(); j++){
			if (studentList2.allStudentList.at(i).name.compare(studentList2.assignedStudentList.at(j).name)){
				foundAssignedStudent = true;
			}
			if(foundAssignedStudent){
					//	cout << "Student " + studentList2.allStudentList.at(i).name + " is assigned."<< endl;
			} else {
						cout << "WARNING! Student " + studentList2.allStudentList.at(i).name + " is not assigned to a project." << endl;
			}
		}

	}

    cout << "Number of projects: " << calc_projects(numStudents, teamSize) << endl;

	cout << endl;
//	cout << "*******************End-of-Project-Team Report*************" << endl;
	return 0;
}


