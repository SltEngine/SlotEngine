/**
 * Main file for the slot machine engine
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include <iostream>

#include "Config.hpp"
#include "Common.hpp"
#include "LineShapes/LineShapeManager.hpp"
#include "Symbols/SymbolManager.hpp"

// Entry point of the slot machine engine
int main(int argc, char**argv)
{
	// Load main configuration first
	Config* config = Config::GetInst();
	if(config->GetLoadErr())
	{	
		std::cerr << std::endl << "Error while loading " << CONFIG_FILE << "." << std::endl << "Closing application." << std::endl;
		
		// Delete the config Singleton
		config->DeleteSingleton();

		return ERR_LOAD_FILE;
	}

	// Display for debug
	config->DebugPrint();

	// Load Line Shape Manager Then
	LineShapeManager* LSM = LineShapeManager::GetInst();
	if(LSM->GetLoadErr())
	{
		std::cerr << std::endl << "Error while loading " << LINE_SHAPES_FILE << "." << std::endl << "Closing application." << std::endl;
		
		// Delete the LSM Singleton
		LSM->DeleteSingleton();

		// Delete the config Singleton
		config->DeleteSingleton();

		return ERR_LOAD_FILE;
	}

	// Display for debug
	LSM->DebugPrint();

	// Load Symbol Manager
	SymbolManager* SM = SymbolManager::GetInst();
	if(SM->GetLoadErr())
	{
		std::cerr << std::endl << "Error while loading " << SYMBOLS_FILE << "." << std::endl << "Closing application." << std::endl;
		
		// Delete the SM Singleton
		SM->DeleteSingleton();

		// Delete the LSM Singleton
		LSM->DeleteSingleton();

		// Delete the config Singleton
		config->DeleteSingleton();

		return ERR_LOAD_FILE;
	}

	// Display for debug
	SM->DebugPrint();

	// Delete all Singletons at the end of the main
	config->DeleteSingleton();
	LSM->DeleteSingleton();
	SM->DeleteSingleton();
	
	return 0;
}
