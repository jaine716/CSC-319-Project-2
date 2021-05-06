//Project #2: project2.h
//Jaine E Perotti
//Riley Smith
//Levy Sanon

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>


using std::cout;
using std::endl;
using std::ostream;
using std::istringstream;
using std::istream;

using namespace std;

//class prototypes
class MovieTitle;
class Person;
class Principals;
class Rating;


//function prototypes
void loadDataSet();         //load all data sets
void loadMovie();           //load movies
void loadPerson();          //load people
void loadPrincipal();       //load principals
void loadRatings();         //load ratings

double scorePerson(string id, int levelOfIndirection, bool incTotalScore);                          //score the actor being searched for (to a specified level of indirection)
double scoreMovieList(vector<MovieTitle *> appearsInTot, bool printOutput);     //score the list of total movies found
vector<MovieTitle *> findAssociateMovies(vector <Person *> appearsWithTot);     //find all the movies that the actor's associates appear in
vector<Person *> findAssociatedActors(vector<string> movieList);                //find all of the co-starring actors
void generateOutputFile(vector<Person *> appearsWithTot);                       //generates the output file
vector<Person *> removeDuplicatePersons(vector<Person *> personList);           //removes duplicate people from a Person * vector
vector<MovieTitle*> removeDuplicateMovies(vector<MovieTitle *> movieList);     //removes duplicate movies from a Movie * vector
vector<MovieTitle *> getMovieObjList(vector<string> movieList);                 //make a vector of MovieTitle for each actor (from vector of tID strings)

//operator overload - prints out all elements of a vector of type T
template <typename T>
std::ostream & operator << (std::ostream & os, const std::vector<T> & vect)
{
    for(auto elem : vect)
    {
        os << *elem << "\t";
    }
    return os;
}

/////////////////////////////////////////////PERSON//////////////////////////////////////////////////////
class Person{

private:
    string nconst;                              //unique person identifier
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
    string knownForTitles;

    vector<MovieTitle *> titleList;             //list of movies they appear in
    vector<string> titleListStr;                //list of titles (string)

public:
    
    Person(string pId, string pName, string bYear, string dYear, string pProf, string knownFor);    //constructor prototype
    virtual ~Person();      //destructor prototype
    Person( const Person &ob);  //copy constructor prototype


    //operator overload
    friend ostream& operator<< (ostream&perStrm, Person obj){		//friend means you can access the private members of the class

		obj.write(perStrm);
		return perStrm;
	}

    //function prototypes
    void write(ostream& perStrm);
    string getID(); 
    string getPrimaryName(); 
    string getKnownForTitles();       
    vector<string> addTitleList();
    void addTitle(MovieTitle * m);
    vector<MovieTitle *> getTitleList();
    vector<string> getTitleListStr();
};

////////////////////////////////////////////////MOVIE/////////////////////////////////////////////////////
class MovieTitle
{
    private:
        string tconst;
        string primaryTitle;
        string originalTitle;
        string titleType;
        string isAdult;
        string startYear;
        string endYear;
        string runtimesMinutes;
        string genres;

        vector<Person *> actorList;
        vector<string> GenresListStr;

    protected:
      

    public:
        
        //constructor prototype
        MovieTitle(string tId, string tType, string pTitle, string oTitle, string isAd, string sYear, string eYear, string rtMin, string genr);
        virtual ~MovieTitle();       //destructor prototype
        MovieTitle( const MovieTitle &ob);      //copy constructor prototype

        //operator overload
        friend ostream& operator<< (ostream&movStrm, MovieTitle obj){		//friend means you can access the private members of the class
            obj.write(movStrm);
            return movStrm;
        }

        //function prototypes
        string getID();
        double getRating();
        void write(ostream& movStrm);
        vector<Person *> getAllActors();
        void addActor( Person * p );
        double getStartYearDouble();
        string getTitle();
        vector<string> addGenreListVector();
        double applyGenrePremium(double rating);

};

//////////////////////////////////////////////PRINCIPALS///////////////////////////////////////////////////


class Principals {
    private:
      string nconst;
      string tconst;
      string ordering;
      string category;
      string job;
      string characters;
      vector<Principals *> principalslist;
    
    public:

    Principals(string t, string order, string n, string cat, string jb, string chars);      //constructor prototype
    virtual ~Principals();          //destructor prototype
    Principals( const Principals &ob);      //copy constructor prototype

    // << operator overload
    friend ostream& operator<< (ostream&prinStrm, Principals obj){		//friend means you can access the private members of the class
    	obj.write(prinStrm);
		return prinStrm;
	}

    //function prototypes
    void write(ostream& prinStrm);
    string getNconst();
    string getTconst();
    string getCategory();

};

////////////////////////////////////////////////RATINGS////////////////////////////////////////////////////

class Rating{

private:
    string tconst;
    string averageRating;
    string numVotes;

public:

    Rating(string tId, string avgR, string nVotes);     //constructor prototype
    ~Rating();                                          //destructor prototype
    Rating( const Rating &ob);                          //copy constructor prototype

    // << operator overload
    friend ostream& operator<< (ostream&rateStrm, Rating obj){		//friend means you can access the private members of the class
    	obj.write(rateStrm);
		return rateStrm;
	}
    
    //function prototypes
    void write(ostream& rateStrm);
    void setRating(string r);
    string getRating();
    double getRatingDouble();
    double getNumVotesDouble();
};