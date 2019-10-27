/*
 * ProjectGroup.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: myles
 */

#include "ProjectGroup.h"


	ProjectGroup::ProjectGroup(int x){
    //default value
		this->pgroupId = x;
		this->groupScore = 0;
	}

bool ProjectGroup::operator==(const ProjectGroup &projectgroupToCompare) const {
	if(this->pgroupId == projectgroupToCompare.pgroupId) {
		return true;
	} else {
		return false;
	}
}
