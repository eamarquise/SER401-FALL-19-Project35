/*
 * Student.h
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#ifndef STUDENT_H_
#define STUDENT_H_

class Student {
	public:
		int id;
	    int type;
	    int* classID;
	    //int skills();

	    Student();
	    Student(int studID, int t, int* clID);
};

#endif /* STUDENT_H_ */
