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
#include <fstream>      //to do file input & output
#include <iomanip>      // io formatting
#include <algorithm>
#include <cassert>

using std::cout;
using std::endl;
using std::ostream;
using std::istringstream;
using std::istream;

using namespace std;

#include "project2.h"

//global variables
map<string, Person *> mapPersons;               //map of persons
map<string, MovieTitle *> mapMovies;            //map of movies
map <string, string> mapPersonsMovieTitles;     //map of movie titles and personIDs
map <string,Rating *> mapMoviesRatings;         //map of movies and their ratings
map <Person *, double> mapAssociateScore;       //map of associate and their score
vector<Person *> whoAppearedInSearch;           //keep track of everyone who has contributed to scoring
double score = 0;                               //holds the score of the actor (searched for on command line)

//holds the file paths retrieved from the command line
char * PERSON_FILE;
char * MOVIE_FILE;
char * PRINCIPAL_FILE;
char * RATING_FILE;
char * OUTPUT_FILENAME;

//Current Command Line Arguments:
/* ./Project2 <name input filename> <title input filename> <principals input filename> <ratings input filename> <score output filename> 
<person Id= nconst > <level of indirection>

e.g. type (on one line):
"./Project2 "/home/jaine/school/CSC319/Project 2/shortInputFiles/name.tsv" "/home/jaine/school/CSC319/Project 2/shortInputFiles/title.tsv" 
"/home/jaine/school/CSC319/Project 2/shortInputFiles/principals.tsv" "/home/jaine/school/CSC319/Project 2/shortInputFiles/ratings.tsv" 
"/home/jaine/school/CSC319/Project 2/shortInputFiles/scoreOutput.tsv" nm6036532 2" on the command line when you run the program */

//Notes on Logic of the Program:
/*  * An indirection level of 0 will calculate just the score of the actor's movies.  A level of 1 will calculate the score of the actors'
      movis plus their associates.  Level of 2+ will recursively repeat the process but on each associate, and so on to the nth level of indirection.
    * This program populates the list of MovieTitles associated with a given actor by scanning BOTH the names.tsv file for knownForTitles
      AND the principals.tsv file wherever an actor is listed as a principal in a movie.

    * Score is a global variable that is the sum of all the scores from each level of indirection (movie score + movies scores of co-stars)
      and represents the score of the original actor.
    * The boolean incTotalScore tells the program whether or not the calculation is for the original actor, and whether or not to increment
      the global score.
    * aScore is a local variable in main() that is used to populate the output file with the scores of all the people who contributed to the
      score of the original actor to a level of indirection of 0.
*/
////////////////////////////////////////////////////////// MAIN ///////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){

    // main body of program here

    //only run the program if there are 8 total command line arguments
    if( argc != 8 ) { 
        cout << "\nIncorrect number of arguments on command line.  Use format: \n";
        cout << "\n[executable file name] [file name] [file title] [file principals] [file ratings] [file output] [string id] [int indirection]\n"; exit(-1); 
    } 

    //assign command line arguments to variables
    PERSON_FILE = argv[1];                          //person file  
    MOVIE_FILE = argv[2];                           //movie file
    PRINCIPAL_FILE = argv[3];                       //principal file
    RATING_FILE = argv[4];                          //rating file
    OUTPUT_FILENAME = argv[5];                      //output file        
    string id = argv[6];                            //nconst (person ID)
    string LOI = argv[7];                           //level of indirection (string)

    int levelOfIndirection;
    
    //convert LOI from string to int and store in levelOfIndirection
    try{    
        levelOfIndirection = stoi(LOI);     //stoi() is a function which converts a string to int
    }
    catch(std::exception& e){               //if conversion is not successful, handle the exception
        cout << "Could not convert string to int." << endl;
    }   

    //load the data sets
    loadDataSet();

    //score the actor
    scorePerson(id, levelOfIndirection, true);       

    //print the score
    cout << score << endl; 

}   //end main

////////////////////////////////////// Get Score for an Actor to the Nth Level of Indirection //////////////////////////////////////////////////////

