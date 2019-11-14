/*
 * StudentsToProjects.cpp
 *
 *  Created on: Oct 30, 2019
 *      Author: Sean
 *      Revised by: Myles
 *      Revised by: Cristi
 *      Revised by: Matthew
 */

#include "StudentsToProjects.h"
#include "Project.h"
#include "Student.h"
#include "Team.h"
//#include "ProjectTeamSet.h"
#include "ClassSection.h"
#include "json/json.h"
#include "Utility.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <chrono>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

StudentsToProjects::StudentsToProjects() {
}

StudentsToProjects::~StudentsToProjects() {
}

constexpr int StudentsToProjects::toConstInt(int constInt) {
	return constInt;
}


/*
 * StudentsToProjectsAssignment
 *
 *  Description:
 *  This function assigns all the students taken in, to the projects taken in.
 *  It finds all the possible team combinations for all the students, for each project.
 *  It stores the top number of teams (user specified) for all the combinations for each project.
 *  Then based on those top teams. It finds the combination of combinations of the horizontal mapping
 *  of teams to the projects. It stores the highest scoring teams to projects set, that has no duplicate
 *  students. If this can not be found, it stores the highest scoring teams to projects set, with the least
 *  amount of duplicate students.
 *
 *Arguments:
 *	Student studentPool[], Project projectPool[], int numStudents, int numProjects, int numSkills
 *	const int teamSize, int numTopTeams
 *
 *Returns:
 *	void
 *
 */
