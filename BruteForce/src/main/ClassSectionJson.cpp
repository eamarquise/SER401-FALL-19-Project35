/****************
* ClassSectionJson.cpp
*
*Author(s) Myles Colina
*
*Description: (what the class does) - A class to store all the functions for student Json data.
*      Includes reading in Student Json Files.
*
* ClassSectionWriter(string filename) - to be implemented in a later sprint.
*
* getClassSectionJsonObject(string filename, int i) - Reads in a json file pertaining to class sections.
* Retrieves the class section in the json file at index int i.
* Stores that information into a ClassSection instance.
* Returns that instance.
*
*/

#include "ClassSectionJson.h"
#include "ClassSection.h"
#include "json/json.h"

#include <fstream>
#include <string>
#include <vector>

ClassSectionJson::ClassSectionJson() {
	// TODO Auto-generated constructor stub
}

ClassSectionJson::~ClassSectionJson() {
	// TODO Auto-generated destructor stub
}

void ClassSectionJson::ClassSectionWriter(string filename){
	//to be implemented in a later sprint.
}

/*********************
* getClassSectionJsonObject(string filename, int i)
*
* Description:
* Reads in a json file pertaining to class sections.
* Retrieves the class section in the json file at index int i.
* Stores that information into a ClassSection instance.
* Returns that instance.
*
*Arguments:
*	string filename, int i
*
*Returns:
*	ClassSection classSection
*
*/
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
            (char)obj["class sections"].get((int)i, "")["ClassID"].asInt();

	return classSection;
}
