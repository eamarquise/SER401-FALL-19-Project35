/*
 * Student.cpp
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *      Description:
 *      A student class to initialize student objects
 *    
 *  Edited on: Oct. 02, 2019
 *  	Author: Elizabeth Marquise
 *  	Description:
 *  	taken from brute.cpp to create indiviudal student.cpp and student.h files
 */

#include "Student.h"
#include <iostream>
#include <string>
using namespace std;

Student::Student(string n, int ss1, int ss2, int ss3, int ss4, int ss5, int tz, bool o){
	this->name = n;
	this->skillScore1 = ss1;
	this->skillScore2 = ss2;
	this->skillScore3 = ss3;
	this->skillScore4 = ss4;
	this->skillScore5 = ss5;
	this->timezone = tz;
	this->online = o;


