//****************************************************************************** 
// File name:	 SalariedEmployee.cpp
// Author:		 Computer Science, Pacific University
// Date:		   4/2/2018
// Class:		   CS 250
// Assignment: Inheritance Lab
// Purpose:		 Demonstrate Inheritance
//******************************************************************************

#include "SalariedEmployee.h"
#include <iostream>


//******************************************************************************
// Constructor:	SalariedEmployee
//
// Description:	Call the Employee default constructor, set mWageRate 
//              and mHoursWorked both to zero.
//
// Parameters:	none
//
// Returned:		none
//******************************************************************************
SalariedEmployee::SalariedEmployee() : Employee(), mSalary(0) {
}

//******************************************************************************
// Constructor:	SalariedEmployee
//
// Description:	Call the Employee constructor with name, set mWageRate 
//              and mHoursWorked both the given parameters.
//
// Parameters:	name        - the name of the Employee
//						  ssn					- social security number
//              salary      - the wage of the Employee
//
// Returned:		none
//******************************************************************************
SalariedEmployee::SalariedEmployee(std::string name, std::string ssn,
  double salary) :
  Employee(name, ssn), mSalary(salary) {
}

//******************************************************************************
// Function:	getPay
//
// Description:	Calculate and return the total pay
//
// Parameters:	none
//
// Returned:	double - the total pay
//******************************************************************************
double SalariedEmployee::getPay() const {
  return mSalary;
}



//******************************************************************************
// Function:	print
//
// Description:	Print the SalariedEmployee to the stream
//
// Parameters:	rcOut - the stream to print to
//
// Returned:	none
//******************************************************************************
void SalariedEmployee::print(ostream& rcOut) const {

  Employee::print(rcOut);

  // OR
  //rcOut << "Name: " << getName() << " SSN: " << getSSN();


  rcOut << " Pay: " << getPay();
}


//****************************************************************************
// Function:	read
//
// Description:	Input the SalariedEmployee from the stream
//
// Parameters:	rcIn - the stream to input from
//
// Returned:	true if an Employee is read, false otherwise
//***************************************************************************

bool SalariedEmployee::read(istream& rcIn) {
  if (Employee::read(rcIn) &&
    rcIn >> mSalary) {
    return true;
  }
  return false;
}

//****************************************************************************
// Function:	  getMonthlyPay
//
// Description:	Get the monthly pay
//
// Parameters:	None
//
// Returned:    The monthly pay
//***************************************************************************

double SalariedEmployee::getMonthlyPay() const {
  return getPay() / 12;
}