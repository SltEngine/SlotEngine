/**
 * A wheel of the slot machine
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 07/10/2013
 */

#include "Wheel.hpp"
#include "../Config.hpp"

// Main contructor
Wheel::Wheel()
{
	m_symbols = new int[Config::GetInst()->GetNumOfSymbols()];
}

// Main destructor
Wheel::~Wheel()
{
	delete[] m_symbols;
}

// Set symbols on the wheel
// Return false if input is wrong
bool Wheel::SetSymbols(const char* info)
{
	return true;
}

// Returns -1 if wrong argument
int Wheel::GetSymbolId(int position)
{
	if(position < 0 || position >= Config::GetInst()->GetNumOfSymbols())
	{
		return -1;
	}

	return m_symbols[position];
}
	
// FOR DEBUG : DISPLAY the values of the class
void Wheel::DebugPrint()
{
}
