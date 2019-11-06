/*
 * ClassSectionJson.h
 *
 *  Created on: 11/06/2019
 *      Author: Cristi DeLeo
 */

#ifndef BRUTEFORCE_SRC_MAIN_CLASSSECTIONJSON_H_
#define BRUTEFORCE_SRC_MAIN_CLASSSECTIONJSON_H_

#include "ClassSection.h"

#include <string>

using namespace std;

class ClassSectionJson {
    public:
        ClassSectionJson();
        virtual ~ClassSectionJson();
        void ClassSectionWriter(string filename);
        ClassSection getClassSectionJsonObject(string filename, int i);
};

#endif /* BRUTEFORCE_SRC_MAIN_CLASSSECTIONJSON_H_ */
