//###########################################################################
//DNASet.h 
//###########################################################################
//***************************************************************************
// File name:	 DNASet.h
// Author:		 Ashley Ung
// Date:			 3/7/2021
// Class:			 CS 250
// Assignment: DNASet Assignment 3
// Purpose:		 Declares a programmer-defined class DNASet for operations to  
//             be performed on DNA strands. 
//***************************************************************************

#pragma once
#ifndef DNALSET_H  
#define DNASET_H  

#include "DNAStrand.h"
#include <iostream>

using namespace std;

class DNASet {
  public: 
    static const int MAX_STRANDS = 100;
    
    DNASet ();
    DNASet intersection (const DNASet &rcOtherSet) const;
    DNASet theUnion (const DNASet &rcOtherSet) const;
    DNAStrand getDNA (const int cIndex) const;
    DNAStrand getLongestStrand () const;
    bool isIn (const DNAStrand &rcDNA) const;
    bool add (const DNAStrand &rcDNA); 
    int getSize () const;
    bool readDNA (istream &rcIn);
    void printDNA (ostream &rcOut) const;
    bool mostSimilar (const DNASet &rcOtherSet, int &rcStrandIndex, 
                      int &rcStrandIndexOther) const;

  private: 
    static const char ADENINE = 'A';
    static const char THYMINE = 'T';
    static const char GUANINE = 'G';
    static const char CYTOSINE = 'C';

    DNAStrand macDNA[MAX_STRANDS];
    int mNumStrands = 0; 
};

#endif                                                                       
  
 
//###########################################################################
//DNASet.cpp 
//###########################################################################
//***************************************************************************
// File name:	 DNASet.cpp
// Author:		 Ashley Ung
// Date:			 3/7/2021
// Class:			 CS 250
// Assignment: DNASet Assignment 3
// Purpose:		 Defines each of the function prototypes associated with class
//						 DNASet.
//***************************************************************************

#include "DNASet.h"
#include <iostream>

using namespace std;

/****************************************************************************
Constructor: 	DNA

Description:  A constructor that initializes every object member of type DNA
              after storage is allocated to the object.

Parameters:		none

Returned:			none
****************************************************************************/
DNASet::DNASet () {
  mNumStrands = 0;
}

/****************************************************************************
Function:    isIn

Description: Determines if a particular DNAStrand already exists in the set. 

Parameters:  rcDNA - the DNA strand to check for 

Returned:		 True, if the DNA strand being passed in is already in the
             DNASet; else, false.
****************************************************************************/
bool DNASet::isIn (const DNAStrand &rcDNA) const {
  bool bIsIn = false;

  for (int i = 0; i < mNumStrands; i++) {
    if (rcDNA.equals (macDNA[i])) {
      bIsIn = true;
    }
  }
  return bIsIn;
}

/****************************************************************************
Function:    add

Description: Adds a DNAStrand to the set. Does not allow duplicate strands in 
             the set.

Parameters:  rcDNA - the DNA strand to add

Returned:		 True, if the DNA is added; else, false. 
****************************************************************************/
bool DNASet::add (const DNAStrand &rcDNA) { 
  bool bIsAdded = false;

  if (!isIn (rcDNA) && mNumStrands < MAX_STRANDS) {
    macDNA[mNumStrands] = rcDNA;
    mNumStrands++;
    bIsAdded = true;
  }

  return bIsAdded;
}

/****************************************************************************
Function:    getSize

Description: Gets the current number of items in the set.  

Parameters:  none  

Returned:		 The current number of items in the set. 
****************************************************************************/
int DNASet::getSize () const {
  return mNumStrands;
}

/****************************************************************************
Function:    union

Description: Builds a new DNASet that is the union of this object and 
             rcOtherSet.

Parameters:  rcOtherSet - the rational set to union with

Returned:		 All of the elements contained in DNASet and rcOtherSet. 
****************************************************************************/
DNASet DNASet::theUnion (const DNASet &rcOtherSet) const {         
  DNASet cUnion; 
  
  for (int i = 0; i < mNumStrands; i++) {
    cUnion.add (macDNA[i]); 
  }

  for (int i = 0; i < rcOtherSet.mNumStrands; i++) {
    cUnion.add (rcOtherSet.macDNA[i]);
  }

  return cUnion;
}

