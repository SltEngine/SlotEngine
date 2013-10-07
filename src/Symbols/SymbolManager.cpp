/**
 * Symbol Manager is a singleton which has all the symbol saved
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 07/10/2013
 */

#include "SymbolManager.hpp"
#include "../Common.hpp"
#include "../Utils/Strings.hpp"

#include <fstream>
#include <stdlib.h>

// Singleton Instance set to 0 at start
SymbolManager* SymbolManager::m_instance = 0;

// Main contructor
SymbolManager::SymbolManager()
{
	// Load all the symbols
	m_loadError = !LoadSymbols();
}

// Main destructor
SymbolManager::~SymbolManager()
{
	// Delete all the lines
	for(std::map<int, Symbol*>::iterator symbol= m_symbols.begin(); symbol != m_symbols.end(); symbol++)
	{
		delete symbol->second;
	}
}

// Get the instance of the singleton
SymbolManager* SymbolManager::GetInst()
{
	// Not instancied
	if(SymbolManager::m_instance == 0)
	{
		m_instance = new SymbolManager();
	}
	
	return m_instance;
}

// Load the symbols from file
bool SymbolManager::LoadSymbols()
{
	// Open the file
	std::ifstream symbolsFile;
	symbolsFile.open(SYMBOLS_FILE, std::ios::in);
	
	// If lineShapesFile is not OK => exit
	if(!symbolsFile.is_open() || !symbolsFile.good())
	{
		return false;
	}
	
	// Each file line represent a Symbol
	// Load and instanciate each Symbol
	while(symbolsFile.good())
	{
		// Get symbols info
		std::string line;
	 	std::getline(symbolsFile, line);
		
		// Get id and type
		std::vector<char*> * idntype = SplitString(line, '|');

		// Check if result is OK
		if(idntype->size() < 1)
		{
			DeleteVector(&idntype);
			continue;
		}
		
		// Get id and type
		std::vector<char*>* idntypeSplitted = SplitString((*idntype)[0], ';');
		
		// Check if result is OK
		if(idntypeSplitted->size() != 2)
		{
			DeleteVector(&idntypeSplitted);
			DeleteVector(&idntype);
			continue;
		}

		// Get id first
		int id = atoi((*idntypeSplitted)[0]);
		SymbolType type = (SymbolType)atoi((*idntypeSplitted)[1]);
		
		// No more needed
		DeleteVector(&idntypeSplitted);
		
		// Check if symbol is already present and type is correct	
		if(m_symbols.find(id) != m_symbols.end() || type >= NUMOFSYMBOLTYPES)
		{
			DeleteVector(&idntype);
			return false;
		}
		
		// Create new Symbol
		Symbol* newSymbol = new Symbol(id, type);
		
		// If the symbol has multipliers
		if(type != WILD)
		{
			// Check if input is correct	
			if(idntype->size() != 2)
			{
				DeleteVector(&idntype);
				delete newSymbol;
				continue;
			}

			// Set symbol multiplier
			if(newSymbol->SetMultiplier((*idntype)[1]) == false)
			{	
				// Error occured during the line setting
				delete newSymbol;
				DeleteVector(&idntype);
				continue;
			}
		}

		// Save the line in the map
		m_symbols[id] = newSymbol;

		// Clean memory
		DeleteVector(&idntype);	
	}

	// Load is OK
	return true;
}

// Delete the singleton
void SymbolManager::DeleteSingleton()
{
	// If singleton is instancied
	if(m_instance != 0)
	{
		delete this;
		m_instance = 0;
	}
}

// Get the error flag
const bool& SymbolManager::GetLoadErr()
{
	return m_loadError;
}

// FOR DEBUG : DISPLAY all the symbol values
void SymbolManager::DebugPrint()
{
	std::cout << std::endl << "DISPLAYING ALL THE SYMBOL VALUES : " << std::endl << std::endl;

	// Display all the symbols
	for(std::map<int, Symbol*>::iterator symbol= m_symbols.begin(); symbol != m_symbols.end(); symbol++)
	{
		symbol->second->DebugPrint();
		std::cout << std::endl;
	}
}
