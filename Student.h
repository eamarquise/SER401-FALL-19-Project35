/*
 * Student.h
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *      Description:
 *      A student class to initialize student objects
 *
 *  Edited on: Oct. 02, 2019
 *  	Author: Elizabeth Marquise
 *  	Description:
 *  	taken from brute.cpp to create individual student.cpp and student.h files
 */

//Early definitions and includes
#ifndef STUDENT_H_
#define STUDENT_H_
#include <string>
#include <vector>


//Main Class
class Student {
public:
	
	//attributes
	string name;
	//skillsScores rank from 0(no knowledge)-4(expert)
	int skillScore1;
	int skillScore2;
	int skillScore3;
	int skillScore4;
	int skillScore5;
	//timezone: 0-pacific, 1-mountain, 2-central, 3-eastern
	int timezone;
	//nline: 0(false)-local student, 1(true)-online student
	bool online;

	//methods
	Student();
	Student(string initName, int ss1, int ss2, int ss3, int ss4, int ss5, int initTimezone, bool initOnlone));

};

#endif /* STUDENT_H_ */
