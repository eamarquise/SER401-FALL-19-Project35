/*
 * bruteteams.cpp
 *
 *  Created on: Oct. 14, 2019
 *      Author: mcilibra
 */


#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <fstream>
#include <algorithm>
#include <time.h>
#include "Skills.h"
#include "Affinity.h"
#include "PreferredMeetingTimes.h"
#include "Student.h"
#include "Project.h"
#include <math.h>

using namespace std;
int possiblities = 0;

// A function to print all combination of a given length from the given array.
void getCombinations(int a[], int sizeofteam, int startIndex, int currentTeamSize, bool assignedStudents[], int totalNumStudents)
{
	// Return if the currLen is more than the required length.
	if(currentTeamSize > sizeofteam)
	return;
	// If currLen is equal to required length then print the sequence.
	else if (currentTeamSize == sizeofteam)
	{
		cout<<"\t";
		for (int i = 0; i < totalNumStudents; i++)
		{
			if (assignedStudents[i] == true)
			{
				cout<<a[i]<<" ";
			}
		}
		possiblities++;
		cout<<endl;
		return;
	}
	// If startIndex equals to totalNumStudents then return. No elements left.
	if (startIndex == totalNumStudents)
	{
		return;
	}

	// If we select the student, put true into assignedStudents, increment our currentTeamSize and startIndex.
	assignedStudents[startIndex] = true;
	getCombinations(a, sizeofteam, startIndex + 1, currentTeamSize + 1, assignedStudents, totalNumStudents);
	// If we dont select the student, put false in the assignedStudents and increment our startIndex.
	assignedStudents[startIndex] = false;
	getCombinations(a, sizeofteam, startIndex + 1, currentTeamSize, assignedStudents, totalNumStudents);
}

int main()
{
	int teamSize = 5;
	int numStudents = 8;

	bool assignedStudents[numStudents];

	int studentList[numStudents] = {0};
	for (int i = 0; i < numStudents; i++){
		assignedStudents[i]= false;
		studentList[i] = i;
	}

	getCombinations(studentList, teamSize, 0, 0, assignedStudents, numStudents);
	cout << endl << "possiblities: " << possiblities;

	return 0;
}
