/*
 * StudentJson.cpp
 *
 *  Created on: Oct 28, 2019
 *      Author: Myles Colina
 *
 *     File revised from archive the file: mainStudent.cpp
 *      Author: Myles Colina
 *
 *
 *      Description:
 *      A class to store all the functions for student Json data.
 *      Includes reading in Student Json Files.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

#include "Student.h"
#include "json/json.h"
#include "StudentJson.h"

using namespace std;

StudentJson::StudentJson() {
	// TODO Auto-generated constructor stub

}

StudentJson::~StudentJson() {
	// TODO Auto-generated destructor stub
}

void StudentJson::StudentWriter(string filename){

	//to be implemented in a later sprint.
}

// Returns a Student object
Student StudentJson::getStudentJsonObject(string filename, int i){

	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	Student student;

	int numSkills = obj["students"].get((int)i, "")["Skills"].size();
	int numTimes = obj["students"].get((int)i, "")["Availability"].size();
	int numAffinities = obj["students"].get((int)i, "")["StudentAffinity"].size();

	student.StudentID = obj["students"].get((int)i, "")["StudentID"].asInt();
	student.ClassID = obj["students"].get((int)i, "")["ClassID"].asInt();

	for(int j = 0; j < numAffinities; j =j+2) {
		pair <int, bool> x = {obj["students"].get((int)i, "")["StudentAffinity"][j].asInt(), obj["students"].get((int)i, "")["StudentAffinity"][j+1].asBool()};
		student.StudentAffinity.push_back(x);
	}

	for(int j = 0; j < numTimes; j++) {
		student.Availability[j] = (char)obj["students"].get((int)i, "")["Availability"][j].asInt();
	}

	for (int j = 0; j < numSkills; j++) {
		student.Skills[j] = (obj["students"].get((int)i, "")["Skills"][j].asInt());
	}

	return student;
}

/*
void StudentJson::StudentReader(string filename){


	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	int StudentID;
    int ClassID;
	int skills[7];
	vector< pair <int, bool> > affinity;
	int times[4];

	int numberOfSkills = 0;
	int numberOfTimes = 0;
	int numberOfAff = 0;

    const Json::Value& numberOfStudents = obj["students"];

    //for loop that iterates of the number of students in the Json file
    //and stores them as Student objects vector <Student> allStudents.
	for(int i = 0; i < numberOfStudents.size(); i++) {

		affinity.clear();
        //reading in Student ID
		StudentID = obj["students"].get((int)i, "")["StudentID"].asInt();

		//reading in Class Id
		ClassID = obj["students"].get((int)i, "")["ClassID"].asInt();

		//reading in Student Skills
		numberOfSkills = obj["students"].get((int)i, "")["Skills"].size();
		for(int j = 0; j < numberOfSkills; j++) {
			skills[j] = (obj["students"].get((int)i, "")["Skills"][j].asInt());
		}

		//reading in Student Affinity
		numberOfAff = obj["students"].get((int)i, "")["StudentAffinity"].size();
	    for(int j = 0; j < numberOfAff; j =j+2) {
	    	pair <int, bool> x = {obj["students"].get((int)i, "")["StudentAffinity"][j].asInt(), obj["students"].get((int)i, "")["StudentAffinity"][j+1].asBool()};
	    	affinity.push_back(x);
		}

		//reading in Availability
		numberOfTimes = obj["students"].get((int)i, "")["Availability"].size();
		for(int j = 0; j < numberOfTimes; j++) {
			times[j] = (char)obj["students"].get((int)i, "")["Availability"][j].asInt();
		}

		//Creating the student, and adding the student to the student list
		Student s(StudentID, ClassID, skills, affinity, times);
		allStudents.push_back(s);

	}
//Json File Reader Test
//*********************************************
	cout <<endl;
    cout<<"STUDENT JSON FILE READER TEST"<<endl;
    cout <<endl;
    cout << "number of Students: " << numberOfStudents.size() << endl;

	//Print out all students
	for(int i = 0; i < allStudents.size(); i++) {
		cout << "Student #" + to_string(i+1)+ " ID: ";
		cout << to_string(allStudents.at(i).StudentID) << endl;
		cout << "Skills: ";
		for(unsigned int j = 0; j < 7; j++) {
				cout << allStudents.at(i).Skills[j];
				cout << " ";
	    }
		cout << endl;
		cout << "Availability: ";
		for (int k = 0; k < 4; k++){
				cout <<  to_string(allStudents.at(i).Availability[k]) ;
				cout << " ";
		}
		cout << endl;
        for (unsigned int x = 0; x < allStudents.at(i).StudentAffinity.size(); x++) {
				cout << "Peer ID: " + to_string(allStudents.at(i).StudentAffinity[x].first) + "  Affinity: " + to_string(allStudents.at(i).StudentAffinity[x].second)<<endl;
				cout << " ";
		}
		cout << endl;
	}
//*********************************************
//End - Json File Reader Test
}*/