/****************************************************************************
Function:    intersection

Description: Builds a new DNASet that is the intersection of this object and
             rcOtherSet.

Parameters:  rcOtherSet - the set to intersect with

Returned:		 The elements that both RationalSet and rcOtherSet have in
             common.
****************************************************************************/
DNASet DNASet::intersection (const DNASet &rcOtherSet) const {      
  DNASet cIntersection;

  for (int i = 0; i < mNumStrands; i++) {
    if (rcOtherSet.isIn (macDNA[i])) {
      cIntersection.add (macDNA[i]);
    }
  }
  return cIntersection;
}

/****************************************************************************
Function:    getDNA

Description: Retrieves a specific DNAStrand from the set.   

Parameters:  index - the integer the user provides in search for the corect 
                     DNAStrand. 

Returned:		 The correct retrieved strand that the user is in search for.
****************************************************************************/
DNAStrand DNASet::getDNA (const int cIndex) const {
  return macDNA[cIndex];
}

/****************************************************************************
Function:    readDNA

Description: Reads a strand from a stream. 

Parameters:  rcIn - the stream to read from

Returned:    True, if the read in strand contains a valid character; else, 
             false. 
****************************************************************************/
bool DNASet::readDNA (istream &rcIn) {
  DNAStrand cNewDNA;
  bool bIsValid = true; 

  while (!rcIn.eof () && bIsValid) {
    if (cNewDNA.read (rcIn)) {
      add (cNewDNA);
    }
    else {
      bIsValid = false;
      cout << "File contains invalid characters :-)";
    }
  }
  return bIsValid;
}

/****************************************************************************
Function:    printDNA

Description: Prints the set to the given ostream. 

Parameters:  rcOut - the stream to print to

Returned:    none
****************************************************************************/
void DNASet::printDNA (ostream &rcOut) const {
  const int ADJUST_FOR_ARRAY = 1; 

  for (int i = 0; i < mNumStrands; i++) {
    macDNA[i].print (rcOut);
    if (i < mNumStrands - ADJUST_FOR_ARRAY) {
      rcOut << " ";
    }
  }
}

/****************************************************************************
Function:    getLongestStrand

Description: Finds the longest DNA strand in each pool. 

Parameters:  none

Returned:    none
****************************************************************************/
DNAStrand DNASet::getLongestStrand () const {
  const int INITIALIZED_INDEX = 0;

  DNAStrand cLongestStrand = macDNA[INITIALIZED_INDEX];
  for (int i = 0; i < mNumStrands; i++) {
    if (cLongestStrand.length () < macDNA[i].length ()) {
      cLongestStrand = macDNA[i];
    }
  }
  return cLongestStrand;
}

/****************************************************************************
Function:     mostSimilar

Description:  Determines the one strand in Pool1 and the one strand in Pool2 
              that are most similar to each other. Handles an empty file, 
              if the file is empty, an empty set will be produced. 

Parameters:   rcOtherSet     - the other set to compare against 
              strandIndexOne - the index of the strands from the set 
              strandIndexTwo - the index of the strands from the other set

Returned:     True, if the strand is valid; else, false and the strand that 
              is the most similar from the two pools. 
****************************************************************************/
bool DNASet::mostSimilar (const DNASet &rcOtherSet, int &rcStrandIndex, 
                          int &rcStrandIndexOther) const {   
  const int EMPTY = 0; 
  bool bIsValid = false; 
  double minimum = 1;
  double pStatHolder = 0;

  if (getSize () != EMPTY && rcOtherSet.getSize () != EMPTY) {
    bIsValid = true;
  }

  for (int i = 0; i < getSize (); i++) {
    for (int j = 0; j < rcOtherSet.getSize (); j++) {
      if (rcOtherSet.getDNA (j).length () == getDNA (i).length ()) {
        pStatHolder = rcOtherSet.getDNA (j).pStat (getDNA (i));
        if (pStatHolder < minimum) {
          minimum = pStatHolder;
          rcStrandIndex = i;
          rcStrandIndexOther = j;
        }
      }
    }
  }
  return bIsValid;
}   
  
 
//###########################################################################
//DNASetDriver.cpp 
//###########################################################################
//***************************************************************************
// File name:	 DNASetDriver.cpp
// Author:		 Ashley Ung
// Date:			 3/7/2021
// Class:			 CS 250
// Assignment: DNASet Assignment 3
// Purpose:		 Driver used to test class DNASet 
// Hours:			 20
// Computer:	 WindowsOS
//***************************************************************************

