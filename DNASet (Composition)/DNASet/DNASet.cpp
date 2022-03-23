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