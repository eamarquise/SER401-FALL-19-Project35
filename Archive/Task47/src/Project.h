/*
 * Project.h
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#ifndef PROJECT_H_
#define PROJECT_H_

class Project {
	public:
		int id;
	    int sponsorID;
	    int type; // 0 = Online | 1 = Ground | 2 = Hybrid
	    int priority; // 0 = Not Required | 1 = Required
	    int* classID;
	    //int skills[NUM_SKILLS];
	    //int* teamMembers[TEAM_SIZE];
	    int compatibilityRating;

	    Project();
	    Project(int projID, int spID, int t, int p, int* clID, int cRating);
};

#endif /* PROJECT_H_ */
