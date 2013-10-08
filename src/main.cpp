/**
 * Main file for the slot machine engine
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sys/time.h>

#include "Config.hpp"
#include "Common.hpp"
#include "LineShapes/LineShapeManager.hpp"
#include "Symbols/SymbolManager.hpp"
#include "Wheels/WheelManager.hpp"
#include "Engine.hpp"

// Entry point of the slot machine engine
int main(int argc, char**argv)
{	
	// Reset the random seed at start
	// Take the time in µsec in order to get different result all the time
	timeval tv;
	gettimeofday(&tv, NULL);
	std::srand(tv.tv_sec * 1000000 + tv.tv_usec);

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

	// Load Wheel Manager
	WheelManager* WM = WheelManager::GetInst();
	if(WM->GetLoadErr())
	{
		std::cerr << std::endl << "Error while loading " << WHEELS_FILE << "." << std::endl << "Closing application." << std::endl;
		
		// Delete the WM Singleton
		WM->DeleteSingleton();

		// Delete the SM Singleton
		SM->DeleteSingleton();

		// Delete the LSM Singleton
		LSM->DeleteSingleton();

		// Delete the config Singleton
		config->DeleteSingleton();
		
		return ERR_LOAD_FILE;
	}
	
	// Display for debug
	WM->DebugPrint();

	// Compute the output now
	Engine* engine = new Engine(100);
	
	// Display for debug
	engine->DebugPrint();

	// Delete all Singletons at the end of the main
	config->DeleteSingleton();
	LSM->DeleteSingleton();
	SM->DeleteSingleton();
	WM->DeleteSingleton();

	// Clean memory
	delete engine;
	return 0;
}
