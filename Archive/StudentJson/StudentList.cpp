/*
 *
 * Disregard this class (it is not being used)
 * StudentList.cpp
 * Description:
 * 		A Class to describe students & related
 *
 *  Created on: Sep. 30, 2019
 *      Author: mcilibra
 *
 *   Edited on: Oct. 06, 2019
 *      Author: eamarquise
 *
 *      Edited on: Oct. 07, 2019
 *      Author: mcolina
 *
 */

#include "StudentList.h"
#include <iostream>
#include <vector>
#include <string>
//#include "json/json.h"

using namespace std;

Student::Student(){

}

Student::Student(string const &n, vector <string> const &s, vector <int> const &times, vector <string> const &aff, bool const &on){
	name_ = n;
	preferredTimes_ = times;
	online_ = on;
	skills_ = s;
	affinity_ = aff;
	//positiveaffinity_ = xaff;
	//negativeaffinity_ = yaff;
}

Student::Student(const Json::Value& jsonObj){
   string nameStr = "name";
   string timesStr = "preferredmeetingtimes";
   string skillsStr = "skills";
   string affStr = "affinity";
   //string xaffStr = "positivAffinity";
  // string yaffStr = "negativeAffinity";
   string onlineStr = "online";
   Json::Value::Members mbr = jsonObj.getMemberNames();
   for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
      Json::Value jsonM = jsonObj[*i];


      if(nameStr.compare(*i)==0){
         name_= jsonM.asString();
      }else if(timesStr.compare(*i)==0){
         preferredTimes_ = vector<int>();
         for(int i=0; i<jsonM.size(); i++){
        	 preferredTimes_.push_back(jsonM[i].asInt());}
         }else if(skillsStr.compare(*i)==0){
             skills_ = vector<string>();
             for(int i=0; i<jsonM.size(); i++){
            	 skills_.push_back(jsonM[i].asString());}
             }else if(affStr.compare(*i)==0){
                        affinity_ = vector<string>();
                 for(int i=0; i<jsonM.size(); i++){
                	    affinity_.push_back(jsonM[i].asString());}
                 }else if(onlineStr.compare(*i)==0){
                         online_ = jsonM.asBool();}
      }
   }



/*
bool Student::operator==(const Student &studentToCompare) const {
	if(this->name.compare(studentToCompare.name) == 0) {
		return true;
	} else {
		return false;
	}
}

bool Student::operator==(const Student *studentToCompare) const {
	if(this->name.compare(studentToCompare->name) == 0) {
		return true;
	} else {
		return false;
	}
}
*/

Json::Value Student::ToJson() const{
	Json::Value value(Json::objectValue);
      value["name"] = name_;

      Json::Value tmp(Json::arrayValue);
      for (int i=0; i<preferredTimes_.size(); i++){
      	  tmp[i] =  preferredTimes_[i]; }
      value["preferredmeetingtimes"] = tmp;

      Json::Value tmp1(Json::arrayValue);
      for (int i=0; i<skills_.size(); i++){
          tmp1[i] =  skills_[i]; }
      value["skills"] = tmp1;

      Json::Value tmp2(Json::arrayValue);
      for (int i=0; i<affinity_.size(); i++){
             tmp2[i] =  affinity_[i]; }
      value["positiveAffinity"] = tmp2;


   /*   Json::Value tmp2(Json::arrayValue);
      for (int i=0; i<positiveaffinity_.size(); i++){
          tmp2[i] =  positiveaffinity_[i]; }
      value["positiveAffinity"] = tmp2;

      Json::Value tmp2(Json::arrayValue);
      for (int i=0; i<negativeaffinity_.size(); i++){
          tmp2[i] =  negativeaffinity_[i]; }
      value["negativeAffinity"] = tmp2; */

      value["online"] = online_;

     return value;
}



StudentList::StudentList() {

	students_ = vector<Student>();

}

const vector<Student>& StudentList::students() const {
	return students_;
}

void StudentList::AddStudent(Student s){
	students_.push_back(s);
}

/*
void StudentList::AddStudentStudent(string const &n, vector <string> const &s, vector <int> const &times, vector <string> const &aff, bool const &on){
	Student student( n, s, times, aff, on);
	students_.push_back(student);
}*/
/*
void StudentList::JsonSave(const char* filename) {
	ofstream out(filename, ofstream::out);
	  Json::Value list_json(Json::objectValue), students_json(Json::arrayValue);
	  for (vector<Student>::iterator it = students_.begin(); it != students_.end(); ++it) {
	    students_json.append((*it).ToJson());
	  }
	  list_json["students"] = students_json;
	  out << list_json;
	  out.close();
}*/


void StudentList::JsonLoad(const char* filename) {
  ifstream in(filename);
  Json::Value list_json;
  in >> list_json;
  for (Json::Value::iterator it = list_json["students"].begin(); it != list_json["students"].end(); ++it) {

	//AddStudent((*it)["n"].asString(), (*it)["s"].asString(), PreferredMeetingTimes times, Affinity aff, bool online);
    //AddPerson((*it)["name"].asString(), (*it)["phone_number"].asString());
  }
  in.close();
}


//Json file reader.
bool StudentList::JsonLoad2(string jsonFileName){
	   bool ret = false;
	   Json::Reader reader;
	   Json::Value root;
	   std::ifstream json(jsonFileName.c_str(), std::ifstream::binary);
	   bool parseSuccess = reader.parse(json,root,false);
	   if(parseSuccess){
	      Json::Value::Members mbr = root.getMemberNames();
	      for(vector<string>::const_iterator i = mbr.begin(); i!= mbr.end(); i++){
	         //cout << *i << " " << endl;
	        Json::Value jsonMedia = root[*i];
	         Student * aStudent = new Student(jsonMedia);
	         //students_[*i] = *aStudent;
	         AddStudent(*aStudent);
	         //cout << "adding ";
	         //aStudent->print();
	      }
	      ret = true;
	   }
	   return ret;
	}



















