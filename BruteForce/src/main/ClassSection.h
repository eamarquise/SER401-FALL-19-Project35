/*
 * ClassSection.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Myles Colina
 *
 *      Description:
 *      Struct header file for use when creating
 *      Class Section objects.
 */

#ifndef BRUTEFORCE_SRC_MAIN_CLASSSECTION_H_
#define BRUTEFORCE_SRC_MAIN_CLASSSECTION_H_
#include <array>
#include <vector>

template <int NumStudents>
struct ClassSection
{
	int ClassSectionID; //Class section Id. unique for each class.
	char Type;  //O = online | G = ground
	//int Enrollment[]; //number of students enrolled in the class section.
	//int ProjectPool[]; //Projects available to the class section
	//vector <int> ProjectPool; //Projects available to the class section

	ClassSection(int cID, char t){
		ClassSectionID = cID;
		Type = t;
	}

};


#endif /* BRUTEFORCE_SRC_MAIN_CLASSSECTION_H_ */
