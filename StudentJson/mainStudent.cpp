/*
 * 	mainStudent.cpp
 *
 *  Created on: Oct. 6, 2019
 *      Author: Myles Colina
 *      Github username: mcolina
 *
 *      Description:
 *      A main class to read in student data from a Json file.
 *
 */

#include <iostream>
#include "StudentList.h"
#include "dist/json/json.h"

//#include "student.h"

using namespace std;


int main(){

	//load in the data from a Json file
	StudentList student_list;
	student_list.JsonLoad2("nameofstudentfile.json");



	//not really needed
	//write the data to a json file
	student_list.JsonSave("studentlist.json");

}
