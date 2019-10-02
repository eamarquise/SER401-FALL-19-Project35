/*
 * Project.h
 *
 *  Created on: Sep 30, 2019
 *      Author: sean
 */

#ifndef PROJECT_H_
#define PROJECT_H_
#include <string>
#include <vector>

class Project {
public:
	//attributes
	std::vector<int> students;//students associated with the project
	std::vector<std::string> projectSkills; //skills required by the project
	char priority;//2 is top priority, 1 is medium priority, 0 is low priority

	//methods
	Project(char priorityInitializer, std::vector<std::string> skillsRequired);
	virtual ~Project();
	void addStudent(int studentID);
	void removeStudent(int studentID);
};

#endif /* PROJECT_H_ */
