#ifndef _H_SYMBOL_H_
#define _H_SYMBOL_H_

/**
 * Symbol represents a symbol on the wheel.
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

/**
 * It contains the rules, id and multiplier of the symbol
 * This is an ABSTRACT class !
 */

class Symbol
{
private:
	// Does the rule of this symbol follows lines
	bool m_ruleFollowsLines;
	// Symbol ID
	int m_id;
	// Multipliers
	int *m_multipliers;
protected:
	// Set the multiplier
	virtual void SetMultiplier() = 0;	
public:
	// Main contructor
	Symbol(int id);
	// Main destructor
	virtual ~Symbol();

	/**** Getters ****/
	const int& GetId();
	const bool& RuleIsFollowingLines();
	/**** END Getters ****/
	
};


#endif
