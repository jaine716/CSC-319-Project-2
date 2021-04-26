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
//#include <boost/algorithm/string.hpp>

using std::cout;
using std::endl;
using std::ostream;
using std::istringstream;
using std::istream;
//using namespace boost::algorithm

using namespace std;

#include "project2.h"

/*******insert the addresses of the data files on your local machine here:*********/
#define MOVIE_FILE "/home/jaine/school/CSC319/Project 2/shortInputFiles/title.tsv"
#define PERSON_FILE "/home/jaine/school/CSC319/Project 2/shortInputFiles/name.tsv"
#define PRINCIPAL_FILE "/home/jaine/school/CSC319/Project 2/shortInputFiles/principals.tsv"
#define RATING_FILE "/home/jaine/school/CSC319/Project 2/shortInputFiles/ratings.tsv"

map<string, Person *> mapPersons;       //map of persons
map<string, MovieTitle *> mapMovies;         //map of movies

/////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////////////
int main(){

    // main body of program here

    string id;
    double score = 0;

    loadDataSet();        //un-comment to load data set

    /*Command line: Project2 <name input filename> <title input filename> <principals input filename> 
            <ratings input filename> <score output filename> <person Id= nconst > <level of indirection>*/

    //below is temporary
    cout << "---------------Project #2---------------" << endl;
  /*  cout << "Enter unique identifier of actor: ";
    cin >> id;

    score = calculateScore(id);

    cout << "The score for this actor is: " << score << endl;
*/
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
void loadMovie(){
    ifstream inFile;
    vector<string> result;
    string cell;
    string tId, tType, pTitle, oTitle, isAd, sYear, eYear, rtMin, genr;

	inFile.open(MOVIE_FILE);

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.
            string str(buf);
            istringstream strstrm(str);
           
           //create a vector of tab-delimeted strings for each line of the file
            while(getline(strstrm, cell, '\t')){
                result.push_back(cell);
            }

            //extract values from each element of the vector and assign them to individual class members
            tId = result.at(0);
            tType = result.at(1);
            pTitle = result.at(2);
            oTitle = result.at(3);
            isAd = result.at(4);
            sYear = result.at(5);
            eYear = result.at(6);
            rtMin = result.at(7);
            genr = result.at(8);

            //create new object m (class Movie)
            MovieTitle * m = new MovieTitle(tId, tType, pTitle, oTitle, isAd, sYear, eYear, rtMin, genr);
            //create map of movies and movie IDs (tconst)
            mapMovies.insert( pair<string, MovieTitle *> (m->getID(), m));

            //print object m and all of it's elements
            cout << *m;
            cout << "-------" << endl;
            result.clear();
            
		}

		inFile.close();
        
        //print map of values
     /*   for(auto it = mapMovies.begin(); it != mapMovies.end(); ++it){
            cout << it->first << " * " << it->second << endl;
        }   */
	}

}

void loadPerson(){
    ifstream inFile;
    vector<string> result;
    string cell;
    string pId, pName, bYear, dYear, pProf, knownFor;

	inFile.open(PERSON_FILE);

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.
            string str(buf);
            istringstream strstrm(str);
           
           //create a vector of tab-delimeted strings for each line of the file
            while(getline(strstrm, cell, '\t')){
                result.push_back(cell);
            }

            //extract values and assign them to class members
            pId = result.at(0);
            pName = result.at(1);
            bYear = result.at(2);
            dYear = result.at(3);
            pProf = result.at(4);
            knownFor = result.at(5); 

            //create new Person object
            Person * p = new Person(pId, pName, bYear, dYear, pProf, knownFor);
            mapPersons.insert( pair<string, Person *> (p->getID(), p));

            //print object p and all of it's elements
            cout << *p;
            cout << "-------" << endl;
            result.clear();
            
		}

		inFile.close();

        //print map of values
    /*    for(auto it = mapPersons.begin(); it != mapPersons.end(); ++it){
            cout << it->first << " * " << it->second << endl;
        }   */
	}
}

void loadPrincipal(){
    ifstream inFile;
    vector<string> result;
    string cell;
    string t, order, n, cat, jb, chars;

	inFile.open(PRINCIPAL_FILE);

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.
            string str(buf);
            istringstream strstrm(str);
           
        //create a vector of tab-delimeted strings for each line of the file
        while(getline(strstrm, cell, '\t')){
            result.push_back(cell);
        }
        
        t = result.at(0);
        order = result.at(1);
        n = result.at(2);
        cat = result.at(3);
        jb = result.at(4);
        chars = result.at(5);

        Principals * pr = new Principals(t, order, n, cat, jb, chars);

        auto itFindPerson = mapPersons.find(n);

        string str1 = itFindPerson->first;      //1st component of the pair
        Person * p = itFindPerson->second;      //2nd component of the pair

        auto itFindMovie = mapMovies.find(t);

        string str2 = itFindMovie->first;       //1st component of pair
        MovieTitle * m = itFindMovie->second;   //2nd component of pair

        if ( p != nullptr && m != nullptr ){
            p->addTitle( m );
            m->addActor( p );
        }

        //print out list of principals
        cout << *pr << endl;
        cout << "-------" << endl;
        result.clear();
    
        } //endwhile

        inFile.close();
    } //endif
}

void loadRatings(){
        ifstream inFile;
    vector<string> result;
    string cell;
    string tId, avgR, nVotes;

	inFile.open(RATING_FILE);

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.
            string str(buf);
            istringstream strstrm(str);
           
           //create a vector of tab-delimeted strings for each line of the file
            while(getline(strstrm, cell, '\t')){
                result.push_back(cell);
            }

            //extract values and assign them to class members
            tId = result.at(0);
            avgR = result.at(1);
            nVotes = result.at(2);
            
            //create new Person object
            Rating * r = new Rating(tId, avgR, nVotes);
            

            //print object p and all of it's elements
            cout << *r;
            cout << "-------" << endl;
            result.clear();
            
		}
		inFile.close();
	}
}

void loadDataSet(){

    loadMovie();

    loadPerson();

    loadPrincipal();

    loadRatings();
}


