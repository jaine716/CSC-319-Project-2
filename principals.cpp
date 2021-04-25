//Project #2: principals.cpp
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

Principals::Principals(string t, string order, string n, string cat, string jb, string chars){      //constructor

    tconst = t;
    ordering = order;
    nconst = n;
    category = cat;
    job = jb;
    characters = chars;

}

void Principals::write(ostream& prinStrm){	    //used for operator overload for <<
	
	prinStrm << tconst << " | " << ordering << " | " << nconst << " | " << category << " | " << job << " | " << characters << endl;
}

Principals::~Principals(){}         //destructor

void Principals::setPrinCharsActor(string n){
    //setter
    //Actor = a;
}

void Principals::setPrinCharsMovie(string t){
    //setter
    //movie = m;
}

string Principals::getPrinCharsActor(string n){
    //getter
    return nconst;
}

string Principals::getPrinCharsMovie(string t){
    //getter
    return tconst;
} 
    