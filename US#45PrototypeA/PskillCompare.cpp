/*
 * 	PskillCompare.cpp
 *
 *  Created on: Oct. 20, 2019
 *      Author: Myles Colina
 *      Github username: mcolina
 *
 *       US#45 Task#63
 *
 *      Description:
 *      This is a prototype of algorithm A:
 *      Project to student skills comparison.
 *      Also includes a student team evaluation
 *      using the project to student comparison
 *      algorithm.
 */

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;

int numProjects=3;
//Student class
class Student {
	public:
		string name;
		// 7 total skills
		//skills each rank from 0(no knowledge)-4(expert)
		vector <int> skills;

		vector<int> skillScores;

		Student();
		Student(string n, vector <int> s){
			this->name = n;
			this->skills = s;
		vector<int> v(numProjects, 0);
                        this->skillScores=v;
	}
		bool operator==(const Student &rhs) const {
		        return rhs.name == name;		    }
};

//Student Team class
class Team {
	public:
	
		vector <Student> team;
		int teamScore;
		Team(vector <Student> t){
		this->team = t;		
		teamScore=0;		}
};


class Project {
	public:
		int pnum;
		
		// 7 total skills
		//skills each rank from 0-1
		vector <int> skills;

		int maxScore;
		
		Project();
		Project(int p_num, vector <int> s){
			
			this->pnum = p_num;
			this->skills = s;
		}
};


//calculates the max score a student could possibly have 
//on the project.
void setMaxScore(Project& p){

 	int max=0;
 	for(int i = 0; i < p.skills.size(); i++){
	
	if (p.skills[i]==1){

	max += 3;
	}
      p.maxScore = max;
}
}



//Project skills to Student skills comparision function.
// It evalutes a list of students, and sorts them based
// on how closly thier skills match the max skills 
// of a given project .
vector <Student> sortS(Project p, vector <Student> st)
{

vector <Student> studentsSorted;
vector <Student> stlist = st;

int best=0;
vector<int> s{ 1, 1, 1, 1, 0, 0, 0 };
Student tempS( "temp", s);


while(stlist.size() != 0){
for(int i = 0; i < stlist.size(); i++){

if (best<=stlist[i].skillScores[p.pnum-1]){
  best = stlist[i].skillScores[p.pnum-1];
  tempS = stlist[i];
}

}

studentsSorted.push_back(tempS);
int pos = find(stlist.begin(), stlist.end(), tempS) - stlist.begin();
	       stlist.erase(stlist.begin() + pos);
best = 0;
}


return studentsSorted;

}





//Project skills to Student skills comparision function.
// It evalutes all students skill scores for all projects.
void PskillsCompare(vector <Project>& p, vector <Student>& st)
{
int score=0;
for(int i = 0; i < p.size(); i++){

for(int j = 0; j < st.size(); j++){


if (p[i].skills.size() == st[j].skills.size()){

for(int k = 0; k < p[i].skills.size(); k++){

 if (p[i].skills[k]==1){
 score +=st[j].skills[k];

}}

st[j].skillScores[p[i].pnum-1] = score;
score=0;}
}
}

}


