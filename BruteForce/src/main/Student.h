/*
 * Student.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Myles Colina
 *
 *      Description:
 *      Struct header file for use when creating
 *      Student objects.
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <array>

using namespace std;

struct Student {
	int StudentID; //student's ID. unique for each student
	int StID; //ID depicting from [0 - NumOfStudents] in that class section.
	int ClassID; //determines which class the student belongs to.
	int PoolID;//for use in determining index number in StudetsToProjects.
	bool Assigned;  //for use to see if the student is assigned to a project yet.
	int ProjectID; //Value given once the student is assigned to a project.
	int Skills[7]; //stores the 7 skills 0 = none | 1 = some | 2 = average | 3 = proficient | 4 = expert
	double skillAverage; //Average skill of the student, used from skills above

	//[0]PeerID | 0 = negative affinity | 1 = positive affinity
	//COUNT will be the maximum number of peer preferences read in from the JSON file amongst students.
	//2D array: int StudentAffinity[Count][2];
	//pair <int, bool> StudentAffinity[Count];
	vector< pair <int, bool> > StudentAffinity;

	//[0] Primary Weekday | [1] Secondary Weekday | [2] Primary Weekend | [3] Secondary Weekend
	//Possible selections:
	//  |0 = Night-time:   12:00AM - 4:00AM |1 = Early Morning: 4:00AM - 8:00AM |
	//	|2 = Morning:      8:00AM - 12:00PM |3 = Afternoon:    12:00PM - 4:00PM |
	//  |4 = Early Evening: 4:00PM - 8:00PM |5 = Evening:      8:00PM - 12:00AM |
	//Each student chooses four out of the six possible time-frames
	//(two selections for weekday availability; two selections for weekend availability)
	int Availability[4];
	Student(){}
	Student(int stID, int cID, int s[], vector< pair <int, bool> > aff,
            int times[]){

		StudentID = stID;
        ClassID = cID;

        for (int i = 0; i < 7; i++){
        	Skills[i] = s[i];
        }

        for (int i = 0; i < aff.size(); i++){
        	pair <int, bool> x = {aff[i].first, aff[i].second};
        	StudentAffinity.push_back(x);
        }

        for (int i = 0; i < 4; i++){
        	Availability[i] = times[i];
        }
	}

	bool operator==(const Student &studentToCompare) const {
		if(this->StudentID == StudentID) {
			return true;
		} else {
			return false;
		}
	}


};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENT_H_ */

