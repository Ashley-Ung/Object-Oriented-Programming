//**********************************************************************
// File name:   main.cpp
// Author:      Ashley Ung 
// Date:        February 14, 2021
// Class:       CS 250-01     
// Assignment:  Cryptography Assignment 1
// Purpose:     To build a program that will take a plain text file and 
//							produce an encrypted file or vice versa.  
// Hours:       26
// Computer OS: MacOS
//**********************************************************************

#include <iostream> 
#include <string> 
#include <fstream>

using namespace std; 

const int gLettersInAlphabet = 26;

void printCharacters (char character, int numberOfCharacters);
void drawHeading (string title, char borderChar, int padding);
void getMappingData (int &numberOfMappings, string &keys); 
void openFileForRead (ifstream &inputFile, string message);
void openFileForWrite (ofstream &outputFile, string message);
void closeFileForRead (ifstream &inputFile);
void closeFileForWrite (ofstream &outputFile); 
void constructMappingArray (char mappingArray[][gLettersInAlphabet], 
														string keys, int numberOfMappings); 
void printMappingArray (const char mappingArray[][gLettersInAlphabet], 
												int numberOfMappings); 
bool isValid (string keys); 
char decodeCharacter (char ciphertextCharacter, 
											const char mappingArray[][gLettersInAlphabet],
											int numberOfMappings); 
char encodeCharacter (char plaintextCharacter, 
											const char mappingArray[][gLettersInAlphabet], 
											int numberOfMappings);

/***********************************************************************
Function:			main

Description:	Executes the cryptography.

Parameters:		None

Returned:			Return Status 
***********************************************************************/
int main () { 
	const string TITLE_STRING = "CRYPTOGRAPHY"; 
	const string PLAINTEXT_PROMPT = "Enter plaintext filename: "; 
	const string CIPHERTEXT_PROMPT = "Enter ciphertext filename: ";
	const int PADDING = 10; 
	const int MAX_MAPPINGS = 25;
	const char BORDER_CHARACTER = '*'; 
	const char ENCRYPT_UPPERCASE = 'E';
	const char DECRYPT_UPPERCASE = 'D';
	const char QUIT_UPPERCASE = 'Q';
	const char Y_UPPERCASE = 'Y';
	
	int numberOfMappings;  
	char choice; 
	char mappingArray[MAX_MAPPINGS][gLettersInAlphabet];
	ifstream inputFile;
	ofstream outputFile;
	string keys;
	string readPrompt;
	string writePrompt; 
	string line; 
	
	drawHeading (TITLE_STRING, BORDER_CHARACTER, PADDING);
	
	do { 
		do { 
			cout << "Enter E) for encrypt, D) for decrypt, or Q) for quit: "; 
	    cin >> choice; 
	    } while (!(ENCRYPT_UPPERCASE == choice 
							 || DECRYPT_UPPERCASE == choice 
							 || QUIT_UPPERCASE == choice));
							 
		if (QUIT_UPPERCASE != choice) { 
			getMappingData (numberOfMappings, keys); 
			constructMappingArray (mappingArray, keys, numberOfMappings); 
			
			if (ENCRYPT_UPPERCASE == choice) {
				readPrompt = PLAINTEXT_PROMPT;
				writePrompt = CIPHERTEXT_PROMPT;
			}
			else { 
				readPrompt = CIPHERTEXT_PROMPT; 
				writePrompt = PLAINTEXT_PROMPT;
			}
			
			openFileForRead (inputFile, readPrompt); 
			openFileForWrite (outputFile, writePrompt);
			
			while (!inputFile.eof ()) {
				getline (inputFile, line);

				if (ENCRYPT_UPPERCASE == choice) {
					for (int i = 0; i < line.length (); i++) { 
						outputFile << encodeCharacter (line[i], 
											    mappingArray, numberOfMappings); 
					}
					cout << endl << "Your message has been encrypted!" << endl 
							 << endl;
				}
			  else { 
					for (int i = 0; i < line.length (); i++) { 
						outputFile << decodeCharacter (line[i], mappingArray, 
												  numberOfMappings); 
					}
					cout << endl << "Your message has been decrypted!" << endl 
							 << endl; 
				}

				if (!inputFile.eof ()) { 
					outputFile << endl; 
				}
			}
			
			closeFileForRead (inputFile); 
			closeFileForWrite (outputFile);
			
			cout << "Would you like to encrypt or decrypt another file "; 
			cout << "(Y or N)?: ";  
			cin >> choice; 
		}
	} while (Y_UPPERCASE == choice && QUIT_UPPERCASE != choice);
	
	return EXIT_SUCCESS; 
}

