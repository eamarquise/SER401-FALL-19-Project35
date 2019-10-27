/*
 * 	Binning.cpp
 *
 *  Created on: Oct. 2, 2019
 *      Author: Myles Colina
 *      Github username: mcolina
 *
 *      Description:
 *      This is a prototype of the Binning Idea which uses threads.
 *      It optimizes the team assignment process by running threads for each
 *      project bin in the set. In this prototype, there are 2 sets each with
 *      3 project bins. In each iteration, threads are run based on the number
 *      of projects left in the set,(3, then 2, then 1). In each thread, team members
 *      are assigned based on skill score, online/on-campus check, affinity check,
 *      and preferred time check. The project bins are then evaluated to see which
 *      team/project is the best match, and is then assigned. The other projects are
 *      then reset, and the threads are run again with the remaining projects and
 *      remaining students.
 *
 *     It prints out status of when each thread is run, and what number it is.
 *     It also prints out the final team assignment for each project.
 */
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <functional>
#include <pthread.h>

using namespace std;

//Matthew's roll function to generate random values.
int roll(int min, int max){
	int value = rand() % (max-min +1) + min;
	return value;
}

class Student {
	public:
		string name;
		// 2D array of project # and skill-score for that project.
		int projectxskill[6][2];

		vector <string> negative_affinity;
		vector <string> positive_affinity;
		// O = online, C = on campus
		string type;

		Student();
		Student(string n, vector <string> na, vector <string> pa, string t){
			this->name = n;
			this->negative_affinity = na;
			this->positive_affinity = pa;
			this->type = t;

            //randomize skill score when creating student
			    for(int i=0; i<6; ++i){
					for(int j=0; j<2; ++j) {
						if (j==0){
							this->projectxskill[i][j] = i+1;
						}else{
							this->projectxskill[i][j] = roll(0,35);
						}	}	}
		}

		bool operator==(const Student &rhs) const {
		        return rhs.name == name;		    }
};

class Project {
	public:
		string name;
		int project_num;
		// skillsScores rank from 0(no knowledge)-4(expert)
		vector <Student> assignedStudents;
		// O = online, C = on campus, (N = not specified //to be done)
		string type;
		Project();
		Project(string n, int p_num, string t){
			this->name = n;
			this->project_num = p_num;
			this->type = t;
		}
};


//List of static variables for use in the program.
  static vector<Student> remainingStudents;
  static vector<Project> project_set1;
  static vector<Project> project_set2;
  static vector<Project> allprojects;
  static vector<Project> assignedprojects;


//Searches over all the remaining students to find the student with the best
//skill score for the project.
Student find_bestStudent(int p_num, vector<Student>& studentlist)
{  vector <string> no_affinity;
	Student best_student("st1", no_affinity, no_affinity,"O");
	int best_score = 0;
	for(int i = 0; i < studentlist.size(); i++){
		int score = studentlist[i].projectxskill[p_num-1][1];

		if (score >= best_score){
			best_score = score;
			best_student = studentlist[i];
		}
	}


 //cout << "Project: " + to_string(best_student.projectxskill[p_num-1][0]) << endl;
 //cout << "Score: " + to_string(best_student.projectxskill[p_num-1][1])  << endl;
 return best_student;
}


//Conducts a type check
bool typecheck(Student& s, Project& p)
{
 if (s.type.compare(p.type) == 0){
	 return true;
 }else{
	 return false;
 }

}



//Conducts an affinity check
// to be done
bool affinitycheck(Student s)
{
    return true;
}

//Conducts a preferred time check
//to be done
bool preferedtimecheck(Student s)
{
	return true;
}


//runs on a separate thread for each project
//assigns 5 students to each project
void project_team_assignment(Project& p)
{
	//cout << "thread # " + to_string(p.project_num) + " running" << endl;

  vector<Student> studentlist = remainingStudents;
  vector <string> no_affinity;
  Student student("st1", no_affinity, no_affinity,"O");
	for(int i = 0; i < 5; i++){
    student = find_bestStudent(p.project_num, studentlist);

    	if(typecheck(student, p) == true){

        }else{
       		i--;
       		studentlist.erase(remove(studentlist.begin(), studentlist.end(), student), studentlist.end());
       		continue;
       	}
    		if(affinitycheck(student) == true){

    		}else{
    			i--;
    	  		studentlist.erase(remove(studentlist.begin(), studentlist.end(), student), studentlist.end());
    			continue;
    		}
    			if(preferedtimecheck(student) == true){

    			}else{
    				i--;
    		  		studentlist.erase(remove(studentlist.begin(), studentlist.end(), student), studentlist.end());
    				continue;
    			}
            //assigns student to project.
    		p.assignedStudents.push_back(student);
    		studentlist.erase(remove(studentlist.begin(), studentlist.end(), student), studentlist.end());

	}

}

