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

void loadMovie();           //load movies
void loadPerson();          //load people
void loadPrincipal();       //load principals

double calculateScore(string id);       //calculate score of actor

//class prototypes
class MovieTitle;
class Person;
class Principals;
class Rating;

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
    vector<Person *> appearsWithList;           //list of people who appear with them  in other movies
    vector<MovieTitle *> knownForList;          //list of movies they are known for

public:
    
    Person(string pId, string pName, string bYear, string dYear, string pProf, string knownFor);    //constructor prototype
    virtual ~Person();      //destructor prototype

    //function prototypes
    void write(ostream& perStrm);

    friend ostream& operator<< (ostream&perStrm, Person obj){		//friend means you can access the private members of the class

		obj.write(perStrm);
		return perStrm;
	}

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
        string primaryTitle;
        string originalTitle;
        string titleType;
        string isAdult;
        string startYear;
        string endYear;
        string runtimesMinutes;
        string genres;

        double score = 0.0;
        vector<Principals *> principalList;
        vector<Person *> actorList;

    protected:
      

    public:
        
        //constructor prototype
        MovieTitle(string tId, string tType, string pTitle, string oTitle, string isAd, string sYear, string eYear, string rtMin, string genr);
        virtual ~MovieTitle();       //destructor prototype

        void write(ostream& movStrm);
        friend ostream& operator<< (ostream&movStrm, MovieTitle obj){		//friend means you can access the private members of the class

		obj.write(movStrm);
		return movStrm;
	}
        string getID();
        double getRating ();
        
        void getPrincipals (Principals * prin);
        void getAllActors (Person * actor);
       
        void addActor( Person * p );
        double setScore(double pscore);

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

    Principals(string t, string order, string n, string cat, string jb, string chars);      //constructor
    virtual ~Principals();          //destructor


    void write(ostream& prinStrm);

    // << operator overload
    friend ostream& operator<< (ostream&prinStrm, Principals obj){		//friend means you can access the private members of the class
    	obj.write(prinStrm);
		return prinStrm;
	}

    void setPrinCharsActor(string n);
    void setPrinCharsMovie(string t);

    void setNconst(string n);
    void setTconst(string t);
    void setCategory(string c);

    string getNconst();
    string getTconst();
    string getCategory();

    void addPrincipal(Principals * principal);

    string getPrinCharsActors(string nconst);
    string getPrinCharsMovies(string tconst);
};

////////////////////////////////////////////////RATINGS////////////////////////////////////////////////////