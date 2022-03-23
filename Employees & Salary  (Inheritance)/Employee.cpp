//**************************************************************************** 
// File name:	 Employee.cpp
// Author:		 Computer Science, Pacific University
// Date:		   4/2/2018
// Class:		   CS 250
// Assignment: Inheritance Lab
// Purpose:		 Demonstrate Inheritance
//*****************************************************************************


#include "Employee.h"

#include <iostream>
#include <string>

//****************************************************************************
// Constructor:	Employee
//
// Description:	Initialize the name with the parameter string
//
// Parameters:	name - the name to store in the object
//							ssn  - employee's social security number
//
// Returned:		none
//***************************************************************************
Employee::Employee(std::string name, std::string ssn) {
	mName = name;
	mSSN = ssn;
}

//****************************************************************************
// Function:	  name
//
// Description:	Retrieve the name of the Employee
//
// Parameters:	none
//
// Returned:		the name of the Employee
//***************************************************************************
std::string Employee::getName() const {
	return mName;
}

//****************************************************************************
// Function:	  ssn
//
// Description:	Retrieve the ssn of the Employee
//
// Parameters:	none
//
// Returned:		the ssn of the Employee
//***************************************************************************
std::string Employee::getSSN() const {
	return mSSN;
}

//****************************************************************************
// Function:	  print
//
// Description:	Output the Employee to the stream
//
// Parameters:	rcOutput - the stream to output to
//
// Returned:		None
//***************************************************************************

void Employee::print(std::ostream& rcOutStream) const {
	rcOutStream << "Name: " << mName << " SSN: " << mSSN;
}

//****************************************************************************
// Function:	  read
//
// Description:	Input the Employee from the stream
//
// Parameters:	rcIn - the stream to input from
//
// Returned:		true if an Employee is read, false otherwise
//***************************************************************************

bool Employee::read(istream& rcIn) {

	if (rcIn >> mName >> mSSN) {
		return true;
	}
	return false;
}


//****************************************************************************
// Function:	  operator<<
//
// Description:	Output the Employee to the stream
//
// Parameters:	rcOut - the stream to output to
//							rcEmpt - the Employee to output
//
// Returned:		the stream.
//***************************************************************************
ostream& operator<<(ostream& rcOut, const Employee& rcEmp) {
	rcEmp.print(rcOut);
	return rcOut;
}