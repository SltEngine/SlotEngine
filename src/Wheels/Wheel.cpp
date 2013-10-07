/**
 * A wheel of the slot machine
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 07/10/2013
 */

#include "Wheel.hpp"
#include "../Config.hpp"
#include "../Utils/Strings.hpp"
#include "../Symbols/SymbolManager.hpp"

#include <stdlib.h>

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
bool Wheel::SetSymbols(std::string info)
{	
	// Get Wheel symbols ids
	std::vector<char*>* symbolsIds = SplitString(info, ',');
	
	// Check if there are enough args
	if(symbolsIds->size() != Config::GetInst()->GetNumOfSymbols())
	{
		DeleteVector(&symbolsIds);
		return false;
	}
	
	// Fill wheel with symbol ids
	for(int i = 0; i < symbolsIds->size(); i++)
	{
		// Get the symbol value
		int value = atoi((*symbolsIds)[i]);

		// Check value with existing Symbol
		if(SymbolManager::GetInst()->GetSymbol(value) == NULL)
		{
			std::cerr << "Symbol " << value << " not found in the symbol manager." << std::endl;
			DeleteVector(&symbolsIds);
			return false;
		}

		// Save the symbol value
		m_symbols[i] = value;
	}
	
	// Free memory
	DeleteVector(&symbolsIds);

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
	// Display symbol ids of the wheel
	for(int i = 0; i < Config::GetInst()->GetNumOfSymbols(); i++)
	{
		std::cout << m_symbols[i] << " ";
	}
}
