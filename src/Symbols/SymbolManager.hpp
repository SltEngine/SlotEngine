#ifndef _H_SYMBOLMANAGER_H_
#define _H_SYMBOLMANAGER_H_

/**
 * Symbol Manager is a singleton which has all the symbol saved
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 07/10/2013
 */

#include "Symbol.hpp"

#include <map>

class SymbolManager
{
private:
	// Singleton Instance
	static SymbolManager* m_instance;
	// Map of symbol
	std::map<int, Symbol*> m_symbols;

	// Main contructor
	SymbolManager();
	// Main destructor
	~SymbolManager();

	// Load the symbols from file
	bool LoadSymbols();
	// Error during load ?
	bool m_loadError;
public:
	// Get the instance of the singleton
	static SymbolManager* GetInst();
	// Delete the singleton
	void DeleteSingleton();

	// Get the error flag
	const bool& GetLoadErr();

	// FOR DEBUG : DISPLAY all the symbol values
	void DebugPrint();
};


#endif

