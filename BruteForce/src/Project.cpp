/*
 * Project.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#include "Project.h"
#include "Utility.h"

extern int NUM_PROJECTS;

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

Project::initializeProjectPool(Project pool[]) {
	Project project;

	for (int i = 0; i < NUM_PROJECTS; i++)
	{
	    project.id = i + 1; // Sequentially assigns Project ID
	    project.sponsorID = getRandomInt(1, (NUM_PROJECTS + 1));
	    project.type = getRandomInt(0, 2);
	    project.priority = getRandomInt(0, 1);

	    pool[i] = project;
	}
}


