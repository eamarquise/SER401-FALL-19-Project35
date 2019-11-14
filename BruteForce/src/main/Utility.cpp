/*
 * Utility.cpp
 *
 *  Created on: Oct. 29, 2019
 *      Author: mcilibra
 */
#include "Utility.h"
#include "json/json.h"
#include "ProjectJson.h"
#include "StudentJson.h"
#include "ClassSectionJson.h"
#include "Project.h"
#include "Student.h"
#include "ClassSection.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

Utility::Utility() {
	// TODO Auto-generated constructor stub
}

Utility::~Utility() {
	// TODO Auto-generated destructor stub
}

void Utility::initProjectPool(string filename, Project projectPool[], int numProjects) {
	ProjectJson PJson;
	for (int i = 0; i < numProjects; i++) {
		*(projectPool + i) = PJson.getProjectJsonObject(filename, i);
	}
}

void Utility::initStudentPool(string filename, Student studentPool[], int numStudents) {
	StudentJson SJson;
	for (int i = 0; i < numStudents; i++) {
		*(studentPool + i) = SJson.getStudentJsonObject(filename, i);
	}
}

void Utility::initClassSectionPool(string filename, ClassSection classSectionPool[],
        Student studentPool[], int numClassSections, int numStudents) {
	ClassSectionJson CSJson;
	Student student;
	ClassSection classSection;

    for (int i = 0; i < numClassSections; i++) {
    	classSection = CSJson.getClassSectionJsonObject(filename, i);
    	int count = 0;
    	for (int j = 0; j < numStudents; j++) {
    		student = *(studentPool + j);
    		if (student.ClassID == classSection.ClassID) {
    			count++;
    		}
    	}
    	classSection.Enrollment = count;
    	*(classSectionPool + i) = classSection;
    }
}

void Utility::initProjectStudentSkills(Project projectPool[], Student studentPool[],
		int projectStudentSkills[], int numProjects, int numStudents, int numSkills) {

	int score = 0;

	for (int i = 0; i < numProjects; i++) {
		Project project;
		project = *(projectPool + i);
		for (int j = 0; j < numStudents; j++) {
			Student student;
			student = *(studentPool + j);
			score = 0;
			for (int k = 0; k < numSkills; k++) {
				score += project.Skills[k] * student.Skills[k];
			}

			*(projectStudentSkills + (i * numStudents) + j) = score;
		}
	}
}

int Utility::getSizeOfJson(string filename, string key) {
	ifstream ifs(filename);
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	return obj[key].size();
}

int Utility::getProjectXskill(Project projectPool[], int i, int j){
	Project project;
	project = *(projectPool + i);
	return project.Skills[j];
}

int Utility::getSkillXstudent(Student studentPool[], int i, int j){
	Student student;
	student = *(studentPool + i);
	return student.Skills[j];
}

vector<vector<int>> Utility::calcProjectXStudentMatrix(vector<Student> students, vector<Project> projects){
	int numStudents = students.size();
	int numProjects = projects.size();
	int numSkills = (sizeof(students.at(0).Skills)/sizeof(*students.at(0).Skills));
	vector<vector<int>> projectXstudentMatrix;
	// create projectXskill matrix
	int projectXskill[numProjects][numSkills] = {0};
	for (int i = 0; i < numProjects; i++){
		for (int j = 0; j < numSkills; j++){
			projectXskill[i][j] = projects.at(i).Skills[j];
		}
	}
	// create skillXstudent matrix transposing skills and students
	int skillXstudent[numSkills][numStudents] = {0};
	for (int i = 0; i < numSkills; i++){
		for (int j = 0; j < numStudents; j++){
			skillXstudent[i][j] = students.at(j).Skills[i];
		}
	}
	//cout << "\t";
	for (int i = 0; i < numStudents ; i++ ){
		//cout << "st" << students.at(i).StudentID << "\t";
	}
	cout<< endl;
	int projectXstudent[numProjects][numStudents];
	for (int rows = 0; rows < numProjects; rows++){
		// print project name to projectxstudent matrix
		//string p = to_string(rows);
		//cout << "p" + p + "\t";
		// do the multiplication
		for (int cols = 0; cols < numStudents; cols++){
			projectXstudent[rows][cols] = {0};
			for (int inner = 0; inner < numSkills; inner++){
				projectXstudent[rows][cols] = projectXstudent[rows][cols] +  projectXskill[rows][inner] * skillXstudent[inner][cols];

			}
			//cout << projectXstudent[rows][cols] << "\t\t";
		}
		//cout << "\n";
	}
	for (int i = 0; i < numProjects; i++){
		vector<int> currProject;
		for (int j= 0; j < numStudents; j++){
			int studentScore = projectXstudent[i][j];
			currProject.push_back(studentScore);
		}
		projectXstudentMatrix.push_back(currProject);
	}
	return projectXstudentMatrix;
} // end calcProjectXStudentMatrix

