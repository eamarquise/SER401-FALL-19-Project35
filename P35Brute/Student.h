/*
 * Affinity.cpp
 * Description:
 * 		A Class to describe project/student skills
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

class Student {
	public:

		//Variables
		std::string name;	//Student name
		Skills studentSkills;	//Student skills
		PreferredMeetingTimes timesAvailable;	//Meetingtimes
		Affinity affinity;	//Work with someone or not
		bool online;	//Online student:  0(false)-local student, 1(true)-online student

		Student();

		Student(std::string n, Skills s, PreferredMeetingTimes times, Affinity aff, bool online);

		bool operator==(const Student &studentToCompare) const;

		bool operator==(const Student *studentToCompare) const;

};

#endif /* STUDENT_H_ */
