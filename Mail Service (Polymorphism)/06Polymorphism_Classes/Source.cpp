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