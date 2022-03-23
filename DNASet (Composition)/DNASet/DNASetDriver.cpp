//***************************************************************************
// File name:	 DNASetDriver.cpp
// Author:		 Ashley Ung 
// Date:			 3/7/2020
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