double scorePerson(string id, int levelOfIndirection, bool incTotalScore){

    //declare variables used in scorePerson
    string actorName;
    Person * foundActor = nullptr;
    Person * header = nullptr;
    vector<MovieTitle *> movieListObj;
    vector<string> movieList;
    vector<Person *> actorList;    
    vector<Person *> appearsWithTot;
    vector<MovieTitle*> appearsInTot;
    double aScore;                      //aScore is different from score (global), it only applies to 0 level of indirection searches from generateOutputFile()


    //search for the person
    auto result = mapPersons.find(id);      
    
    if(result != mapPersons.end()){             //if a match is found
        auto h = mapPersons.find("nconst");     //this finds the header line
        
        header = h->second;                 //the first line of the file has the header (nconst, primaryName, knownForTitles, etc.)
        foundActor = result->second;        //this returns the Person object (actor information) if the actor is found

        whoAppearedInSearch.push_back(foundActor);      //keep track of who's appeared in the search
        
        movieList = result->second->getTitleListStr();      //this is the list of their movies, all in one string
        
    /********** find all movies actor apears in **********/

        //make a vector of MovieTitle that the actor appears in 
        movieListObj = getMovieObjList(movieList);                  //take the list of movies (all one string) and turn it into a vector of Movie objects

        //remove duplicates and sort
        movieListObj = removeDuplicateMovies(movieListObj);

    /********** get all the actors that appear in movies alongside actor being searched for ***********/           
        appearsWithTot = findAssociatedActors(movieList);

        //remove if they appear with themselves
        for (auto it = appearsWithTot.begin(); it != appearsWithTot.end(); ++it){        
            if(*it == foundActor){
              
                appearsWithTot.erase(it);
                it--;        //don't point to something that no longer exists     
            }
            if(levelOfIndirection == 1)                  //if on 2nd to last level of ind. add the appearsWithTot to whoAppearedInSearch    
                whoAppearedInSearch.push_back(*it);      //keep track of who's appeared in the search
        }

    /************ Score the Movies ********************/

        if(levelOfIndirection == 1)   //generate the score and file on 2nd to last iteration (otherwise the scores are for the next batch of associated actors)
            whoAppearedInSearch = removeDuplicatePersons(whoAppearedInSearch);
        
        if(std::find(whoAppearedInSearch.begin(), whoAppearedInSearch.end(), foundActor) != whoAppearedInSearch.end()){       //only add the score if the actor hasn't already contributed to the total
            if(incTotalScore == true)                                                //only increment the global score when called from main()
                score += (scoreMovieList(movieListObj, false));                      //calculate the scores of the list of movies
            aScore = (scoreMovieList(movieListObj, false));                          //this score is for 0 level of indirection searches only (for output file generation of actor+their co-stars' movies score)
        }
        
    /************* create the output file *************/
        if(levelOfIndirection == 1){                //generate the file on 2nd to last iteration (otherwise the scores are for the next batch of associated actors)
            generateOutputFile(whoAppearedInSearch);     //generate the output file and go back to main
        }

       if(levelOfIndirection != 0){
            //do this process all over again for every actor on the list
            for(auto it = appearsWithTot.begin(); it != appearsWithTot.end(); ++it){
                scorePerson((*it)->getID(), levelOfIndirection-1, true);                      //recursive call of scorePerson()           
            }
        }     
    }
    else{
        cout << "Actor's name not found." << endl;      //print message if no actor's name is found
    }
    return aScore;
}

///////////////////////////////// Get List of Movie Objects for Each Actor From Vector of Strings /////////////////////////////////
vector<MovieTitle *> getMovieObjList(vector<string> movieList){

    vector<MovieTitle *> movieListObj;
    string tId;
    MovieTitle * result = nullptr;
    
    for(auto it = movieList.begin(); it != movieList.end(); ++it){      //go through the movie list
            tId = (*it);
            auto mov = mapMovies.find(tId);     //find the titleID in the movie map
            if(mov != mapMovies.end()){         //check if the title was found
                result = mov->second;           //result is the movie object
                movieListObj.push_back(result); //push the found movie into the list of movie objects
            }
            else{
                //cout << "\tMovie not found." << endl;
            }
        }
    return movieListObj;   //return the list of movie objects
}

