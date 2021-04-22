//Project #2: project.cpp
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
using std::istream;

using namespace std;

#include "project2.h"

map<string, Person *> mapPersons;       //map of persons
map<string, Movie *> mapMovies;         //map of movies

/////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////////////
int main(){

    // main body of program here

    string id;
    double score;

    //loadDataSet();        //un-comment to load data set

    /*Command line: Project2 <name input filename> <title input filename> <principals input filename> 
            <ratings input filename> <score output filename> <person Id= nconst > <level of indirection>*/

    //below is temporary
    cout << "---------------Project #2---------------" << endl;
    cout << "Enter unique identifier of actor: ";
    cin >> id;

    score = calculateScore(id);

    cout << "The score for this actor is: " << score << endl;

    /*Producing the output:

    1-The program must produce on the console (cout) the calculated score for the <person Id= nconst >.
    2-For each person (nconst), which are used to calculate the score of <person Id= nconst >, you must calculate their own score. 
    In the file <score output filename>, you must output in a tab-delimited format(one per line): <nconst> \t <score>. 
    The output must be sorted by ascending nconst. */

}
/////////////////////////////////////////CALCULATE SCORE////////////////////////////////////////////////////////////////
double calculateScore(string id){
    double score = 0;

    return score;
}

/////////////////////////////////////////LOADING THE DATA////////////////////////////////////////////////////////////////
/*
void loadMovie(istream & is){
    char buf[255];                  //a literal must end with binary zero
    while(is.getline(buf, 255)){    //read data from file object and put it into string
        string str(buf);
        Movie * m = new Movie( str );
        mapMovies.insert( pair<string, Movie *> (m->getID(), m));
    }
}

void loadPerson(istream & is){
    char buf[255];                  //a literal must end with binary zero
    while(is.getline(buf, 255)){    //read data from file object and put it into string
        string str(buf);
        Person * p = new Person( str );
        mapPersons.insert( pair<string, Person *> (p->getID(), p));
    }
}

void loadPrincipal(istream & is){
    char buf[255];                  //a literal must end with binary zero
    while(is.getline(buf, 255)){    //read data from file object and put it into string
        string str(buf);

        //...hard code length... for demo purposes only
        string mId = str.substr(0,1);
        string pId = str.substr(2,3);

        auto itFindPerson = mapPersons.find(pId);

        string str1 = itFindPerson->first;      //1st component of the pair
        Person * p = itFindPerson->second;      //2nd component of the pair

        auto itFindMovie = mapMovies.find( mId );

        string str2 = itFindMovie->first;       //1st component of pair
        Movie * m = itFindMovie->second;        //2nd component of pair

        if ( p != nullptr && m != nullptr ){
            p->addTitle( m );
            m->addActor( p );
        }
    
    }
}


void loadDataSet(){

    string testMovieData( "1\n2\n");
    istringstream isMovie( testMovieData);

    loadMovie( isMovie );

    string testPersonData( "100\n200\n");
    istringstream isPerson( testPersonData);

    loadPerson( isPerson);

    string testPrincipalData("1,100\n1,200\n2,100\n");
    istringstream isPrincipal( testPrincipalData );

    loadPrincipal( isPrincipal );

}
*/

