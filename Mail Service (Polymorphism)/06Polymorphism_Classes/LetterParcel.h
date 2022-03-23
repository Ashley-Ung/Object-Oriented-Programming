//***************************************************************************
// File name:	 LetterParcel.h
// Author:		 Ashley Ung 
// Date:		   4/20/2021
// Class:		   CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory.
// Purpose:    Declares a programmer-defined child class LetterParcel 
//             representing information for a letter parcel. 
//***************************************************************************

#pragma once

#include "Parcel.h"
#include <string>
#include <iostream>

using namespace std;

class LetterParcel : public Parcel {

  public:
    LetterParcel (); 
    LetterParcel (int trackingNumber, string sender, string reciever,       
                  int weight, int travelDistance);

    virtual int getDeliveryDay () const;
    virtual double getInsuranceCost ();
    virtual double getRushCost ();
    virtual double getParcelCost ();
    virtual double getCost ();
    
    virtual void setInsurance ();
    virtual void setRush ();

    virtual bool read (istream &rcIn);
    virtual void print (ostream &rcOut) const;

};