/***********************************************************************
Function:			drawHeading

Description:	Outputs a heading by outputting a name between a row of
							asterisks. 

Parameters:		title 			- the title name of the heading
							borderChar  - displays the title with a border
							padding     - displays the title with padding spaces

Returned:			None 
***********************************************************************/
void drawHeading (string title, char borderChar, int padding) { 
	
	const int SPACING_GAP = 2; 
	const int END_ASTERICKS = 2; 
	
	int titleLength = SPACING_GAP + padding * END_ASTERICKS 
										+ title.length ();  
 
	for (int i = 0; i < titleLength; i++) { 
		cout << borderChar; 
	}
	
	cout << endl << borderChar;
	
	for (int i = 0; i < padding; i++) {
		cout << " ";
	}
	
	cout << title;
	
	for (int i = 0; i < padding; i++) {
		cout << " " ; 
	}
	
	cout << borderChar << endl;
		
	for (int i = 0; i < titleLength; i++) {
		cout << borderChar; 
	}
	
	cout << endl << endl;
}

/***********************************************************************
Function:			getMappingData  

Description:	Prompts the user for the number of mappings and the keys. 
							The number of mappings and keys are returned through the 
							parameters.  

Parameters:		numberOfMappings - the amount of interations the  
																 mapping should execute
							keys 						 - the mapping letters 
Returned:			None
***********************************************************************/
void getMappingData (int &numberOfMappings, string &keys) { 	
	const int MIN_MAPPINGS = 2; 
	const int MAX_MAPPINGS = 25; 
	
	numberOfMappings = 0;
	
	do {
		cout << "Enter the number of mappings to use (2-25): "; 
		cin >> numberOfMappings;
	} while (numberOfMappings < MIN_MAPPINGS 
					 || numberOfMappings > MAX_MAPPINGS);
	
	do {
		cout << "Enter the " << numberOfMappings << " keys: ";  
		cin >> keys; 
	} while ((keys.length () != numberOfMappings) 
						|| !(isValid (keys))); 
}

/***********************************************************************
Function:			isValid  

Description:	This function validates if the user inputted capitalized 
							keys. 

Parameters:		key - the mapping letters

Returned:			bIsCapitalized 
***********************************************************************/
bool isValid (string keys) { 
	bool bIsValid = true; 
	const char LETTER_Z = 'Z';
	const char LETTER_A = 'A';
	
	for (int i = 0; i < keys.length (); i++) { 
		if (keys.at (i) > LETTER_Z || keys.at (i) < LETTER_A) { 
			bIsValid = false;
		}
	}
	return bIsValid; 
}

/***********************************************************************
Function:			openFileForRead 

Description:	Accepts a message to be displayed, then prompts the user 
							to enter a plaintext file validating that the file exists 
							and is open. 

Parameters:		inputFile - a file that contains data that serve as the 
													input of the program.
							message   - the statment to be printed to the screen

Returned:			None
***********************************************************************/
void openFileForRead (ifstream &inputFile, string message) { 
	string inputMessage;  
	
	do { 
		cout << message; 
		cin >> inputMessage; 
		inputFile.open (inputMessage);
	} while (!inputFile.is_open ());
}

/***********************************************************************
Function:			openFileForWrite 

Description:	Similar to openFileForRead only we are writing to a file.  

Parameters:		outputFile - a file that contains data that serve as the 
													 output of the program
							message    - the statement to be printed on the screen

Returned:			None
***********************************************************************/
void openFileForWrite (ofstream &outputFile, string message) { 
	string outputMessage;
	
	do { 
		cout << message; 
		cin >> outputMessage; 
		outputFile.open (outputMessage);
	} while (!outputFile.is_open ());  
}

