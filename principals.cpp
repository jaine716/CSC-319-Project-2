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

void Principals::setNconst(string n){
    //setter
    nconst = n;
}

void Principals::setTconst(string t){
    //setter
    tconst = t;
}

void Principals::setCategory(string c){   
    //setter
    category = c;
}

string Principals::getNconst(){
    //getter
    return nconst;
}

string Principals::getTconst(){
    //getter
    return tconst;
} 

string Principals::getCategory(){
    //getter
    return category;
} 

void Principals::addPrincipal(Principals * principal){
    principalslist.push_back(principal);
} 

string Principals::getPrinCharsActors(string n){
/*    for (int x = 0; x >= principalslist.size(); ++x)
    {
        if (n.compare(&principalslist[x]->getNconst() == nconst))
        {
            cout<<&principalslist[x]->getNconst()<<endl;
        }
        
    }
 */   
}

string Principals::getPrinCharsMovies(string tconst){
    //copy paste above once working for tconst
}