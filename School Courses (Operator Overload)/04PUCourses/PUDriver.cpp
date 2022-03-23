//***************************************************************************
// File name:	 PUDriver.cpp
// Author:		 Ashley Ung
// Date:			 3/30/2021
// Class:			 CS 250
// Assignment: Course using Classes.
// Purpose:		 Driver used to test class Course
// Hours:			 14
// Computer:	 WindowsOS
//***************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Course.h"

using namespace std;

void drawHeading (string title, char borderChar, int padding);
bool openFileForRead (ifstream &rcInFile, string fileName);
void printMenuHeading ();          
int findCourse (string prefix, string courseNumber, Course* apcCourse[],
                int numCourses);
string isValidPrefix ();
string getCourse (string &rPrefix);

/****************************************************************************
Function:		  main

Description:	main driver for the Course Matrix using Classes to show how
              each member function in DNA can be used.

Parameters:		none

Returned:			exit status
****************************************************************************/
int main () {
  const string TITLE_STRING = "PACIFIC UNIVERSITY COURSES";
  const string INPUT_FILE = "courses.txt";
  const char BORDER_CHARACTER = '*';                                        
  const int PADDING = 0;
  const int MAX_COURSES = 10;
  const int PRINT_ALL = 1;
  const int PRINT_ONE_COURSE = 2;
  const int ADD_STUDENT = 3;
  const int QUIT = 4;
  const int INVALID_COURSE = -1;

  Course* apcCourse[MAX_COURSES];
  string courseNumber;
  string prefix;
  int numCourses = 0;                                          
  int choice;
  int index;

  drawHeading (TITLE_STRING, BORDER_CHARACTER, PADDING);                      

  ifstream inFile;

  if (openFileForRead (inFile, INPUT_FILE)) {   
    while (!inFile.eof ()) {  
      apcCourse[numCourses] = new Course;
      inFile >> *apcCourse[numCourses];
      if (apcCourse[numCourses]->isValid () && numCourses < MAX_COURSES) {
        numCourses++;
      }
      else if (numCourses > MAX_COURSES) {
        cout << "Error, the file contains more than 10 courses.";
        exit (EXIT_FAILURE);
      }
    }
  }
  else {
    exit (EXIT_FAILURE);
  }                                                 

  do {

    bool bIsFound = false;

    do {
      printMenuHeading ();
      cout << endl << "Option: ";
      cin >> choice;
      cout << endl;
    } while (!(PRINT_ALL == choice || PRINT_ONE_COURSE == choice
             || ADD_STUDENT == choice || QUIT == choice));

    switch (choice) {
      case PRINT_ALL:
        for (int i = 0; i < numCourses; i++) {
          cout << *apcCourse[i] << endl;
        }
        break;

      case PRINT_ONE_COURSE:
        bIsFound = false;

        courseNumber = getCourse (prefix);
        index = findCourse (prefix, courseNumber, apcCourse, numCourses);

        if (INVALID_COURSE != index) {
          cout << *apcCourse[index] << endl;
        }
        else {
          cout << "The course does not exist :-)";
        }
        break;

      case ADD_STUDENT:
        bIsFound = false;

        courseNumber = getCourse (prefix);
        index = findCourse (prefix, courseNumber, apcCourse, numCourses);

        if (index != INVALID_COURSE) {
          cout << *apcCourse[index] << endl;
          bIsFound = true;
          if (!(apcCourse[index]->isFull ())) {
            ++* apcCourse[index];
            bIsFound = true;
            cout << endl << "Student was added to the course." << endl;
          }
          else {
            cout << endl << "The course is already full." << endl;
          }
        }
        
        if (!bIsFound) {
          cout << endl <<  "The course does not exist :-)";               
        }
        break;
    }

  } while (choice != QUIT);

    for (int i = 0; i < numCourses; i++) {
      delete apcCourse[i];
    }

    inFile.close ();

    return EXIT_SUCCESS;
}

