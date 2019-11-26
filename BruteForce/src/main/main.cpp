/*
 * Filename: main.cpp
 * Created On: 10/27/2019
 * Purpose: driver for BruteForce prototype.
 */
#include "Student.h"
#include "Project.h"
#include "ClassSection.h"
#include "Test.h"
#include "json/json.h"
#include "StudentJson.h"
#include "ProjectJson.h"
#include "ClassSectionJson.h"
#include "Utility.h"
#include "StudentsToProjects.h"

#include <iostream>
#include <utility>
#include <array>
#include <algorithm>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <chrono>

#include <bits/stdc++.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

using namespace std;
using namespace std::chrono;



int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}
int getValuePhy(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int getValueVirt(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

constexpr int toConstInt(int constInt) {
	return constInt;
}

//StudentsToProjectsAssignments will run in this method. This method is called by the threads.
void threadFunction(Student studentPool[],
		Project projectPool[], const int numStudents, const int numProjects, const int numSkills,
		const int teamSize, const int numTopTeams, string results[], int classSection) {


	//Find the number of teams of 5 and number of teams of 4 needed for this class section.
	Utility util;
	int numTeamsOf4 = util.NumOfTeamsOf4(numStudents, teamSize);
	int numTeamsOf5 = abs(numTeamsOf4*4 - numStudents)/5;
	int count4T = 0;
	int count5T = 0;
	vector <int> TeamsNeeded;

	for(int i=0; i<numProjects; i++) {

		if(count5T < numTeamsOf5){
		TeamsNeeded.push_back(5);
		count5T++;

		}else if(count4T < numTeamsOf4){
			TeamsNeeded.push_back(4);
			count4T++;
		}
	}



	/***** SORTING STUDENTS BASED ON SKILL *****/
		//creating student skill average
		for(int i=0; i<numStudents; i++) {
			double average1=0;
			for(int m=0; m < numSkills; m++) {
				average1 += studentPool[i].Skills[m];
			}
			average1 = average1/numSkills;
			studentPool[i].skillAverage = average1;
		}

		//Averaging student skills into a sorted array
		for(int i=0; i < numStudents; i++){
			Student student;
			for(int j=(i+1); j < numStudents; j++){
				if (studentPool[j].skillAverage > studentPool[i].skillAverage) {
					student = studentPool[i];
					studentPool[i] = studentPool[j];
					studentPool[j] = student;
				}
			}
		 }

		//Counting project priority
		int count1 = 0;
		int count2 = 0;

		for(int i=0; i<numProjects; i++){
			if(projectPool[i].Priority ==2) { count2++; }
			if(projectPool[i].Priority ==1) { count1++; }
		}

     	int count0 = abs(numProjects - count2 - count1);

		//make sure each priority section does not have 1 project.(should have 0, or 2 or more.)
		if (count2==1){
			if(count1 > 2){
				count1--;
				count2++;
			}else if(count1 == 1){
				count1--;
				count2++;
			}else if(count1 == 2){
					count1--;
					count2++;
					count1--;
					count2++;
			}else if(count0 > 2){
				count0--;
				count2++;
			}else if(count0 == 1){
				count0--;
				count2++;
		}else if(count0 == 2){
			count0--;
			count2++;
			count0--;
			count2++;
		}}

		if (count1==1){
			if (count2>=1 && count2 !=2){
			count2++;
			count1--;
			}else if (count0>=1 && count0 !=2){
				count1--;
				count0++;
			}else if (count0==2){
				count1++;
				count1++;
				count0--;
				count0--;
			}
		}


		if (count0==1){
			if (count2>=1 && count2 !=2){
			count2++;
			count0--;
			}else if (count1>=1&& count1 !=2){
			 count0--;
			 count1++;
			}else if (count1==2){
				count0++;
				count0++;
				count1--;
				count1--;
			}
		}


		if(count1==2){
			count1--;
			count1--;
			count2++;
			count2++;
		}

		if(count0==2){
					count0--;
					count0--;
					count2++;
					count2++;
				}



		int newcount0 = 0;
		int newcount1 = 0;
		int newcount2 = 0;
		int c0 = 0;
		int c1 = 0;
		int c2 = 0;

		for(int i=0; i<numProjects; i++) {

			if(c2 < count2){
			newcount2 += TeamsNeeded[i];
			c2++;
			}else if(c1 < count1){
				newcount1 += TeamsNeeded[i];
				c1++;
				}else if(c0 < count0){
					newcount0 += TeamsNeeded[i];
					c0++;
					}

		}



		//const int count1C = count1*5;
		//const int count2C = count2*5;

		const int count0C = newcount0;
		const int count1C = newcount1;
		const int count2C = newcount2;

		const int COUNT_0 = toConstInt(count0C);
		const int COUNT_1 = toConstInt(count1C);
		const int COUNT_2 = toConstInt(count2C);

		const int PCOUNT_0 = toConstInt(count0);
		const int PCOUNT_1 = toConstInt(count1);
		const int PCOUNT_2 = toConstInt(count2);

		//Pushing students onto project priority arrays
		Student STpriority1[COUNT_1];
		Student STpriority2[COUNT_2];
		Student STpriority0[COUNT_0];
		//Student STpriority0[numStudents - COUNT_2 - COUNT_1];
		//int COUNT_0 = numStudents - COUNT_2 - COUNT_1;

		//std::copy(studentPool + 0, studentPool+(COUNT_2-1), STpriority2);
		//std::copy(studentPool +(COUNT_2), studentPool +(COUNT_2+COUNT_1-1), STpriority1);
		//std::copy(studentPool +(COUNT_2+COUNT_1), studentPool +(numStudents), STpriority0);

		int snum1 = 0;
		int snum2 = 0;
		int snum0 = 0;

		for(int i=0; i<numStudents; i++){

					if(i <  COUNT_2){

						STpriority2[snum2] =studentPool[i];
						snum2++;

					}else if(i >= COUNT_2 && i< COUNT_2+COUNT_1){

						STpriority1[snum1] = studentPool[i];
						snum1++;

					}else if(i >= COUNT_2+COUNT_1 ){

						STpriority0[snum0] = studentPool[i];
						snum0++;
					}
				}



		//Pushing projects onto project priority arrays
		Project PRpriority1[PCOUNT_1];
		Project PRpriority2[PCOUNT_2];
		Project PRpriority0[PCOUNT_0];
		//Project PRpriority0[numProjects - count1 - count2];
		//int PCOUNT_0 = numProjects - count1 - count2;

		int pnum1 = 0;
		int pnum2 = 0;
		int pnum0 = 0;
/*
		for(int i=0; i<numProjects; i++){

			if(projectPool[i].Priority == 2){

				PRpriority2[pnum2] = projectPool[i];
				pnum2++;
			}else if(projectPool[i].Priority == 1){

				PRpriority1[pnum1] = projectPool[i];
				pnum1++;
			}else if(projectPool[i].Priority == 0){

				PRpriority0[pnum0] = projectPool[i];
				pnum0++;}
		}*/

		for(int i=0; i<numProjects; i++){

					if(i < count2){

						PRpriority2[pnum2] = projectPool[i];
						pnum2++;
					}else if(i >= count2 && i< count2+count1){

						PRpriority1[pnum1] = projectPool[i];
						pnum1++;
					}else if(i >= count2 + count1){

						PRpriority0[pnum0] = projectPool[i];
						pnum0++;}
				}

		cout << "Class section # " << classSection<<endl;

		cout << "numProjects: " <<numProjects<<endl;
		cout << "P2: " <<PCOUNT_2<<endl;
		cout << "P1: " <<PCOUNT_1<<endl;
		cout << "P0: " <<PCOUNT_0<<endl;
		cout << "numStudents: " <<numStudents<<endl;
	    cout << "S2: " <<COUNT_2<<endl;
	    cout << "S1: " <<COUNT_1<<endl;
		cout << "S0: " <<COUNT_0<<endl;
/*if(classSection == 1){

	for(int i=0; i<PCOUNT_2; i++){
		cout<<"Project ID"<<PRpriority2[i].ProjectID<<endl;
	}

	cout<<"Students: ";
	for(int i=0; i<COUNT_2; i++){
			cout<<STpriority2[i].StudentID<<" "<<endl;
		}
	cout<<endl;
}*/


	StudentsToProjects x;
 if(COUNT_2 != 0 && PCOUNT_2 != 0){
	//1st Call to function: Highest priority projects and highest skill average students
	*(results+(classSection*3+0)) = x.StudentsToProjectsAssignment(STpriority2, PRpriority2,
			COUNT_2, PCOUNT_2, numSkills, teamSize, numTopTeams);}
 cout<<"Call 1 done"<<endl;

 if(COUNT_1 != 0 && PCOUNT_1 != 0){
	//2nd Call to function: middle priority projects and middle skill average students
	*(results+(classSection*3+1)) = x.StudentsToProjectsAssignment(STpriority1, PRpriority1,
			COUNT_1, PCOUNT_1, numSkills, teamSize, numTopTeams);}
 cout<<"Call 2 done"<<endl;

 if(COUNT_0 != 0 && PCOUNT_0 != 0){
   //3rd Call to function: lowest priority projects and lowest skill average students
	*(results+(classSection*3+2)) = x.StudentsToProjectsAssignment(STpriority0, PRpriority0,
		    COUNT_0, PCOUNT_0, numSkills, teamSize, numTopTeams);}
 cout<<"Call 3 done"<<endl;


}




int main(){

	//timer to keep track of program runtime
	    auto start = high_resolution_clock::now();
		srand(time(NULL));

	cout << "Hi Team 35" << endl;

	//reading in inputs
	int tempProj, tempStud;
	cout << "#Projects: ";
	cin >> tempProj;
	cout << "#Students: ";
	cin >> tempStud;

	const int NUM_PROJECTS = toConstInt(tempProj);
	const int NUM_STUDENTS = toConstInt(tempStud);
	const int NUM_SKILLS = 7;
	const int NUM_CLASS_SECTIONS = 4;

	Utility util;

	util.makeProjectJSON(NUM_PROJECTS, NUM_SKILLS);
	util.makeStudentJSON(NUM_STUDENTS, NUM_SKILLS);

	const string PROJECT_FILE = "./newProjects.json";
	const string STUDENT_FILE = "./newStudents.json";
	//const string PROJECT_FILE = "./SampleJsonFiles/80Projects.json";
	//const string STUDENT_FILE = "./SampleJsonFiles/400Students.json";
	const string CLASS_SECTION_FILE = "./SampleJsonFiles/4ClassSections.json";

	//Change this value to change the number of top teams stored.
    int tempNumTopTeams = 5;
    int tempTeamSize = 5;

	const int NUM_TOP_TEAMS = toConstInt(tempNumTopTeams);
	const int TEAM_SIZE = toConstInt(tempTeamSize);

	StudentJson SJson;
	ProjectJson PJson;
	ClassSectionJson CSJson;

	//Project *PROJECT_POOL = new Project[NUM_PROJECTS];
	//Student *STUDENT_POOL = new Student[NUM_STUDENTS];
	Project PROJECT_POOL[NUM_PROJECTS];
	Student STUDENT_POOL[NUM_STUDENTS];
	ClassSection CLASS_SECTION_POOL[NUM_CLASS_SECTIONS];

	int PROJECT_STUDENT_SKILLS[NUM_PROJECTS * NUM_STUDENTS];

	Test t;

	// INITIALIZE POOLS
	util.initProjectPool(PROJECT_FILE, PROJECT_POOL, NUM_PROJECTS);
	util.initStudentPool(STUDENT_FILE, STUDENT_POOL, NUM_STUDENTS);
	util.initClassSectionPool(CLASS_SECTION_FILE, CLASS_SECTION_POOL, STUDENT_POOL,
            NUM_CLASS_SECTIONS, NUM_STUDENTS);
	util.initProjectStudentSkills(PROJECT_POOL, STUDENT_POOL,
			PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS, NUM_SKILLS);


	//string *results = new string[NUM_CLASS_SECTIONS*3]; //Stores the results the assignment of students to projects each class section
	string results[NUM_CLASS_SECTIONS*3];
	//int *studentsInSections = new int[NUM_CLASS_SECTIONS]; //stores the number of students in each class section
	//int *projectsInSections = new int[NUM_CLASS_SECTIONS]; //stores the number of students in each class section
	int studentsInSections[NUM_CLASS_SECTIONS]; //stores the number of students in each class section
    int projectsInSections[NUM_CLASS_SECTIONS]; //stores the number of students in each class section

	//initialize to 0
	for(int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		studentsInSections[i] = 0;
		projectsInSections[i] = 0;
	}

	for(int i = 0; i < NUM_CLASS_SECTIONS*3; i++) {
				results[i] = "x";
		}

	//set the number of students in each class section to the indexes of studentsInSections[]
	for(int i = 0; i < NUM_STUDENTS; i++) {
		for(int j = 0; j < NUM_CLASS_SECTIONS; j++) {
			if(STUDENT_POOL[i].ClassID == j) {
				studentsInSections[j]++;
			}
		}
	}







	// PARTITION POOLS BY TYPE (ONLINE/GROUND/HYBRID)
	util.projectTypePartition(PROJECT_POOL, NUM_PROJECTS, 'O', 'G', 'H');
	util.classSectionTypePartition(CLASS_SECTION_POOL, NUM_CLASS_SECTIONS, 'O', 'G');

	// ASSIGN EACH PROJECT TO A CLASS SECTION BASED ON STUDENT-PROJECT SCORE
	util.projectToSectionAssignment(PROJECT_POOL, STUDENT_POOL, CLASS_SECTION_POOL,
				NUM_PROJECTS, NUM_STUDENTS, NUM_CLASS_SECTIONS, NUM_SKILLS, studentsInSections );

	cout << endl << "After Project to Class Section Assignment: " << endl ;
	t.PrintProjectPool(PROJECT_POOL, NUM_PROJECTS, NUM_SKILLS);


	cout << to_string(getValuePhy() + getValueVirt()) << " KB total memory usage" << endl;

// BEGIN - STUDENTS TO PROJECTS ASSIGNMENT

    //Threads for each class section will start here
    //Students will be partitioned here by skill averages
    //projects will be partitioned by priority

	//THREADS FOR EACH CLASS SECTION...Sean Rogers



	//set the number of projects in each class section to the indexes of projectsInSections[]
		for(int i = 0; i < NUM_PROJECTS; i++) {
			for(int j = 0; j < NUM_CLASS_SECTIONS; j++) {
				if(PROJECT_POOL[i].ClassID == j) {
					projectsInSections[j]++;
				}
			}
		}

	cout << "StudentID|ClassID: ";

	//Print out for testing
	for(int i = 0; i < NUM_STUDENTS; i++) {
		cout << STUDENT_POOL[i].StudentID << "|" << STUDENT_POOL[i].ClassID << "  ";
	}

	cout << endl;

	//create a thread for each class section. store each thread in threads[]
	//thread threads[NUM_CLASS_SECTIONS];

	for(int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		//store students in a single class section to *STUDENT_POOL_SECTION_X
		Student STUDENT_POOL_SECTION_X[studentsInSections[i]];
		//Student *STUDENT_POOL_SECTION_X = new Student[studentsInSections[i]];
		int indexToAddStudent = 0; //used to add a student to STUDENT_POOL_SECTION_X[] from STUDENT_POOL[]

		cout << "StudentIDs in Class Section " << to_string(i) << ": ";

		for(int j = 0; j < NUM_STUDENTS; j++) {
			if(STUDENT_POOL[j].ClassID == i) {
				STUDENT_POOL_SECTION_X[indexToAddStudent] = STUDENT_POOL[j];
				indexToAddStudent++;
			}
		}

		Project PROJECT_POOL_SECTION_X[projectsInSections[i]];
		//Project *PROJECT_POOL_SECTION_X = new Project[projectsInSections[i]];
		int indexToAddProject = 0; //used to add a student to STUDENT_POOL_SECTION_X[] from STUDENT_POOL[]

		//separate the projects into an array by class section
		for(int j = 0; j < NUM_PROJECTS; j++) {
					if(PROJECT_POOL[j].ClassID == i) {
						PROJECT_POOL_SECTION_X[indexToAddProject] = PROJECT_POOL[j];
						indexToAddProject++;
					}
				}


		for(int j = 0; j < studentsInSections[i]; j++) {
			cout << STUDENT_POOL_SECTION_X[j].StudentID << " ";
		}

		cout << "Total: " + to_string(studentsInSections[i]) << endl;
		threadFunction(STUDENT_POOL_SECTION_X, PROJECT_POOL_SECTION_X, studentsInSections[i], projectsInSections[i], NUM_SKILLS, TEAM_SIZE, NUM_TOP_TEAMS, results, i);

		//threads[i] = thread (threadFunction, STUDENT_POOL, PROJECT_POOL, NUM_STUDENTS, NUM_PROJECTS, NUM_SKILLS, TEAM_SIZE, NUM_TOP_TEAMS);
		//threads[i] = thread (threadFunction, STUDENT_POOL_SECTION_X, PROJECT_POOL_SECTION_X, studentsInSections[i], projectsInSections[i], NUM_SKILLS, TEAM_SIZE, NUM_TOP_TEAMS, results, i);
	}




    //join threads
/*	for(int i = 0; i < NUM_CLASS_SECTIONS; i++) {
		threads[i].join();

	}*/
    for(int i = 0; i < NUM_CLASS_SECTIONS*3; i++) {
		cout << results[i] << endl;
	}
	//END THREADS FOR EACH CLASS SECTION...Sean Rogers

//END -STUDENTS TO PROJECTS ASSIGNMENT


    //KEEP TRACK OF TIME THE PROGRAM TAKES TO RUN
	  	auto stop = high_resolution_clock::now();
	  	auto duration = duration_cast<milliseconds>(stop - start);
		cout << endl;
		cout << endl;
		cout << getValueVirt() + getValuePhy() << " KB of memory usage: End of entire program" << endl;
		cout << endl;
		cout << "Program Runtime"<<endl;
	  	cout << "time in milliseconds: ";
	  	cout << duration.count() << endl;;
	  	cout << endl;

    //Tests
	//Test t;
	//t.StructTest();
	//t.PrintProjectPool(PROJECT_POOL, NUM_PROJECTS, NUM_SKILLS);
	//t.PrintStudentPool(STUDENT_POOL, NUM_STUDENTS, NUM_SKILLS);
	//t.PrintProjectStudentSkills(PROJECT_STUDENT_SKILLS, NUM_PROJECTS, NUM_STUDENTS);

	// Drivers to read in rules, like class section definitions
	// ex - getRules(capStoneCourseDefinitions);

	// Drivers to crunch stuff
	// ex - mapProjectsToClasses(rules);

	// Drivers to write Json
	// ex - composeReport();

	// Drivers to convert Json into some kind of report, like excel or json to pdf?
	// ex - writeReport();
	return 0;
}
