

#include <iostream>
#include <thread>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;




class Student {
	public:
		string name;
		// 2D array of project # and skillscore for that project.

		int projectxskill(*)[2];

		vector <string> negative_affinity;
		vector <string> positive_affinity;
		// O = online, C = on campus, N = not specified
		string type;

		Student();
		Student(string n, vector <string> na, vector <string> pa, int pskill[6][2], string t){
			this->name = n;
			this->projectxskill = pskill;
			this->negative_affinity = na;
			this->positive_affinity = pa;
			this->type = t;
		}
};

class Project {
	public:
		string name;
		int project_num;
		// skillsScores rank from 0(no knowledge)-4(expert)
		vector <Student> assignedStudents;
		// O = online, C = on campus, N = not specified
		string type;
		Project();
		Project(string n, int p_num, string t){
			this->name = n;
			this->project_num = p_num;
			this->type = t;
		}
};


  static vector<Student> remainingStudents;
  static vector<Project> project_set1;
  static vector<Project> project_set2;
  static vector<Project> allprojects;
  static vector<Project> assignedprojects;

int randomnum()
{
	 srand((unsigned)time(0));
	    int random_num;
	    for(int index=0; index<35; index++){
	        random_num = (rand()%10)+1;
	      return random_num;
	    }
}

int(*)[2] randskillscore()
{
	int rand_matrix[6][2]=
	{
			{1, randomnum()},
			{2, randomnum()},
			{3, randomnum()},
			{4, randomnum()},
			{5, randomnum()},
			{6, randomnum()},
	};

	return rand_matrix;
}
//Searches over all the remaining students to find the student with the best
//skill score for the project.
Student find_bestStudent(int p_num, vector<Student> studentlist)
{  Student best_student;
	int best_score = 0;
	for(int i = 0; i < studentlist.size(); i++){
		int score = studentlist[i].projectxskill[p_num+1][1];
		if (score >= best_score){
			best_score=score;
			best_student = studentlist[i];
		}
	}

 return best_student;
}

bool typecheck(Student s, Project p)
{
 if (s.type.compare(p.type) == 0){
	 return true;
 }else if(p.type.compare("N") == 0){
	 return true;}
 else{
	 return false;
 }

}

bool affinitycheck(Student s)
{
    return true;

}

bool preferedtimecheck(Student s)
{
  //to do
	return true;

}
//run on a separate thread for each project
void project_team_assignment(Project p)
{
  vector<Student> studentlist = remainingStudents;
  Student student;
	for(int i = 0; i < 4; i++){
    student = find_bestStudent(p.project_num, studentlist);

    	if(typecheck(student, p) == true){


        }else{
       		i--;
       		int pos = find(studentlist.begin(), studentlist.end(), student) - studentlist.begin();
       		studentlist.erase(studentlist.begin() + pos);
       		continue;
       	}
    		if(affinitycheck(student) == true){


    		}else{
    			i--;
    			int pos = find(studentlist.begin(), studentlist.end(), student) - studentlist.begin();
    			studentlist.erase(studentlist.begin() + pos);
    			continue;
    		}
    			if(preferedtimecheck(student) == true){

    			}else{
    				i--;
    				int pos = find(studentlist.begin(), studentlist.end(), student) - studentlist.begin();
    				studentlist.erase(studentlist.begin() + pos);
    				continue;
    			}
            //assigns student to project.
    		p.assignedStudents.push_back(student);
	}

}

//threads for project set 1.
Project set1_threads(){
std::vector<std::thread> threads;

       cout << "project set 1 threads" << endl;
		for(int i = 0; i < project_set1.size(); i++){

			  cout << "thread # " + i + " running" << endl;
		    threads.push_back(std::thread(project_team_assignment ,project_set1));
}

		//join all threads.
		for (auto& th : threads) th.join();


		return project_team_evaluation(project_set1);
}

//threads for project set 2.

Project set2_threads(){
std::vector<std::thread> threads;

        cout << "project set 2 threads" << endl;
		for(int i = 0; i < project_set2.size(); i++){

			cout << "thread # " + i + " running" << endl;
		    threads.push_back(std::thread( project_team_assignment, project_set2));
}

		//join all threads.
		for (auto& th : threads) th.join();


		return project_team_evaluation(project_set2);
}



//to-do
//right now, this just assigns the first project as the best one.
//set1
Project project_team_evaluation1(vector <Project> plist)
{  Project best_project;


  best_project = plist[0];
  project_set1[1].assignedStudents.clear();
  project_set1[2].assignedStudents.clear();

  project_set1.erase(studentlist.begin())
  return best_project;
}

