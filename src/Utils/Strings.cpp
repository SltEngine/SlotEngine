/**
 * Strings file contains functions which are useful to handle strings
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 06/10/2013
 */

#include "Strings.hpp"

#include <iostream>
#include <string.h>

// Split a char* into different char* using the delimiter
std::vector<char*>* SplitString(const char* input, char delimiter)
{	
	// Output of this function
	std::vector<char*>* result = new std::vector<char*>();

	// This is where our current string begins
	int currentStringIndex = 0;
	
	// Size of the input
	int size = strlen(input);

	// Split the string
	for(int i = 0; i < size; i++)
	{
		// If there is a delimiter
		if(strncmp(input + i, &delimiter, 1) == 0)
		{
			// Size of the string
			int strSize = i - currentStringIndex;

			// If previous was a delimiter too => skip
			if(strSize == 0)
			{	
				currentStringIndex = i + 1; 
				continue;
			}
			
			// Create, fill and add the new string	
			char* newString = new char[strSize + 1];
			memcpy(newString, (char*)input + currentStringIndex, strSize);
			newString[strSize] = 0;
			result->push_back(newString);

			// Update current Index
			currentStringIndex = i + 1; 
		}
	}

	// Do not forget the last string
	if(currentStringIndex != size)
	{
		// Size of the string
		int strSize = size - currentStringIndex;
	
		// Create, fill and add the new string	
		char* newString = new char[strSize + 1];
		memcpy(newString, (char*)input + currentStringIndex, strSize);
		newString[strSize] = 0;
		result->push_back(newString);
	}

	// Return the output
	return result;
}

// Split a string into different char* using the delimiter
std::vector<char*>* SplitString(const std::string& input, char delimiter)
{	
	return SplitString(input.c_str(), delimiter);
}

// Delete vector of char*
void DeleteVector(std::vector<char*>** input)
{
	// Vector to empty and delete
	std::vector<char*>* vect = *input;

	// Delete each element
	std::vector<char*>::iterator elt;
	for(elt = vect->begin(); elt != vect->end(); elt++)
	{
		delete[] *elt;
	}

	// Delete the vector
	delete vect;
	*input = 0;
}

// Display a vector of char*
void PrintVector(std::vector<char*>* input)
{
	// Display each element
	std::vector<char*>::iterator elt;
	for(elt = input->begin(); elt != input->end(); elt++)
	{
		std::cout << *elt << std::endl;
	}
}