void StudentsToProjects::StudentsToProjectsAssignment(Student studentPool[],
		Project projectPool[], const int numStudents,const int numProjects,const int numSkills,
		const int teamSize,const int numTopTeams) {

	//timer to keep track of program runtime
    auto start = high_resolution_clock::now();
	srand(time(NULL));


	 const int TOP_TEAMS = toConstInt(numTopTeams);
	 const int TEAM_SIZE = toConstInt(5);
	 int PxSskill_size = numStudents*numProjects;
	 const int PROJECTXSTUDETNSKILL_SIZE = toConstInt(PxSskill_size);


	Team currentTeam;

   //used to store the top teams for every project.
	Team temp;
	Team currentTopTeams[TOP_TEAMS];

	//array to store checks for the top scores.
	int topscores[TOP_TEAMS];
   //initialize arrays to 0,
	 for(int j = 0; j < TOP_TEAMS; j++) {
			 currentTopTeams[j]=temp;
			 topscores[j] = 0;
		 }

	 //2d array to store the top teams for every project
	Team topTeams[numProjects][TOP_TEAMS];

   //variable to store the team's skill score
    int teamskillscore = 0;
   //counter to keep track of students on a team
    int num =0;

 //------------------Do skill calculations for the student pool and the project pool.

    //give each student a PoolID.
    //and fill in skill sum score
    int studentSkillSums[numStudents];
    for(int i = 0; i < numStudents; i++) {
    	studentPool[i].PoolID = i;
    	studentSkillSums[i] = 0;
    	for(int j = 0; j < numSkills; j++) {
    	studentSkillSums[i] += studentPool[i].Skills[j];
    	 }
    }

    //give each project a PoolID
    //Calculate max skill score for each project.
    int maxProjectSkills[numProjects];
    int maxProjectScore=0;
    for(int i = 0; i < numProjects; i++) {
    	projectPool[i].PoolID = i;
    	maxProjectSkills[i] = 0;

    	for(int j = 0; j < numSkills; j++) {
    	maxProjectScore += projectPool[i].Skills[j] * 4;
    		}
    	maxProjectSkills[i] = maxProjectScore * TEAM_SIZE;
    	maxProjectScore = 0;
    }

  //get project skill X student skill matrix
    int ProjectXStudentSkills[PROJECTXSTUDETNSKILL_SIZE];

    Utility util;
    util.initProjectStudentSkills(projectPool, studentPool,
    		ProjectXStudentSkills, numProjects, numStudents,numSkills);

    int skillSums[TEAM_SIZE];
    int studentSkills[TEAM_SIZE];
    for(int i = 0; i < TEAM_SIZE; i++) {
    	studentSkills[i] =0;
    	skillSums[i]=0;
    }
//------------------------end skill calculations


 //START--------------Team Combination process to find every student team combination for each project
    cout << "STUDENTS TO PROJECTS ASSIGNMENT RUNNING..." << endl;
        	for(int i = 0; i < numProjects; i++) {

        		//new combination process
        		int studentIndexes[teamSize];
        		for(int i = 0; i < teamSize; i++) {
        			studentIndexes[i] = i+1;
        		}
        		int indexToIncrement = teamSize - 1;
        		bool permuting = true;

        		//creates the combination of student teams
        		while(permuting) {
        			for(int j = 0; j < teamSize; j++) {
        				//adds the student to the team for each combination
        				currentTeam.team[num] = studentPool[studentIndexes[j] - 1];
        				studentSkills[num] =*(ProjectXStudentSkills + (i * numStudents) + currentTeam.team[num].PoolID);
        				skillSums[num] = studentSkillSums[currentTeam.team[num].PoolID];
        				num++;
        				//following commented out portion is for debugging purposes,
        				//for(int k = 0; k < numSkills; k++) {
        				//	teamskillscore += studentPool[studentIndexes[j] - 1].Skills[k] * projectPool[i].Skills[k];
        				//}
        			}
        			//----Now the team for this combination is formed.-----

        			//Negative Affinity Check
        			//check returns true if there is negative affinity on the team,
        	        //and false if there is no negative affinity.
        			if (negativeAffinityCheck(currentTeam.team) == false){

        				//call to 3 team score functions
        				//TeamScore = func1() + func2() + func3()
        			    teamskillscore = ProjectCompareTeamScore(studentSkills, maxProjectSkills[i]) +
        				SkillCompareTeamScore(skillSums) + AvailabilityTeamScore(currentTeam.team);

        				currentTeam.TeamScore = teamskillscore;
        				currentTeam.projectID = projectPool[i].ProjectID;
                        //loop to compare the new team's score to the top scores.
        				for(int k = 0; k < TOP_TEAMS; k++) {
        						    if (k == 0){
        						    	if (currentTeam.TeamScore > topscores[k] ){
        						    	topscores[k] = currentTeam.TeamScore;
        						        currentTopTeams[k] = currentTeam;
        						        break;

        						    	}
        						    }else{
        						    	if ( currentTeam.TeamScore == topscores[k-1] | currentTeam.TeamScore > topscores[k] ){
        						        		topscores[k] = currentTeam.TeamScore;
        						        	    currentTopTeams[k] = currentTeam;
        						        	    break;
        								 }
        				}}

        		    }//end affinity check

        		   //reset these values for the next team combination
        			num = 0;
        			teamskillscore = 0;
        			currentTeam.TeamScore = 0;

        			studentIndexes[indexToIncrement]++;
        			while(studentIndexes[indexToIncrement] == numStudents - ((teamSize - 1) - (indexToIncrement + 1))){
        				indexToIncrement--;
        				if(indexToIncrement < 0) {
        					permuting = false;
        					break;
        				} else {
        					studentIndexes[indexToIncrement]++;
        				}
        			}
        			while(indexToIncrement < teamSize - 1 && permuting) {
        				indexToIncrement++;
        				studentIndexes[indexToIncrement] = studentIndexes[indexToIncrement - 1] + 1;
        			}
        		}//return to create the next team combination


        		//for each iteration over the number of projects, add in the top teams for that project into
        		//the top teams 2d array.
        		 for(int j = 0; j < TOP_TEAMS; j++) {
        				 topTeams[i][j] = currentTopTeams[j];
        				 topscores[j] = 0;
        				 }

        		cout << "Project # " + to_string(projectPool[i].ProjectID) + "  team combinations complete. " << endl;

        	} // end i loop (for each project)

 //END---------------------Team Combination process


 // START--------------------Project Set combinations here
        	cout << "TOP TEAMS TO PROJECTS SET RUNNING..." << endl;

        	//Needed variables
        	Team currentSet[numProjects];
        	Team bestSet[numProjects];
			Team uniqueSet[numProjects];
			Team bestSetWithDuplicates[numProjects];
			Team temp2;
			int teamNum = 0;
			int ProjectSetScore = 0;
			int BestProjectSetScore = 0;
			int topscore = 0;
			int TopUniquesSetScore = 0;
			int TopDuplicateSetScore = 0;
			int leastDuplicateSet = 0;

			int currentduplicatCount= 0;
			int duplicateCount = 0;

			for (int i = 0; i < numProjects; i++) {
				currentSet[i] = temp2;
				bestSet[i] = temp2;
				uniqueSet[i] = temp2;
				bestSetWithDuplicates[i] = temp2;
			}

        	    // to keep track of next element in each of
        	    // the n arrays
        	    //int* indices = new int[numProjects];
				int indices[numProjects];
        	    // initialize with first element's index
        	    for (int i = 0; i < numProjects; i++){
        	        indices[i] = 0;}

        	    while (1) {

        	        //adds a team from each top team array to the project Set.
        	        for (int i = 0; i < numProjects; i++) {

        	            currentSet[teamNum] = topTeams[i][indices[i]];
        	            //int duplicateCount = duplicateCheck(currentSet);
        	            //if (threshold > duplicateCount){
        	            //flag=true;
        	            //break;}
        	            ProjectSetScore += topTeams[i][indices[i]].TeamScore;
        	            teamNum++;
        	        }
                    //if flag{
        	        //Project teams combination formed,

        	        //Print loop for debugging
        	        /*for(int i = 0; i < numProjects; i++){
        	        	cout << "Team for project#" + to_string(i) + " ";
        	        				for(int k = 0; k < teamSize; k++) {
        	        					cout<< to_string(currentSet[i].Team[k].StudentID) + " ";
        	        				}
        	        				cout << endl;
        	        }
        	        cout<< "Project set score: "<< ProjectSetScore<<endl;*/


        	        //Duplicate student check()

        	        //if duplicate student check == 0.
        	        //check value against topUique score
        	        if(ProjectSetScore >= topscore){

        	        	for (int i = 0; i < numProjects; i++) {

        	        		bestSet[i] = currentSet[i];
        	        		BestProjectSetScore = ProjectSetScore;
        	        		topscore = BestProjectSetScore;
        	        	}

        	        }

        	        //reset values
                    teamNum = 0;
                    ProjectSetScore = 0;

        	        int next = numProjects - 1;
        	        while (next >= 0 &&
        	              (indices[next] + 1 >= TOP_TEAMS))
        	            next--;

        	        // no such array is found so no more
        	        // combinations left
        	        if (next < 0){
        	            break;}

        	        // if found move to next element in that
        	        // array
        	        indices[next]++;

        	        // for all arrays to the right of this
        	        // array current index again points to
        	        // first element
        	        for (int i = next + 1; i < numProjects; i++){
        	            indices[i] = 0;
        	        }
        	    //}//end if flag
        	    }

// END -------------------Project Set combinations





	//Print out all the top teams with team scores for each project.
	cout<< "Top "<<TOP_TEAMS<<" teams for each project"<<endl;

	for(int i = 0; i < numProjects; i++) {
		Project project = *(projectPool + i);
		cout<< "Projects #" + to_string(project.ProjectID) + " Student Teams:"<<endl;
		for(int j = 0; j < TOP_TEAMS; j++) {

			cout << "Team #" + to_string(j) + " ";
			for(int k = 0; k < teamSize; k++) {

				cout<< to_string(topTeams[i][j].team[k].StudentID) + " ";

			}
			cout << endl;
			cout<< "TeamScore: " + to_string(topTeams[i][j].TeamScore)<<endl;
		}
		cout << endl;
	}

	//Prints out the best project set found.
	cout << endl;
	cout<< "Best Project Set "<<endl;
	cout<< "==============================================="<<endl;
	for(int i = 0; i < numProjects; i++){
		cout << "Team for project#" + to_string(bestSet[i].projectID) + " ";
	    for(int k = 0; k < teamSize; k++) {
	        	cout<< to_string(bestSet[i].team[k].StudentID) + " ";
	   }
	    cout << endl;
	     }
	     cout<< "Best Project Set score: "<< BestProjectSetScore<<endl;


	     //KEEP TRACK OF TIME THE PROGRAM TAKES TO RUN
	  	auto stop = high_resolution_clock::now();
	  	auto duration = duration_cast<milliseconds>(stop - start);

	  	cout << "time in milliseconds: ";
	  	cout << duration.count() << endl;;
	  	cout << endl;



}//END StudentsToProjectsAssignment


