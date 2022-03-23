//****************************************************************************** 
// File name:	 HourlyEmployee.cpp
// Author:		 Computer Science, Pacific University
// Date:		   4/2/2018
// Class:		   CS 250
// Assignment: Inheritance Lab
// Purpose:		 Demonstrate Inheritance
//******************************************************************************

#include "HourlyEmployee.h"
#include <iostream>


//******************************************************************************
// Constructor:	HourlyEmployee
//
// Description:	Call the Employee default constructor, set mWageRate 
//              and mHoursWorked both to zero.
//
// Parameters:	none
//
// Returned:		none
//******************************************************************************
HourlyEmployee::HourlyEmployee() : Employee(), mWageRate(0),
mHoursWorked(0) {
}

//******************************************************************************
// Constructor:	HourlyEmployee
//
// Description:	Call the Employee constructor with name, set mWageRate 
//              and mHoursWorked both the given parameters.
//
// Parameters:	name        - the name of the Employee
//						  ssn					- social security number
//              hourlyRate  - the wage of the Employee
//              hoursWorked - the hours the Employee worked
//
// Returned:		none
//******************************************************************************
HourlyEmployee::HourlyEmployee(std::string name, std::string ssn,
  double hourlyRate, double hoursWorked) :
  Employee(name, ssn), mWageRate(hourlyRate),
  mHoursWorked(hoursWorked) {
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
double HourlyEmployee::getPay() const {
  return mWageRate * mHoursWorked;
}

//******************************************************************************
// Function:	addWorkedHours
//
// Description:	Add hours to HoursWorked
//
// Parameters:	hours - the hours to add
//
// Returned:	none
//******************************************************************************
void HourlyEmployee::addWorkedHours(double hours) {
  mHoursWorked += hours;
}

//******************************************************************************
// Function:	print
//
// Description:	Print the HourlyEmployee to the stream
//
// Parameters:	rcOut - the stream to print to
//
// Returned:	none
//******************************************************************************
void HourlyEmployee::print(ostream& rcOut) const {

  Employee::print(rcOut);

  // OR
  //rcOut << "Name: " << getName() << " SSN: " << getSSN();

  rcOut << " Wage: " << mWageRate << " HoursWorked: " << mHoursWorked;
  rcOut << " Pay: " << getPay();
}


//****************************************************************************
// Function:	read
//
// Description:	Input the HourlyEmployee from the stream
//
// Parameters:	rcIn - the stream to input from
//
// Returned:	true if an Employee is read, false otherwise
//***************************************************************************

bool HourlyEmployee::read(istream& rcIn) {
  if (Employee::read(rcIn) &&
    rcIn >> mWageRate >> mHoursWorked) {
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

double HourlyEmployee::getMonthlyPay() const {
  return getPay();
}