//set2
Project project_team_evaluation2(vector <Project> plist)
{  Project best_project;


  best_project = plist[0];
  project_set2[1].assignedStudents.clear();
  project_set2[2].assignedStudents.clear();

  project_set2.erase(studentlist.begin())



  return best_project;
}

void


int main()
{

	//vector<Student> remainingStudents;
	//vector<Project> project_set1;
	//vector<Project> project_set2;
	//vector<Project> allprojects;

		// Important numbers
		int numStudents = 30;
		int numProjects = 3;
		int numSkills = 5;
		int teams = numStudents / numProjects;



		// Create Students, 20 Online students and 10 on-campus students
		//The skill scores are randomly generated each time.
		//for now, there is no affinity check.
		vector <string> no_affinity;

		Student st1("st1", no_affinity, no_affinity, randskillscore(),"O");
		Student st2("st2",no_affinity, no_affinity, randskillscore(),"O");
		Student st3("st3", no_affinity, no_affinity, randskillscore(),"O");
		Student st4("st4",no_affinity, no_affinity, randskillscore(),"O");
		Student st5("st5", no_affinity, no_affinity, randskillscore(),"O");
		Student st6("st6",no_affinity, no_affinity, randskillscore(),"O");
		Student st7("st7",no_affinity, no_affinity, randskillscore(),"O");
		Student st8("st8",no_affinity, no_affinity, randskillscore(),"O");
		Student st9("st9", no_affinity, no_affinity, randskillscore(),"O");
		Student st10("st10", no_affinity, no_affinity, randskillscore(),"O");
		Student st11("st11", no_affinity, no_affinity, randskillscore(),"O");
		Student st12("st12", no_affinity, no_affinity, randskillscore(),"O");
		Student st13("st13", no_affinity, no_affinity, randskillscore(),"O");
		Student st14("st14", no_affinity, no_affinity, randskillscore(),"O");
		Student st15("st15", no_affinity, no_affinity, randskillscore(),"O");
		Student st16("st16", no_affinity, no_affinity, randskillscore(),"O");
		Student st17("st17", no_affinity, no_affinity, randskillscore(),"O");
		Student st18("st18", no_affinity, no_affinity, randskillscore(),"O");
		Student st19("st19", no_affinity, no_affinity, randskillscore(),"O");
		Student st20("st20", no_affinity, no_affinity, randskillscore(),"O");
		Student st21("st21", no_affinity, no_affinity, randskillscore(),"C");
		Student st23("st22", no_affinity, no_affinity, randskillscore(),"C");
		Student st23("st23", no_affinity, no_affinity, randskillscore(),"C");
		Student st24("st24", no_affinity, no_affinity, randskillscore(),"C");
		Student st25("st25", no_affinity, no_affinity, randskillscore(),"C");
		Student st26("st26", no_affinity, no_affinity, randskillscore(),"C");
		Student st27("st27", no_affinity, no_affinity, randskillscore(),"C");
		Student st28("st28", no_affinity, no_affinity, randskillscore(),"C");
		Student st29("st29", no_affinity, no_affinity, randskillscore(),"C");
		Student st30("st30", no_affinity, no_affinity, randskillscore(),"C");
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


		// Create Projects Set1 (highest priority projects)
		Project p1("p1", 1, "O");
		Project p2("p2", 2, "N");
		Project p3("p3", 3, "C");
		projects_set1.push_back(p1);
		projects_set1.push_back(p2);
		projects_set1.push_back(p3);

		// Create Projects Set2 (lowest priority projects)
		Project p4("p1", 1, "N");
		Project p5("p2", 2, "N");
		Project p6("p3", 3, "O");
		projects_set2.push_back(p4);
		projects_set2.push_back(p5);
		projects_set2.push_back(p6);


		allprojects.push_back(p1);
		allprojects.push_back(p2);
		allprojects.push_back(p3);
		allprojects.push_back(p4);
		allprojects.push_back(p5);
		allprojects.push_back(p6);


		assignedprojects.push_back(set1_threads());
		assignedprojects.push_back(set1_threads());
		assignedprojects.push_back(set1_threads());


		assignedprojects.push_back(set2_threads());
		assignedprojects.push_back(set2_threads());
		assignedprojects.push_back(set2_threads());




		//print out projects and assigned teams.
		for(int i = 0; i < assignedprojects.size(); i++){
			cout << "Project #" + assignedprojects[i] + " team members" << endl;

			for(int j = 0; j < assignedprojects[i].assignedStudents.size(); j++){

				cout << assignedprojects[i].assignedStudents[j].name <<endl ;



			}
		}

		}

		return 0;
	}

