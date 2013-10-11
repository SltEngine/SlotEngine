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
#include <string.h>

#include "Config.hpp"
#include "Common.hpp"
#include "LineShapes/LineShapeManager.hpp"
#include "Symbols/SymbolManager.hpp"
#include "Wheels/WheelManager.hpp"
#include "Engine.hpp"

// Trace enabled ?
static bool g_trace = false;
// RTE enabled ?
static bool g_rte = false;
// Variable enabled ?
static bool g_var = false;

// Display instruction if args are wrong
void DisplayInfos(char* progName)
{
	std::cout << "To use this program please use " << progName << " <money> <flags> or " << progName << " <flags> <money>" << std::endl;
	std::cout << "Money should be a positive number !" << std::endl;
	std::cout << "Flags : " << std::endl << " no flags : it display standart output which can be used in the php page." << std::endl;
	std::cout << "-t : to display trace (Warning !! You cannot use this for your php page)." << std::endl;
	std::cout << "-rte : to display rte of your setup (Warning !! You cannot use this for your php page)." << std::endl;
	std::cout << "-v : to display variance of your setup (Warning !! You cannot use this for your php page)." << std::endl;
}

// Entry point of the slot machine engine
int main(int argc, char**argv)
{	
	// Money input
	int money = 0;

	// Check argc and set flags
	if(argc <= 1)
	{
		DisplayInfos(argv[0]);
		return 0;
	}
	else
	{
		// Check for flag and money input
		for(int i = 1; i < argc; i++)
		{
			// Flag input
			if(argv[i][0] == '-')
			{	
				// Trace enabled
				if(strncmp(argv[i], "-t", 2) == 0)
				{
					g_trace = true;
				}
				// RTE enabled
				else if(strncmp(argv[i], "-rte", 4) == 0)
				{
					g_rte = true;
				}
				// Variance enabled
				else if(strncmp(argv[i], "-v", 2) == 0)
				{
					g_var = true;
				}
			}
			// Money input
			else
			{
				money = atoi(argv[i]);
			}
		}
	}

	// Check money value
	if(money <= 0)
	{
		DisplayInfos(argv[0]);
		return 0;
	}

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
	if(g_trace)
	{
		config->DebugPrint();
	}

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
	if(g_trace)
	{
		LSM->DebugPrint();
	}

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
	if(g_trace)
	{
		SM->DebugPrint();
	}

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
	if(g_trace)
	{
		WM->DebugPrint();
	}

	// Compute the output now
	Engine* engine = new Engine(money);
	
	// Display for debug
	if(g_trace)
	{
		engine->DebugPrint();
		engine->SendResultExplanation();
	}
	
	// Display the output for php page
	engine->SendResult();
	
	// Display RTE
	if(g_var)
	{
		std::cout << "Computing RTE..." << std::endl;
		float rte = engine->ComputeRTE();
		std::cout << "RTE = " << rte << std::endl;
		std::cout << "Computing Variance..." << std::endl;
		std::cout << "Variance = " << engine->ComputeVariance(rte) << std::endl;
	}
	else if(g_rte)
	{	
		std::cout << "Computing RTE..." << std::endl;
		std::cout << "RTE = " << engine->ComputeRTE() << std::endl;
	}	
	
	// Delete all Singletons at the end of the main
	config->DeleteSingleton();
	LSM->DeleteSingleton();
	SM->DeleteSingleton();
	WM->DeleteSingleton();

	// Clean memory
	delete engine;
	return 0;
}
