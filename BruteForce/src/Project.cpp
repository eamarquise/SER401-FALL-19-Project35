/*
 * Project.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#include "Project.h"
#include "Utilities.h"

#include <algorithm>

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


void Project::swapProjects(Project* p1, Project* p2) {
	Project* tempP = p1;
	p1 = p2;
	p2 = tempP;
}





void Project::projectTypePartition(Project arr[], int n, int lowVal, int highVal) {
    int start = 0;
    int end = n - 1;

    for (int i = 0; i <=end; ) {
        if (arr[i].type < lowVal) {
        	swapProjects(&arr[i++], &arr[start++]);
        } else if (arr[i].type > highVal) {
        	swapProjects(&arr[i], &arr[end--]);
        } else {
            i++;
        };
    }
}

