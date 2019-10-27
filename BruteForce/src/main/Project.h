/*
 * Project.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Myles Colina
 *
 *      Description:
 *      Struct header file for use when creating
 *      Project objects.
 */

#ifndef BRUTEFORCE_SRC_MAIN_PROJECT_H_
#define BRUTEFORCE_SRC_MAIN_PROJECT_H_
#include <array>

struct Project
{
	int ProjectID; //Project Id. unique for each project.
	int ClassID; //value determined when project is assigned to a class section.
	char Type;  //O = online | G = ground | H = hybrid
	// 0 = does not have to be assigned | 1 = preferred to be assigned | 2 = must be assigned
	int Priority;
	int Skills[7]; //for each skill, 0 = not required | 1 = nice to have skill | 2 = required skill
};

#endif /* BRUTEFORCE_SRC_MAIN_PROJECT_H_ */
