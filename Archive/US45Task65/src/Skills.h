/*
 * Skills.h
 * Description:
 * 		A Class to describe project/student skills
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 */

#ifndef SKILLS_H_
#define SKILLS_H_
#include <vector>

class Skills {
public:
	// Skills has an vector to store skillScores
	// skillsScores rank from 0(no knowledge)-4(expert)
	// currently under Important Numbers (main().
	std::vector<int> skillScoreArray;
	Skills();
	~Skills();
};

#endif /* SKILLS_H_ */
