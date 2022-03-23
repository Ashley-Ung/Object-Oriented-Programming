//***************************************************************************
// File name:	 OvernightPackageParcel.cpp
// Author:		 Ashley Ung 
// Date:		   4/20/2021
// Class:		   CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory.
// Purpose:		 Defines each of the function prototypes associated with the
//             child class OvernightPackageParcel.
//***************************************************************************

#include "OvernightPackageParcel.h"
#include <iostream>

//***************************************************************************
// Constructor:	OvernightPackageParcel
//
// Description:	Call the OvernightPackageParcel default constructor, set   
//              mVolume to zero.  
//
// Parameters:	none
//
// Returned:		none
//***************************************************************************
OvernightPackageParcel::OvernightPackageParcel () : Parcel () {
  mVolume = 0;
}

//***************************************************************************
// Constructor:	OvernightPackageParcel
//
// Description:	Call the Parcels constructor, set mVolume equal to the given 
//              parameter. 
//
// Parameters:	trackingNumber    - the tracking number to store  
//							sender            - parcel's sender
//              reciever          - parcel's reciever 
//              weight            - parcel's weight in ounces 
//              travelDistance    - distance package will travel 
//              volume            - the volume of the package
//
// Returned:		none
//***************************************************************************
OvernightPackageParcel::OvernightPackageParcel (int trackingNumber,        
                                                std::string sender,     
                                                std::string reciever, 
                                                int weight, 
                                                int travelDistance, 
                                                int volume) : 
                                                Parcel (trackingNumber, 
                                                        sender, reciever,
                                                        weight, 
                                                        travelDistance) {
  mVolume = volume; 
}

//***************************************************************************
// Function:	  getDeliveryDay
//
// Description:	Obtains the delivery day of the Parcel by taking into account 
//              whether the parcel was rushed, which will rush the package by 
//              one day. Typically, a package will be delivered within 1 day 
//              if the travel distance is less than or equal to 1000 miles; 
//              otherwise, if the travel distance is greater than 1000 miles,
//              it will take 2 days. 
// 
// Parameters:	none
//
// Returned:		The delivery day of the package parcel. 
//***************************************************************************
int OvernightPackageParcel::getDeliveryDay () const {
  const int RUSHED_DELIVERY_DAY = 1;
  const int ONE_DAY = 1; 
  const int TWO_DAYS = 2;
  const int LONG_DISTANCE_MILES = 1000;

  int deliveryDay; 

  if (mbIsRushed) {
    deliveryDay = RUSHED_DELIVERY_DAY;
  }
  else if (mTravelDistance <= LONG_DISTANCE_MILES) {
    deliveryDay = ONE_DAY;
  }
  else {
    deliveryDay = TWO_DAYS;
  }

  return deliveryDay;
}

//***************************************************************************
// Function:	  getInsuranceCost
//
// Description:	Obtains the insurance cost if the package is insured. The 
//              insurance cost is 25% of the current cost.  
//
// Parameters:	none
//
// Returned:		The cost of the insurance. 
//***************************************************************************
double OvernightPackageParcel::getInsuranceCost () {
  const double INSURANCE_RATE = 1.25;

  double cost = 0;

  if (mbIsInsured) {
    cost = INSURANCE_RATE;
  }
  return cost;
}

//***************************************************************************
// Function:	  getRushCost
//
// Description:	Obtains the rush cost if the package is rushed. The rush 
//              cost is 75% of the current cost. 
//
// Parameters:	none
//
// Returned:		The rush cost for the letter. 
//***************************************************************************
double OvernightPackageParcel::getRushCost () {
  const double RUSH_RATE = 0.75;

  double cost = 0;

  if (mbIsRushed) {
    cost = getParcelCost () * RUSH_RATE;
  }
  return cost;
}

//***************************************************************************
// Function:	  getParcelCost
//
// Description:	Obtains the cost of the Parcel. The cost of a package is 
//              $20 if the volume of the package is greater than 100; 
//              otherwise, it is $12.
//
// Parameters:	none
//
// Returned:		The cost of the package.  
//***************************************************************************
double OvernightPackageParcel::getParcelCost () {
  const int HIGH_VOLUME = 100;
  const int HIGH_VOLUME_COST = 20;
  const int LOW_VOLUME_COST = 12;

  double cost = 0;

  if (mVolume > HIGH_VOLUME) {
    cost = HIGH_VOLUME_COST;
  }
  else {
    cost = LOW_VOLUME_COST;
  }

  return cost;
}

//***************************************************************************
// Function:	  getCost
//
// Description:	Returns the total cost of the parcel, after taking into 
//              account whether the parcel is rushed and insured and includes
//              those costs after evaluating if the parcel is insured and 
//              rush; does this by calling the getRushCost and the 
//              getInsuranceCost functions. 
//
// Parameters:	none
//
// Returned:		The total cost of the overnight package parcel. 
//***************************************************************************
double OvernightPackageParcel::getCost () {
  return getParcelCost () + getInsuranceCost () + getRushCost ();
}

//***************************************************************************
// Function:	  setInsurance 
//
// Description:	If the parcel is insured, the default bool for mbIsInsured is 
//              reassigned with "true". 
//
// Parameters:	none
//
// Returned:		none 
//***************************************************************************
void OvernightPackageParcel::setInsurance () {             
  mbIsInsured = true;
}

//***************************************************************************
// Function:	  setRush
//
// Description:	If the parcel is rushed, the default bool for mbIsRushed is 
//              reassigned with "true". 
//
// Parameters:	none
//
// Returned:		none
//***************************************************************************
void OvernightPackageParcel::setRush () {
  mbIsRushed = true;
}

//***************************************************************************
// Function:	  read
//
// Description:	Inputs the OvernightPackageParcel to the stream if the read 
//              in data is valid. 
//
// Parameters:	rcIn - the stream to read from 
//
// Returned:		True, if the OvernightPackageParcel volume is read in; else, 
//              false. 
//***************************************************************************
bool OvernightPackageParcel::read (istream &rcIn) {
  bool bIsRead = Parcel::read (rcIn);

  if (rcIn >> mVolume) {
    bIsRead = true;
  }
  else {
    bIsRead = false;
  }
  return bIsRead;
}

//***************************************************************************
// Function:	  print
//
// Description:	Print the OvernightPackageParcel to the stream.
//
// Parameters:	rcOut - the stream to print to
//
// Returned:	  none
//***************************************************************************
void OvernightPackageParcel::print (ostream &rcOut) const {

  Parcel::print (rcOut);

  if (mbIsInsured) {      
    rcOut << " INSURED\t";
  }

  if (mbIsRushed) {
    rcOut << " RUSH\t";
  }
 
  rcOut << " OVERNIGHT!\t";

}