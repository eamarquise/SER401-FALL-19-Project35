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

template <int NumStudents, int NumProjects>
struct ClassSection
{
	int ClassSectionID; //Class section Id. unique for each class.
	char Type;  //O = online | G = ground
	int Enrollment[NumStudents]; //number of students enrolled in the class section.
	int ProjectPool[NumProjects]; //Projects available to the class section
};


#endif /* BRUTEFORCE_SRC_MAIN_CLASSSECTION_H_ */
