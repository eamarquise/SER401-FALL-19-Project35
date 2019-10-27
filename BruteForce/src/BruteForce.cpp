/*
 * main.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#include "Project.h"
#include "Student.h"
#include "ClassSection.h"
#include "Utilities.h"

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
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

int getRandomInt(int min, int max) {
	int value = rand() % (max-min +1) + min;
	return value;
}

Project* initializeProjectPool(Project pool[]) {
	Project project;
	// CONSTANT VARIABLE DECLARATION
	int NUM_PROJECTS1 = 200;

	for (int i = 0; i < NUM_PROJECTS1; i++)
	{
	    project.id = i + 1; // Sequentially assigns Project ID
	    project.sponsorID = getRandomInt(1, (NUM_PROJECTS1 + 1));
	    project.type = getRandomInt(0, 2);
	    project.priority = getRandomInt(0, 1);

	    pool[i] = project;

	    cout << &pool[i] << endl;
	}

	return pool;
}

int main() {
	clock_t start, end;
	start = clock();

	srand(time(0));

	int possibilityCount = 0;
	int teamIDincrementor = 0;
	int groupCounter = 0;

	Project p;
	p = Project();
	Project projectPool[NUM_PROJECTS];
	Project* projectArr = &(initializeProjectPool(projectPool))[0];

	cout<< "Brute FOrce" << endl;

	for (int i = 0; i < NUM_PROJECTS; i++)
	    {
	        std::cout << "ID: " << &(projectArr->id) << "   ";
	        std::cout << "Type: " << projectPool[i].type << "   ";
	        std::cout << "Priority: " << projectPool[i].priority << "   ";
	        std::cout << "Class ID: " << *projectPool[i].classID << "   ";
	        std::cout << std::endl;
	    }

	return(0);
}
