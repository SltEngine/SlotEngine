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

class Symbol
{
private:
	// Does the rule of this symbol follows lines
	bool m_ruleFollowsLines;
	// Symbol ID
	int m_id;
	// Gain Multipliers
	int *m_multipliers;
public:
	// Main contructor
	Symbol(int id);
	// Main destructor
	virtual ~Symbol();

	// Set the symbol multiplier
	// Return false if input is wrong
	bool SetMultiplier(const char* info);

	/**** Getters ****/
	const int& GetId();
	const bool& RuleIsFollowingLines();
	// Returns -1 if wrong argument
	int GetMultiplier(int numOfOccurences);
	/**** END Getters ****/
	
	// FOR DEBUG : DISPLAY the values of the class
	void DebugPrint();
};

// Type of the symbol
typedef enum SymbolType
{
	NORMAL,
	FREESPINS,
	BONUS,
	WILD,
	NUMOFSYMBOLTYPES	// WARNING! Please let this value always at the end to know the number of symbol types
}SymbolType;


#endif
