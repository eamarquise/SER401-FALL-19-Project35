/*
 * Team1.cpp
 *
 *  Created on: Oct 17, 2019
 *      Author: mcolina
 *      Name: Myles Colina
 */

#include "Team.h"



Team::Team(int id, int pId ){
	this->teamID= id;
	this->projectID= pId;
	this->teamScore=0;
}

bool Team::operator==(const Team &teamToCompare) const {
	if(this->teamID==teamToCompare.teamID == 0) {
		return true;
	} else {
		return false;
	}
}

