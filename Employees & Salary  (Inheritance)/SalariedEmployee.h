//****************************************************************************** 
// File name:	 SalariedEmployee.h
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

class SalariedEmployee : public Employee {
public:
  SalariedEmployee();
  SalariedEmployee(string name, string ssn,
    double salary);

  double getPay() const;

  virtual void print(ostream& rcOut) const;
  virtual bool read(istream& rcIn);

  virtual double getMonthlyPay() const;

private:
  double mSalary;
};