/////////////////////////////////////// Find Associated Actors (Co-Stars) //////////////////////////////////////////////
vector<Person *> findAssociatedActors(vector<string> movieList){

    vector<Person *> appearsWith;
    vector<Person *> appearsWithTot;

    for(auto it = movieList.begin(); it != movieList.end(); ++it){      //go through the movie list
            
        auto appW = mapMovies.find(*it);    //find the movie in the map
        if(appW != mapMovies.end()){        //if there is a non-zero list of movies
            appearsWith = appW->second->getAllActors();     //find the associated actors
            appearsWithTot.insert(appearsWithTot.end(), appearsWith.begin(), appearsWith.end());       //insert those actors into the appearsWithTot vector of <Person *>
            
        }
        else{
            cout << "\tNo associated actors found." << endl;
        }
    }
        
    //remove duplicates
    appearsWithTot = removeDuplicatePersons(appearsWithTot);

    return appearsWithTot;  //return the list of actors <Person *>
}

/////////////////////////////////////////// Find Associate's Movies ///////////////////////////////////////////////////
vector<MovieTitle *> findAssociateMovies(vector <Person *> appearsWithTot){

    vector<MovieTitle *> appearsInTot;
    vector<MovieTitle *> appearsIn1;
    vector<MovieTitle *> appearsIn2;
        
    for(auto it = appearsWithTot.begin(); it != appearsWithTot.end(); ++it){
                    
        auto movW = mapPersons.find((*it)->getID());
        if(movW != mapPersons.end()){
            appearsIn1 = getMovieObjList(movW->second->addTitleList());                         //gets titles scanned from principals file (vector of string)
            appearsIn2 = getMovieObjList(movW->second->getTitleListStr());                      //get titles from scanned from names file (vector of string)
            appearsInTot.insert(appearsInTot.end(), appearsIn1.begin(), appearsIn1.end());      //concatenate the vectors
            appearsInTot.insert(appearsInTot.end(), appearsIn2.begin(), appearsIn2.end());
        }
        else{
            cout << "\tAssociated movie not found." << endl;
        }
    }
        
    //remove duplicates and sort
    appearsInTot = removeDuplicateMovies(appearsInTot);

    return appearsInTot;
}
///////////////////////////////////////////// Score Movie List ////////////////////////////////////////////////////////
double scoreMovieList(vector<MovieTitle *> appearsInTot, bool printOutput){

    double scoreLoc = 0;

    //remove duplicates and sort
    appearsInTot = removeDuplicateMovies(appearsInTot);

    for(auto it = appearsInTot.begin(); it!= appearsInTot.end(); ++it){

        auto movID = (*it)->getID();
        auto r = mapMoviesRatings.find(movID);      //search for the rating associated with the movie ID
        auto m = mapMovies.find(movID);             //search for the movie associated with the movie ID

        if(r != mapMoviesRatings.end() && m != mapMovies.end()){                    //if rating and title are found
            double ratingD = r->second->getRatingDouble();                          //get the rating (type double) of the movie
            double numVotes = r->second->getNumVotesDouble();                       //get the number of votes (type double)
            vector<string> genreList = m->second->addGenreListVector();             //populate the vector of genres
            double scorePremium = m->second->applyGenrePremium(ratingD*numVotes);   //apply the premium based on the highest scoring genre

            if(printOutput == true)
            cout << "\t\tage: " << (2020 - m->second->getStartYearDouble()) << " | ";

            if((2020 - m->second->getStartYearDouble()) < 50){            //only award points if the movie is less than 50 years old
                scorePremium = scorePremium * (100 - (2020 - m->second->getStartYearDouble()))/100;
            }
            else{       //otherwise the score is zero
                scorePremium = 0;
            }

            scoreLoc+=scorePremium;        //increment the total score

            if(printOutput == true)
            cout << m->second->getTitle() << " | Score: " << scorePremium << endl;
            
        }
        else{       //if no rating is found

            if(printOutput == true)
            cout << "\t\t" << (*it)->getTitle() << " | rating not found." << endl;
        }
    }
    if(printOutput == true)
    cout << "\n\tSum : " << scoreLoc << endl << endl;
    return scoreLoc;
}

