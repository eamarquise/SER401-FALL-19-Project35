/*
 * Team1.h
 *
 *  Created on: Oct 17, 2019
 *      Author: mcolina
 *      Name: Myles Colina
 */

#ifndef TEAM_H_
#define TEAM_H_
#include <string.h>
#include <vector>
#include "Student.h"

using namespace std;
class Team {
public:
		//Variables
			vector <Student> team;
			vector <int> studentIDs;
			int teamID;
			int projectID;
			int teamScore;	//Project skills 0(no knowledge)-4(expert)

		//Methods

		Team(int id, int pId );
		bool operator==(const Team &teamToCompare) const;

};

#endif /* PROJECT_H_ */
