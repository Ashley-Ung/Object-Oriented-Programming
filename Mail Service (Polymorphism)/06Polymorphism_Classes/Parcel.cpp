//***************************************************************************
// File name:	 Parcel.cpp
// Author:		 Ashley Ung 
// Date:		   4/20/2021
// Class:		   CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory. 
// Purpose:		 Defines each of the function prototypes associated with the
//             parent class Parcel.
//***************************************************************************

#include "Parcel.h"
#include <iostream>
#include <string>

//***************************************************************************
// Constructor:	Parcel
//
// Description:	Initialize the to and from address, weight, and travel 
//              distance equal to the given parameters.  
//
// Parameters:	trackingNumber    - the tracking number to store  
//							sender            - parcel's sender
//              reciever          - parcel's reciever 
//              weight            - parcel's weight in ounces 
//              travelDistance    - distance package will travel  
//
// Returned:		none
//***************************************************************************
Parcel::Parcel (int trackingNumber, std::string sender, 
                std::string reciever, int weight, int travelDistance) {  
  mTrackingNumber = trackingNumber;
  mSenderAddress = sender; 
  mRecieverAddress = reciever;
  mWeight = weight;
  mTravelDistance = travelDistance; 
  mbIsInsured = false; 
  mbIsRushed = false; 
  mbIsDelivered = false; 
}

//***************************************************************************
// Function:	  getInsured 
//
// Description:	Retrieves the binary variable of the parcel in regards to 
//              insurance, the two possible values are true or false. 
//
// Parameters:	none
//
// Returned:		The value of the parcel depending on if it has insurance
//              (true) or not (false).
//***************************************************************************
bool Parcel::getInsured () const {
  return mbIsInsured;   
}

//***************************************************************************
// Function:	  getRushed
//
// Description:	Retrieves the binary variable of the parcel in regards to 
//              if it is rushed, the two possible values are true or false. 
//
// Parameters:	none
//
// Returned:		The value of the parcel depending on if it is rushed (true)
//              not rushed (false).
//***************************************************************************
bool Parcel::getRushed () const {
  return mbIsRushed;               
}

//***************************************************************************
// Function:	  getTID
//
// Description:	Retrieve the tracking ID number of the parcel. 
//
// Parameters:	none 
//
// Returned:		The tracking ID number of the parcel. 
//***************************************************************************
int Parcel::getTID () const {
  return mTrackingNumber;
}

//***************************************************************************
// Function:	  read
//
// Description:	Inputs the Parcel to the stream if the read in data is 
//              valid. 
//
// Parameters:	rcIn - the stream to read from 
//
// Returned:		True, if the Parcel TID, to and from address is read in; 
//              else, false. 
//***************************************************************************
bool Parcel::read (istream &rcIn) {
  bool bIsRead = true;

  if (rcIn >> mTrackingNumber >> mRecieverAddress >> mSenderAddress
           >> mWeight >> mTravelDistance) {
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
// Description:	Output the Parcel to the stream
//
// Parameters:	rcOut   - the stream to output to 
//
// Returned:		ostream - the output stream
//***************************************************************************
void Parcel::print (std::ostream &rcOut) const {
  rcOut << endl << "TID: " << mTrackingNumber << "\tFrom: " << mSenderAddress
        << "\tTo: " << mRecieverAddress << "\t";
}