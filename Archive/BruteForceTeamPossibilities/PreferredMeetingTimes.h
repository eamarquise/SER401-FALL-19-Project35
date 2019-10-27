/*
 * PreferredMeetingTimes.h
 * Description:
 * 		A Class to give a student's meeting times
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 */

#ifndef PREFERREDMEETINGTIMES_H_
#define PREFERREDMEETINGTIMES_H_
#include <vector>

class PreferredMeetingTimes {
	/* 	preferredMeetingTime: Based on MST
	 *  will take the 3 preferred meeting times for students in order of importance.
	 * 	0)	Night-time: 12:00AM - 4:00AM
	 *	1)	Early Morning: 4:00AM - 8:00AM
	 *	2)	Morning: 8:00AM - 12:00PM
	 *	3)	Afternoon: 12:00PM - 4:00PM
	 *	4)	Early Evening: 4:00PM - 8:00PM
	 *	5)  Evening: 8:00PM - 12:00AM
	 */
	public:
		std::vector<int> meetingTimes;
};

#endif /* PREFERREDMEETINGTIMES_H_ */
