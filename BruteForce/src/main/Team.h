/*
 * Team.h
 *
 *  Created on: Nov 11, 2019
 *      Author: Myles Colina
 *
 *      Description:
 *      STeam header file for use when creating
 *      student team.
 */

#ifndef TEAM_H_
#define TEAM_H_

#include <iostream>
#include <utility>
#include <string>
#include <array>
#include "Student.h"


using namespace std;

//template<int teamsize>
struct Team {

	Student team[5]; //stores the student teams
	int TeamScore; //stores the team's score

	Team(){}

};

#endif /* TEAM_H_ */
