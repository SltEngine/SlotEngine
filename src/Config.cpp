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

// Singleton Instance
Config* Config::m_instance = 0;

// Main contructor
Config::Config()
{
	// Load all the config variables
	LoadConfig();
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
void Config::LoadConfig()
{
	std::ifstream configFile;
	configFile.open(CONFIG_FILE, std::ios::in);
	
	if(!configFile.is_open() || !configFile.good())
	{
		m_loadError = true;
		return;
	}
	
	configFile >> m_numberOfLines;
	if(!configFile.good())
	{
		m_loadError = true;
		return;
	}

	configFile >> m_numberOfSymbols;
	if(!configFile.good())
	{
		m_loadError = true;
		return;
	}

	configFile >> m_numberOfWheels;
	if(!configFile.good())
	{
		m_loadError = true;
		return;
	}

	m_loadError = false;
}

// Delete the ref of the singleton
void Config::DeleteRef()
{
	m_numOfSingletonRef--;
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

// FOR DEBUG : DISPLAY the values of the class of the config
void Config::DebugPrint()
{
	std::cout << "Singleton Instance Number : " << m_instance << std::endl;
	std::cout << "Number of currently used singletons : " << m_numOfSingletonRef << std::endl;	
	std::cout << "Number of lines in the slot machine : " << m_numberOfLines << std::endl;
	std::cout << "Number of symbols on one wheel : " << m_numberOfSymbols << std::endl;
	std::cout << "Number of wheels : " <<  m_numberOfWheels << std::endl;
	std::cout << "Load error flag : " << m_loadError << std::endl;
	
}
