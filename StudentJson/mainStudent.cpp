/*
 * 	mainStudent.cpp
 *
 *  Created on: Oct. 6, 2019
 *      Author: Myles Colina
 *      Github username: mcolina
 *
 *
 *
 *      Description:
 *      A main class to read in a student data from a Json file.
 *      Modified to use the same process as the project Json file reader
 *      in SecondProject.cpp by SeanRog
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Student.h"
#include "json/json.h"



using namespace std;

//function to print the list of students
void printStudentList (vector <Student> &studentlist){


	for(int i = 0; i < studentlist.size(); i++) {
	cout << "Student ";
			cout << studentlist.at(i).name << endl;
			cout << "Skills: ";
			for (unsigned int j = 0; j < studentlist.at(i).studentSkills.size(); j++) {
				cout << studentlist.at(i).studentSkills.at(j);
				cout << " ";
			}
			cout << endl;
			cout << "Preferred Meeting Times: ";
						for (unsigned int j = 0; j < studentlist.at(i).timesAvailable.size(); j++) {
							cout << studentlist.at(i).timesAvailable.at(j);
							cout << " ";
			}
			cout << endl;
			cout << "Affinity: ";
			for (unsigned int j = 0; j < studentlist.at(i).affinity.size(); j++) {
							cout << studentlist.at(i).affinity.at(j);
							cout << " ";
			}
			cout << endl;
			cout << "Online: ";
			cout << studentlist.at(i).online << endl;

			cout << endl;
		}
}



int main(){

		ifstream ifs("students.json");
		Json::Reader reader;
		Json::Value obj;
		reader.parse(ifs, obj);

		vector<Student> studentlist;
		string name;
		vector<string> skills;
		vector<string> affinity;
		vector<int> timesAvailable;
		bool online;

		int numberOfSkills = 0;
		int numberOfTimes = 0;
		int numberOfAff = 0;


        const Json::Value& numberOfStudents = obj["students"];
        cout << "number of Students: " << numberOfStudents.size() << endl;

        //for loop that iterates of the number of students in the Json file
        //and stores them as Student objects in a student list.
		for(int i = 0; i < numberOfStudents.size(); i++) {
			skills.clear();
			affinity.clear();
			timesAvailable.clear();

			name = obj["students"].get((int)i, "")["name"].asString();

			numberOfSkills = obj["students"].get((int)i, "")["skills"].size();
			for(int j = 0; j < numberOfSkills; j++) {
				skills.push_back(obj["students"].get((int)i, "")["skills"][j].asString());

			}

			numberOfTimes = obj["students"].get((int)i, "")["preferredmeetingtimes"].size();
					for(int j = 0; j < numberOfTimes; j++) {
						timesAvailable.push_back(obj["students"].get((int)i, "")["preferredmeetingtimes"][j].asInt());

					}

		    numberOfAff = obj["students"].get((int)i, "")["affinity"].size();
					for(int j = 0; j < numberOfAff; j++) {
						 affinity.push_back(obj["students"].get((int)i, "")["affinity"][j].asString());

					}


			online = obj["students"].get((int)i, "")["online"].asBool();

			//adding the student to the student list
			Student s(name, skills, timesAvailable, affinity, online);
			studentlist.push_back(s);

		}
    //call to print function
	printStudentList(studentlist);

	return 1;
}
