/*
 * StudentJson.h
 *
 *  Created on: Oct 28, 2019
 *      Author: myles
 */

#ifndef BRUTEFORCE_SRC_MAIN_STUDENTJSON_H_
#define BRUTEFORCE_SRC_MAIN_STUDENTJSON_H_
#include <string>
using namespace std;

class StudentJson {
public:
	StudentJson();
	virtual ~StudentJson();
	void StudentReader(string filename);
	void StudentWriter(string filename);

};

#endif /* BRUTEFORCE_SRC_MAIN_STUDENTJSON_H_ */