/****************************************************************************
Function:    drawHeading

Description: Outputs a heading by outputting a name between a row of 
             astericks. 

Parameters:  title      - the title name of the heading
             borderChar - displays the title with a border
             padding    - displays the title with padding spaces

Returned:		 none
****************************************************************************/
void drawHeading (string title, char borderChar, int padding) {
  const int SPACING_GAP = 2;
  const int END_ASTERICKS = 2;

  int titleLength = padding * END_ASTERICKS 
                    + static_cast<int>(title.length ());

  for (int i = 0; i < titleLength; i++) {
    cout << borderChar;
  }

  cout << endl;

  for (int i = 0; i < padding; i++) {
    cout << " ";
  }

  cout << title;

  for (int i = 0; i < padding; i++) {
    cout << " ";
  }

  cout << endl;

  for (int i = 0; i < titleLength; i++) {
    cout << borderChar;
  }

  cout << endl;
}

/****************************************************************************
Function:     openFileForRead

Description:  Checks if the file is open, if the file is not open, the
              program will return false, else, true.

Parameters:   inFile   - reading in the file stream
              fileName - the name of the file

Returned:			True if the file is open; else, false.
****************************************************************************/
bool openFileForRead (ifstream &rcInFile, string fileName) {
  bool bIsOpen = true;

  rcInFile.open (fileName);

  if (!rcInFile.is_open ()) {
    cout << "Error opening file.";
    bIsOpen = false;
  }
  return bIsOpen;
}

/****************************************************************************
Function:    printMenuHeading

Description: Prints the possible menu selections. 

Parameters:  none 

Returned:		 none
****************************************************************************/
void printMenuHeading () {
  const string OPTION_ALL_COURSES = "1. Print all courses";
  const string OPTION_ONE_COURSE = "2. Print one course";
  const string OPTION_ADD_STUDENT = "3. Add a student to a course";
  const string OPTION_QUIT = "4. Quit";

  cout << endl << setfill ('-') << setw (28) << "" << endl
       << OPTION_ALL_COURSES << endl << OPTION_ONE_COURSE << endl
       << OPTION_ADD_STUDENT << endl << OPTION_QUIT << endl << setfill ('-')
       << setw (28) << "" << endl;
}

/****************************************************************************
Function:    findCourse

Description: Locates a match between the the user inputted course number and
             prefix with the course number and prefix in the file.

Parameters:  prefix       - the course prefix to compare against
             courseNumber - the course number to compare against
             *apcCourse[] - an array of pointers to Course
             numCourses   - the number of courses

Returned:    Returns the course number if the course number and prefix being
             inputted matches a course number and prefix in the file.
****************************************************************************/
int findCourse (string prefix, string courseNumber, Course* apcCourse[],
                int numCourses) {
  int courseNum = -1;

  for (int i = 0; i < numCourses; i++) {
    if (apcCourse[i]->courseMatch (prefix, courseNumber)) {
      courseNum = i;
    }
  }
  return courseNum;
}

/****************************************************************************
Function:    isValidPrefix 

Description: Checks if the user inputs a valid prefix, if the user inputs an 
             invalid prefix, the user is prompted to enter another prefix  
             until a valid prefix is inputted.

Parameters:  none 

Returned:    The valid prefix, which is either CS or MATH.
****************************************************************************/
string isValidPrefix () {
  string prefix; 

  do {
    cout << "Prefix: ";
    cin >> prefix;
  } while ((prefix != "CS") && (prefix != "MATH"));

  return prefix;
}

/****************************************************************************
Function:    getCourse

Description: Calls isValidPrefix to check if the prefix is valid, and if the 
             prefix is valid, then takes in the course number. 

Parameters:  rPrefix - the prefix being passed in to be checked for validity. 

Returned:    Returns the course number. 
****************************************************************************/
string getCourse (string &rPrefix) {
  string courseNumber;

  rPrefix = isValidPrefix (); 

  cout << "Number: ";
  cin >> courseNumber;
  cout << endl;

  return courseNumber; 
}