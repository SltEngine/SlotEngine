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

// Entry point of the slot machine engine
int main(int argc, char**argv)
{
	// Load main configuration first
	Config* config = Config::GetInst();
	if(config->GetLoadErr())
	{	
		std::cerr << "Error : Could not load " << CONFIG_FILE << "." << std::endl << "Closing application." << std::endl;
		
		// Delete the config Ref
		config->DeleteRef();

		return ERR_LOAD_FILE;
	}

	// Display for debug
	config->DebugPrint();

	// Load Line Shape Manager Then
	LineShapeManager* LSM = LineShapeManager::GetInst();
	if(LSM->GetLoadErr())
	{
		std::cerr << "Error : Could not load " << LINE_SHAPES_FILE << "." << std::endl << "Closing application." << std::endl;
		
		// Delete the LSM Ref
		LSM->DeleteRef();

		return ERR_LOAD_FILE;
	}

	return 0;
}
