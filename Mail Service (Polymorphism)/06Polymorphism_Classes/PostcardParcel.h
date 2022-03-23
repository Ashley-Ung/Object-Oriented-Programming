//***************************************************************************
// File name:	 PostcardParcel.h
// Author:		 Ashley Ung
// Date:			 4/20/2021
// Class:			 CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory.
// Purpose:		 Declares a programmer-defined child class PostcardParcel 
//             representing information for a postcard parcel. 
//***************************************************************************

#pragma once 

#include "PostcardParcel.h"
#include "Parcel.h"
#include <string>
#include <iostream>

using namespace std;

class PostcardParcel : public Parcel {

  public:
    PostcardParcel ();
    PostcardParcel (int trackingNumber, string sender, string reciever,
                    int weight, int travelDistance, string message);
   
    virtual int getDeliveryDay () const;
    virtual double getInsuranceCost ();
    virtual double getRushCost ();
    virtual double getParcelCost ();
    virtual double getCost ();
    
    virtual void setInsurance ();
    virtual void setRush ();

    virtual bool read (istream &rcIn);
    virtual void print (ostream &rcOut) const;

  private:
    string mMessage;

};