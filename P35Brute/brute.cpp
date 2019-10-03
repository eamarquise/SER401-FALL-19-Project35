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

// Contains Function
// function to check if a vector contains a certain int as an element.
// returns true or false
bool contains(vector<int> v, int x){
	return ! (v.empty() || find(v.begin(), v.end(), x) == v.end());
}

// SearchVector Function - need to test!
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
	return returnValue;
}

// Role Function
// will roll a random number between the min and max
// will use this to create random Students and Projects.
int roll(int min, int max){
	int value = rand() % (max-min +1) + min;
	return value;
}
class Skills {
public:
	vector<int> skillScoreArray;
};

class Student {
	public:
		string name;
		// timezone: 0-pacific, 1-mountain, 2-central, 3-eastern
		int timezone;
		// online: 0(false)-local student, 1(true)-online student
		bool online;
		// studentSkills has an vector to store skillScores
		// skillsScores rank from 0(no knowledge)-4(expert)
		Skills studentSkills;

		Student();
		Student(string n, Skills s, int tz, bool o){
			this->name = n;
			this->timezone = tz;
			this->online = o;
			this->studentSkills = s;
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

int main(){
	cout << "brute force project x student matrix application for student-project team allocation" << endl;
	cout << "************************************************************************************" << endl;

	// Important numbers
	int numStudents = 20;
	int numProjects = 4;
	int numSkills = 5;
	// teamSize can be used after we figure out how to build teams recursively.
	// int teamSize = 4;
	srand(time(0));

	cout << "testing randomly generated students and projects" << endl;
	cout << endl;
	StudentList studentList2; // using randomly generated students
	ProjectList projectList2; // using randomly generated projects

	// Create randomly generated Students and put them in
	// StudentList2
	for (int i = 0; i < numStudents ; i++){
		string studentName = "st" + to_string(i);
		Skills tempSkills;
		for (int j = 0 ; j < numSkills; j++){
			int skillScore = roll(0, 4);
			tempSkills.skillScoreArray.push_back(skillScore);
		}
		int skillScore1 = roll(0, 4);
		int skillScore2 = roll(0, 4);
		int skillScore3 = roll(0, 4);
		int skillScore4 = roll(0, 4);
		int skillScore5 = roll(0, 4);
		int timezone = roll(0,3);
		bool online = (bool)roll(0,1);
		Student tempStudent(studentName, tempSkills, timezone, online);
		studentList2.allStudentList.push_back(tempStudent);
	}

	// Create randomly generated Projects and put them in
	// ProjectList2
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

	// display random students for testing can delete later
	cout << endl << "Random students in studentList2" << endl;
	for (int i = 0; i < (signed)studentList2.allStudentList.size(); i++){
		string studentString = studentList2.allStudentList.at(i).name + "\t";
		for (int j = 0; j < numSkills; j++){
			studentString += "Skill" + to_string(i)+ ": " + to_string(studentList2.allStudentList.at(i).studentSkills.skillScoreArray.at(j)) + "\t";
		}
		studentString += "TimeZone: " + to_string(studentList2.allStudentList.at(i).timezone) + "\t";
		studentString += "Online: " + to_string(studentList2.allStudentList.at(i).online);
		cout << studentString << endl;
	}

	// display random projects for testing can delete later
	cout << endl << "Random projects in projectList2" << endl;
	for (int i = 0; i < (signed)projectList2.allProjectList.size(); i++){
		string projectString = projectList2.allProjectList.at(i).name + "\t";
		for (int j = 0; j < numSkills; j++){
			projectString += "Skill" + to_string(i)+ ": " + to_string(projectList2.allProjectList.at(i).projectSkills.skillScoreArray.at(j)) + "\t";
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
		for (int j = 0; j < (signed)studentList2.allStudentList.size(); j++){
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
	int projectxstudent[numProjects][numStudents];
	// porjectxstudent2 is keeping track of the randomized students and projects
	int projectxstudent2[numProjects][numStudents];

	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		string p = to_string(rows);
		cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectxstudent[rows][cols] = {0};
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

	// assignedStudents will keep track of students that have already been selected for a project.
	// each element is a student name (ie for st12, it would be 12)
	vector<int> assignedStudents;

	// firstStudent, secondStudent, thirdStudent, and fourthStudent will be Student name.
	// 1 will be for st1, 12 for st12
	// first, second, third, and fourth will store the values of the 4 highest scoring students per project.
	// Students already selected for a previous project will be omitted.
	int firstStudent, secondStudent, thirdStudent, fourthStudent, fifthStudent;
	int first, second, third, fourth, fifth;

	// For each project
	for (int i = 0; i < numProjects; i++){
		firstStudent = secondStudent = thirdStudent = fourthStudent = fifthStudent = first = second = third = fourth = fifth = -1;
		// For each Student
		for (int j = 0 ; j < numStudents; j++){
			// check if student on this iteration has already been assigned to a project
			// if so, go to next student.
			//pair<bool,int> searchResult = searchVector(studentList2.assignedStudentList, studentList2.allStudentList.at(j));
			//if (searchResult.first){
			//	continue;
			//}
			if (contains(assignedStudents, j) == true){
				continue;
			}
			// check if the current iteration's project is local and if the current student is online.
			// if project local and student is online, go to next student.
			// presumption that an online project can be accomplished by local students too.
			if (projectList2.allProjectList.at(i).online == true && studentList2.allStudentList.at(j).online == true){
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

		// need to get searchVector method working right so we can even check this vector during the iterations for matches.
		// then we can uncomment this and delete the following lines using assignedStudents
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(firstStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(secondStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(thirdStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(fourthStudent));
//		studentList2.assignedStudentList.push_back((Student)studentList2.allStudentList.at(fifthStudent));

		assignedStudents.push_back(firstStudent);
		assignedStudents.push_back(secondStudent);
		assignedStudents.push_back(thirdStudent);
		assignedStudents.push_back(fourthStudent);
		assignedStudents.push_back(fifthStudent);

		cout << "p" + to_string(i) + " team members" << endl;
		cout << "1) " + studentList2.allStudentList.at(firstStudent).name + "\t" + to_string(first) << endl;
		cout << "2) " + studentList2.allStudentList.at(secondStudent).name + "\t" + to_string(second) << endl;
		cout << "3) " + studentList2.allStudentList.at(thirdStudent).name + "\t" + to_string(third) << endl;
		cout << "4) " + studentList2.allStudentList.at(fourthStudent).name + "\t" + to_string(fourth) << endl;
		cout << "5) " + studentList2.allStudentList.at(fifthStudent).name + "\t" + to_string(fifth) << endl;
		cout << endl;

	}//end project loop

	return 0;
}


