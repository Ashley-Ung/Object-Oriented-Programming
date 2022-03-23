//***************************************************************************
// File name:	 LetterParcel.cpp
// Author:		 Ashley Ung 
// Date:		   4/20/2021
// Class:		   CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory.
// Purpose:		 Defines each of the function prototypes associated with the
//             child class LetterParcel.
//***************************************************************************

#include "LetterParcel.h"
#include <iostream>

//***************************************************************************
// Constructor:	LetterParcel 
//
// Description:	Default constructor for letter parcel.  
//
// Parameters:	none
//
// Returned:		none
//***************************************************************************
LetterParcel::LetterParcel () : Parcel () {
}

//***************************************************************************
// Constructor:	LetterParcel 
//
// Description:	Call the Parcel constructor, set mInsurance equal to the  
//              given parameter. 
//
// Parameters:	trackingNumber    - the tracking number to store  
//							sender            - parcel's sender
//              reciever          - parcel's reciever 
//              weight            - parcel's weight in ounces 
//              travelDistance    - distance package will travel 
//
// Returned:		none
//***************************************************************************
LetterParcel::LetterParcel (int trackingNumber, std::string sender,       
                            std::string reciever, int weight,
                            int travelDistance) :
                            Parcel (trackingNumber, sender, reciever,
                            weight, travelDistance) {
}

//***************************************************************************
// Function:	  getDeliveryDay
//
// Description:	Obtains the delivery day of the Parcel by taking into account 
//              whether the parcel was rushed, which will rush the letter by 
//              one day. Typically, a letter will travel 100 miles per day
//              and travel a minimum of 1 day. 
// 
// Parameters:	none
//
// Returned:		The delivery day of the letter Parcel. 
//***************************************************************************
int LetterParcel::getDeliveryDay () const {
  const int MINIMUM_DAY = 1;
  const int RUSHED_DAY = 1;
  const int MILES_PER_DAY = 100;

  int deliveryDay = 0;

  deliveryDay += mTravelDistance / MILES_PER_DAY;  

  if (mbIsRushed && deliveryDay > MINIMUM_DAY) {
    deliveryDay -= RUSHED_DAY;
  }

  if (deliveryDay < MINIMUM_DAY) {
    deliveryDay = MINIMUM_DAY;
  }

  return deliveryDay;
}
//***************************************************************************
// Function:	  getInsuranceCost
//
// Description:	Obtains the insurance cost if the letter is insured. The 
//              insurance cost is $0.45.  
//
// Parameters:	none
//
// Returned:		The cost of the insurance. 
//***************************************************************************
double LetterParcel::getInsuranceCost () {
  double const INSURANCE_COST = 0.45;

  double cost = 0;

  if (mbIsInsured) {
    cost = INSURANCE_COST;
  }
  return cost;
}

//***************************************************************************
// Function:	  getRushCost
//
// Description:	Obtains the rush cost if the letter is rushed. The rush 
//              cost is 10% of the cost. 
//
// Parameters:	none
//
// Returned:		The rush cost for the letter. 
//***************************************************************************
double LetterParcel::getRushCost () {
  const double DISCOUNT_CONVERSION = 10;

  double cost = 0;

  if (mbIsRushed) {
    cost = getParcelCost () / DISCOUNT_CONVERSION;
  }
  return cost;
}

//***************************************************************************
// Function:	  getParcelCost
//
// Description:	Obtains the cost of the Parcel. The cost of a letter is 
//              $0.45 per ounce. 
//
// Parameters:	none
//
// Returned:		The cost of the letter. 
//***************************************************************************
double LetterParcel::getParcelCost () {
  double const COST_PER_OUNCE = 0.45;
  return mWeight * COST_PER_OUNCE;
}

//***************************************************************************
// Function:	  getCost
//
// Description: Returns the total cost of the letter parcel, after taking 
//              into account whether the letter is rushed and insured and 
//              includes those costs after evaluating if the parcel is 
//              insured and rush; does this by calling the getRushCost and  
//              the getInsuranceCost functions. 
//
// Parameters:	none
//
// Returned:		The total cost of the letter parcel. 
//***************************************************************************
double LetterParcel::getCost () { 
  return getParcelCost () + getInsuranceCost () + getRushCost ();
}

//***************************************************************************
// Function:	  setInsurance 
//
// Description:	If the parcel is insured, the default bool for mbIsInsured is 
//              reassigned to "true". 
//
// Parameters:	none
//
// Returned:		none 
//***************************************************************************
void LetterParcel::setInsurance () {     
  mbIsInsured = true; 
}

//***************************************************************************
// Function:	  setRush
//
// Description:	If the parcel is rushed, the default bool for mbIsRushed is 
//              reassigned to "true". 
//
// Parameters:	none
//
// Returned:		none
//***************************************************************************
void LetterParcel::setRush () {
  mbIsRushed = true;
}

//***************************************************************************
// Function:	  read
//
// Description:	Inputs the LetterParcel to the stream if the read in data
//              is valid.
//
// Parameters:	rcIn - the stream to read from
//
// Returned:		True, if the LetterParcel is read in; else, false.
//***************************************************************************
bool LetterParcel::read (istream &rcIn) {  
  bool bIsRead = Parcel::read (rcIn);

  if (bIsRead) {
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
// Description:	Print the LetterParcel to the stream.
//
// Parameters:	rcOut - the stream to print to
//
// Returned:	  none
//***************************************************************************
void LetterParcel::print (ostream &rcOut) const {

  Parcel::print (rcOut);

  if (mbIsInsured) { 
    rcOut << " INSURED\t";
  }

  if (mbIsRushed) {
    rcOut << "RUSH\t";
  }
}