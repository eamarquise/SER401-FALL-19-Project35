/*
 *  Filename: main.cpp
 *  Description: Main class for Brute Force Prototype.
 *
 *  Date Created: 16 October 2019
 *  Author: Cristi DeLeo
 *
 *  Date Modified:
 *  Author:
 */

#include "Project.h"

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	cout << "Begin Brute Force Prototype" << endl;
	cout << "********************************************************************" << endl;

	int numStudents = 100;
	int teamSize = 5;

    Project project1 = Project("Test Project 1", "Sponsor 1", 'O', 1);

    cout << "Number of projects: " << project1.calc_projects(numStudents, teamSize) << endl;
    cout << endl;

	return 0;
}
