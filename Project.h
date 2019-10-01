/*
 * Project.h
 *
 *  Created on: Sep 30, 2019
 *      Author: sean
 */

#ifndef PROJECT_H_
#define PROJECT_H_

class Project {
	int PROJECT_SKILLS_LENGTH; //will be initialized by an argument and will be used to initialize the skills required array
	int STUDENTS_LENGTH; //will be initialized to 5 because projects can only have 5 students max
	int* projectSkills; //this will point to an array of all the skills required.
	int* students; //this will point to an array of the ID of each student that matches with this project
public:
	Project(int projectSkillsLength);
	virtual ~Project();
};

#endif /* PROJECT_H_ */
