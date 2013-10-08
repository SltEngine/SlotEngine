#ifndef _H_SYMBOL_H_
#define _H_SYMBOL_H_

/**
 * Symbol represents a symbol on the wheel.
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include <iostream>

// Type of the symbol
typedef enum SymbolType
{
	NORMAL,
	FREESPINS,
	BONUS,
	WILD,
	NUMOFSYMBOLTYPES	// WARNING! Please let this value always at the end to know the number of symbol types
}SymbolType;

class Symbol
{
private:
	// Symbol ID
	int m_id;
	// Gain Multipliers
	int *m_multipliers;
	// Symbol type
	SymbolType m_type;
public:
	// Main contructor
	Symbol(int id, SymbolType type);
	// Main destructor
	virtual ~Symbol();

	// Set the symbol multiplier
	// Return false if input is wrong
	bool SetMultiplier(const char* info);

	/**** Getters ****/
	const int& GetId();
	const SymbolType& GetType();
	// Returns -1 if wrong argument
	int GetMultiplier(int numOfOccurrences);
	/**** END Getters ****/
	
	// FOR DEBUG : DISPLAY the values of the class
	void DebugPrint();
};

#endif
