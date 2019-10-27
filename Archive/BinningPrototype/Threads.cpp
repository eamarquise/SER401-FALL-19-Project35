
#include <iostream>
#include <thread>
#include <vector>
#include <string.h>
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

//Project class
class Project {
	public:
		string name;
		int project_num;
		string assignedStudents[5];
		int assignmentScore;
		// O = online, C = on campus, N = not specified
		string type;
		Project();
		Project(string n, int p_num, string t){
			this->name = n;
			this->project_num = p_num;
			this->type = t;
		}
};

//assignment function.
// Does not do much right now, just gives each project bin, a
// fake assignment score from 50-100

void project_team_assignment(Project& p)
{

	for(int i = 0; i < 5; i++){
	p.assignedStudents[i]= i+1;
	}
	p.assignmentScore = roll(50,100);

	cout << "thread # " + to_string(p.project_num) + " running" << endl;
}





int main()
{

	  	    vector<Project> project_set1;
	  	    vector<Project> project_set2;


	  	    // Create Projects Set1 (highest priority projects)
	        Project p1("p1", 1,  "O");
			Project p2("p2", 2, "N");
			Project p3("p3", 3, "C");
			project_set1.push_back(p1);
			project_set1.push_back(p2);
			project_set1.push_back(p3);

			// Create Projects Set2 (lowest priority projects)
			Project p4("p4", 4, "N");
			Project p5("p5", 5, "N");
			Project p6("p6", 6, "O");
			project_set2.push_back(p4);
			project_set2.push_back(p5);
			project_set2.push_back(p6);



			//Create threads for the project bins in set 1.
			//One thread gets run for each project bin.
	        vector<thread> threads;

	        cout << "project set 1 threads" << endl;
			for(int i = 0; i < project_set1.size(); i++){

					thread th = thread(project_team_assignment, ref(project_set1[i]));
					threads.push_back(move(th));
				 //threads.push_back(thread(project_team_assignment, project_set1[i]));
	            }

			//join all set 1 threads.
			for (auto& th : threads) th.join();





			             //Create threads for the project bins in set 2.
						//One thread gets run for each project bin.
			            vector<thread> threads2;

				        cout << "project set 2 threads" << endl;
						for(int i = 0; i < project_set2.size(); i++){

								thread th2 = thread(project_team_assignment, ref(project_set2[i]));
								threads2.push_back(move(th2));
							 //threads2.push_back(thread(project_team_assignment, project_set1[i]));
				            }

						//join all set 2 threads.
						for (auto& th2 : threads2) th2.join();



						//checks to see which project in set 1 has the best team/project match
								int best;
								Project pA("p1", 1,  "O");
								pA.assignmentScore = 0;
								for(int i = 0; i < project_set1.size(); i++){

								if (project_set1[i].assignmentScore > best){
									best = project_set1[i].assignmentScore;
									pA = project_set1[i];
								}
								}
						//Print results for project Set 1
						cout << "Set 1 Projects"<<endl;
						for(int i = 0; i < project_set1.size(); i++){
						cout << "Project #" + to_string(project_set1[i].project_num) + " Assignment score: " + to_string(project_set1[i].assignmentScore) << endl;
                        }
						cout << "The selected: Project #" + to_string(pA.project_num) + " Assignment score: " + to_string(pA.assignmentScore) << endl;



						//checks to see which project in set 2 has the best team/project match
						best = 0;
						Project pB("p1", 1,  "O");
						pB.assignmentScore = 0;
						for(int i = 0; i < project_set2.size(); i++){

						if (project_set2[i].assignmentScore > best){
							best = project_set2[i].assignmentScore;
							pB = project_set2[i];
						}
						}
						//Print results for project Set 2
						cout << "Set 2 Projects"<<endl;
						for(int i = 0; i < project_set2.size(); i++){
						cout << "Project #" + to_string(project_set2[i].project_num) + " Assignment score: " + to_string(project_set2[i].assignmentScore) << endl;
						}
						cout << "The selected: Project #" + to_string(pB.project_num) + " Assignment score: " + to_string(pB.assignmentScore) << endl;

						return 0;
}
