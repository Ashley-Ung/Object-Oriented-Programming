//***************************************************************************
// File name:	 Course.cpp
// Author:		 Ashley Ung
// Date:			 3/30/2021
// Class:			 CS 250
// Assignment: A class Course representing the information for one course.
// Purpose:		 Declares programmer-defined class Course for operations to be 
//             performed on one course. 
//***************************************************************************

#pragma once

#include <iostream>

using namespace std;

class Course {
  public:
    Course ();

    bool isFull () const;                                               
    bool courseMatch (const string &rcPrefix, 
                      const string &rcCourseNumber) const;
    bool isValid () const;

    Course& operator++ ();

    friend istream& operator>> (istream &rcInput, Course &rcCourse); 
    friend ostream& operator<< (ostream &rcOutput, const Course &rcCourse);

  private: 
    string mPrefix; 
    string mCourseNumber; 
    int mCapacity; 
    int mCurrentEnrollment; 
};

