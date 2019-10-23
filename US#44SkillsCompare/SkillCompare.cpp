/*
 * 	SkillCompare.cpp
 *
 *  Created on: Oct. 16, 2019
 *      Author: Myles Colina
 *      Github username: mcolina
 *
 *       US#44 Task#55
 *
 *      Description:
 *      This is a prototype of algorithm A:
 *      Student to student skills comparison.
 *      Also includes a studetn team evaluation
 *      using the studetn to student comparison
 *      algorithm.
 */

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>

using namespace std;


//Student class
class Student {
	public:
		string name;
		
		vector <int> skills;

		Student();
		Student(string n, vector <int> s){
			this->name = n;
			this->skills = s;
	}
		//bool operator==(const Student &rhs) const {
	 	//       return rhs.name == name;		    }
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

//Checks the comparison score, and evaluates it into a string expression.
string scoreCheck(int score){

	if (score == 0 || score == 1){
	return "Excellent match";

	}else if(score == 2 || score == 3){
	return "Good match";

	}else if(score == 4 || score == 5){
	return "Decent match";

	}else if(score > 5 && score < 9){
	return "Bad match";

	}else if(score >= 9){
	return "Worst match";

	}

	return "No match";

}

//function to return the score of a comparison between 2 students.
int getCompareScore(Student st1, Student st2)
{
	vector <int> s1 = st1.skills;
	vector <int> s2 = st2.skills;
	int result[7];
        int sum = 0;

	if(s1.size()==s2.size()){
	for(int i = 0; i < s1.size(); i++){
	result[i] = s1[i] - s2[i];
	}
       
        for(int i = 0; i < s1.size(); i++){
	sum += result[i];
	}
	
        sum = abs(sum);
	return sum;
}
}

//Function to give a value based on the comparison score.
//Used for student team comparisons.
int getTeamScoring(int score)
{
	if (score == 0 || score == 1){
	return 3;

	}else if(score == 2 || score == 3){
	return 2;

	}else if(score == 4 || score == 5){
	return 1;

	}else if(score > 5 && score < 9){
	return 0;

	}else if(score >= 9){
	return -1;

	}

	return 0;
}

//Student skills comparision function.
void skillsCompare(Student st1, Student st2)
{
	vector <int> s1 = st1.skills;
	vector <int> s2 = st2.skills;
	int result[7];
        int sum = 0;

	if(s1.size()==s2.size()){
	for(int i = 0; i < s1.size(); i++){
	result[i] = s1[i] - s2[i];
	}
       
        for(int i = 0; i < s1.size(); i++){
	sum += result[i];
	}
	
        sum = abs(sum);

}
        //print out results to console.
 	cout << "Student comparison between: " + st1.name + " and " + st2.name << endl;
	cout << st1.name + " skills: ";
        for(int i = 0; i < s1.size(); i++){
	cout <<  to_string(s1[i]) + " | ";}

	cout <<"\n"+ st2.name + " skills: ";
        for(int i = 0; i < s2.size(); i++){
	cout <<  to_string(s2[i]) + " | ";}

	cout << "\n" << "score: " << to_string(sum) + " " + scoreCheck(sum) << endl;
        cout << endl;	
	cout << endl;
}


//Student team skills comparision function.
void teamCompare(vector <Student> team)
{

	for(int i = 0; i < team.size(); i++){
     		
	

	}	

	
}

//Student team skills comparison function.
//compares all students in a team to eachother, and scores the 
// team based on those comparisons.
// on a team of 5 students, there will be 10 comparisons.
void TeamCompare(Team& t, int reqLen, int s, int currLen, bool check[], int l)
{
  vector <Student> team = t.team;
  vector<int> x{ 3, 0, 2, 3, 2, 2, 1 };
   Student s1("NULL", x);
   Student s2("NULL", x);
   if(currLen > reqLen){
   return;}
   else if (currLen == reqLen) {
     // cout<<"\t";
      for (int i = 0; i < l; i++) {
         if (check[i] == true) {
           // cout<<team[i]<<" ";
             int x = s1.name.compare("NULL");
             if ( x == 0){
                  s1 = team[i];   
		
		}else{
		  s2 = team[i];	}
         }
      }
   

     int score = getCompareScore(s1, s2);
     t.teamScore += getTeamScoring(score);

     cout << s1.name + " and " + s2.name + " comparison score: " + to_string(score);
     cout << " Value : " + to_string(getTeamScoring(score))<< endl;

      	s1.name="NULL";
   	s2.name="NULL";
  
      return;
   }
   if (s == l) {
      return;
   }
   //recursive call
   check[s] = true;
   TeamCompare(t, reqLen, s + 1, currLen + 1, check, l);

   //recursive call  
   check[s] = false;
   TeamCompare(t, reqLen, s + 1, currLen, check, l);    
}




int main()
{
		//Student objects

		vector<int> s{ 3, 0, 2, 3, 2, 2, 1 };
	  	Student st1("st1", s);

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

	

//Student to student comparisions
		cout << "STUDENT TO STUDENT COMPARISIONS" << endl;
		cout << "==================================================" << endl;

		//perfect skills match
		cout << "Sample perfect skills match" << endl;
		skillsCompare(st1, st2);

		//complimentary skills match
		cout << "Sample complimentary skills match" << endl;
		skillsCompare(st3, st4);

		//Bad skills match
		cout << "Sample Bad skills match" << endl;
		skillsCompare(st5, st6);

		//compare 2 star students
		cout << "Compare 2 star students" << endl;
		skillsCompare(st2, st8);

		//compare 2 star students
		cout << "Compare 2 star students" << endl;
		skillsCompare(st8, st3);

    		//compare 2 middle performer students
		cout << "Compare 2 middle performer students" << endl;
		skillsCompare(st13, st9);

                //compare 2 middle performer students
		cout << "Compare 2 middle performer students" << endl;
		skillsCompare(st9, st5);

		//compare 2 'dud' students
		cout << "Compare 2 'dud' students" << endl;
		skillsCompare(st7, st10);

		//compare 2 'dud' students
		cout << "Compare 2 'dud' students" << endl;
		skillsCompare(st6, st10);

		//compare star to middle perforemer
		cout << "Compare star to middle perforemer" << endl;
		skillsCompare(st8, st9);

		//compare middle performer to dud 
		cout << "Compare middle performer to dud " << endl;
		skillsCompare(st5, st7);

		//compare star to dud
		cout << "Compare star to dud" << endl;
		skillsCompare(st1, st6);



//Now testing Student team comparisons
		cout << endl;
		cout << "STUDENT TEAM COMPARISIONS" << endl;
		cout << "==================================================" << endl;


		//creating a team of 5 star students
		vector <Student> Team1;	
		Team1.push_back(st1);
		Team1.push_back(st2);
		Team1.push_back(st3);
		Team1.push_back(st8);
		Team1.push_back(st11);

		Team T1(Team1);

		//creating a team of 5 middle performer students
		vector <Student> Team2;	
		Team2.push_back(st4);
		Team2.push_back(st5);
		Team2.push_back(st9);
		Team2.push_back(st12);
		Team2.push_back(st13);

		Team T2(Team2);

		//creating a team of 5 'dud' students
		vector <Student> Team3;	
		Team3.push_back(st6);
		Team3.push_back(st7);
		Team3.push_back(st10);
		Team3.push_back(st14);
		Team3.push_back(st15);

		Team T3(Team3);

		//creating a mixed team students
		// 2 star, 2 dud, 1 middle preformer
		vector <Student> Team4;	
		Team4.push_back(st1);
		Team4.push_back(st8);
		Team4.push_back(st14);
		Team4.push_back(st15);
		Team4.push_back(st9);

		Team T4(Team4);


		//(Team 1) team comparsison
		cout << "Team 1: team of all star students" << endl;
                int n = T1.team.size();
		bool check[n];
		for(int i = 0; i < T1.team.size(); i++){
		check[i] = false;
		}

		TeamCompare( T1, 2, 0, 0, check, T1.team.size());
		cout << "Adding all the values..." << endl;
		cout << "Team 1's team score : " + to_string(T1.teamScore) << endl;
		cout << endl;
		cout << endl;

		//(Team 2) team comparsison
		cout << "Team 2: team of all middle performer students" << endl;
                int n2 = T2.team.size();
		bool check2[n2];
		for(int i = 0; i < T2.team.size(); i++){
		check[i] = false;
		}

		TeamCompare( T2, 2, 0, 0, check2, T2.team.size());
		cout << "Adding all the values..." << endl;
		cout << "Team 2's team score : " + to_string(T2.teamScore) << endl;
		cout << endl;
		cout << endl;

		//(Team 3) team comparsison
		cout << "Team 3: team of all 'dud' students" << endl;
                int n3 = T3.team.size();
		bool check3[n3];
		for(int i = 0; i < T3.team.size(); i++){
		check[i] = false;
		}

		TeamCompare( T3, 2, 0, 0, check3, T3.team.size());
		cout << "Adding all the values..." << endl;
		cout << "Team 3's team score : " + to_string(T3.teamScore) << endl;
		cout << endl;
		cout << endl;

		//(Team 4) team comparsison
		cout << "Team 4: team of mixed students" << endl;
		cout << "2 star, 2 'dud', 1 middle performer" <<endl;
                int n4 = T4.team.size();
		bool check4[n4];
		for(int i = 0; i < T4.team.size(); i++){
		check[i] = false;
		}

		TeamCompare( T4, 2, 0, 0, check4, T4.team.size());
		cout << "Adding all the values..." << endl;
		cout << "Team 4's team score : " + to_string(T4.teamScore) << endl;
		cout << endl;
		cout << endl;


	        return 0;

	}


