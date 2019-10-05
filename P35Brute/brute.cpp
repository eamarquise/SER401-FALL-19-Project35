/*
 * brute.cpp
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *      Description:
 *      A brute force draft attempt at student to project allocation
 *
 */
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>

using namespace std;

// Begin External Functions

/* Roll function will return a random number between and including
 * the supplied min and max.
 * for example roll(0,4) will return 0,1,2,3,or 4.
 */
int roll(int min, int max){
	int value = rand() % (max-min +1) + min;
	return value;
}
// End External Functions

// Begin Classes
class Skills {
public:
	// Skills has an vector to store skillScores
	// skillsScores rank from 0(no knowledge)-4(expert)
	// currently under Important Numbers (main().
	vector<int> skillScoreArray;
};

class PreferredMeetingTimes {
	/* 	preferredMeetingTime: Based on MST
	 *  will take the 3 preferred meeting times for students in order of importance.
	 * 	0)	Night-time: 12:00AM - 4:00AM
	 *	1)	Early Morning: 4:00AM - 8:00AM
	 *	2)	Morning: 8:00AM - 12:00PM
	 *	3)	Afternoon: 12:00PM - 4:00PM
	 *	4)	Early Evening: 4:00PM - 8:00PM
	 *	5)  Evening: 8:00PM - 12:00AM
	 */
	public:
		vector<int> meetingTimes;
};

class Affinity {
	public:
		vector<string> preferredStudents;
		vector<string> avoidedStudents;
};

class Student {
	public:
		string name;
		Skills studentSkills;
		PreferredMeetingTimes timesAvailable;
		Affinity affinity;
		// online: 0(false)-local student, 1(true)-online student
		bool online;

		Student();
		Student(string n, Skills s, PreferredMeetingTimes times, Affinity aff, bool online){
			this->name = n;
			this->timesAvailable = times;
			this->online = online;
			this->studentSkills = s;
			this->affinity = aff;
		}
		bool operator==(const Student &studentToCompare) const {
			if(this->name.compare(studentToCompare.name) == 0) {
				return true;
			} else {
				return false;
			}
		}
};

class Project {
	public:
		string name;
		// online: 0(false)-local student, 1(true)-online student
		bool online;
		// projectSkills has a vector to store skillScores
		// skillsScores rank from 0(no knowledge)-4(expert)
		Skills projectSkills;