//-----TEAM SCORE CALCULATING FUNCTIONS------


/*
 * AvailabilityTeamScore
 *
 * Description:
 * 	This function returns a score of 0-20 determining
 * 	the quality of the team by comparing the Availability of students
 * 	on a team to each other.
 *
 *Arguments:
 *	Student team[]
 *
 *Returns:
 *  integer value from 0 to 20.
 */
int StudentsToProjects::AvailabilityTeamScore(Student team[5]){

	int timeCompareScore = 0;

	timeCompareScore += StudentToStudentAvailibility(team[0], team[1]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[2]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[0], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[2]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[1], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[2], team[3]);
	timeCompareScore += StudentToStudentAvailibility(team[2], team[4]);
	timeCompareScore += StudentToStudentAvailibility(team[3], team[4]);


	    //score 0-40
		//return timeCompareScore;

		//configure the score from 0-40 to 0-20
		float percent= 0;
		float max = 40;
		percent = timeCompareScore/ max;
		percent = percent * 20;
		percent = (int)percent;

		//return the score 0-20
		//return timeCompareScore;
		return percent;
}


/*
 * StudentToStudentAvailibility
 *
 * Description:
 * 	helper function for AvailabilityTeamScore, compares 2 students
 * 	returns an Availability comparison score of 0 - 4.
 *
 *Arguments:
 *	Student s1, Student s2
 *
 *Returns:
 *  integer value from 0 to 4.
 */
 int StudentsToProjects::StudentToStudentAvailibility(Student s1, Student s2){

	int score = 0;

	//checks preferred weekday selections
	if(s1.Availability[0] == s2.Availability[0]){
		score += 2;
	}else if ((s1.Availability[1] == s2.Availability[1]) | (s1.Availability[1] == s2.Availability[0]) |(s1.Availability[0] == s2.Availability[1])){
		score += 2;
	}

	//checks preferred weekend selections
	if(s1.Availability[2] == s2.Availability[2]){
			score += 2;
		}else if ((s1.Availability[3] == s2.Availability[3]) | (s1.Availability[3] == s2.Availability[2]) |(s1.Availability[2] == s2.Availability[3])){
			score += 2;
		}

	return score;
}

