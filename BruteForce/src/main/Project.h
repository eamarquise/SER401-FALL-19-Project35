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
	int ProjectID; 	//Project Id. unique for each project.
	int ClassID; 	//value determined when project is assigned to a class section.
	char Type;  	//O = online | G = ground | H = hybrid
	int Priority;	// 0 = does not have to be assigned | 1 = preferred to be assigned | 2 = must be assigned
	int Skills[7]; 	//for each skill, 0 = not required | 1 = nice to have skill | 2 = required skill
	Project(){}

	//Constructor
	Project(int pID, char t, int priority, int pskills[]){

		ProjectID = pID;
		Type = t;
		Priority = priority;
		for (int i = 0; i < 7; i++){
		      Skills[i] = pskills[i];
		}
	}
};

#endif /* BRUTEFORCE_SRC_MAIN_PROJECT_H_ */
