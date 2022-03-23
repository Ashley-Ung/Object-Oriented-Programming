//***************************************************************************
// File name:	 Parcel.h
// Author:		 Ashley Ung 
// Date:		   4/20/2021
// Class:		   CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory. 
// Purpose:		 Declares a programmer-defined parent class Parcel representing 
//             information for one mail parcel. 
//***************************************************************************

#pragma once

#include <iostream>

using namespace std;

class Parcel {

  public:  
    Parcel (int trackingNumber = 0, string sender = "", string reciever = "",   
            int weight = 0, int travelDistance = 0);

    bool getInsured () const;  
    bool getRushed () const; 
    int getTID () const;             

    virtual int getDeliveryDay () const = 0;                
    virtual double getInsuranceCost () = 0;                            
    virtual double getRushCost () = 0;                                
    virtual double getParcelCost () = 0;                       
    virtual double getCost () = 0;     
    virtual void setInsurance () = 0;
    virtual void setRush () = 0; 

    virtual bool read (istream &rcIn);
    virtual void print (ostream &rcOut) const;

  protected : 
    int mWeight;
    int mTravelDistance;
    bool mbIsInsured;
    bool mbIsRushed;
    bool mbIsDelivered; 

  private:
    string mSenderAddress;
    string mRecieverAddress;
    int mTrackingNumber;  
    double mCost; 

};

