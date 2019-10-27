//============================================================================
// Name        : StudentJsonCreator.cpp
// Author      : Sean Rogers
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <time.h>

using namespace std;

//creates a vector with user defined size and size of a random set of integers. All elements in the vector are unique
vector<int> writeVector(int size, int randSize) {
	vector<int> vec;
	if(randSize < size) {
		cout << "First parameter must be smaller than second parameter" << endl;
		return vec;
	}
	bool found;
	int i = 0;
	while(i < size) {
		int randomNum = rand() % randSize;
		found = false;
		for(unsigned int j = 0; j < vec.size(); j++) {
			if(vec.at(j) == randomNum) {
				found = true;
			}
		}
		if(!found) {
			vec.push_back(randomNum);
			i++;
		}
	}
	return vec;
}

// creates numFiles number of student json files and numStudents number of students in each file
void jsonWriteStudents(int numStudents, int numFiles){
	ofstream file_id;
	string fileName = "studentsAuto";
	string fileX = "0";
	string fileExtension = ".json";


	vector<int> vector;
	string studentName;
	string otherStudentName;
	string otherStudentNumber;

	int numOfAffinities = 0;
	srand(time(NULL));

	//Declare Json Values obj, student, students, and skills
	Json::Value obj;
	Json::Value student;
	Json::Value students(Json::arrayValue);
	Json::Value skills(Json::arrayValue);
	Json::Value preferredmeetingtimes(Json::arrayValue);
	Json::Value affinity(Json::arrayValue);

	//create numFiles amount of json files
	for(int h = 0; h < numFiles; h++) {
		fileX = to_string(h);
		file_id.open(fileName + fileX + fileExtension);

	//create  different Json::Value student with random values for their attributes.
	for(int i = 0; i < numStudents; i++) {
		for(int j = 0; j < 6; j++) {
			skills.append(rand() % 5);
		}

		int meetingTimesRand = rand() % 5 + 1;
		vector = writeVector(meetingTimesRand, 7);
		for(unsigned int j = 0; j < vector.size(); j++) {
			preferredmeetingtimes.append(vector.at(j));
		}

		//todo for the current student being generated, assign affinity to a random list of students
		numOfAffinities = rand() % 10;
		while(numOfAffinities > numStudents) {
			numOfAffinities = rand() % 10;
		}
		vector = writeVector(numOfAffinities, numStudents);
		for(int j = 0; j < numOfAffinities; j++) {
			otherStudentName = "First";
			otherStudentNumber = to_string(rand() % 100);
			otherStudentName.append(otherStudentNumber);
			otherStudentName.append(" Last");
			otherStudentName.append(otherStudentNumber);
			affinity.append(otherStudentName);
		}

		//assign the student's name
		studentName = "First";
		studentName.append(to_string(i+1));
		studentName.append(" Last");
		studentName.append(to_string(i+1));

		//assign name, skills, meeting times, affinity, and online to Json::Value student
		student["name"] = studentName;
		student["skills"] = skills;
		student["preferredmeetingtimes"] = preferredmeetingtimes;
		student["affinity"] = affinity;
		student["online"] = rand() % 3;

		//put student in students then start over
		students.append(student);
		skills.clear();
		preferredmeetingtimes.clear();
		affinity.clear();
	} //end i loop
	obj["students"] = students;




	Json::StyledWriter styledWriter;
	file_id << styledWriter.write(obj);
	file_id.close();
	} //end h loop

}

int main() {
	jsonWriteStudents(30, 20);
	return 1;

}