//Project set 1 evaluation
//Evaluates how good a match the team is to the project in the set.
// it returns the best one, assigns those students to the project,
//removes the selected project form the list, and resets the other projects.
//right now, this just assigns the first project as the best one.

Project project_team_evaluation1(vector <Project>& plist)
{  Project best_project("p1", 3, "O");


  best_project = plist[0];
  for(int i = 0; i < project_set1[0].assignedStudents.size(); i++){
 	       int pos = find(remainingStudents.begin(), remainingStudents.end(), project_set1[0].assignedStudents[i]) - remainingStudents.begin();
 	       remainingStudents.erase(remainingStudents.begin() + pos);
   			}
  project_set1[1].assignedStudents.clear();
  project_set1[2].assignedStudents.clear();

  assignedprojects.push_back(best_project);

  project_set1.erase(plist.begin());
  return best_project;
}

//Project set 2 evaluation
//Evaluates how good a match the team is to the project in the set.
// it returns the best one, assigns those students to the project,
//removes the selected project form the list, and resets the other projects.
//right now, this just assigns the first project as the best one.

Project project_team_evaluation2(vector <Project>& plist)
{  Project best_project("p1", 2, "O");


  best_project = plist[0];
  for(int i = 0; i < project_set2[0].assignedStudents.size(); i++){
	       int pos = find(remainingStudents.begin(), remainingStudents.end(), project_set2[0].assignedStudents[i]) - remainingStudents.begin();
	       remainingStudents.erase(remainingStudents.begin() + pos);
  			}
  project_set2[1].assignedStudents.clear();
  project_set2[2].assignedStudents.clear();

  assignedprojects.push_back(best_project);

  project_set2.erase(plist.begin());
  return best_project;
}

//threads for project set 1.
//This is were the threads are created, run and join back up.
// runs threads based on number of remaining projects in the set.
// first 3, then 2 then 1.
Project set1_threads(){
vector<thread> threads;

       cout << "project set 1 threads" << endl;
		for(int i = 0; i < project_set1.size(); i++){

			cout << "thread # " + to_string(i+1) + " running" << endl;
				thread th = thread(project_team_assignment, ref(project_set1[i]));
				 threads.push_back(move(th));
			// threads.push_back(thread(project_team_assignment, ref(project_set1[i])));
}

		//join all threads.
		for (auto& th : threads) th.join();


		return project_team_evaluation1(project_set1);
}

//threads for project set 2.
//This is were the threads are created, run and join back up.
// runs threads based on number of remaining projects in the set.
// first 3, then 2 then 1.
Project set2_threads(){
vector<thread> threads;

        cout << "project set 2 threads" << endl;
		for(int i = 0; i < project_set2.size(); i++){

			cout << "thread # " + to_string(i+1) + " running" << endl;
			thread th = thread(project_team_assignment, ref(project_set2[i]));
			threads.push_back(move(th));
		    //threads.push_back(thread(project_team_assignment, ref(project_set2[i])));
}

		//join all threads.
		for (auto& th : threads){
			th.join();
		}


		return project_team_evaluation2(project_set2);
}





//main class


