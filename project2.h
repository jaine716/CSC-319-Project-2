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

//function prototypes
void loadDataSet();                     //load the data set

void loadMovie(istream & is);           //load movies
void loadPerson(istream & is);          //load people
void loadPrincipal(istream & is);       //load principals

double calculateScore(string id);       //calculate score of actor

//class prototypes
class MovieTitle;
class Person;
class Principals;
class Rating;

/////////////////////////////////////////////PERSON//////////////////////////////////////////////////////
class Person{

private:
    string nconst;                      //unique person identifier
    string primaryName;                 //name of person

    string primaryProfession[3];        //top 3 primary professions of person (array)

    vector<MovieTitle *> titleList;          //list of movies they appear in
    vector<Person *> appearsWithList;   //list of people who appear with them  in other movies
    vector<MovieTitle *> knownForList;       //list of movies they are known for

public:
    Person(string str);     //constructor prototype
    virtual ~Person();      //destructor prototype

    //function prototypes
    string getID();         
    void addTitle( MovieTitle * m );
    void addToAppearsWith(Person * p);
    void addToKnownForList(MovieTitle * m);

};

////////////////////////////////////////////////MOVIE/////////////////////////////////////////////////////
class MovieTitle
{


    private:
        string tconst;
        double score = 0.0;
        string primaryTitle;
        string originalTitle;
        string titleType;
        bool isAdult;
        string startYear;
        string endYear;
        string runtimesMinutes;
        string genres;
        vector<Principals *> principalList;
        vector<Person *> actorList;

    protected:
      

    public:
        
        MovieTitle(string str);      //constructor prototype
        virtual ~MovieTitle();       //destructor prototype

        double getRating ();
        
        void getPrincipals (Principals * prin);
        void getAllActors (Person * actor);
    
        string getID();
        void addActor( Person * p );
        double setScore(double pscore);

};


/*class Movie{

private:
string tconst;
double score = 0.0;
int year;
vector<Person *> actorList;

public:

Movie(string str);      //constructor prototype
virtual ~Movie();       //destructor prototype

//function prototypes
string getID();
void addActor( Person * p );
double setScore(double pscore);

};*/

//////////////////////////////////////////////PRINCIPALS///////////////////////////////////////////////////


class Principals {
    private:
      string nconst;
      string tconst;
      int ordering;
      string category;
      string job;
      string characters;
    
    public:

    
    Principals(string n, string t); //constructor
    virtual ~Principals();          //destructor

    void setPrinCharsActor(string n);

    void setPrinCharsMovie(string t);

    string getPrinCharsActor(string n);

    string getPrinCharsMovie(string t);
};

////////////////////////////////////////////////RATINGS////////////////////////////////////////////////////