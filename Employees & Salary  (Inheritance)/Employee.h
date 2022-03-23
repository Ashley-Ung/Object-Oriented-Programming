//**************************************************************************** 
// File name:	 Employee.h
// Author:		 Computer Science, Pacific University
// Date:		   4/2/2018
// Class:		   CS 250
// Assignment: Inheritance Lab
// Purpose:		 Demonstrate Inheritance
//*****************************************************************************

#pragma once

#include <iostream>

using namespace std;

class Employee {
public:
  Employee(string name = "", string ssn = "");
  ~Employee() { cout << "Employee dtor" << endl; }
  string getName() const;
  string getSSN() const;
  virtual void print(ostream& rcOutStream) const;
  virtual bool read(istream& rcIn);

  virtual double getMonthlyPay() const = 0;

private:
  std::string mName,
    mSSN;
};