#include <iostream>
#include <fstream> 
#include <iomanip>
#include "DNAStrand.h"
#include "DNASet.h"

using namespace std;

void drawHeading (string title, char borderChar, int padding);
bool openFileForRead (ifstream &rcInFile, string fileName);
void printPoolSets (DNASet cFirstDNASet, DNASet cSecondDNASet);
void printIntersection (DNASet cFirstDNASet, DNASet cSecondDNASet);
void printUnion (DNASet cFirstDNASet, DNASet cSecondDNASet);
void printLongestStrand (DNASet cFirstDNASet, DNASet cSecondDNASet);
void printMostSimilar (DNASet cFirstDNASet, DNASet cSecondDNASet);

/****************************************************************************
Function:		  main

Description:	Main driver for the DNASet using Classes to show how each
              member function in DNAStrand can be used.

Parameters:		none

Returned:			exit status
****************************************************************************/
int main () {
  const string TITLE_STRING = "DNA POOL ANALYZER";
  const string INPUT_FILE_ONE= "Pool1.txt";
  const string INPUT_FILE_TWO = "Pool2.txt";
  const char BORDER_CHARACTER = '*';
  const int PADDING = 1;
  DNASet cFirstDNASet;
  DNASet cSecondDNASet;

  ifstream inFile;  

  if (openFileForRead (inFile, INPUT_FILE_ONE)) {
    if (!cFirstDNASet.readDNA (inFile)) {
      inFile.close ();
      exit (EXIT_FAILURE);
    }
    inFile.close ();
  }
  else {
    exit (EXIT_FAILURE);
  }

  if (openFileForRead (inFile, INPUT_FILE_TWO)) {
    if (!cSecondDNASet.readDNA (inFile)) {
      inFile.close ();
      exit (EXIT_FAILURE);
    }
    inFile.close ();
  }
  else {
    exit (EXIT_FAILURE);
  }

  drawHeading (TITLE_STRING, BORDER_CHARACTER, PADDING);
  printPoolSets (cFirstDNASet, cSecondDNASet);
  printIntersection (cFirstDNASet, cSecondDNASet);
  printUnion (cFirstDNASet, cSecondDNASet);
  printLongestStrand (cFirstDNASet, cSecondDNASet); 
  printMostSimilar (cFirstDNASet, cSecondDNASet);

  return EXIT_SUCCESS;
}

