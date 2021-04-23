//Project #2: movie.cpp
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

MovieTitle::MovieTitle(string str){
    tconst = str;
    //should recieve more info here...
}

MovieTitle::~MovieTitle(){

}

double MovieTitle::getRating()
{
                
}

void MovieTitle::getPrincipals (Principals * prin){   
    principalList.push_back(prin);            
}

void MovieTitle::getAllActors (Person * actor){
     actorList.push_back(actor);           
}


void MovieTitle::addActor( Person * p ){
    actorList.push_back( p );
}

string MovieTitle::getID(){
        return tconst;
    }

double MovieTitle::setScore(double pscore){
    this->score = pscore;
}

