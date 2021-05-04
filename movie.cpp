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
#include <algorithm>

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


double MovieTitle::setScore(){
    //this->score = pscore;
}

double MovieTitle::getStartYearDouble(){
    
    try{    
        double startYearDouble = stod(startYear);
        return startYearDouble;
    }
    catch(std::exception& e){
        cout << "Could not convert string to double." << endl;
    }    
}

vector<string> MovieTitle::addGenreListVector() {

    string genrestr = this->genres;
    istringstream strstrm(genrestr);
    string cell;

    while(getline(strstrm, cell, ',')){

        GenresListStr.push_back(cell);
        //cout << cell << " ";
    }
       
    return GenresListStr;
}

double MovieTitle::applyGenrePremium(double rating){

    double ratingPremium; 
    vector<double> rPremVec;
    string genreStr;
    if(GenresListStr.size() != 0){   //if the list of genres is not empty
        for(auto it = GenresListStr.begin(); it!= GenresListStr.end(); ++it){
            genreStr = (*it);
        
            if(genreStr == "Comedy"){
                ratingPremium = ( rating + (rating * 0.2 ) );
                rPremVec.push_back(ratingPremium);
            }
            else if(genreStr == "Drama"){
                ratingPremium = (rating * 1.4);
                rPremVec.push_back(ratingPremium);
            }
            else if(genreStr == "Romance"){
                ratingPremium = (rating - ( rating * 0.2 ) );
                rPremVec.push_back(ratingPremium);
            }
            else if(genreStr == "Horror"){
                ratingPremium = (rating - ( rating * 0.3 ) );
                rPremVec.push_back(ratingPremium);
            }
            else{
                ratingPremium = (rating - ( rating * 0 ) );
                rPremVec.push_back(ratingPremium);
                //std::cout << "Movie genre not found \n";
            }
    
        
        } //end for loop
        ratingPremium = *max_element(rPremVec.begin(), rPremVec.end());
    }       
    else{
            ratingPremium = rating;
            cout << "\nNo genre list available." << endl;
        }

    
    
return ratingPremium; 
}