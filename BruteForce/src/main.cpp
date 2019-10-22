/*
 * main.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#include "Project.h"
#include "Student.h"
#include "ClassSection.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>

#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
//#include "Skills.h"
//#include "Affinity.h"
//#include "PreferredMeetingTimes.h"
#include "Student.h"
#include "Project.h"
//#include "ProjectGroup.h"
//#include "Team.h"
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

// CONSTANT VARIABLE DECLARATION
const int NUM_PROJECTS = 200;
const int NUM_PROJECT_ATTRIBUTES = 5;
const int NUM_SKILLS = 7;
const int NUM_STUDENTS = 500;
const int TEAM_SIZE = 5;
const int NUM_CLASS_SECTIONS = 4;
const int MIN_STUDENT_ID = 1000;
const int MAX_STUDENT_ID = 9999;
const int NUM_MEETING_TIMES = 6;
const int NUM_MEETING_TIME_SEL = 3;


int main()
{
	clock_t start, end;
	start = clock();

	srand(time(0));

	int possibilityCount = 0;
	int teamIDincrementor = 0;
	int groupCounter = 0;

	Project projectPool[NUM_PROJECTS];
	Project *projectArr = initializeProjectPool(projectPool);

	return 0;
}
