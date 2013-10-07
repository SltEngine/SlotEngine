/**
 * Symbol represents a symbol on the wheel.
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include "Symbol.hpp"
#include "../Config.hpp"
#include "../Utils/Strings.hpp"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Main contructor
Symbol::Symbol(int id, SymbolType type)
{
	// Instanciate multipliers and set to zero
	m_multipliers = new int[Config::GetInst()->GetNumOfWheels()];
	memset(m_multipliers, 0, Config::GetInst()->GetNumOfWheels()*sizeof(int));
	// Id of the symbol
	m_id = id;
	// Set the type
	m_type = type;
}

// Main destructor
Symbol::~Symbol()
{
	delete[] m_multipliers;
}

// Set the symbol information
// Return false if input is wrong
bool Symbol::SetMultiplier(const char* info)
{	
	// Get cell values
	std::vector<char*>* multipliers = SplitString(info, ';');
	
	// Get config pointer
	Config* config = Config::GetInst();
	
	// The number of cell is wrong => error
	if(config->GetNumOfWheels() != multipliers->size())
	{
		DeleteVector(&multipliers);
	}
	
	// Save multiplier values
	for(int i = 0; i< multipliers->size(); i++)
	{
		m_multipliers[i] = atoi((*multipliers)[i]);
	}
	
	DeleteVector(&multipliers);
	return true;
}

// FOR DEBUG : DISPLAY the values of the class
void Symbol::DebugPrint()
{
	// Display id
	std::cout << "Id = " << m_id << std::endl;
	// Display type
	std::cout << "Type = " << m_type << std::endl;
	// Multipliers
	std::cout << "Multipliers = ";
	// Iterate on multiplier values
	for(int i = 0; i < Config::GetInst()->GetNumOfWheels(); i++)
	{
		// Display multiplier value
		std::cout << m_multipliers[i] << " ";
	}
	std::cout << std::endl;
}

/**** Getters ****/
const int& Symbol::GetId()
{
	return m_id;
}

const SymbolType& Symbol::GetType()
{
	return m_type;
}

// Returns -1 if wrong argument
int Symbol::GetMultiplier(int numOfOccurences)
{
	// Error in argument
	if(numOfOccurences >= Config::GetInst()->GetNumOfWheels())
	{
		return -1;
	}
	return m_multipliers[numOfOccurences];
}

/**** END Getters ****/