/*
 * SkillCompareTeamScore
 *
 * Description:
 * 	This function returns a score of 0-40 determining
 * 	the quality of the team by comparing the student's skills to each other
 *
 *Arguments:
 *	Student team[]
 *
 *Returns:
 *  integer value from 0 to 40.
 */
int StudentsToProjects::SkillCompareTeamScore( int studentSkills[5]){

int teamCompareScore = 0;


teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[1]);
teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[2]);
teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[3]);
teamCompareScore += StudentToStudentSkill(studentSkills[0], studentSkills[4]);
teamCompareScore += StudentToStudentSkill(studentSkills[1], studentSkills[2]);
teamCompareScore += StudentToStudentSkill(studentSkills[1], studentSkills[3]);
teamCompareScore += StudentToStudentSkill(studentSkills[1], studentSkills[4]);
teamCompareScore += StudentToStudentSkill(studentSkills[2], studentSkills[3]);
teamCompareScore += StudentToStudentSkill(studentSkills[2], studentSkills[4]);
teamCompareScore += StudentToStudentSkill(studentSkills[3], studentSkills[4]);

	return teamCompareScore;

}

/*
 * StudentToStudentSkill
 *
 * Description:
 * 	helper function for SkillCompareTeamScore
 * 	returns a student to student comparison score of 0 - 4.
 *
 *Arguments:
 *	Student s1, Student s2
 *
 *Returns:
 *  integer value from 0 to 4.
 */
