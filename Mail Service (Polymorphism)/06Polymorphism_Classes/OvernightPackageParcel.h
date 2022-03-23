//***************************************************************************
// File name:	 OvernightPackageParcel.h
// Author:		 Ashley Ung
// Date:			 4/20/2021
// Class:			 CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory.
// Purpose:    Declares a programmer-defined child class 
//             OvernightPackageParcel representing information for an 
//             overnight package parcel. 
//***************************************************************************

#pragma once 

#include "OvernightPackageParcel.h"
#include "Parcel.h"
#include <string>
#include <iostream>

using namespace std;

class OvernightPackageParcel : public Parcel {

  public:
    OvernightPackageParcel ();
    OvernightPackageParcel (int trackingNumber, string sender,
                            string reciever, int weight, int travelDstance, 
                            int volume);

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
    int mVolume;

};