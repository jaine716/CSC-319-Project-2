//Project #2: person.cpp
//Jaine E Perotti
//Riley Smith
//Levy Sanon

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <memory>
#include <fstream>   //to do file input & output
#include <iomanip>  // io formatting

using std::cout;
using std::endl;
using std::ostream;
using std::istringstream;

using namespace std;

#include "project2.h"

//Put member functions, constructors, destructors, copy constructors, copy-assignment operators, etc. in here

Person::Person(string pId, string pName, string bYear, string dYear, string pProf, string knownFor){       //constructor
    nconst = pId;
    primaryName = pName;
    birthYear = bYear;
    deathYear = dYear;
    primaryProfession = pProf;
    knownForTitles = knownFor;
}

Person::~Person(){      //destructor

}

void Person::write(ostream& perStrm){	//used by operator overload for <<
	
	perStrm << nconst << " | " << primaryName << " | " << birthYear << " | " << deathYear << " | " << primaryProfession << " | " << knownForTitles << endl;
}

string Person::getID(){
        return nconst;
    }
string Person::getPrimaryName(){
    return primaryName;
}

vector<string> Person::addTitleList() {

        string titlestr = this->knownForTitles;
        istringstream strstrm(titlestr);
        string cell;

        while(getline(strstrm, cell, ',')){

            titleListStr.push_back(cell);
            //cout << cell << " ";
        }
        
    return titleListStr;
}

void Person::addTitle(MovieTitle * m) {
    titleList.push_back(m);
}

void Person::addToAppearsWith(Person * p){
        appearsWithList.push_back(p);
    }

void Person::addToKnownForList(MovieTitle * m){
        knownForList.push_back(m);
    }


