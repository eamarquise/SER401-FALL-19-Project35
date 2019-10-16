/*
 * 	SkillCompare.cpp
 *
 *  Created on: Oct. 17, 2019
 *      Author: Myles Colina
 *      Github username: mcolina
 *
 *       US#44 Task#55
 *
 *      Description:
 *      This is a prototype of algorithum A:
 *      Studetn to student skills comparison.
 *
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

//Checks the comparison score.
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



//Student skills comparision function.
void skillsCompare(Student st1, Student st2)
{
	vector <int> s1 = st1.skills;
	vector <int> s2 = st2.skills;
	int result[7];
        int sum;

	if(s1.size()==s2.size()){
	for(int i = 0; i < s1.size(); i++){
	result[i] = s1[i] - s2[i];
	}
       
        for(int i = 0; i < s1.size(); i++){
	sum += result[i];
	}
	
        sum = abs(sum);

}
 	cout << "Student comparison between: " + st1.name + " and " + st2.name << endl;
	cout << "score: " + to_string(sum) + " " + scoreCheck(sum) << endl;
        cout << endl;	
}


//Student team skills comparision function.
void teamCompare(Student st1, Student st2)
{

	
}


int main()
{
		vector <Student> allStudents;

		//vector<int> s{ 3, 0, 2, 3, 2, 2, 1 };

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

//Student to student comparisions

		//perfect skills match
		skillsCompare(st1, st2);

		//complimentary skills match
		skillsCompare(st3, st4);

		//Bad skills match
		skillsCompare(st5, st6);

		//compare 2 star students
		skillsCompare(st2, st8);

		//compare 2 star students
		skillsCompare(st8, st3);

    		//compare 2 middle preformer students
		skillsCompare(st8, st9);

                //compare 2 middle preformer students
		skillsCompare(st9, st5);

		//compare 2 'dud' students
		skillsCompare(st7, st10);

		//compare 2 'dud' students
		skillsCompare(st6, st10);

		//compare star to middle preforemer
		skillsCompare(st8, st9);

		//compare middle preformer to dud 
		skillsCompare(st5, st7);

		//compare star to dud
		skillsCompare(st1, st6);


	        return 0;

	}


