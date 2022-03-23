#pragma once
//***************************************************************************
// File name:		DNAStrand.h
// Author:			chadd williams 
// Date:				2/26/2020
// Class:				CS 250
// Assignment:  DNA Set
// Purpose:			Declares programmer-defined class DNAStrand for operations to
//              be performed on DNA strands. 
//***************************************************************************

#include <string>
#include <iostream>

using namespace std;

class DNAStrand {

	public:
		DNAStrand reverse () const;
		DNAStrand complement () const;

		bool read (istream&);
		void print (ostream&) const;
		double pStat (const DNAStrand&) const;
		int length () const;
		bool equals (const DNAStrand &rcOther) const;

		static const char ADENINE = 'A';
		static const char THYMINE = 'T';
		static const char CYTOSINE = 'C';
		static const char GUANINE = 'G';

	private:
		string mDNA;
};