int main()
{


		// Create Students, 20 Online students and 10 on-campus students
		//The skill scores are randomly generated each time.
		//for now, there is no affinity check.
		vector <string> no_affinity;

		Student st1("st1", no_affinity, no_affinity,"O");
		Student st2("st2",no_affinity, no_affinity,"O");
		Student st3("st3", no_affinity, no_affinity,"O");
		Student st4("st4",no_affinity, no_affinity,"O");
		Student st5("st5", no_affinity, no_affinity,"O");
		Student st6("st6",no_affinity, no_affinity,"O");
		Student st7("st7",no_affinity, no_affinity,"O");
		Student st8("st8",no_affinity, no_affinity,"O");
		Student st9("st9", no_affinity, no_affinity,"O");
		Student st10("st10", no_affinity, no_affinity,"O");
		Student st11("st11", no_affinity, no_affinity,"O");
		Student st12("st12", no_affinity, no_affinity,"O");
		Student st13("st13", no_affinity, no_affinity,"O");
		Student st14("st14", no_affinity, no_affinity,"O");
		Student st15("st15", no_affinity, no_affinity,"O");
		Student st16("st16", no_affinity, no_affinity,"O");
		Student st17("st17", no_affinity, no_affinity,"O");
		Student st18("st18", no_affinity, no_affinity,"O");
		Student st19("st19", no_affinity, no_affinity,"O");
		Student st20("st20", no_affinity, no_affinity,"O");
		Student st21("st21", no_affinity, no_affinity,"C");
		Student st22("st22", no_affinity, no_affinity,"C");
		Student st23("st23", no_affinity, no_affinity,"C");
		Student st24("st24", no_affinity, no_affinity,"C");
		Student st25("st25", no_affinity, no_affinity,"C");
		Student st26("st26", no_affinity, no_affinity,"C");
		Student st27("st27", no_affinity, no_affinity,"C");
		Student st28("st28", no_affinity, no_affinity,"C");
		Student st29("st29", no_affinity, no_affinity,"C");
		Student st30("st30", no_affinity, no_affinity,"C");
		remainingStudents.push_back(st1);
		remainingStudents.push_back(st2);
		remainingStudents.push_back(st3);
		remainingStudents.push_back(st4);
		remainingStudents.push_back(st5);
		remainingStudents.push_back(st6);
		remainingStudents.push_back(st7);
		remainingStudents.push_back(st8);
		remainingStudents.push_back(st9);
		remainingStudents.push_back(st10);
		remainingStudents.push_back(st11);
		remainingStudents.push_back(st12);
		remainingStudents.push_back(st13);
		remainingStudents.push_back(st14);
		remainingStudents.push_back(st15);
		remainingStudents.push_back(st16);
		remainingStudents.push_back(st17);
		remainingStudents.push_back(st18);
		remainingStudents.push_back(st19);
		remainingStudents.push_back(st20);
		remainingStudents.push_back(st21);
		remainingStudents.push_back(st22);
		remainingStudents.push_back(st23);
		remainingStudents.push_back(st24);
		remainingStudents.push_back(st25);
		remainingStudents.push_back(st26);
		remainingStudents.push_back(st27);
		remainingStudents.push_back(st28);
		remainingStudents.push_back(st29);
		remainingStudents.push_back(st30);


		//cout << "Project: " + to_string(st1.projectxskill[0][0])  << endl;
		// cout << "Score: " + to_string(st1.projectxskill[0][1])  << endl;


		// Create Projects Set1 (highest priority projects)
		Project p1("p1", 1, "O");
		Project p2("p2", 2, "O");
		Project p3("p3", 3, "C");
		project_set1.push_back(p1);
		project_set1.push_back(p2);
		project_set1.push_back(p3);

		// Create Projects Set2 (lowest priority projects)
		Project p4("p4", 4, "O");
		Project p5("p5", 5, "C");
		Project p6("p6", 6, "O");
		project_set2.push_back(p4);
		project_set2.push_back(p5);
		project_set2.push_back(p6);


		allprojects.push_back(p1);
		allprojects.push_back(p2);
		allprojects.push_back(p3);
		allprojects.push_back(p4);
		allprojects.push_back(p5);
		allprojects.push_back(p6);


		//Call the threads to run
		set1_threads();
		set1_threads();
		set1_threads();

		set2_threads();
		set2_threads();
		set2_threads();


		//print out projects and assigned teams.
		for(int i = 0; i < assignedprojects.size(); i++){
			cout << "Project Bin #" + to_string(assignedprojects[i].project_num) + " team members" << endl;

			for(int j = 0; j < assignedprojects[i].assignedStudents.size(); j++){

				cout << ": " + assignedprojects[i].assignedStudents[j].name <<endl ;

			}
		}

		return 0;

		}


