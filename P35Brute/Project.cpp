/*
 * Project.cpp
 * Description:
 * 		A Class to describe projects & related
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 */

#include "Project.h"

Project::Project(std::string n, Skills s, bool o){
	this->name = n;
	this->online = o;
	this->projectSkills = s;
}

bool Project::operator==(const Project &projectToCompare) const {
	if(this->name.compare(projectToCompare.name) == 0) {
		return true;
	} else {
		return false;
	}
}

