//###########################################################################
//LetterParcel.h 
//###########################################################################
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
  
 
//###########################################################################
//OvernightPackageParcel.h 
//###########################################################################
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
  
 
//###########################################################################
//Parcel.h 
//###########################################################################
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

   
  
 
//###########################################################################
//PostcardParcel.h 
//###########################################################################
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
  
 
//###########################################################################
//LetterParcel.cpp 
//###########################################################################
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
  
 
//###########################################################################
//OvernightPackageParcel.cpp 
//###########################################################################
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
  
 
//###########################################################################
//Parcel.cpp 
//###########################################################################
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
  
 
//###########################################################################
//PostcardParcel.cpp 
//###########################################################################
//***************************************************************************
// File name:	 PostcardParcel.cpp
// Author:		 Ashley Ung 
// Date:		   4/20/2021
// Class:		   CS 250
// Assignment: A class hierarchy on mail services demonstrating the use of 
//             polymorphism, virtual functions, and dynamic memory.
// Purpose:		 Defines each of the function prototypes associated with the
//             child class PostcardParcel. 
//***************************************************************************

#include "PostcardParcel.h"
#include <iostream>

//***************************************************************************
// Constructor:	PostcardParcel 
//
// Description:	Call the PostcardParcel default constructor, set mMessage to  
//              an empty string.
//
// Parameters:	none
//
// Returned:		none
//***************************************************************************
PostcardParcel::PostcardParcel () : Parcel () {
  mMessage = "";
}

//***************************************************************************
// Constructor:	PostcardParcel 
//
// Description:	Call the Parcel constructor, set mMessage equal to the
//              given parameter. 
//
// Parameters:	trackingNumber    - the tracking number to store  
//							sender            - parcel's sender  
//              reciever          - parcel's reciever 
//              weight            - parcel's weight 
//              travelDistance    - distance package will travel  
//              message           - message on the postcard
//
// Returned:		none
//***************************************************************************
PostcardParcel::PostcardParcel (int trackingNumber, std::string sender,
                                std::string reciever, int weight,
                                int travelDistance, std::string message) :
                                Parcel (trackingNumber, sender, reciever,
                                weight, travelDistance) {
  mMessage = message;
}

