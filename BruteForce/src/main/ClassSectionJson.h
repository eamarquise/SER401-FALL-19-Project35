/*
 * ClassSectionJson.h
 *
 *  Created on: 11/06/2019
 *      Author: Cristi DeLeo
 */

#ifndef CLASSSECTIONJSON_H_
#define CLASSSECTIONJSON_H_

#include "ClassSection.h"

#include <string>

using namespace std;

class ClassSectionJson {
    public:
        ClassSectionJson();
        void ClassSectionWriter(string filename);
        ClassSection getClassSectionJsonObject(string filename, int i);
        ~ClassSectionJson();
};

#endif /* BRUTEFORCE_SRC_MAIN_CLASSSECTIONJSON_H_ */
