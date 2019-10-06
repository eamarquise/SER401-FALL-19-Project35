/*
 * Affinity.cpp
 * Description:
 * 		A Class to describe project/student skills
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 */

#ifndef AFFINITY_H_
#define AFFINITY_H_

#include <vector>
#include <string>

class Affinity {
public:
	std::vector<std::string> preferredStudents;
	std::vector<std::string> avoidedStudents;
	Affinity();
	virtual ~Affinity();
};

#endif /* AFFINITY_H_ */