int StudentsToProjects::StudentToStudentSkill( int skillsum1, int skillsum2){

	  int score = skillsum1 - skillsum2;
      score = abs(score);

	  if (score == 0 || score == 1){
	  	return 4;

	  	}else if(score == 2 || score == 3){
	  	return 3;

	  	}else if(score == 4 || score == 5){
	  	return 2;

	  	}else if(score > 5 && score < 9){
	  	return 1;

	  	}else if(score >= 9){
	  	return 0;

	  	}

}


/*
 * ProjectCompareTeamScore
 *
 * Description:
 * 	This function returns a score of 0-40 determining
 * 	the quality of the team by comparing the max skills a team could have
 *  on a certain project, to the team's overall skills.
 *
 *Arguments:
 *	Student team[]
 *
 *Returns:
 *  integer value from 0 to 40.
 *
 */
 int StudentsToProjects::ProjectCompareTeamScore(int studentSkills[5], int maxProjectScore){

	int teamSkillSum = 0;

	for( int i = 0; i < 5 ; i++ ){
	 teamSkillSum += studentSkills[i]; }

    //calculate percentage
	float percent= 0;
	float max = 0;
	max = maxProjectScore;
	percent = teamSkillSum/ max;
	percent = percent * 40;
	percent = (int)percent;

    //return the score 0-40
	return percent;

}

/*
 * negativeAffinityCheck
 *
 * currently takes in a vector of students, which represents a possible team combination.
 * function checks to see if any students have negative affinity toward one another.
 * If negative affinity between team members IS NOT found, function will return a boolean value of false,
 * If negative affinity between team member IS found, function will return a boolean value of true.
 */
bool StudentsToProjects::negativeAffinityCheck(Student team[5]){
	// start of with negativeAffinity being false - meaning we have not found negative affinity.
	// We will return true if we find an instance of negative affinity in this team combination.
	bool negativeAffinity = false;
	// We begin with an outer loop of that will examine each student in the team
	for (int studentTeamCounter = 0; studentTeamCounter < 5; studentTeamCounter++){

		// if the current student's affinity list is empty - we don't need about comparing any other students - so on to the next iteration
		if (team[studentTeamCounter].StudentAffinity.empty()){
			continue;
		} else {
			// lets take a look at the current students affinity list
			for (int currentStudentAffinityCounter = 0; currentStudentAffinityCounter < team[studentTeamCounter].StudentAffinity.size(); currentStudentAffinityCounter++){
				// next we will loop through all other students comparing the current students affinity to other students, checking for negative affinity.
				for (int otherStudentsCounter = 0; otherStudentsCounter < 5; otherStudentsCounter++){

					// because we are looping, if the current student happens to be the other student, lets continue to the next iteration.
					if (team[studentTeamCounter].StudentID == team[otherStudentsCounter].StudentID){
						continue;
						// next for each student id in the current students affinity list, lets see if the other student has the same Student ID
						// and if the affinity boolean value is false, meaning negative affinity. The current student doesn't want to work with
						// the other student. In this case we will change our negativeAffinity flag to true. We can break out of this function with
						// one instance of negative affinity. The team won't work.
					} else {
						if ((team[studentTeamCounter].StudentAffinity.at(currentStudentAffinityCounter).first == team[otherStudentsCounter].StudentID) && (team[studentTeamCounter].StudentAffinity.at(currentStudentAffinityCounter).second == false)){
							negativeAffinity = true;
							break;
						}
					} // end otherStudentsCounter loop
				}
				if (negativeAffinity == true){
					break;
				}
			} // end currentStudentAffinityCounter loop
		}
		if (negativeAffinity == true){
			break;
		}
	} // end studentTeamCounter loop
	return negativeAffinity;
}
