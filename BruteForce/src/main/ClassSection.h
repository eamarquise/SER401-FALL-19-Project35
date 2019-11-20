/*
 * ClassSection.h
 *
 * Description:
 * Student to project allocation requires a model of a class or section
 * that a student would be assigned to and a project would be available in.
 * The ClassSection allows for student and project population partitioning
 * which greatly reduces complex combination calculations. Unique identifiers
 * are captured, such as the ClassID, and relational attributes are defined,
 * such as the Type, that will help identify projects available for each
 * instance of a ClassSection.
 *
 *
 *  Created on: Oct 27, 2019
 *      Author: Myles Colina & Fall 2019 SER401 Team35
 */

#ifndef CLASSSECTION_H_
#define CLASSSECTION_H_

struct ClassSection {
	int ClassID;	// Unique integer that identifies each unique instance of a ClassSection.
	char Type;  	// Some ClassSections are dedicated to online or local students to the univerisity. Type is defined as: O = online | G = ground
	int Enrollment;	// Common integer depicting the number of students enrolled in the instance of a ClassSection.

	ClassSection(){}
	ClassSection(int cID, char t){
		ClassID = cID;
		Type = t;
	}
};

#endif
