/*
 * Disregard this class (it is not being used)
 *
 * Student.cpp
 * Description:
 * 		A Class to describe students & related
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 *
 *   Edited on: Oct. 07, 2019
 *      Author: mcolina
 *
 */

#ifndef STUDENT_H_
#define STUDENT_H_
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include "json/json.h"

using namespace std;

class Student {
	public:

		//Variables
		//string name;	//Student name
		//Skills studentSkills;	//Student skills
		//PreferredMeetingTimes timesAvailable;	//Meetingtimes
		//Affinity affinity;	//Work with someone or not
		//bool online;	//Online student:  0(false)-local student, 1(true)-online student

	    string name_;
	   // vector <string> positiveaffinity_;
	    //vector <string> negativeaffinity_;
	    vector <string> affinity_;
	    vector <int> preferredTimes_;
	    vector <string> skills_;
	    bool online_;

		Student();
		Student(string const &n, vector <string> const &s, vector <int> const &times, vector <string> const &aff, bool const &on);
		Student(const Json::Value& jsonObj);
		//bool operator==(const Student &studentToCompare) const;
		//bool operator==(const Student *studentToCompare) const;
		const string& n() const;
		const vector<string>& aff() const;
		//const vector<string>& yaff() const;
		const vector<string>& s() const;
		const vector<int>& times() const;
		const bool& online() const;
		Json::Value ToJson() const;

};



class StudentList {
private:
	  //vector<Student> students_;
public:
  vector<Student> students_;
  StudentList();
  const vector<Student>& students() const;
  void JsonSave(const char* filename);
  void JsonLoad(const char* filename);
  bool JsonLoad2(string jsonFileName);

  void AddStudent(Student s);
  //void AddStudentStudent(string const &name, vector <string> const &s, vector <int> const &times, vector <string> const &aff, bool const &on);
  const vector<Student>::iterator& begin();
  const vector<Student>::iterator& end();
};





#endif /* STUDENT_H_ */
