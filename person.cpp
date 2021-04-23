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

Person:: Person(string str){     //constructor
            nconst = str;
            //...recieve more information?
        }

Person::~Person(){      //destructor

    }

string Person::getID(){
        return nconst;
    }

void Person::addTitle( MovieTitle * m ) {
        titleList.push_back(m);
    }

void Person::addToAppearsWith(Person * p){
        appearsWithList.push_back(p);
    }

void Person::addToKnownForList(MovieTitle * m){
        knownForList.push_back(m);
    }


