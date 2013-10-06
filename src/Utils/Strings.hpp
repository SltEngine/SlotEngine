/**
 * Strings file contains functions which are useful to handle strings
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 06/10/2013
 */

#ifndef _H_STRINGS_H_
#define _H_STRINGS_H_

#include <vector>
#include <iostream>

// Split a char* into different char* using the delimiter
std::vector<char*>* SplitString(const char* input, char delimiter);
// Split a string into different char* using the delimiter
std::vector<char*>* SplitString(const std::string& input, char delimiter);
// Delete a vector of char*
void DeleteVector(std::vector<char*>** input);
// Display a vector of char*
void PrintVector(std::vector<char*>* input);

#endif
