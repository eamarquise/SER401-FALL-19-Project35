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

#include "Student.h"

Student::Student(std::string n, Skills s, PreferredMeetingTimes times, Affinity aff, bool online){
	this->name = n;
	this->timesAvailable = times;
	this->online = online;
	this->studentSkills = s;
	this->affinity = aff;
}

bool Student::operator==(const Student &studentToCompare) const {
	if(this->name.compare(studentToCompare.name) == 0) {
		return true;
	} else {
		return false;
	}
}

bool Student::operator==(const Student *studentToCompare) const {
	if(this->name.compare(studentToCompare->name) == 0) {
		return true;
	} else {
		return false;
	}
}