int main()
{

		//Project objects

		vector<int> ps{ 1, 1, 1, 1, 0, 0, 0 };
	  	Project p1( 1, ps);

		vector<int> ps2{ 1, 1, 0, 0, 1, 1, 1 };
	  	Project p2( 2, ps2);

		vector<int> ps3{ 0, 0, 0, 1, 1, 0, 0 };
	  	Project p3( 3, ps3);

                
		//Student objects

		vector<int> s1{ 3, 1, 1, 0, 3, 3, 1 };
		Student st1("st1", s1);

		vector<int> s2{ 3, 0, 2, 3, 2, 2, 1 };
		Student st2("st2", s2);

 		vector<int> s3{ 3, 1, 1, 0, 3, 3, 1 };
		Student st3("st3", s3);

		vector<int> s4{ 0, 2, 3, 2, 1, 1, 2 };
		Student st4("st4", s4);

		vector<int> s5{ 2, 2, 2, 1, 2, 2, 0 };
		Student st5("st5", s5);

		vector<int> s6{ 1, 2, 0, 0, 1, 0, 1 };
		Student st6("st6", s6);

		vector<int> s7{ 0, 1, 2, 0, 1, 0, 1 };
		Student st7("st7", s7);

		vector<int> s8{ 3, 3, 2, 2, 0, 2, 2 };
		Student st8("st8", s8);

  		vector<int> s9{ 2, 2, 2, 1, 2, 2, 0 };
		Student st9("st9", s9);

		vector<int> s10{ 1, 2, 2, 1, 0, 0, 2 };
		Student st10("st10", s10);

		vector<int> s11{ 3, 2, 2, 3, 0, 0, 2 };
		Student st11("st11", s11);

		vector<int> s12{ 1, 2, 2, 1, 1, 0, 2 };
		Student st12("st12", s12);

		vector<int> s13{ 3, 1, 2, 2, 0, 0, 2 };
		Student st13("st13", s13);


		vector<int> s14{ 1, 0, 2, 1, 1, 0, 0 };
		Student st14("st14", s14);

		vector<int> s15{ 2, 1, 1, 1, 0, 1, 1 };
		Student st15("st15", s15);



		vector<Project> allProjects;
		allProjects.push_back(p1);
		allProjects.push_back(p2);
		allProjects.push_back(p3);


		vector<Student> allStudents;
		allStudents.push_back(st1);
		allStudents.push_back(st2);
		allStudents.push_back(st3);
		allStudents.push_back(st4);
		allStudents.push_back(st5);
		allStudents.push_back(st6);
		allStudents.push_back(st7);
		allStudents.push_back(st8);
		allStudents.push_back(st9);
		allStudents.push_back(st10);
		allStudents.push_back(st11);
		allStudents.push_back(st12);
		allStudents.push_back(st13);
		allStudents.push_back(st14);
		allStudents.push_back(st15);
 

	//set max score for each project
   
        setMaxScore(p1);
        setMaxScore(p2);
        setMaxScore(p3);



	// calculte the skills scores for each student
	// for each of the projects.
	PskillsCompare(allProjects, allStudents);
	


        // Get a sorted student list for each project based
	//on the skill scores.
	 vector <Student> p1Students;
 	 p1Students = sortS(p1, allStudents);

	  vector <Student> p2Students;
	  p2Students = sortS(p2, allStudents);

	  vector <Student> p3Students;
	  p3Students = sortS(p3, allStudents);




	//Student to student comparisions
		cout << "PROJECT TO STUDENT COMPARISIONS" << endl;
		cout << "==================================================" << endl;
		cout << endl;		

	  //print out results to console.
		cout << "Project #1 Max skill score: " + to_string(p1.maxScore)<< endl;
	 	cout << "Sorted student list for projet #1 "<< endl;
		cout << "Project #1 Max skill score: " + to_string(p1.maxScore)<< endl;
		for(int i = 0; i < p1Students.size(); i++){
		cout <<  p1Students[i].name + " score: " + to_string(p1Students[i].skillScores[0]) << endl;
		}
		cout << endl;	
		cout << endl;

		cout << "Project #2 Max skill score: " + to_string(p2.maxScore)<< endl;
	 	cout << "Sorted student list for projet #2 "<< endl;
		cout << "Project #2 Max skill score: " + to_string(p2.maxScore)<< endl;
		for(int i = 0; i < p2Students.size(); i++){
		cout <<  p2Students[i].name + " score: " + to_string(p2Students[i].skillScores[1]) << endl;
		}
		cout << endl;	
		cout << endl;


		cout << "Project #3 Max skill score: " + to_string(p3.maxScore)<< endl;
	 	cout << "Sorted student list for projet #3 "<< endl;
		cout << "Project #3 Max skill score: " + to_string(p3.maxScore)<< endl;
		for(int i = 0; i < p3Students.size(); i++){
		cout <<  p3Students[i].name + " score: " + to_string(p3Students[i].skillScores[2]) << endl;
		}
		cout << endl;	
		cout << endl;


	        return 0;

	}


