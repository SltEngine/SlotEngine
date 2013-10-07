#ifndef _H_WHEEL_H_
#define _H_WHEEL_H_

/**
 * A wheel of the slot machine
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 07/10/2013
 */

#include <iostream>

class Wheel
{
private:
	// Symbols on the wheel
	int *m_symbols;
public:
	// Main contructor
	Wheel();
	// Main destructor
	virtual ~Wheel();

	// Set symbols on the wheel
	// Return false if input is wrong
	bool SetSymbols(std::string info);

	/**** Getters ****/
	// Returns -1 if wrong argument
	int GetSymbolId(int position);
	/**** END Getters ****/
	
	// FOR DEBUG : DISPLAY the values of the class
	void DebugPrint();
};

#endif
