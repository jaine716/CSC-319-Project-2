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

MovieTitle::MovieTitle(string tId, string tType, string pTitle, string oTitle, string isAd, string sYear, string eYear, string rtMin, string genr){

    tconst = tId;
    titleType = tType;
    primaryTitle = pTitle;
    originalTitle = oTitle;
    isAdult = isAd;
    startYear = sYear;
    endYear = eYear;
    runtimesMinutes = rtMin;
    genres = genr;

}

void MovieTitle::write(ostream& movStrm){	    //used for operator overload for <<
	movStrm << tconst << " | " << titleType << " | " << primaryTitle << " | " << originalTitle << " | " << isAdult << " | " << startYear << " | " << endYear << " | " << runtimesMinutes << " | " << genres << endl;
}

MovieTitle::~MovieTitle(){
}

double MovieTitle::getRating(){                
}
string MovieTitle::getTitle(){
    return primaryTitle;
}

MovieTitle* MovieTitle::getAddress(){   
    return this;
}

vector<Person *> MovieTitle::getAllActors (){
    return actorList;           
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