//////////////////////////////////////// Generate the Output File ///////////////////////////////////////////////////
void generateOutputFile(vector<Person *> appearsWithTot){
    
    fstream out_file;                   //filestream for the output file
    vector<string> personScores;        //holds each line that will go into the output file (personID, name, and score - tab-delimeted)
    double actorScore;
    string actorScoreStr;

    out_file.open(OUTPUT_FILENAME, ios::out);                       //open the output file
    if(!out_file){
        cout << "Unable to create the output file." << endl;        //print message if unable to open the output file
    }
    else{       //if able to open the output file

        //create a vector of <string> which is the person'd ID concatenated with their name and score, separated by tabs
        for (auto it = appearsWithTot.begin(); it != appearsWithTot.end(); ++it){

            actorScore = scorePerson((*it)->getID(), 0, false);     //score in output file = score of the individual who appeared on the list to 0 level of indirection
            actorScoreStr = to_string(actorScore);                  //convert score (double) to string

            personScores.push_back((*it)->getID() + "\t" + actorScoreStr + "\n");
        }

        //sort the vector<string> personScores by ascending order (nconst)
        std::sort(personScores.begin(),personScores.end());

        //write each element of personScores (line of information) to the output file
        for (auto it = personScores.begin(); it != personScores.end(); ++it){
            out_file << *it;
        }
    }
}

////////////////////////////////////// Remove Duplicate Person Objects From Vector //////////////////////////////////////
vector<Person *> removeDuplicatePersons(vector<Person *> personList){
   
    std::sort(personList.begin(),personList.end());                 //sort
    auto dup = std::unique(personList.begin(), personList.end());   //check for duplicates
    personList.erase(dup, personList.end());                        //erase duplicates

    return personList;
}

///////////////////////////////////////// Remove Duplicate Movie Objects From Vector ////////////////////////////////////
vector<MovieTitle*> removeDuplicateMovies(vector<MovieTitle *> movieList){
   
    std::sort(movieList.begin(),movieList.end());                   //sort
    auto dup = std::unique(movieList.begin(), movieList.end());     //check for duplicates
    movieList.erase(dup, movieList.end());                          //erase duplicates

    return movieList;
}

///////////////////////////////////////// LOADING THE DATA ////////////////////////////////////////////////////////////////
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

            result.clear();
		}

		inFile.close();
        cout << "Movies Loaded Successfully" << endl;
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

            //add those titles to the list of titles (MovieTitle Objects)
            while(getline(strm, cell, ',')){
                titleList.push_back(cell);
            }

            //get a vector of the movies in knownForTitles
            titleListObj = getMovieObjList(titleList);

            int i = 0;
            for(auto it = titleListObj.begin(); it != titleListObj.end(); ++it){
                
                if((p != nullptr) && (titleListObj[i] != nullptr)){
                    p->addTitle(titleListObj[i]);
                    auto itFindMov = mapMovies.find(titleListObj[i]->getID());
                    MovieTitle * m = itFindMov->second;
                    m->addActor(p);
                }
                i++;
            }
            result.clear();    
		}

		inFile.close();
        cout << "Names Loaded Successfully" << endl;
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

        string str1 = itFindPerson->first;      //1st component of the pair
        Person * p = itFindPerson->second;      //2nd component of the pair

        auto itFindMovie = mapMovies.find(t);

        string str2 = itFindMovie->first;       //1st component of pair
        MovieTitle * m = itFindMovie->second;   //2nd component of pair

        if ( p != nullptr && m != nullptr ){
            p->addTitle( m );
            m->addActor( p );
        }

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

            auto itFindMovie = mapMovies.find(tId);         //find the movie corresponding with titleID in rating

            MovieTitle * m = itFindMovie->second;           //2nd component of pair is the movies

            if(m != nullptr){
                mapMoviesRatings.insert( pair<string, Rating *> (m->getID(), r));       //map the movie with it's rating
            }

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

