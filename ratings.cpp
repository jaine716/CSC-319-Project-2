//Project #2: ratings.cpp
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
Rating::Rating(string tId, string avgR, string nVotes){
    tconst = tId;
    averageRating = avgR;
    numVotes = nVotes;
}

Rating::~Rating(){
}

void Rating::write(ostream& rateStrm){	//used by operator overload for <<
	rateStrm << tconst << " | " << averageRating << " | " << numVotes << " | " << endl;
}


void Rating::setRating(string r){
    averageRating = r;
}

string Rating::getRating(){    
    return averageRating;
}

double Rating::getRatingDouble(){
    
    try{    
        double avgRdouble = stod(averageRating);
        return avgRdouble;
    }
    catch(std::exception& e){
        cout << "Could not convert string to double." << endl;
    }
}

double Rating::getNumVotesDouble(){
    
    try{    
        double numVotesDouble = stod(numVotes);
        return numVotesDouble;
    }
    catch(std::exception& e){
        cout << "Could not convert string to double." << endl;
    }
}
