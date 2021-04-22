README.txt
CSC319 Object-Oriented Programming: Project #2
SUNY Plattsburgh Computer Science Department

---------------------------

Grading:
1. Class diagram(using OO concept in your design/implementation): 20%
In your implementation, you must take advantage of object-oriented programming.
2. Code Implementation: implementation of the class diagram in C++: 80%
3. Bonus: 10%, if your final submission is 7 days before the deadline.
If you do not participate to the code implementation, this component of your grade will be lowered.

---------------------------

Specification:
Your program must load data from IMDB to calculate a score for a specific actor.
The original data came from https://www.imdb.com/interfaces/. Some rows were removed, but none were modified.
You must use the files on the linux server at: /home/mmail002/Project2/input.
All files are TSV (Tab-Separated Values), where each value is separated by a tab (‘\b’). Each file has a header to describe each value. Also, the website has information about it.

Four files are used:
- name.tsv: information on each person: nconst, primaryName, birthyear,deathYear,primaryProfession, knownForTitles. nconst is the unique identifier. Some titles do not have a birthYear, instead it is “\N”. When a person does not have a birthYear, the
year 1900 is used.
- title.tsv: information on each movie: tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres. tconst is the unique identifier. Some title do not have a startYear, instead it is “\N”. When a movie does not have a startYear, the year 2200 is used. Some genres can be empty, with the value “\N”.
- principals.tsv: person and their role per title: tconst, ordering, nconst, category, job, characters. Per movie (tconst), per person(nconst) the category(actress-actor, director, producer, editor..)they had.
- ratings.tsv: rating per movie: tconst, averageRating, numVotes

Only a subset of the data available at IMDB is used to limit the disk storage, memory requirement and
the execution time.

For some ratings, some movies may not be part of the dataset. For some principals, the movie or the person may not be part of the dataset.

Your program must be called project2.cpp.

Command line:
Project2 <name input filename> <title input filename> <principals input filename> <ratings input filename> <score output filename> <person Id= nconst > <level of indirection>

---------------------------

Calculating the Score:
For the person id(name.nconst), you must calculate the sum of the score for all the movies they have participated in(principals.nconst -> principals.tconst). The score is the sum of all the movie’s score of everyone that were involved with them in a movie, and for each individual, the sum of their movies’ score up to <level of indirection>.

name:
nconst      birthyear
1           1950
2           1960
3           1980
4           1990 

title:
tconst      startYear       genres:
10          1990            Short,Western
20          2000            Comedy,Short       
30          2010            Comedy,Family,Romance

Principals:
tconst      nconst          category
10          1               producer
10          2               actress
20          2               director
20          3               actor
30          4               actor

Level of indirection:
<person Id=3> < level of indirection=2>
3 -> was in movie 20. The movie 20, had 2 and 3. <- level of indirection = 1
2 was in the 10 and 20 <- level of indirection = 2

---------------------------

Calculating a movie score:

Basic movie score: ratings.averageRating * ratings.numVotes.

A movie score, is adjusted based on the genre and the year it started.

Genres    Movie Score Premium
Comedy        +20%
Drama         +40%
Romance       -20%
Horror        -30%
Other         no premium

Based on the startYear, you calculate a premium of the score based on: Score * (100 – (2020 – startYear))/100. The minimum value of (2020 – startYear) is 50.

---------------------------

Producing the output:

1-The program must produce on the console (cout) the calculated score for the <person Id= nconst >.
2-For each person (nconst), which are used to calculate the score of <person Id= nconst >, you must calculate their own score. In the file <score output filename>, you must output in a tab-delimited format(one per line):
<nconst> \t <score>. The output must be sorted by ascending nconst.