/****************************************************************************
Function:    drawHeading

Description: Outputs a heading by outputting a name between a row of 
             astericks. 

Parameters:  title      - the title name of the heading
             borderChar - displays the title with a border
             padding    - displays the title with padding spaces

Returned:		 none
****************************************************************************/
void drawHeading (string title, char borderChar, int padding) {

  const int SPACING_GAP = 2;
  const int END_ASTERICKS = 2;

  int titleLength = SPACING_GAP + padding * END_ASTERICKS
                    + static_cast<int>(title.length ());

  for (int i = 0; i < titleLength; i++) {
    cout << borderChar;
  }

  cout << endl << borderChar;

  for (int i = 0; i < padding; i++) {
    cout << " ";
  }

  cout << title;

  for (int i = 0; i < padding; i++) {
    cout << " ";
  }

  cout << borderChar << endl;

  for (int i = 0; i < titleLength; i++) {
    cout << borderChar;
  }

  cout << endl << endl;
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
Function:     printPoolSets

Description:  Displays the DNA sets read in from Pool1 and Pool2.

Parameters:   cFirstDNASet    - the first pool of the DNA set from the file
              cSecondDNASet   - the second pool of the DNA set from the file

Returned:		  none
****************************************************************************/
void printPoolSets (DNASet cFirstDNASet, DNASet cSecondDNASet) {
  cout << "Pool 1" << endl << setfill ('-') << setw (6) << "" << endl;
  cFirstDNASet.printDNA (cout);
  cout << endl << endl << "Pool 2" << endl << setfill ('-') << setw (6) << ""
       << endl;
  cSecondDNASet.printDNA (cout);
}

/****************************************************************************
Function:     printIntersection

Description:  Displays the DNAStrands that appear in common in both sets. 

Parameters:   cFirstDNASet    - the first pool of the DNA set from the file
              cSecondDNASet   - the second pool of the DNA set from the file

Returned:		  none
****************************************************************************/
void printIntersection (DNASet cFirstDNASet, DNASet cSecondDNASet) {
  cout << endl << endl << "In both Pools" << endl << setfill ('-')
       << setw (13) << "" << endl;
  (cFirstDNASet.intersection (cSecondDNASet)).printDNA (cout);
}

/****************************************************************************
Function:     printUnion

Description:  Displays all of the DNAStrands that appear in both sets.

Parameters:   cFirstDNASet    - the first pool of the DNA set from the file
              cSecondDNASet   - the second pool of the DNA set from the file

Returned:		  none
****************************************************************************/
void printUnion (DNASet cFirstDNASet, DNASet cSecondDNASet) {
  cout << endl << endl << "In at least one Pool" << endl << setfill ('-')
       << setw (20) << "" << endl;
  cFirstDNASet.theUnion (cSecondDNASet).printDNA (cout);
}

/****************************************************************************
Function:     printLongestStrand

Description:  Displays the longest DNAStrand that exists in each set. If a 
              tie is encountered, the strands closest to the top of the file 
              has top priority to be printed over the strands below it. 

Parameters:   cFirstDNASet    - the first pool of the DNA set from the file
              cSecondDNASet   - the second pool of the DNA set from the file

Returned:		  none
****************************************************************************/
void printLongestStrand (DNASet cFirstDNASet, DNASet cSecondDNASet) {
  DNAStrand cLongestStrand;

  cout << endl << endl << "Longest Strand in each Pool" << endl
       << setfill ('-') << setw (27) << "" << endl << "Pool1: ";
  cLongestStrand = cFirstDNASet.getLongestStrand ();
  cLongestStrand.print (cout);
  cout << endl << "Pool2: ";
  cLongestStrand = cSecondDNASet.getLongestStrand ();
  cLongestStrand.print (cout);
}

/****************************************************************************
Function:     printMostSimilar 

Description:  Determines which strands from Pool1 and Pool2 are most similar 
              and prints both strands to the screen. 

Parameters:   cFirstDNASet    - the first pool of the DNA set from the file
              cSecondDNASet   - the second pool of the  DNA set from the file

Returned:		  none
****************************************************************************/
void printMostSimilar (DNASet cFirstDNASet, DNASet cSecondDNASet) {
  const int HUNDREDTHS_PLACE = 2;
  int strandOne;
  int strandTwo;

  cout << endl << endl << "Most Similar:" << endl << setfill ('-')
       << setw (19) << "" << endl;
  if (cFirstDNASet.mostSimilar (cSecondDNASet, strandOne, strandTwo)) {
    cout << "P-Stat: " << fixed << setprecision (HUNDREDTHS_PLACE)
         << cFirstDNASet.getDNA (strandOne).pStat 
            (cSecondDNASet.getDNA (strandTwo)) << endl << "Pool1: ";  
    cFirstDNASet.getDNA (strandOne).print (cout);
    cout << endl << "Pool2: ";
    cSecondDNASet.getDNA (strandTwo).print (cout);
  }
}