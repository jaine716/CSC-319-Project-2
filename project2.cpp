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
#include <algorithm>
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
#define MOVIE_FILE "/home/jaine/school/CSC319/Project 2/input/title.tsv"
#define PERSON_FILE "/home/jaine/school/CSC319/Project 2/input/name.tsv"
#define PRINCIPAL_FILE "/home/jaine/school/CSC319/Project 2/input/principals.tsv"
#define RATING_FILE "/home/jaine/school/CSC319/Project 2/input/ratings.tsv"

map<string, Person *> mapPersons;       //map of persons
map<string, MovieTitle *> mapMovies;         //map of movies
map <string, string> mapPersonsMovieTitles;     //map of movie titles and personIDs


/////////////////////////////////////////////MAIN///////////////////////////////////////////////////////////////////
int main(){

    // main body of program here

    string id;
    string actorName;
    double score = 0;
    Person * foundActor = nullptr;
    Person * header = nullptr;
    vector<MovieTitle *> movieListObj;
    vector<string> movieList;
    vector<Person *> actorList;

    vector<Person *> appearsWith;
    vector<Person *> appearsWithTot;

    vector<MovieTitle *> appearsIn1;
    vector<MovieTitle *> appearsIn2;
    vector<MovieTitle*> appearsInTot;

    cout << "---------------Project #2---------------" << endl;

    loadDataSet();        //un-comment to load data set

    /*Command line: Project2 <name input filename> <title input filename> <principals input filename> 
            <ratings input filename> <score output filename> <person Id= nconst > <level of indirection>*/

    //below is temporary

    char cont = 'y';
    while (cont == 'y'){
    
    cout << "Enter unique identifier of actor: ";
    cin >> id;
    auto result = mapPersons.find(id);
    
    if(result != mapPersons.end()){     //if a match is found
        auto h = mapPersons.find("nconst");
        
        header = h->second;
        foundActor = result->second;

        movieList = result->second->getTitleListStr(); 
        actorName = result->second->getPrimaryName();

        cout << "\n\nThe actor's name is: " << actorName  << endl;
        cout << endl << "\t" << *header << endl;
        cout << "\t" << *foundActor << endl;

        //find all movies actor apears in
        cout << "Movie list for " << actorName  << ": " << endl; 
        cout << endl;

        //make a vector of MovieTitle that the actor appears in
        movieListObj = findMovies(movieList);
        cout << "\t" << movieListObj;

        cout << "\n" << actorName << " appears with: \n" << endl;

        
        //get all the actors that appear in movies alongside actor being searched for
    //**********add method to eliminate someone appearing with themselves***********//
    
        for(auto it = movieList.begin(); it != movieList.end(); ++it){
            
            //cout << (*it) << " " << movieList.size() << endl;
            auto appW = mapMovies.find(*it);
            if(appW != mapMovies.end()){        //if there is a non-zero list of movies
                appearsWith = appW->second->getAllActors();
                appearsWithTot.insert(appearsWithTot.end(), appearsWith.begin(), appearsWith.end());
                //cout << "appears with: " << appearsWith << endl;
            }
            else{
                cout << "\tNo associated actors found." << endl;
            }
        }
        
        //removie duplicates
        std::sort(appearsWithTot.begin(),appearsWithTot.end());
        auto du = std::unique(appearsWithTot.begin(), appearsWithTot.end());
        appearsWithTot.erase(du, appearsWithTot.end());
        

        //remove if they appear with themselves
        for (auto it = appearsWithTot.begin(); it != appearsWithTot.end(); ++it){        
            if(*it == foundActor){
                //cout << "duplicate erased" << endl;
                appearsWithTot.erase(it);
                it--;        //don't point to something that no longer exists     
            }
        }
          
        cout << "\t" << appearsWithTot;
        cout << endl;

        //get all the movies that those associated actors appeared in
        if(appearsWithTot.begin() != appearsWithTot.end()){
            cout << "\n" << actorName << "'s associates appear in the following titles: \n" << endl;

            for(auto it = appearsWithTot.begin(); it != appearsWithTot.end(); ++it){
                    
                auto movW = mapPersons.find((*it)->getID());
                if(movW != mapPersons.end()){
                    appearsIn1 = findMovies(movW->second->addTitleList());      //gets titles from principals (vector of string)
                    appearsIn2 = findMovies(movW->second->getTitleListStr());      //get titles from person (vector of string)
                    appearsInTot.insert(appearsInTot.end(), appearsIn1.begin(), appearsIn1.end());      //concatenate the vectors
                    appearsInTot.insert(appearsInTot.end(), appearsIn2.begin(), appearsIn2.end());
                }
                else{
                    cout << "\tAssociated movie not found." << endl;
                }
            }
        }
        else{
            cout << "\tCannot search for associated movies (no associated actors were found)." << endl;
        }
        //remove duplicates and sort
        std::sort(appearsInTot.begin(),appearsInTot.end());
        auto dup = std::unique(appearsInTot.begin(), appearsInTot.end());
        appearsInTot.erase(dup, appearsInTot.end());

        cout << "\t" << appearsInTot << endl;

    }
    else{
        cout << "Actor's name not found." << endl;
    }
 /*   score = calculateScore(id);

    cout << "The score for this actor is: " << score << endl;*/

    /*Producing the output:

    1-The program must produce on the console (cout) the calculated score for the <person Id= nconst >.
    2-For each person (nconst), which are used to calculate the score of <person Id= nconst >, you must calculate their own score. 
    In the file <score output filename>, you must output in a tab-delimited format(one per line): <nconst> \t <score>. 
    The output must be sorted by ascending nconst. */

    cout << "Do you wish to search for another person?  [type 'y' for yes, 'n' for no]: ";
    cin >> cont;


    }

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

    cout << "Loading Movies.....\n" << endl;

	inFile.open(MOVIE_FILE);

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
        int count = 0;
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.

            if((++count % 1000) == 0){
                cout << ".";
            }

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
            //cout << *m;
            result.clear();
		}

		inFile.close();
        cout << "Movies Loaded Successfully" << endl;
        //print map of values
