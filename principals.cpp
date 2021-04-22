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

Principals::Principals(string n, string t){

    nconst = n;
    tconst = t;

}

Principals::~Principals(){}

    void Principals::setPrinCharsActor(string a){
        //setter
        Actor = a;
    }

    void Principals::setPrinCharsMovie(string m){
        //setter
        movie = m;
    }

    string Principals::getPrinCharsActor(){
        //getter
        return Actor;
    }

    string Principals::getPrinCharsMovie(){
        //getter
        return movie;
    } 