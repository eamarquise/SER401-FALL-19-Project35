/*
 * ClassSection.h
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#ifndef CLASSSECTION_H_
#define CLASSSECTION_H_

class ClassSection {
	public:
		int id;
	    int type;
	    int minNumProjects;
	    int classSize;
	    double sizeRatio;
	    //std::vector<int> roster();
	    //std::vector<int> projects();

	    ClassSection();
	    ClassSection(int clID, int t, int minProj, int clSize, double sizeRatio);
};

#endif /* CLASSSECTION_H_ */
