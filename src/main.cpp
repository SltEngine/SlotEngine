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

// Entry point of the slot machine engine
int main(int argc, char**argv)
{
	// Load main configuration first
	Config* config = Config::GetInst();
	if(config->GetLoadErr())
	{	
		std::cerr << "Error : Could not load " << CONFIG_FILE << "." << std::endl << "Closing application." << std::endl;
		return ERR_LOAD_FILE;
	}

	// Display for debug
	config->DebugPrint();

	return 0;
}
