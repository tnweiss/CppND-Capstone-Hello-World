# CPPND: Capstone Hello World Repo

For my udacity cpp capstone, I chose to create my own application. I built the begining of a local file query enging. With this you can query 
local CSV or TSV files using sql like "SELECT FROM WHERE" syntax. 

In this project I've supplied some GDELT data as an example. You can find more information about this 
data [here](https://blog.gdeltproject.org/gdelt-2-0-our-global-world-in-realtime/)

The gdeltConfig.txt file supplies the project with the headers for the TSV. You'll notice it also has a dummy
table specified in my example. This project has the capability to query many different files with different data sources as long as they are defined in the supplied config file.

When running this binary you can also specify the number of threads you would like to use and at the end of execution
the project will tell you what the execution time was so you can decide which thread count is optimal for you.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Query --config ../gdeltConfig.txt -s Actor1Name,Day -f gdelt -w Day=20190708 --data ../data/ --threads 1`
  
## Flags & Running
Below is a list of flags and their descriptions

  --config is the location of the config file defining the keys for the TSV
  -s is short for SELECT, the columns you want returned when an entry matches the query
  -f is short for FROM, this is the table you want to query from
  -w is short for WHERE, this can only be KEY=VALUE. So far only thge '=' works
  --data is the location to the folder with the data
  --threads is the number of threads you would like to do

Below is a list of example queries

- `./Query --config ../gdeltConfig.txt -s Actor1Name,MonthYear -f gdelt -w Day=20190708 --data ../data/ --threads 1`
- `./Query --config ../gdeltConfig.txt -s NumMentions,QuadClass,MonthYear -f gdelt -w Actor1Name=USA --data ../data/ --threads 3`
- `./Query --config ../gdeltConfig.txt -s GlobalEventID -f gdelt -w Actor1Name=USA --data ../data/ --threads 2`


## Class Structure

Below I've listed the classes and a high level description of what they do.

- <b>Dataframe</b> This class holds a set of data, typically a row of the TSV
- <b>Engine</b> This is the class that orchestrates the execution of the queries. It will start up the threads, collect results, and distribute work.
- <b>Query</b> Used to hold the query details and assess whether a dataframe matches the query results
- <b>ResultFrame</b> A child of the dataframe class, used to denote the dataframe is a result set
- <b>Source</b> A data source, typically referring to a type of CSV. The members are populated with data from the config
- <b>Sources</b> A class that manages the sources defined in the config. 

## Expected output

The expected output should be a set of data along with data about the execution. Below you can see an example of the output

```
~/Desktop/workspace/CppND-Capstone-Hello-World/build$ ./Query --config ../gdeltConfig.txt -s GlobalEventID,Day,Actor1Name -f gdelt -w Day=20190708 --data ../data/ --threads 3

----------File Query Engine----------

Loading config file from: ../gdeltConfig.txt

Loading data from: ../data/

Using 3 threads

QUERY:
SELECT GlobalEventID, Day, Actor1Name, 
FROM gdelt
WHERE Day = 20190708

Results:
GlobalEventID       Day                 Actor1Name          
933645588           20190708                                
933645589           20190708            CHN                 
933645590           20190708            CVL                 
933645591           20190708            CVL                 
933645592           20190708            CVL                 
933645593           20190708            EUR                 
933645594           20190708            GOV                 
933645595           20190708            GOV                 
933645596           20190708            GOV                 
933645597           20190708            JUD                 
933645598           20190708            JUD                 
933645599           20190708            NZL                 
933645600           20190708            NZLGOV              
933645601           20190708            SET                 
933645602           20190708            THA                 
933645603           20190708            THA                 
933645604           20190708            THA                 
933645605           20190708            USA                 
933645606           20190708            USA                 
933645607           20190708            USA                 
933645608           20190708            USA                 
933643473           20190708                                
933643474           20190708            CHN                 
933643475           20190708            SLB                 


Found 24 results
Execution Time: 124 milliseconds
```
## Rubric

### Loops, Functions, I/O

- The project demonstrates an understanding of C++ functions and control structures. <b>File: common.cpp Line: 84 </b>
- The project reads data from a file and process the data, or the program writes data to a file. <b>File: engine.cpp Line: 33 </b>
- The project accepts user input and processes the input. <b>File: main.cpp Line: 25 </b>

### Object Oriented Programming

- The project uses Object Oriented Programming techniques. <b>File: dataframe.cpp dataframe.h </b>
- Classes use appropriate access specifiers for class members. <b>File: dataframe.h Line: 12 & 30 </b>
- Class constructors utilize member initialization lists.  <b>File: resultFrame.h Line: 8 </b>
- Classes abstract implementation details from their interfaces. <b>File: query.cpp Line: 28 </b>
- Classes encapsulate behavior. <b>File: engine.h Line: 53 </b>
- Classes follow an appropriate inheritance hierarchy. <b>File: resultFrame.h dataframe.h </b>
- Overloaded functions allow the same function to operate on different parameters. <b> file: dataframe.h Line: 13 & 14 </b>
- Derived class functions override virtual base class functions. <b> Dataframe.h:20 & resultFrame.h:15 </b>
- Templates generalize functions in the project. <b>File: engine.h Line: 13 </b>

### Memory Management

- The project makes use of references in function declarations. <b>File: dataframe.h Line: 14 31</b>
- The project uses destructors appropriately. <b> File: query.cpp Line: 63 </b>
- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. <b>File: dataframe.cpp Line: 9</b>
- The project follows the Rule of 5. <b>File: dataframe.h</b>
- The project uses move semantics to move data, instead of copying it, where possible. <b>File: source.cpp Line: 40</b>
- The project uses smart pointers instead of raw pointers. <b>File: dataframe.h Line: 31</b>

### Concurrency

- The project uses multithreading. <b>File: engine.cpp Line: 15</b>
- A promise and future is used in the project. <b> N/A </b>
- A mutex or lock is used in the project <b>File: engine.h Line: 43</b>
- A condition variable is used in the project. <b> N/A </b>