// TASK: 107 AUTHOR: CRISTI DELEO
// PARTITION BY PROJECT TYPE (PRIMARY = O | SECONDARY = G | TERTIARY = H
void Utility::projectTypePartition(Project projectPool[], int numProjects,
		char t0, char t1, char t2) {

	int start = 0;
	int end = numProjects - 1;
	int t0Index = 0;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Type == t0) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Type != t0) {
			swap(projectPool[i], projectPool[end--]);
	    } else {
	    	i++;
	    };
	}

	t0Index = 0;

	for (int i = 0; i <=end; ) {
		if (projectPool[i].Type == t0) {
			t0Index++;
			i++;
		} else {
			i++;
		};
	}

	start = t0Index;
	end = numProjects - 1;

	for (int i = t0Index; i <=end; ) {
		if (projectPool[i].Type == t1) {
			swap(projectPool[i++], projectPool[start++]);
		} else if (projectPool[i].Type != t1) {
			swap(projectPool[i], projectPool[end--]);
		} else {
			i++;
		};
	}
}

void Utility::printIntMatrix(vector<vector<int>> a){
	cout << endl;
	for (int i = 0; i < a.size() ; i++){
		for (int j = 0 ; j < a.at(i).size() ; j++){
			cout << a.at(i).at(j) << "\t";
		}
		cout << endl;
	}
}

/*  ProjectToSectionPercentages(vector<vector<Student>> studentList, vector<Project> projectList)
 *
 *    Function returns a 2d array [number of projects] [ number of class sections]
 *   containing the percentages, 0-100, of how the students in a class section compare to that project
 *
 *      Author: Myles Colina
 */
int** Utility::ProjectToSectionPercentages(vector<vector<Student>> studentList,
        vector<Project> projectList, int numProjects, int NumOfClassSections) {

	//create a 2d array containing the sum of all the students skills, for each skill.
	int SectionSkills[NumOfClassSections][7] = {0};
	int numStudentsByClass[NumOfClassSections];

    Student student;
    Project project;

    for(int i = 0; i < NumOfClassSections; i++) {
        //number of students in class sections
        int numStudents = studentList[i].size();
        numStudentsByClass[i] = numStudents;

        for(int j = 0; j < numStudents; j++) {
            student = studentList[i][j];
            for(int k = 0; k < 7; k++) {
				SectionSkills[i][k] += student.Skills[k];
            }
        }
    }

    //Print out to make sure Section Skills is correct.
    /*cout <<endl;
	cout<<"Class Section Skills Matrix"<<endl;
	for (int i = 0; i < NumOfClassSections; ++i)
	  	    {
	  	        for (int j = 0; j < 7; j++)
	  	        {
	  	            cout << SectionSkills[i][j] << ' ';
	  	        }
	  	        cout <<endl;
	  	    }*/

    //create skillXproject matrix
	int skillXproject[numProjects][7] = {0};

	for (int i = 0; i < 7; i++){
		for (int j = 0; j < numProjects; j++) {
            skillXproject[i][j] = projectList[j].Skills[i];
        }
    }

	//Print out to make sure skillXproject is correct
	/*cout <<endl;
	cout<<"Project Skills Matrix"<<endl;
	for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < numProjects; j++) {
            cout << skillXproject[i][j] << ' ';
        }
	  	cout <<endl;
    }*/

    // Calculate Project x Section skills Matrix
	int projectXsection[numProjects][NumOfClassSections];

	for (int rows = 0; rows < numProjects; rows++) {
        // do the multiplication
	  	for (int cols = 0; cols < NumOfClassSections; cols++) {
	  		projectXsection[rows][cols] = {0};
	  		for (int inner = 0; inner < 7; inner++) {
	  			projectXsection[rows][cols] = projectXsection[rows][cols]
                        +  SectionSkills[cols][inner] * skillXproject[inner][rows];
            }
        }
    }

    //Print out to make sure projectXsection is correct
    /* cout <<endl;
    cout<<"projectXsection Matrix"<<endl;
    for (int i = 0; i < numProjects; ++i) {
        for (int j = 0; j < NumOfClassSections; j++) {
            cout << projectXsection[i][j] << ' ';
        }
        cout <<endl;
    }*/

    //create a 2d array for the projects, containing the maximum
    //skill score sum a student could have on that project.
    int ProjectSkills[numProjects][1] = {0};

    for (int i = 0; i < numProjects; i++) {
        int sum = 0;
        for (int j = 0; j < 7; j++) {
            sum  = sum + projectList[i].Skills[j];
        }
        ProjectSkills[i][0] = sum * 4;
    }

    //Print out to make sure ProjectSkills is correct
    /*	  cout <<endl;
    cout<<"ProjectSkills Matrix"<<endl;
    for (int i = 0; i < numProjects; ++i) {
        cout << ProjectSkills[i][0] << ' ';
        cout <<endl;
    }*/

    //gets the percentages and stores them in a new 2d matrix.
    int** percentMatrix = 0;
    percentMatrix = new int *[numProjects];

    for (int i = 0; i < numProjects; i++) {
        percentMatrix[i] = new int [NumOfClassSections];
        for (int j = 0; j < NumOfClassSections; j++) {
            float percent= 0;
            float x = 0;
            x = (ProjectSkills[i][0] * numStudentsByClass[j]);
            percent = projectXsection[i][j]/ x;
            percent = percent * 100;
            percent = (int)percent;

            //store percentage in matrix as int, so if 88.8, it will be 88.
            percentMatrix[i][j] = percent;
        }
    }
    return  percentMatrix;
}//end ProjectToSectionPercentages


