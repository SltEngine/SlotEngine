/**
 * Config singleton which contains the main 
 * configuration values of the slot machine.
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include <iostream>
#include <fstream>

#include "Config.hpp"
#include "Common.hpp"

// Singleton Instance set to 0 at start
Config* Config::m_instance = 0;

// Main contructor
Config::Config()
{
	// Load all the config variables
	m_loadError = !LoadConfig();
	// One ref is using this instance now
	m_numOfSingletonRef = 1;
}

// Main destructor
Config::~Config()
{
}

// Get the instance of the singleton
Config* Config::GetInst()
{
	// Not instancied
	if(Config::m_instance == 0)
	{
		m_instance = new Config();
	}
	else
	{	// Instancied => increased number of ref
		m_instance->m_numOfSingletonRef++;
	}
	return m_instance;
}

// Load config from txt file
// Returns false if load failed
bool Config::LoadConfig()
{
	// Open the file
	std::ifstream configFile;
	configFile.open(CONFIG_FILE, std::ios::in);
	
	// If file is wrong => exit
	if(!configFile.is_open() || !configFile.good())
	{
		return false;
	}
	
	// Get the number of lines
	configFile >> m_numberOfLines;
	if(!configFile.good())
	{
		return false;
	}
	
	// Get the number of symbols
	configFile >> m_numberOfSymbols;
	if(!configFile.good())
	{
		return false;
	}

	// Get the number of wheels
	configFile >> m_numberOfWheels;
	if(!configFile.good())
	{
		return false;
	}

	return true;
}

// Delete the ref of the singleton
void Config::DeleteRef()
{
	// Decrement the number of ref
	m_numOfSingletonRef--;
	// IF it is 0 => not used anymore => delete
	if(m_numOfSingletonRef == 0)
	{
		delete this;
		m_instance = 0;
	}
}

// Get the error flag
const bool& Config::GetLoadErr()
{
	return m_loadError;
}

// Get the number of wheels
const int& Config::GetNumOfWheels()
{
	return m_numberOfWheels;
}

// Get the number of lines
const int& Config::GetNumOfLines()
{
	return m_numberOfLines;
}

// FOR DEBUG : DISPLAY the values of the class of the config
void Config::DebugPrint()
{
	std::cout << std::endl << "DISPLAYING CONFIG VALUES : " << std::endl << std::endl;
	
	std::cout << "Singleton Instance Number : " << m_instance << std::endl;
	std::cout << "Number of currently used singletons : " << m_numOfSingletonRef << std::endl;	
	std::cout << "Number of lines in the slot machine : " << m_numberOfLines << std::endl;
	std::cout << "Number of symbols on one wheel : " << m_numberOfSymbols << std::endl;
	std::cout << "Number of wheels : " <<  m_numberOfWheels << std::endl;
	std::cout << "Load error flag : " << m_loadError << std::endl;
	
}
