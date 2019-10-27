/*
 * Project.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#include "Project.h"

Project::Project(){
	id = 0;
	sponsorID = 0;
	type = 0; // 0 = Online | 1 = Ground | 2 = Hybrid
	priority = 0; // 0 = Not Required | 1 = Required
	classID = 0;
	//int skills[NUM_SKILLS];
	//int* teamMembers[TEAM_SIZE];
	compatibilityRating = 0;
}