// ARRAY VERSION
void Utility::arrayProjectToSectionPercentages(Project projectPool[],
        Student studentPool[], ClassSection classSectionPool[],
		int percentMatrix[], int numProjects, int numStudents, int numClassSections,
		int numSkills) {

	//create a 2d array containing the sum of all the students skills, for each skill.
	int SectionSkills[numClassSections * numSkills] = {0};
	int numStudentsByClass[numClassSections] = {0};

    Student student;
    Project project;
    ClassSection classSection;

    for(int i = 0; i < numClassSections; i++) {
    	classSection = *(classSectionPool + i);
        numStudentsByClass[i] = classSection.Enrollment;
        for(int j = 0; j < numStudentsByClass[i]; j++) {
            student = *(studentPool + j);
            for(int k = 0; k < numSkills; k++) {
				SectionSkills[(i * numSkills) + k] += student.Skills[k];
            }
        }
    }

    //create skillXproject matrix
	int skillXproject[numProjects * numSkills];

	for (int i = 0; i < numSkills; i++){
		for (int j = 0; j < numProjects; j++) {
			project = *(projectPool + j);
            skillXproject[(i * numProjects) + j] = project.Skills[i];
        }
    }

    // Calculate Project x Section skills Matrix
	int projectXsection[numProjects * numClassSections] = {0};

	for (int i = 0; i < numProjects; i++) {
	  	for (int j = 0; j < numClassSections; j++) {
	  		projectXsection[(i * numClassSections) + j] = {0};
	  		for (int k = 0; k < numSkills; k++) {
	  			projectXsection[(i * numClassSections) + j] +=
                        SectionSkills[(j * numSkills) + k] * skillXproject[(k * numProjects) + i];
            }
        }
    }

    //create a 2d array for the projects, containing the maximum
    //skill score sum a student could have on that project.
    int ProjectSkills[numProjects] = {0};

    for (int i = 0; i < numProjects; i++) {
        int sum = 0;
        project = *(projectPool + i);
        for (int j = 0; j < numSkills; j++) {
            sum += project.Skills[j];
        }
        ProjectSkills[i] = sum * 4;
    }

    //gets the percentages and stores them in a new 2d matrix.
    //int percentMatrix[numProjects][numClassSections] = {0};

    for (int i = 0; i < numProjects; i++) {
        for (int j = 0; j < numClassSections; j++) {
            float percent= 0;
            float x = 0;
            x = (ProjectSkills[i] * numStudentsByClass[j]);
            percent = projectXsection[(i * numClassSections) + j] / x;
            percent = percent * 100;
            percent = (int)percent;

            //store percentage in matrix as int, so if 88.8, it will be 88.
            percentMatrix[(i * numClassSections) + j] = percent;
        }
    }
    //return  percentMatrix;
}//end ProjectToSectionPercentages
