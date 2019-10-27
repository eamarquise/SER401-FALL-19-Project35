/*
 * Student.h
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
#ifndef STUDENT_H_
#define STUDENT_H_
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include "json/json.h"

using namespace std;
class Student {
	public:

		//Variables
		std::string name;	//Student name
		vector <string> studentSkills;	//Student skills
		vector <int> timesAvailable;	//Meetingtimes
		vector <string> affinity;	//Work with someone or not
		bool online;	//Online student:  0(false)-local student, 1(true)-online student

		Student();
		Student(std::string n, vector <string> s, vector <int> times, vector <string> aff, bool online);
		bool operator==(const Student &studentToCompare) const;
		bool operator==(const Student *studentToCompare) const;

};

#endif /* STUDENT_H_ */
