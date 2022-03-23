//***************************************************************************
// File name:		DNAStrand.cpp
// Author:			chadd williams 
// Date:				2/26/2020
// Class:				CS 250
// Assignment:  DNA Set
// Purpose:		  Defines each of the function prototypes associated with class
//						  DNAStrand.
//***************************************************************************

#include "DNAStrand.h"

//***************************************************************************
// Function:		reverse
//
// Description:	Produce the reverse of the current DNA
//
// Parameters:  none
//
// Returned:		DNAStrand - a new DNA object that is the reverse of the 
//							current object.
//***************************************************************************
DNAStrand DNAStrand::reverse () const {
	DNAStrand cRetVal;

	for (int i = static_cast<int> (mDNA.length ()) - 1; i >= 0; --i) {
		cRetVal.mDNA.push_back (mDNA.at (i));
	}

	return cRetVal;
}

//***************************************************************************
// Function:		lenth
//
// Description:	Get the length of the current DNAStrand
//
// Parameters:  none
//
// Returned:		int - the length
//***************************************************************************
int DNAStrand::length () const {
	return static_cast<int>(mDNA.length ());
}

//***************************************************************************
// Function:		complement
//
// Description:	Produce the complement of the current DNA
//
// Parameters:  none
//
// Returned:		DNAStrand - a new DNA object that is the complement of the 
//							current object
//***************************************************************************
DNAStrand DNAStrand::complement () const {
	DNAStrand cRetVal;
	char value = ADENINE;
	for (unsigned int i = 0; i < mDNA.length () ; ++i) {
		switch (mDNA.at (i)) {
			case ADENINE: value = THYMINE;
										break;
			case THYMINE: value = ADENINE;
										break;
			case CYTOSINE:value = GUANINE;
										break;
			case GUANINE: value = CYTOSINE;
										break;
		}
		cRetVal.mDNA.push_back (value);
	}

	return cRetVal;
}

//***************************************************************************
// Function:		read
//
// Description:	read a strand from a stream
//
// Parameters:  rcIn - the stream to read from
//
// Returned:		true if the strand was valid, false otherwise.
//***************************************************************************
bool DNAStrand::read (istream &rcIn) {
	bool bRetVal = true;
	char value;

	if ( ! (rcIn >> mDNA)) 	{
		bRetVal = false;
	}

	for (unsigned int i = 0; i < mDNA.length (); ++i) {
		value = mDNA.at(i);
		if (!(ADENINE == value || THYMINE == value || GUANINE == value ||
			 CYTOSINE == value)) {
			bRetVal = false;
		}
	}
	return bRetVal;
}

//***************************************************************************
// Function:		print
//
// Description:	print a strand to a stream
//
// Parameters:  rcOut - the stream to print to
//
// Returned:		None
//***************************************************************************
void DNAStrand::print (ostream &rcOut) const {
	rcOut << mDNA;
}

//***************************************************************************
// Function:		pstat
//
// Description:	Determine the pstat between two strands
//
// Parameters:  rcOther - the strand to compare against
//
// Returned:		double : the pStat value
//***************************************************************************
double DNAStrand::pStat (const DNAStrand &rcOther) const {
	double count = 0;

	for (unsigned int i = 0; i < mDNA.length (); ++i) {
		if (mDNA.at (i) != rcOther.mDNA.at (i)) {
			count++;
		}
	}

	return count / mDNA.length ();
}

//***************************************************************************
// Function:		equals
//
// Description:	Accepts a DNAStrand object and returns true if the passed in 
//							DNAStrand object is identitcal to the current DNAStrand 
//							object, otherwise the function will return false. 
//
// Parameters:  rcOther - the strand to compare against
//
// Returned:		True if the passed in DNAStrand object is identical to the 
//							current DNAStrand; else, false. 
//***************************************************************************
bool DNAStrand::equals (const DNAStrand &rcOther) const {
	return (mDNA == rcOther.mDNA);
}
