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

using namespace std;

// function to check if a vector contains a certain int as an element.
// returns true or false
bool contains(vector<int> v, int x){
	return ! (v.empty() || find(v.begin(), v.end(), x) == v.end());
}

// searchVector
// Alternative function to search a vector<T> for element T.
// this should be able to be used to search for Students or Project vectors.
template <typename T>
pair <bool, int> searchVector(const vector<T> &vectorToSearch, const T &elementToFind){

	pair<bool, int> returnValue;

	auto it = find(vectorToSearch.begin(), vectorToSearch.end(), elementToFind);

	if (it != vectorToSearch.end()){
		returnValue.first = true;
		returnValue.second = distance(vectorToSearch.begin(), it);
	} else {
		returnValue.first = false;
		returnValue.second = -1;
	}
}

class Student {
	public:
		string name;
		// skillsScores rank from 0(no knowledge)-4(expert)
		int skillScore1;
		int skillScore2;
		int skillScore3;
		int skillScore4;
		int skillScore5;
		// timezone: 0-pacific, 1-mountain, 2-central, 3-eastern
		int timezone;
		// online: 0(false)-local student, 1(true)-online student
		bool online;

		Student();
		Student(string n, int ss1, int ss2, int ss3, int ss4, int ss5, int tz, bool o){
			this->name = n;
			this->skillScore1 = ss1;
			this->skillScore2 = ss2;
			this->skillScore3 = ss3;
			this->skillScore4 = ss4;
			this->skillScore5 = ss5;
			this->timezone = tz;
			this->online = o;
		}
};

class Project {
	public:
		string name;
		// skillsScores rank from 0(no knowledge)-4(expert)
		int skillScore1;
		int skillScore2;
		int skillScore3;
		int skillScore4;
		int skillscore5;
		Project();
		Project(string n, int ss1, int ss2, int ss3, int ss4, int ss5, bool o){
			this->name = n;
			this->skillScore1 = ss1;
			this->skillScore2 = ss2;
			this->skillScore3 = ss3;
			this->skillScore4 = ss4;
			this->skillscore5 = ss5;
			this->online = o;
		}
		// online: 0(false)-local student, 1(true)-online student
		bool online;
};

class StudentList {
	public:
		vector<Student> allStudentList;
		vector<Student> assignedStudentList;
};

class ProjectList {
	public:
		vector<Project> allProjectList;
};

