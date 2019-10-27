/*
 * main.cpp
 *
 *  Created on: Oct 22, 2019
 *      Author: cristi
 */

#include "Project.h"
#include "Student.h"
#include "ClassSection.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <forward_list>
#include <ctime>
#include <chrono>
#include <set>

using namespace std::chrono;

// CONSTANT VARIABLE DECLARATION
const int NUM_PROJECTS = 200;
const int NUM_PROJECT_ATTRIBUTES = 5;
const int NUM_SKILLS = 7;
const int NUM_STUDENTS = 500;
const int TEAM_SIZE = 5;
const int NUM_CLASS_SECTIONS = 4;
const int MIN_STUDENT_ID = 1000;
const int MAX_STUDENT_ID = 9999;

/*struct Project {
    int id;
    int sponsorID;
    int type; // 0 = Online | 1 = Ground | 2 = Hybrid
    int priority; // 0 = Not Required | 1 = Required
    int* classID;
    int skills[NUM_SKILLS];
    int* teamMembers[TEAM_SIZE];
    int compatibilityRating;
};

struct ClassSection {
    int id;
    int type;
    int minNumProjects;
    int classSize;
    double sizeRatio;
    std::vector<int> roster();
    std::vector<int> projects();
};

struct Student {
    int id;
    int type;
    int* classID;
    int skills();
};
*/
int getRandomInt(int min, int max) {
	int value = rand() % (max-min +1) + min;
	return value;
};

void classSectionTypePartition(ClassSection arr[], int n, int lowVal, int highVal) {
    int start = 0;
    int end = n - 1;

    for (int i = 0; i <=end; ) {
        if (arr[i].type == lowVal) {
            std::swap(arr[i++], arr[start++]); // @suppress("Invalid arguments")
        } else if (arr[i].type == highVal) {
            std::swap(arr[i], arr[end--]); // @suppress("Invalid arguments")
        } else {
            i++;
        };
    }
};

void studentTypePartition(Student arr[], int n, int lowVal, int highVal) {
    int start = 0;
    int end = n - 1;

    for (int i = 0; i <=end; ) {
        if (arr[i].type < lowVal) {
            std::swap(arr[i++], arr[start++]); // @suppress("Invalid arguments")
        } else if (arr[i].type > highVal) {
            std::swap(arr[i], arr[end--]); // @suppress("Invalid arguments")
        } else {
            i++;
        };
    }
};

void projectTypePartition(Project arr[], int n, int lowVal, int highVal) {
    int start = 0;
    int end = n - 1;

    for (int i = 0; i <=end; ) {
        if (arr[i].type < lowVal) {
            std::swap(arr[i++], arr[start++]); // @suppress("Invalid arguments")
        } else if (arr[i].type > highVal) {
            std::swap(arr[i], arr[end--]); // @suppress("Invalid arguments")
        } else {
            i++;
        };
    }
}

int getNumOnlineClassSections(ClassSection arr[NUM_CLASS_SECTIONS]) {
    int value = 0;
    int i = 0;

    while (arr[i].type == 0 && i < NUM_CLASS_SECTIONS) {
        value++;
        i++;
    }

    return value;
}

int getNumOnlineStudents(Student arr[NUM_STUDENTS]) {
    int value = 0;
    int i = 0;

    while (arr[i].type == 0 && i < NUM_STUDENTS) {
        value++;
        i++;
    }

    return value;
}

int getNumOnlineProjects(Project arr[NUM_PROJECTS]) {
    int value = 0;
    int i = 0;

    while (arr[i].type == 0 && i < NUM_PROJECTS) {
        value++;
        i++;
    }

    return value;
}

int getNumGroundProjects(Project arr[NUM_PROJECTS], int partitionStart) {
    int value = 0;
    int i = partitionStart;

    while (arr[i].type == 1 && i < NUM_PROJECTS) {
        value++;
        i++;
    }

    return value;
}

