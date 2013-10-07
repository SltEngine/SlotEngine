/**
 * Wheel Manager is a singleton which has all the wheel saved
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 07/10/2013
 */

#include "WheelManager.hpp"
#include "../Common.hpp"
#include "../Utils/Strings.hpp"

#include <fstream>
#include <stdlib.h>

// Singleton Instance set to 0 at start
WheelManager* WheelManager::m_instance = 0;

// Main contructor
WheelManager::WheelManager()
{
	// Load all the wheels
	m_loadError = !LoadWheels();
}

// Main destructor
WheelManager::~WheelManager()
{
	// Delete all the lines
	for(std::vector<Wheel*>::iterator wheel= m_wheels.begin(); wheel != m_wheels.end(); wheel++)
	{
		delete *wheel;
	}
}

// Get the instance of the singleton
WheelManager* WheelManager::GetInst()
{
	// Not instancied
	if(WheelManager::m_instance == 0)
	{
		m_instance = new WheelManager();
	}
	
	return m_instance;
}

// Load the wheels from file
bool WheelManager::LoadWheels()
{
	// Open the file
	std::ifstream wheelsFile;
	wheelsFile.open(WHEELS_FILE, std::ios::in);
	
	// If wheelsFile is not OK => exit
	if(!wheelsFile.is_open() || !wheelsFile.good())
	{
		return false;
	}
	
	// Each file line represent a Wheel
	// Load and instanciate each Wheel
	while(wheelsFile.good())
	{
		// Get wheels info
		std::string line;
	 	std::getline(wheelsFile, line);
	
	}

	// Load is OK
	return true;
}

// Delete the singleton
void WheelManager::DeleteSingleton()
{
	// If singleton is instancied
	if(m_instance != 0)
	{
		delete this;
		m_instance = 0;
	}
}

// Get the error flag
const bool& WheelManager::GetLoadErr()
{
	return m_loadError;
}

// FOR DEBUG : DISPLAY all the wheel values
void WheelManager::DebugPrint()
{
	std::cout << std::endl << "DISPLAYING ALL THE WHEEL VALUES : " << std::endl << std::endl;

	// Display all the wheels
	for(std::vector<Wheel*>::iterator wheel= m_wheels.begin(); wheel != m_wheels.end(); wheel++)
	{
		(*wheel)->DebugPrint();
		std::cout << std::endl;
	}
}
