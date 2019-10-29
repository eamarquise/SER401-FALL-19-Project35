/*
 * StudentJson.cpp
 *
 *  Created on: Oct 28, 2019
 *      Author: Myles Colina
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
#include "Student.h"
#include "json/json.h"
#include "StudentJson.h"
//#include "Global.h"

using namespace std;

StudentJson::StudentJson() {
	// TODO Auto-generated constructor stub

}

StudentJson::~StudentJson() {
	// TODO Auto-generated destructor stub
}

void StudentJson::StudentWriter(string filename){

}

void StudentJson::StudentReader(string filename){


	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	//variable to store all students
	vector<Student> allStudents;

	//int NumOfClassSections = 1;
	//vector<vector<Student>> studentsInClass(NumOfClassSections);

	int StudentID;
    int ClassID;
	int skills[7];
	vector< pair <int, bool> > affinity;
	int times[4];


	int numberOfSkills = 0;
	int numberOfTimes = 4;
	int numberOfAff = 0;

	cout <<endl;
	cout<<"STUDENT JSON FILE READER TEST"<<endl;
    const Json::Value& numberOfStudents = obj["students"];
    cout <<endl;
    cout << "number of Students: " << numberOfStudents.size() << endl;

    //for loop that iterates of the number of students in the Json file
    //and stores them as Student objects in a student list.
	for(int i = 0; i < numberOfStudents.size(); i++) {

		affinity.clear();
        //reading in Student ID
		StudentID = obj["students"].get((int)i, "")["StudentID"].asInt();

		//reading in Class Id
		ClassID = obj["students"].get((int)i, "")["ClassID"].asInt();

		//reading in student skills
		numberOfSkills = obj["students"].get((int)i, "")["Skills"].size();
		for(int j = 0; j < numberOfSkills; j++) {
			skills[j] = (obj["students"].get((int)i, "")["Skills"][j].asInt());
		}

		//reading in Availability
		for(int j = 0; j < numberOfTimes; j++) {
			times[i] = (obj["students"].get((int)i, "")["Availability"][j].asInt());
		}

		//reading in student affinity
	    numberOfAff = obj["students"].get((int)i, "")["affinity"].size();
		for(int j = 0; j < numberOfAff; j =j+2) {
			pair <int, bool> x = {obj["students"].get((int)i, "")["StudentAffinity"][j].asInt(), obj["students"].get((int)i, "")["StudentAffinity"][j+1].asBool()};
		    affinity.push_back(x);
				}

		//adding the student to the student list
		Student s(StudentID, ClassID, skills, affinity, times);
		allStudents.push_back(s);

	}

	//Print out all student Ids.
	for(int i = 0; i < allStudents.size(); i++) {
		cout << "Student #" + to_string(i+1)+ " ID: ";
					cout << to_string(allStudents.at(i).StudentID) << endl;
	}


/*
	//put the students into different class sections
    int x=0;
    Student prev, current, next;
    prev = allStudents[0];
	while(x < NumOfClassSections){


	for(int i = 0; i < allStudents.size(); i++) {

	current = allStudents[i];
	//next = allStudents[i+1];
	if(i+1 != allStudents.size()+1){
		if(current.ClassID == prev.ClassID){
		studentsInClass[x].push_back(allStudents[i]);}
		else{
			x++;
		}
		prev = allStudents[i];

	}
	}
	}*/

}



