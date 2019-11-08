/*
 * ClassSection.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Myles Colina
 *
 *      Description:
 *      Struct header file for use when creating
 *      Class Section objects.
 */

#ifndef CLASSSECTION_H_
#define CLASSSECTION_H_

struct ClassSection {
	int ClassID;
	char Type;  // O = online | G = ground
	int Enrollment;

	ClassSection(){}
	ClassSection(int cID, char t){
		ClassID = cID;
		Type = t;
	}
};

#endif