int getNumHybridProjects(Project arr[NUM_PROJECTS], int partitionStart) {
    int value = 0;
    int i = partitionStart;

    while (arr[i].type == 2 && i < NUM_PROJECTS) {
        value++;
        i++;
    }

    return value;
}

int main()
{
    auto start = high_resolution_clock::now();

    int numOnlineProjects = 0;
    int numGroundProjects = 0;
    int numHybridProjects = 0;
    int numOnlineStudents = 0;
    int numGroundStudents = 0;
    int numOnlineClassSections = 0;
    int numGroundClassSections = 0;

    int countProjectsAssignedClass = 0;

    // INITIALIZE PROJECT POOLS
    Project projectPool[NUM_PROJECTS];
    Project project;

    for (int i = 0; i < NUM_PROJECTS; i++)
    {
        project.id = i + 1; // Sequentially assigns Project ID
        project.sponsorID = getRandomInt(1, (NUM_PROJECTS + 1));
        project.type = getRandomInt(0, 2);
        project.priority = getRandomInt(0, 1);

        projectPool[i] = project;
    }

    // INITIALIZE STUDENT POOL
    Student studentPool[NUM_STUDENTS];
    Student student;

    int min = MIN_STUDENT_ID;
    int max = MAX_STUDENT_ID;
    std::vector<int> generatedValues(NUM_STUDENTS);
    int value = getRandomInt(min, max);

    for (int i = 0; i < NUM_STUDENTS; i++) {
        while (std::find(generatedValues.begin(), generatedValues.end(), value)
        != generatedValues.end()) {
            value = getRandomInt(min, max);
        }
        generatedValues.push_back(value);
        student.id = value;
        student.type = getRandomInt(0, 2);
        studentPool[i] = student;
    }

    // DEALLOCATE MEMORY GENERATED BY VECTOR
    generatedValues.clear();
    std::vector<int>().swap(generatedValues);

    // INITIALIZE CLASS SECTION POOL
    ClassSection classSectionPool[NUM_CLASS_SECTIONS];
    ClassSection classSection;
    int currentType = 0;

    for (int i = 0; i < NUM_CLASS_SECTIONS; i++)
    {
        classSection.id = i + 1; // Sequentially assigns Class Section ID
        classSection.type = currentType; // Class Sections can only be Online-0 or Ground-1
        classSection.classSize = 0;

        if (currentType == 1){
            currentType = 0;
        } else if (currentType == 0){
            currentType = 1;
        };

        classSectionPool[i] = classSection;
    }

    // PARTITION POOLS
    classSectionTypePartition(classSectionPool, NUM_CLASS_SECTIONS, 0, 1);
    studentTypePartition(studentPool, NUM_STUDENTS, 1, 1);
    projectTypePartition(projectPool, NUM_PROJECTS, 1, 1);

    int i = 0;
    int j = 0;

    numOnlineClassSections = getNumOnlineClassSections(classSectionPool);
    numOnlineStudents = getNumOnlineStudents(studentPool);
    numOnlineProjects = getNumOnlineProjects(projectPool);
    numGroundProjects = getNumGroundProjects(projectPool, numOnlineProjects);
    numHybridProjects = getNumGroundProjects(projectPool, numGroundProjects);

    // ASSIGN EACH ONLINE STUDENT TO AN ONLINE CLASS SECTION
    while (i < numOnlineStudents) {
        if (j >= numOnlineClassSections) {
            j = 0;
        } else if (j < numOnlineClassSections) {
            studentPool[i].classID = &classSectionPool[j].id;
            classSectionPool[j].classSize++;
            i++;
            j++;
        };
    }

    i = numOnlineStudents;
    j = numOnlineClassSections;

    // ASSIGN EACH GROUND STUDENT TO A GROUND CLASS SECTION
    while (i < NUM_STUDENTS) {
        if (j >= NUM_CLASS_SECTIONS) {
            j = numOnlineClassSections;
        } else if (j < NUM_CLASS_SECTIONS) {
            studentPool[i].classID = &classSectionPool[j].id;
            classSectionPool[j].classSize++;
            i++;
            j++;
        };
    }

    int minNumProjectsAllSections = 0;

    for (int i = 0; i < NUM_CLASS_SECTIONS; i++) {
        classSectionPool[i].minNumProjects = classSectionPool[i].classSize / TEAM_SIZE;
        minNumProjectsAllSections = minNumProjectsAllSections + classSectionPool[i].minNumProjects;
    }

    for (int i = 0; i < NUM_CLASS_SECTIONS; i++) {
        classSectionPool[i].sizeRatio = (static_cast<double>(classSectionPool[i].minNumProjects) / minNumProjectsAllSections);
    }

    int currentSectionNumOnlineProjects = 0;
    j = 0;
    i = 0;

    while (i < numOnlineProjects) {
        if (j < numOnlineClassSections) {
            currentSectionNumOnlineProjects = classSectionPool[j].sizeRatio * numOnlineProjects;

            for (int k = 0; k < currentSectionNumOnlineProjects; k++) {
                projectPool[i].classID = &classSectionPool[j].id;
                i++;
                countProjectsAssignedClass++;
            }
            j++;
        } else if (j >= numOnlineClassSections) {
            j = 0;
            while (i < numOnlineProjects) {
                if (j >= numOnlineClassSections) {
                    j = 0;
                } else if (j < numOnlineClassSections) {
                    projectPool[i].classID = &classSectionPool[j].id;
                    i++;
                    j++;
                    countProjectsAssignedClass++;
                };
            }
        };
    }

    j = numOnlineClassSections;
    int currentSectionNumGroundProjects = 0;
    i = numOnlineProjects;

    while (i < (numOnlineProjects + numGroundProjects)) {
        if (j >= numOnlineClassSections && j < NUM_CLASS_SECTIONS) {
            currentSectionNumGroundProjects = classSectionPool[j].sizeRatio * numGroundProjects;

            for (int k = 0; k < currentSectionNumGroundProjects; k++) {
                projectPool[i].classID = &classSectionPool[j].id;
                i++;
                countProjectsAssignedClass++;
            }
            j++;
        } else {
            j = numOnlineClassSections;
            while (i < (numOnlineProjects + numGroundProjects)) {
                if (j < numOnlineClassSections || j >= NUM_CLASS_SECTIONS) {
                    j = numOnlineClassSections;
                } else if (j >= numOnlineClassSections && j < NUM_CLASS_SECTIONS) {
                    projectPool[i].classID = &classSectionPool[j].id;
                    i++;
                    j++;
                    countProjectsAssignedClass++;
                };
            }
        };
    }

    int currentSectionNumHybridProjects = 0;
    j = 0;

    while (i < NUM_PROJECTS) {
        if (j < NUM_CLASS_SECTIONS) {
            currentSectionNumHybridProjects = classSectionPool[j].sizeRatio * numHybridProjects;

            for (int k = 0; k < currentSectionNumHybridProjects; k++) {
                projectPool[i].classID = &classSectionPool[j].id;
                i++;
                countProjectsAssignedClass++;
            }
            j++;
        } else {
            j = 0;
            while (i < NUM_PROJECTS) {
                if (j >= NUM_CLASS_SECTIONS) {
                    j = 0;
                } else if (j < NUM_CLASS_SECTIONS) {
                    projectPool[i].classID = &classSectionPool[j].id;
                    i++;
                    j++;
                    countProjectsAssignedClass++;
                };
            }
        };
    }

    for (int i = 0; i < NUM_PROJECTS; i++)
    {
        std::cout << "ID: " << projectPool[i].id << "   ";
        std::cout << "Type: " << projectPool[i].type << "   ";
        std::cout << "Priority: " << projectPool[i].priority << "   ";
        std::cout << "Class ID: " << *projectPool[i].classID << "   ";
        std::cout << std::endl;
    }

    std::cout<< "Total Number of Projects Assigned a Class Id: " << countProjectsAssignedClass << std::endl;

    return 0;
}




