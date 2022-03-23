//****************************************************************************** 
// File name:	 HourlyEmployee.h
// Author:		 Computer Science, Pacific University
// Date:		   4/2/2018
// Class:		   CS 250
// Assignment: Inheritance Lab
// Purpose:		 Demonstrate Inheritance
//******************************************************************************

#pragma once

#include "Employee.h"
#include <string>
#include <iostream>

using namespace std;

class HourlyEmployee : public Employee {
public:
  HourlyEmployee();
  HourlyEmployee(string name, string ssn,
    double hourlyRate, double hoursWorked);
  ~HourlyEmployee() { cout << "HourlyEmployee dtor" << endl; }

  double getPay() const;
  void addWorkedHours(double hours);

  virtual void print(ostream& rcOut) const;
  virtual bool read(istream& rcIn);

  virtual double getMonthlyPay() const;

private:
  double mWageRate;
  double mHoursWorked;
};