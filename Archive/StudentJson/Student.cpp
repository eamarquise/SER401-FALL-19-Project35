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
 *
 *
 *   Edited on: Oct. 10, 2019
 *      Author: mcolina
 */

#include "Student.h"
#include "json/json.h"

Student::Student(std::string n, vector <string> s, vector <int> times, vector <string> aff, bool online){
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

