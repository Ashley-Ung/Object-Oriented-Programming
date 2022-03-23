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