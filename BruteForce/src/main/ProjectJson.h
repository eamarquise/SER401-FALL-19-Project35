/*
 * ProjectJson.h
 *
 *  Created on: Oct 29, 2019
 *      Author: myles
 */

#ifndef BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_
#define BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_
#include <string>
using namespace std;

class ProjectJson {
public:
	ProjectJson();
	virtual ~ProjectJson();
	void ProjectReader(string filename);
    void ProjectWriter(string filename);
};

#endif /* BRUTEFORCE_SRC_MAIN_PROJECTJSON_H_ */