/*        for(auto it = mapMovies.begin(); it != mapMovies.end(); ++it){
            cout << it->first << " * " << it->second << endl;
        }   */
	}
    else{
        cout << "Unable to open movie file." << endl;
    }
    cout << "-------" << endl;
}

void loadPerson(){
    ifstream inFile;
    vector<string> result;
    string cell;
    string pId, pName, bYear, dYear, pProf, knownFor;

    cout << "Loading Names.....\n" << endl;

	inFile.open(PERSON_FILE);
    int count = 0;

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.

            if((++count % 1000) == 0){
                cout << ".";
            }

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
            mapPersonsMovieTitles.insert( pair<string, string> (p->getID(), p->getKnownForTitles()));
            
            auto itFindMovies = mapPersonsMovieTitles.find(pId);
            string movieList = itFindMovies->second;
            vector<string> titleList;
            vector<MovieTitle *> titleListObj;

            //parse out knownForTitles
            istringstream strm(movieList);
            string cell;

            while(getline(strm, cell, ',')){
                titleList.push_back(cell);
                //cout << " cell: " << cell << " ";
            }

            //get a vector of the movies in knownForTitles
            titleListObj = findMovies(titleList);

            //cout << endl << p->getPrimaryName() << ": ";

            int i = 0;
            for(auto it = titleListObj.begin(); it != titleListObj.end(); ++it){
                
                if((p != nullptr) && (titleListObj[i] != nullptr)){
                    p->addTitle(titleListObj[i]);
                    auto itFindMov = mapMovies.find(titleListObj[i]->getID());
                    MovieTitle * m = itFindMov->second;
                    m->addActor(p);
                    //cout << titleListObj[i]->getTitle() << " " << titleListObj[i]->getID() << " | ";
                }
                i++;
            }
            //cout << endl;

            //print object p and all of it's elements
            //cout << *p;
            result.clear();
            
		}

		inFile.close();
        cout << "Names Loaded Successfully" << endl;
        //print map of values
        /*for(auto it = mapPersonsMovieTitles.begin(); it != mapPersonsMovieTitles.end(); ++it){
            cout << it->first << " * " << it->second << endl;
        }   */
	}
    else{
        cout << "Unable to open name file." << endl;
    }
    cout << "-------" << endl;
}

void loadPrincipal(){
    ifstream inFile;
    vector<string> result;
    string cell;
    string t, order, n, cat, jb, chars;

    cout << "Loading Principals.....\n" << endl;

	inFile.open(PRINCIPAL_FILE);
    int count = 0;

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.

            if((++count % 1000) == 0){
                cout << ".";
            }

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
        //if no match found? do something

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
        //cout << *pr;
        result.clear();
    
        } //endwhile


        inFile.close();
        cout << "Loaded Principals Successfully" << endl;
    } //endif
    else{
        cout << "Unable to open principals file." << endl;
    }
    cout << "-------" << endl;
}

void loadRatings(){
    ifstream inFile;
    vector<string> result;
    string cell;
    string tId, avgR, nVotes;

    cout << "Loading Ratings.....\n" << endl;

	inFile.open(RATING_FILE);
    int count = 0;

    if ( inFile.is_open() ) {
		char buf[255]; //a literal must end by a binary zero '\0'
		while( inFile.getline(buf, 255) ){ //read data from file object and put it into string.

            if((++count % 1000) == 0){
                cout << ".";
            }

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
            //cout << *r;
            result.clear();
		}
		inFile.close();
        cout << "Loaded Ratings Successfully" << endl;
	}
    else{
        cout << "Unable to open ratings file." << endl;
    }
    cout << "-------" << endl;
}

void loadDataSet(){

    loadMovie();

    loadPerson();

    loadPrincipal();

    loadRatings();
}

/////////////////////////////////Find List of Movies for Each Actor//////////////////////////////////////////////////
vector<MovieTitle *> findMovies(vector<string> movieList){

    vector<MovieTitle *> movieListObj;
    string tId;
    MovieTitle * result = nullptr;
    
    for(auto it = movieList.begin(); it != movieList.end(); ++it){
            tId = (*it);
            auto mov = mapMovies.find(tId);
            if(mov != mapMovies.end()){
                result = mov->second;
                movieListObj.push_back(result);
            }
            else{
                //cout << "\tMovie not found." << endl;
            }
        }
    return movieListObj;   
}