		Project();
		Project(string n, Skills s, bool o){
			this->name = n;
			this->online = o;
			this->projectSkills = s;
		}
		bool operator==(const Project &projectToCompare) const {
			if(this->name.compare(projectToCompare.name) == 0) {
				return true;
			} else {
				return false;
			}
		}


};

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
		for (int i = 0 ; i < numOfMeetingTimesToSelect ; i++){
			int time = roll(0, (numMeetingTimesAvailable - 1));
			times.meetingTimes.push_back(time);
		}
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
		string projectName = "p" + to_string(i);
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




	// Assign Students to Projects
	// firstStudent, secondStudent, thirdStudent, and fourthStudent will be Student name.
	// 0 will be for st0, 12 for st12.
	// first, second, third, and fourth will store the values of the [teamSize=5 currently] highest scoring students per project.
	// Students already selected for a previous project will be skipped and we will look at the next student.
	cout << "*************Beginning-of-Project-Team Report*************" << endl;
	cout << endl;
	int firstStudent, secondStudent, thirdStudent, fourthStudent, fifthStudent;
	int first, second, third, fourth, fifth;

	// For each project
	for (int i = 0; i < numProjects; i++){
		firstStudent = secondStudent = thirdStudent = fourthStudent = fifthStudent = first = second = third = fourth = fifth = -1;
		// For each Student
		for (int j = 0 ; j < numStudents; j++){
			// check if student on this iteration has already been assigned to a project if so, go to next student.
			vector<Student>::iterator assignedStudentIterator;
			assignedStudentIterator = find(studentList2.assignedStudentList.begin(), studentList2.assignedStudentList.end(), studentList2.allStudentList.at(j));
			if (assignedStudentIterator != studentList2.assignedStudentList.end()){
				continue;
			}
			// check if the current iteration's project is local and if the current student is online.
			// if project local and student is online, go to next student.
			// presumption that an online project can be accomplished by local students too.
			if (projectList2.allProjectList.at(i).online == false && studentList2.allStudentList.at(j).online == true){
				continue;
			}

			if (projectxstudent2[i][j] > first){
				fifth = fourth;
				fifthStudent = fourthStudent;
				fourth = third;
				fourthStudent = thirdStudent;
				third = second;
				thirdStudent = secondStudent;
				second = first;
				secondStudent = firstStudent;
				first = projectxstudent2[i][j];
				firstStudent = j;
			}
			else if (projectxstudent2[i][j] > second){
				fifth = fourth;
				fifthStudent = fourthStudent;
				fourth = third;
				fourthStudent = thirdStudent;
				third = second;
				thirdStudent = secondStudent;
				second = projectxstudent2[i][j];
				secondStudent = j;
			}
			else if (projectxstudent2[i][j] > third){
				fifth = fourth;
				fifthStudent = fourthStudent;
				fourth = third;
				fourthStudent = thirdStudent;
				third = projectxstudent2[i][j];
				thirdStudent = j;
			}
			else if (projectxstudent2[i][j] > fourth){
				fifth = fourth;
				fifthStudent = fourthStudent;
				fourth = projectxstudent2[i][j];
				fourthStudent = j;
			}
			else if (projectxstudent2[i][j] > fifth){
				fifth = projectxstudent2[i][j];
				fifthStudent = j;
			}
		} // end student loop

		// if a project team of 5 could not be filled out with available students, move on to next project.
		if ((fifthStudent == -1) || (fourthStudent == -1) || (thirdStudent == -1) || (secondStudent == -1) || (firstStudent == -1))
		{
			cout << "Project" + to_string(i)+  " can not be filled by " + to_string(teamSize) + " Students, moving on to next project" << endl;
			cout << endl;
			continue;
		}

		// these students have been assigned to the current project. We will push them
		// into a vector so we can compare already assigned students while iterating through the next project.
		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(firstStudent));
		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(secondStudent));
		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(thirdStudent));
		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(fourthStudent));
		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(fifthStudent));

		// print project team to console
		cout << "p" + to_string(i) + "\tStudent\tOnline:" + to_string(projectList2.allProjectList.at(i).online) << endl;
		cout << "1)\t" + studentList2.allStudentList.at(firstStudent).name + "\tScore: " + to_string(first)   << endl;
		cout << "2)\t" + studentList2.allStudentList.at(secondStudent).name + "\tScore: " + to_string(second)  << endl;
		cout << "3)\t" + studentList2.allStudentList.at(thirdStudent).name + "\tScore: " + to_string(third)  << endl;
		cout << "4)\t" + studentList2.allStudentList.at(fourthStudent).name + "\tScore: " + to_string(fourth)   << endl;
		cout << "5)\t" + studentList2.allStudentList.at(fifthStudent).name + "\tScore: " + to_string(fifth) << endl;
		cout << endl;

	}//end project loop

	// check if all students assigned
	vector<Student>::iterator assignedStudentIterator;
	for (int i = 0 ; i < numStudents; i++){
		assignedStudentIterator = find(studentList2.assignedStudentList.begin(), studentList2.assignedStudentList.end(), studentList2.allStudentList.at(i));
		if(assignedStudentIterator != studentList2.assignedStudentList.end()){
		//	cout << "Student " + studentList2.allStudentList.at(i).name + " is assigned."<< endl;
		} else {
			cout << "WARNING! Student " + studentList2.allStudentList.at(i).name + " is not assigned to a project." << endl;
		}
	}

	cout << endl;
	cout << "*******************End-of-Project-Team Report*************" << endl;
	return 0;
}