/***********************************************************************
Function:			closeFileForRead 

Description:	Closes a file opened for reading. 

Parameters:		inputFile - a file that contains data that serve as input 
													to the program. 

Returned:			None
***********************************************************************/
void closeFileForRead (ifstream &inputFile) {
	inputFile.close ();
}

/***********************************************************************
Function:			closeFileForWrite

Description:	Closes a file opened for writing.  

Parameters:		outputFile - a file that contains data that serve as the 
													 output of the program

Returned:			None
***********************************************************************/
void closeFileForWrite (ofstream &outputFile) {
	outputFile.close ();
}

/***********************************************************************
Function:			constructMappingArray

Description:	This function will go through the string character by 
							character. 

Parameters:		mappingArray     - an array that stores the mapping  
																 data and the letters in the alphabet
							keys             - the mapping letters 
							numberOfMappings - the amount of interations the  
																 mapping should execute
Returned:			None
***********************************************************************/
void constructMappingArray (char mappingArray[][gLettersInAlphabet], 
														string keys, int numberOfMappings) {
	const int ASCII_VALUE_Z = 90;  
	
	for (int i = 0; i < numberOfMappings; i++) {
		for (int j = 0; j < gLettersInAlphabet; j++) {
			 if (keys.at (i) + j > ASCII_VALUE_Z) {
				 mappingArray[i][j] = keys.at (i) + j - gLettersInAlphabet; 
			 }
			 else { 
				 mappingArray[i][j] = keys.at (i) + j;
			 }
		 }
	 }
}

/***********************************************************************
Function:			printMappingArray 

Description:	This function is for debugging. The mapping array will be
							printed out and the user will check if the mappingArray 
							is correct.

Parameters:		mappingArray       - an array that stores the mapping  
																   data and the letters in the alphabet
							numberOfMappings   - the amount of interations the  
																	 mapping should execute

Returned:			None
***********************************************************************/
void printMappingArray (const char mappingArray[][gLettersInAlphabet], 
												int numberOfMappings) {
		cout << endl; 
		
		for (int i = 0; i < numberOfMappings; i++) { 
			for (int j = 0; j < gLettersInAlphabet; j++) {
				cout << mappingArray[i][j]; 
			}
			cout << endl;
		}
}

/***********************************************************************
Function:			decodeCharacter 

Description:	Using the number of mappings and the mappingArray, this 
							this function takes an encoded character and returns a 
							decoded character. 

Parameters:		ciphertextCharacter - the decode character 
							mappingArray        - an array that stores the mapping  
																    data and the letters in the alphabet
							numberOfMappings    - the amount of interations the  
																	  mapping should execute
																	  
Returned:			ciphertextCharacter
***********************************************************************/
char decodeCharacter (char ciphertextCharacter, 
											const char mappingArray[][gLettersInAlphabet], 
											int numberOfMappings) { 
	const char LETTER_A = 'A'; 			
			
	for (int i = numberOfMappings; i >= 0; i--) {
		for (int j = 0; j < gLettersInAlphabet; j++) { 
			if (mappingArray[i][j] == ciphertextCharacter) {
				ciphertextCharacter = LETTER_A + j; 
				j = gLettersInAlphabet;
			}
		}
	}		
	return ciphertextCharacter; 
}

/***********************************************************************
Function:			encodeCharacter 

Description:	Using the number of mappings and the mappingArray, this 
							function takes a plaintext character and returns a 
							ciphertext character. 

Parameters:		plaintextCharacter - the encode character 
							mappingArray       - an array that stores the mapping  
																   data and the letters in the alphabet
							numberOfMappings   - the amount of interations the  
																	 mapping should execute

Returned:			plaintextCharacter
***********************************************************************/
char encodeCharacter (char plaintextCharacter, 
											const char mappingArray[][gLettersInAlphabet], 
											int numberOfMappings) { 	
	int column; 
	const char LETTER_A = 'A'; 
	const int ASCII_A = 65;
	const int ASCII_Z = 90;
	
	if (ASCII_Z >= plaintextCharacter && ASCII_A <= plaintextCharacter) {
		for (int i = 0; i < numberOfMappings; i++) { 
			column = plaintextCharacter - LETTER_A; 
			plaintextCharacter = mappingArray[i][column]; 
		}
	}
	return plaintextCharacter; 
}
