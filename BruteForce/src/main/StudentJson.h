/*
 * StudentJson.h
 *
 *  Created on: Oct 28, 2019
 *      Author: myles
 */

#ifndef BRUTEFORCE_SRC_MAIN_STUDENTJSON_H_
#define BRUTEFORCE_SRC_MAIN_STUDENTJSON_H_

#include <string>
#include "Student.h"

using namespace std;

class StudentJson {
public:
	vector <Student> allStudents;
	StudentJson();
	virtual ~StudentJson();
	int StudentReader(string filename);
	void StudentWriter(string filename);
	Student getStudentJsonObject(string filename, int i);
};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTJSON_H_ */
