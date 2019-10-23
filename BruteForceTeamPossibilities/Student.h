/*
 * Student.cpp
 * Description:
 * 		A Class to describe students & related
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include <string.h>
#include "Skills.h"
#include "PreferredMeetingTimes.h"
#include "Affinity.h"

using namespace std;
class Student {
	public:

		//Variables
		std::string name;	//Student name
		int sId;	//Student id
		Skills studentSkills;	//Student skills
		PreferredMeetingTimes timesAvailable;	//Meetingtimes
		Affinity affinity;	//Work with someone or not
		bool online;	//Online student:  0(false)-local student, 1(true)-online student
		vector <int> skillScores;

		Student();
		Student(std::string n, int Id, Skills s, PreferredMeetingTimes times, Affinity aff, bool online, vector <int> skillsList);
		bool operator==(const Student &studentToCompare) const;
		bool operator==(const Student *studentToCompare) const;

};

#endif /* STUDENT_H_ */