//***************************************************************************
// Function:	  getDeliveryDay
//
// Description:	Obtains the delivery day of the Parcel by taking into account 
//              whether the parcel was rushed, which will rush the postcard 
//              by one day. Typically, a postcard will travel 10 miles per 
//              day and travel a minimum of 1 day. 
//
// Parameters:	none
//
// Returned:		The delivery day. 
//***************************************************************************
int PostcardParcel::getDeliveryDay () const {
  const int MINIMUM_DAY = 1;
  const int RUSHED_DAY = 2;
  const int MILES_PER_DAY = 10;

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
// Description:	Obtains the insurance cost if the postcard is insured. The 
//              insurance cost is $0.15.  
//
// Parameters:	none
//
// Returned:		The cost of the insurance. 
//***************************************************************************
double PostcardParcel::getInsuranceCost () {
  double const INSURANCE_COST = 0.15;

  double cost = 0;

  if (mbIsInsured) {
    cost = INSURANCE_COST;
  }
  return cost;
}

//***************************************************************************
// Function:	  getRushCost
//
// Description:	Obtains the rush cost if the postcard is rushed. The rush 
//              cost is $0.25. 
//
// Parameters:	none
//
// Returned:		The rush cost for the postcard. 
//***************************************************************************
double PostcardParcel::getRushCost () {
  const double RUSH_COST = 0.25;

  double cost = 0;

  if (mbIsRushed) {
    cost = RUSH_COST;
  }
  return cost;
}

//***************************************************************************
// Function:	  getParcelCost
//
// Description:	Obtains the cost of the Parcel. The cost of a postcard is 
//              $0.15 regardless of the postcard's weight. 
//
// Parameters:	none
//
// Returned:		The cost of the postcard. 
//***************************************************************************
double PostcardParcel::getParcelCost () {
  double const POSTCARD_COST = 0.15;
  return POSTCARD_COST;
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
// Returned:		The total cost of the postcard parcel. 
//***************************************************************************
double PostcardParcel::getCost () {
  return getInsuranceCost () + getRushCost () + getParcelCost ();
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
void PostcardParcel::setInsurance () {
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
void PostcardParcel::setRush () {
  mbIsRushed = true;
}

//***************************************************************************
// Function:	  read
//
// Description:	Inputs the PostcardParcel to the stream if the read in data
//              is valid. 
//
// Parameters:	rcIn - the stream to read from 
//
// Returned:		True, if the PostcardParcel volume is read in; else, false. 
//***************************************************************************
bool PostcardParcel::read (istream &rcIn) {
  bool bIsRead = Parcel::read (rcIn);

  if (rcIn >> mMessage) {
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
// Description:	Print the PostcardParcel to the stream.
//
// Parameters:	rcOut - the stream to print to
//
// Returned:	  none
//***************************************************************************
void PostcardParcel::print (ostream &rcOut) const {

  Parcel::print (rcOut);

  if (mbIsInsured) {
    rcOut << "INSURED\t";
  }

  if (mbIsRushed) {
    rcOut << "RUSH\t";
  }

  rcOut << mMessage << "\t";

}
   
  
 
//###########################################################################
//Source.cpp 
//###########################################################################
//***************************************************************************
// File name:	 Source.cpp
// Author:		 Ashley Ung
// Date:			 4/20/2021
// Class:			 CS 250
// Assignment: A class hierarchy to demonstrate the use of polymorphism, 
//             virtual functions, and dynamic memory. 
// Purpose:		 Driver used to read various mail parcels from a data file and 
//             allows the user to view the parcels, add insurance, rush 
//             delivery, or deliver any parcel. 
// Hours:		   24
// Computer:	 WindowsOS
//***************************************************************************

#include <iostream>
#include <iomanip>
#include <fstream>
#include "LetterParcel.h"
#include "PostcardParcel.h"
#include "OvernightPackageParcel.h"

using namespace std;

bool openFileForRead (ifstream &rcInFile, string fileName);
void printMenuHeading ();
void populatingArray (Parcel *apcParcel[], int &numParcels, 
                      ifstream &inFile);
void printAll (Parcel *apcParcel[], int &numParcels);
void addInsurance (Parcel *apcParcel[], int &numParcels);
void addRush (Parcel *apcParcel[], int &numParcels);
void deliverParcel (Parcel *apcParcel[], int &numParcels);
bool validTID (Parcel *apcParcel[], int TID, int &numParcels);

/****************************************************************************
Function:		  main

Description:	The main driver for Parcel using Classes to show how each 
              member function in Parcel can be used.

Parameters:		none

Returned:			exit status
****************************************************************************/
int main() {
  const string INPUT_FILE = "parcels.txt";
  const int MAX_PARCEL = 25;
  const int PRINT_ALL = 1; 
  const int ADD_INSURANCE = 2; 
  const int ADD_RUSH = 3; 
  const int DELIVER = 4;
  const int QUIT = 5; 
  char const LETTER = 'L';
  char const POSTCARD = 'P';
  char const OVERNIGHT_PACKAGE = 'O';

  Parcel *apcParcel[MAX_PARCEL] = { nullptr }; 
  int numParcels = 0;
  char parcelType;
  int choice = 1;

  ifstream inFile; 

  openFileForRead (inFile, INPUT_FILE);

  cout << "Mail Simulator!" << endl; 

  while (inFile >> parcelType && numParcels < MAX_PARCEL) {   
    switch (parcelType) {
      case LETTER: 
        apcParcel[numParcels] = new LetterParcel; 
        populatingArray (apcParcel, numParcels, inFile);
        break; 

      case POSTCARD:
        apcParcel[numParcels] = new PostcardParcel;
        populatingArray (apcParcel, numParcels, inFile);
        break; 

      case OVERNIGHT_PACKAGE:
        apcParcel[numParcels] = new OvernightPackageParcel;
        populatingArray (apcParcel, numParcels, inFile);
        break;

      default :
        break; 
    }
  }

  if (numParcels == 0) {
    cout << "We have no parcels to deliver :-)";
    exit (EXIT_FAILURE);
  }

  do {

    do {
      printMenuHeading ();
      cout << endl << "Choice> "; 
      cin >> choice;
    } while (!(PRINT_ALL == choice || ADD_INSURANCE == choice
             || ADD_RUSH == choice || DELIVER == choice || QUIT == choice));

    switch (choice) {
      case PRINT_ALL:
        printAll (apcParcel, numParcels);
        break;

      case ADD_INSURANCE:
        addInsurance (apcParcel, numParcels);
        break;

      case ADD_RUSH:
        addRush (apcParcel, numParcels);
        break;

      case DELIVER:
        deliverParcel (apcParcel, numParcels);
        break;
    }
  } while (choice != QUIT); 
  
  for (int i = 0; i < numParcels; i++) {
    delete apcParcel[i];
  }

  inFile.close ();

  return EXIT_SUCCESS;
}

/****************************************************************************
Function:     openFileForRead

Description:  Checks if the file is open, if the file is not open, the
              program will return false, else, true.

Parameters:   inFile   - reading in the file stream
              fileName - the name of the file

Returned:			True if the file is open; else, false.
****************************************************************************/
bool openFileForRead (ifstream &rcInFile, string fileName) {
  bool bIsOpen = true;

  rcInFile.open (fileName);

  if (!rcInFile.is_open ()) {
    cout << "Error opening file.";
    bIsOpen = false;
  }

  return bIsOpen;
}

/****************************************************************************
Function:    printMenuHeading

Description: Prints the possible menu selections.

Parameters:  none

Returned:		 none
****************************************************************************/
void printMenuHeading () {
  const string OPTION_PRINT_ALL = "1. Print All";
  const string OPTION_ADD_INSURANCE = "2. Add Insurance";
  const string OPTION_ADD_RUSH = "3. Add Rush";
  const string OPTION_DELIVER = "4. Deliver";
  const string OPTION_QUIT = "5. Quit"; 

  cout << endl << OPTION_PRINT_ALL << endl << OPTION_ADD_INSURANCE << endl
       << OPTION_ADD_RUSH << endl << OPTION_DELIVER << endl << OPTION_QUIT 
       << endl;
}

/****************************************************************************
Function:    populatingArray

Description: Populates the array by storing the read in values from the file
             into the array apcParcels. 

Parameters:  apcParcel     - an array of pointers to Parcel
             numParcels    - the number of parcels 
             inFile        - data read in from the file stream 

Returned:		 none
****************************************************************************/
void populatingArray (Parcel *apcParcel[], int &numParcels, 
                      ifstream &inFile) {
  apcParcel[numParcels]->read (inFile); 
  numParcels++;
}

/****************************************************************************
Function:    printAll

Description: Prints all the data about the parcels that was read in from the 
             file. 

Parameters:  apcParcel  - an array of pointers to Parcel
             numParcels - the number of parcels 

Returned:		 none
****************************************************************************/
void printAll (Parcel *apcParcel[], int &numParcels) {
  for (int i = 0; i < numParcels; i++) {
    if (apcParcel[i] != nullptr) {
      apcParcel[i]->print (cout); 
    }
  }

  cout << endl;
}

/****************************************************************************
Function:    addInsurance 

Description: If the user chooses to insure the parcel, the insurance cost 
             of the parcel is implemented. 

Parameters:  apcParcel  - an array of pointers to Parcel
             numParcels - the number of parcels 

Returned:		 none
****************************************************************************/
void addInsurance (Parcel *apcParcel[], int &numParcels) {
  const int INDEX_ADJUSTMENT = 1;
  
  int TID;

  cout << endl << "TID> ";
  cin >> TID;

  if (validTID (apcParcel, TID, numParcels)) {
    if (apcParcel[TID - INDEX_ADJUSTMENT] != nullptr) {
      apcParcel[TID - INDEX_ADJUSTMENT]->setInsurance ();
      cout << "Added Insurance for $"
           << apcParcel[TID - INDEX_ADJUSTMENT]->getInsuranceCost ();
      apcParcel[TID - INDEX_ADJUSTMENT]->print (cout);
      cout << endl;
    }
  }
}

/****************************************************************************
Function:    addRush

Description: If the user chooses to rush the parcel, the rush cost is 
             implemented. 

Parameters:  apcParcel  - an array of pointers to Parcel
             numParcels - the number of parcels 

Returned:		 none
****************************************************************************/
void addRush (Parcel *apcParcel[], int &numParcels) {
  const int INDEX_ADJUSTMENT = 1;
  
  int TID;

  cout << endl << "TID> ";
  cin >> TID;

  if (validTID (apcParcel, TID, numParcels)) {
    if (apcParcel[TID - INDEX_ADJUSTMENT] != nullptr) {
      apcParcel[TID - INDEX_ADJUSTMENT]->setRush ();
      cout << "Added Rush for $"
           << apcParcel[TID - INDEX_ADJUSTMENT]->getRushCost ();
      apcParcel[TID - INDEX_ADJUSTMENT]->print (cout);
      cout << endl;
    }
  }
}

/****************************************************************************
Function:    deliverParcel

Description: If the user chooses to deliver the parcel, the program will
             output the total cost of the parcel as well as the amount of 
             days the parcel will take to be delivered. 

Parameters:  apcParcel    - an array of pointers to Parcel
             numParcels   - the number of parcels 

Returned:		 none
****************************************************************************/
void deliverParcel (Parcel *apcParcel[], int &numParcels) {
  const int INDEX_ADJUSTMENT = 1;

  int TID; 

  cout << endl << "TID> ";
  cin >> TID;

  if (validTID (apcParcel, TID, numParcels)) {
    if (apcParcel[TID - INDEX_ADJUSTMENT] != nullptr) {
      apcParcel[TID - INDEX_ADJUSTMENT]->getDeliveryDay ();
      cout << "Delivered!" << endl
           << apcParcel[TID - INDEX_ADJUSTMENT]->getDeliveryDay ()
           << " Day, $" << fixed << setprecision (2)
           << apcParcel[TID - INDEX_ADJUSTMENT]->getCost ();
      apcParcel[TID - INDEX_ADJUSTMENT]->print (cout);
      cout << endl;
      delete apcParcel[TID - INDEX_ADJUSTMENT];
      apcParcel[TID - INDEX_ADJUSTMENT] = nullptr;
    }
  }
}

/****************************************************************************
Function:    validTID

Description: Checks if the TID value entered is a valid value. If the user 
             inputs a bad TID, the menu and choice prompt will display again.

Parameters:  apcParcel    - an array of pointers to Parcel
             TID          - the tracking ID number of the parcel
             numParcels   - the number of parcels

Returned:		 True, if the tracking ID number is valid; else, false. 
****************************************************************************/
bool validTID (Parcel *apcParcel[], int TID, int &numParcels) {
  bool bIsValidTID = false; 

  for (int i = 0; i < numParcels; i++) {
    if (apcParcel[i] != nullptr && apcParcel[i]->getTID () == TID) {
      bIsValidTID = true;
    }
  }

  return bIsValidTID;
}   