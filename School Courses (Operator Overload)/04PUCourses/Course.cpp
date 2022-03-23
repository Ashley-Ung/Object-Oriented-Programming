//***************************************************************************
// File name:	 Course.cpp
// Author:		 Ashley Ung
// Date:			 3/30/2021
// Class:			 CS 250
// Assignment: A class Course representing the information for one course.
// Purpose:		 Defines each of the function prototypes associated with class
//						 Course.
//***************************************************************************

#include "Course.h"

using namespace std;

/****************************************************************************
Constructor: 	Course

Description:  A constructor that initializes every object member of type 
              Course after storage is allocated to the object.

Parameters:		none

Returned:			none
****************************************************************************/
Course::Course () {																													
	mPrefix = "";
	mCourseNumber = "";
	mCapacity = -1; 
	mCurrentEnrollment = -1;
}

//*************************************************************************** 
// Function:		operator>>																										 
//
// Description: Overloads the extraction operator (>>) to read in information 
//							for one course.
//
// Parameters:  rcInput    - the stream to read from 
//							rcCourse	 - the Course to read into 
//
// Returns:			Returns the input of a Course object. 
//***************************************************************************
istream& operator>> (istream &rcInput, Course &rcCourse) {
	rcInput >> rcCourse.mPrefix >> rcCourse.mCourseNumber
		      >> rcCourse.mCapacity >> rcCourse.mCurrentEnrollment; 

	return rcInput;
}

//*************************************************************************** 
// Function:		operator<<																								
//
// Description: Overloads the insertion operator (<<) to print out the 
//							information for one course. 
//
// Parameters:  rcOutput   - the stream to print to 
//							rcCourse   - the Course to output 
//
// Returns:			Returns the output of a Course object.
//***************************************************************************
ostream& operator<< (ostream &rcOutput, const Course &rcCourse) {
	rcOutput << rcCourse.mPrefix << " " << rcCourse.mCourseNumber << " "
					 << "Cap: " << rcCourse.mCapacity << " " << "Available: " 
					 << rcCourse.mCapacity - rcCourse.mCurrentEnrollment;

	return rcOutput;
}

//***************************************************************************
// Function:		operator++																								
//
// Description: Overloads the addition operator (++) to increase the 
//							enrollment of a course by 1. 
//
// Parameters:  none 
//
// Returns:			The current object.																				
//***************************************************************************
Course& Course::operator++ () {
	++mCurrentEnrollment;
	return *this;
}

/****************************************************************************
Function :   isFull

Description: Determines if a course is full. 

Parameters:  none

Returned:		 True, if the capacity of the course is full, else; false.  
****************************************************************************/
bool Course::isFull () const {
	bool bIsFull = true; 

	if (mCurrentEnrollment < mCapacity) {
		bIsFull = false;
	}

	return bIsFull;
}

/****************************************************************************
Function :   courseMatch

Description: Determines if a course matches a passed in prefix and course	
						 number. 

Parameters:	 rcPrefix       - the course prefix to compare against 
						 rcCourseNumber - the course number to compare against 

Returned:    True, if the prefix and course number matches the prefix and
					   course number in the file; else, false. 
****************************************************************************/
bool Course::courseMatch (const string &rcPrefix, 
												  const string &rcCourseNumber) const {
	bool bIsEqual = false; 

	if (mPrefix == rcPrefix && mCourseNumber == rcCourseNumber) {
		bIsEqual = true;
	}

	return bIsEqual; 
}

/****************************************************************************
Function :   isValid

Description: Checks if the file contains an invalid prefix or if the current 
						 enrollment is larger than the capacity. 

Parameters:	 none 

Returned:    True, if the file contains a valid prefix and the current 
				     enrollment does not exceed the capacity; else, false. 
****************************************************************************/
bool Course::isValid () const {
	const string PREFIX_MATH = "MATH";
	const string PREFIX_CS = "CS";

	bool bIsValid = true;

	if ((mPrefix != PREFIX_MATH && mPrefix != PREFIX_CS)) {
		bIsValid = false;
		cout << "Error, file contains an invalid prefix. :-(" << endl;
	}
	if (mCurrentEnrollment > mCapacity) {
		cout << "Error, the current enrollment is larger than the capacity. :-("
		     << endl;
	}
	else {
		bIsValid = true; 
	}
	return bIsValid;
}