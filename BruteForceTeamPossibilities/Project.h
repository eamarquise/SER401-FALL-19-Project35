/*
 * Project.h
 * Description:
 * 		A Class to describe projects & related
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 */

#ifndef PROJECT_H_
#define PROJECT_H_
#include <string>
#include <vector>
#include "Skills.h"
#include "Team.h"

using namespace std;
class Project {
	public:

		//Variables
		std::string name;	//Project name
		int pId;        //Project id
		bool online;		//Online project or not  0(false)-local student, 1(true)-online student
		Skills projectSkills;	//Project skills 0(no knowledge)-4(expert)

		//stores all the possible teams for this project.
		vector <Team> teams;

		//Methods
		Project();
		Project(std::string n, int id, Skills s, bool o);
		bool operator==(const Project &projectToCompare) const;

};

#endif /* PROJECT_H_ */