int main(){
	cout << "brute force project x student matrix" << endl;

	// Important numbers
	int numStudents = 20;
	int numProjects = 4;
	int numSkills = 5;
	int teams = numStudents / numProjects;

	StudentList studentList;
	ProjectList projectList;

	// Create Students and Student List
	Student st0("st0", 2, 2, 2, 0, 2, 2, 0);
	Student st1("st1", 3, 0, 3, 0, 0, 2, 1);
	Student st2("st2", 3, 1, 2, 3, 0, 2, 0);
	Student st3("st3", 3, 0, 2, 2, 0, 1, 1);
	Student st4("st4", 1, 3, 1, 2, 2, 1, 0);
	Student st5("st5", 3, 3, 0, 2, 0, 2, 1);
	Student st6("st6", 3, 1, 0, 3, 2, 1, 0);
	Student st7("st7", 1, 2, 1, 2, 3, 1, 1);
	Student st8("st8", 3, 0, 1, 3, 0, 2, 0);
	Student st9("st9", 1, 3, 0, 3, 2, 2, 1);
	Student st10("st10", 3, 3, 2, 0, 2, 2, 0);
	Student st11("st11", 2, 1, 2, 3, 0, 2, 1);
	Student st12("st12", 3, 0, 1, 0, 0, 1, 0);
	Student st13("st13", 3, 2, 3, 2, 1, 2, 1);
	Student st14("st14", 2, 1, 2, 2, 1, 1, 0);
	Student st15("st15", 3, 3, 3, 2, 3, 3, 1);
	Student st16("st16", 2, 3, 3, 0, 1, 2, 0);
	Student st17("st17", 2, 1, 0, 1, 0, 2, 1);
	Student st18("st18", 2, 3, 2, 0, 3, 1, 0);
	Student st19("st19", 1, 2, 2, 3, 1, 1, 1);

	studentList.allStudentList.push_back(st0);
	studentList.allStudentList.push_back(st1);
	studentList.allStudentList.push_back(st2);
	studentList.allStudentList.push_back(st3);
	studentList.allStudentList.push_back(st4);
	studentList.allStudentList.push_back(st5);
	studentList.allStudentList.push_back(st6);
	studentList.allStudentList.push_back(st7);
	studentList.allStudentList.push_back(st8);
	studentList.allStudentList.push_back(st9);
	studentList.allStudentList.push_back(st10);
	studentList.allStudentList.push_back(st11);
	studentList.allStudentList.push_back(st12);
	studentList.allStudentList.push_back(st13);
	studentList.allStudentList.push_back(st14);
	studentList.allStudentList.push_back(st15);
	studentList.allStudentList.push_back(st16);
	studentList.allStudentList.push_back(st17);
	studentList.allStudentList.push_back(st18);
	studentList.allStudentList.push_back(st19);

	// Create Projects and ProjectList
	Project p0("p0", 1, 3, 3, 1, 3, 0);
	Project p1("p1", 0, 0, 3, 2, 2, 0);
	Project p2("p2", 3, 1, 0, 1, 2, 1);
	Project p3("p3", 3, 0, 0, 2, 0, 1);

	projectList.allProjectList.push_back(p0);
	projectList.allProjectList.push_back(p1);
	projectList.allProjectList.push_back(p2);
	projectList.allProjectList.push_back(p3);

	// Fill in Project x SkillScore Matrix (4x5)
	int projectxskill[numProjects][numSkills] =
	{
			{p0.skillScore1, p0.skillScore2, p0.skillScore3, p0.skillScore4, p0.skillscore5},
			{p1.skillScore1, p1.skillScore2, p1.skillScore3, p1.skillScore4, p1.skillscore5},
			{p2.skillScore1, p2.skillScore2, p2.skillScore3, p2.skillScore4, p2.skillscore5},
			{p3.skillScore1, p3.skillScore2, p3.skillScore3, p3.skillScore4, p3.skillscore5}
	};
	// Fill in SkillScore x Student Matrix (5x20)
	int skillxstudent[numSkills][numStudents] =
	{
			{st0.skillScore1, st1.skillScore1, st2.skillScore1, st3.skillScore1, st4.skillScore1, st5.skillScore1, st6.skillScore1, st7.skillScore1, st8.skillScore1, st9.skillScore1, st10.skillScore1, st11.skillScore1, st12.skillScore1, st13.skillScore1, st14.skillScore1, st15.skillScore1, st16.skillScore1, st17.skillScore1, st18.skillScore1, st19.skillScore1},
			{st0.skillScore2, st1.skillScore2, st2.skillScore2, st3.skillScore2, st4.skillScore2, st5.skillScore2, st6.skillScore2, st7.skillScore2, st8.skillScore2, st9.skillScore2, st10.skillScore2, st11.skillScore2, st12.skillScore2, st13.skillScore2, st14.skillScore2, st15.skillScore2, st16.skillScore2, st17.skillScore2, st18.skillScore2, st19.skillScore2},
			{st0.skillScore3, st1.skillScore3, st2.skillScore3, st3.skillScore3, st4.skillScore3, st5.skillScore3, st6.skillScore3, st7.skillScore3, st8.skillScore3, st9.skillScore3, st10.skillScore3, st11.skillScore3, st12.skillScore3, st13.skillScore3, st14.skillScore3, st15.skillScore3, st16.skillScore3, st17.skillScore3, st18.skillScore3, st19.skillScore3},
			{st0.skillScore4, st1.skillScore4, st2.skillScore4, st3.skillScore4, st4.skillScore4, st5.skillScore4, st6.skillScore4, st7.skillScore4, st8.skillScore4, st9.skillScore4, st10.skillScore4, st11.skillScore4, st12.skillScore4, st13.skillScore4, st14.skillScore4, st15.skillScore4, st16.skillScore4, st17.skillScore4, st18.skillScore4, st19.skillScore4},
			{st0.skillScore5, st1.skillScore5, st2.skillScore5, st3.skillScore5, st4.skillScore5, st5.skillScore5, st6.skillScore5, st7.skillScore5, st8.skillScore5, st9.skillScore5, st10.skillScore5, st11.skillScore5, st12.skillScore5, st13.skillScore5, st14.skillScore5, st15.skillScore5, st16.skillScore5, st17.skillScore5, st18.skillScore5, st19.skillScore5}
	};

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
	int projectxstudent[numProjects][numStudents];

	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		string p = to_string(rows);
		cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectxstudent[rows][cols] = 0;

			for (int inner = 0; inner < numSkills; inner++){
				projectxstudent[rows][cols] = projectxstudent[rows][cols] +  projectxskill[rows][inner] * skillxstudent[inner][cols];
			}
			cout << projectxstudent[rows][cols] << "\t";
		}
		cout << "\n";
	}
	cout << endl;

	// Assign Students to Projects

	// assignedStudents will keep track of students that have already been selected for a project.
	// each element is a student name (ie for st12, it would be 12)
	vector<int> assignedStudents;

	// firstStudent, secondStudent, thirdStudent, and fourthStudent will be Student name.
	// 1 will be for st1, 12 for st12
	// first, second, third, and fourth will store the values of the 4 highest scoring students per project.
	// Students already selected for a previous project will be omitted.
	int firstStudent, secondStudent, thirdStudent, fourthStudent;
	int first, second, third, fourth;

	// For each project
	for (int i = 0; i < numProjects; i++){
		firstStudent = secondStudent = thirdStudent = fourthStudent = first = second = third = fourth = -1;
		// For each Student
		for (int j = 0 ; j < numStudents; j++){
			// check if student on this iteration has already been assigned to a project
			// if so, go to next student.
			if (contains(assignedStudents, j) == true){
				continue;
			}
			// check if the current iteration's project is local and if the current student is online.
			// if project local and student is online, go to next student.
			// presumption that an online project can be accomplished by local students too.
			if (projectList.allProjectList.at(i).online == 0 && studentList.allStudentList.at(j).online == 1){
				continue;
			}
			if (projectxstudent[i][j] > first){
				fourth = third;
				fourthStudent = thirdStudent;
				third = second;
				thirdStudent = secondStudent;
				second = first;
				secondStudent = firstStudent;
				first = projectxstudent[i][j];
				firstStudent = j;
			}
			else if (projectxstudent[i][j] > second){
				fourth = third;
				fourthStudent = thirdStudent;
				third = second;
				thirdStudent = secondStudent;
				second = projectxstudent[i][j];
				secondStudent = j;
			}
			else if (projectxstudent[i][j] > third){
				fourth = third;
				fourthStudent = thirdStudent;
				third = projectxstudent[i][j];
				thirdStudent = j;
			}
			else if (projectxstudent[i][j] > fourth){
				fourth = projectxstudent[i][j];
				fourthStudent = j;
			}
		} // end student loop
		assignedStudents.push_back(firstStudent);
		assignedStudents.push_back(secondStudent);
		assignedStudents.push_back(thirdStudent);
		assignedStudents.push_back(fourthStudent);
		cout << "p" + to_string(i) + " team members" << endl;
		cout << "1) st" + to_string(firstStudent) + "\t" + to_string(first) << endl;
		cout << "2) st" + to_string(secondStudent) + "\t" + to_string(second) << endl;
		cout << "3) st" + to_string(thirdStudent) + "\t" + to_string(third) << endl;
		cout << "4) st" + to_string(fourthStudent) + "\t" + to_string(fourth) << endl;
		cout << endl;
	}//end project loop

	return 0;
}


