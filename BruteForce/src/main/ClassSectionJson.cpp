/*
 * ClassSectionJson.cpp
 *
 *  Created on: Oct 28, 2019
 *  Author: Myles Colina
 *
 *  File revised from archive the file: mainStudent.cpp
 *  Author: Myles Colina
 *
 *
 *  Description:
 *      A class to store all the functions for student Json data.
 *      Includes reading in Student Json Files.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <utility>
#include <algorithm>

#include "ClassSection.h"
#include "json/json.h"
#include "ClassSectionJson.h"

using namespace std;

ClassSectionJson::ClassSectionJson() {
	// TODO Auto-generated constructor stub
}

ClassSectionJson::~ClassSectionJson() {
	// TODO Auto-generated destructor stub
}

void ClassSectionJson::ClassSectionWriter(string filename){
	//to be implemented in a later sprint.
}

// Returns a Class Section object
ClassSection ClassSectionJson::getClassSectionJsonObject(string filename, int i){
	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	ClassSection classSection;

    string tempType;
	tempType = obj["class sections"].get((int)i, "")["Type"].asString();

    classSection.Type = tempType[0];
    classSection.ClassID =
            obj["class sections"].get((int)i, "")["ClassID"].asInt();

    ifs.close();

	return classSection;
}
