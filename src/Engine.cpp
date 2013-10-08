/**
 * Engine contains the engine class which is used to compute the final result
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 08/10/2013
 */

#include "Engine.hpp"
#include "Config.hpp"
#include "LineShapes/LineShapeManager.hpp"
#include "Symbols/SymbolManager.hpp"
#include "Wheels/WheelManager.hpp"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cstring>

// Main constructor
Engine::Engine(int moneyInput)
{
	m_money = moneyInput;
	m_wheelPositions = new int[Config::GetInst()->GetNumOfWheels()];
	SetWheelPositions();

	// Update the global gain multiplier
	m_globalGainMultiplier = 0;
 	ComputeGainMultiplier();
}

// Main destructor
Engine::~Engine()
{
	delete[] m_wheelPositions;
}

// Set the wheel positions randomly
void Engine::SetWheelPositions()
{
	for(int i = 0; i < Config::GetInst()->GetNumOfWheels(); i++)
	{
		m_wheelPositions[i] = std::rand() % Config::GetInst()->GetNumOfSymbols();
	}
}

// FOR DEBUG : DISPLAY the values of the class of the config
void Engine::DebugPrint()
{
	std::cout << std::endl << "ENGINE OUTPUTS " << std::endl << std::endl;
	std::cout << "Wheel positions :" << std::endl;
	for(int k = 0; k <  Config::GetInst()->GetNumOfLines(); k++)
	{
		for(int i = 0; i < Config::GetInst()->GetNumOfWheels(); i++)
		{
			Wheel * wheel = WheelManager::GetInst()->GetWheel(i);
			if(wheel == NULL)
			{
				std::cerr << "Error in Engine DebugPrint, could not get correct wheel" << std::endl;
				return;
			}
			std::cout << wheel->GetSymbolId((m_wheelPositions[i] + k) % Config::GetInst()->GetNumOfSymbols()) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "Gain multiplier " << m_globalGainMultiplier << std::endl;
	std::cout << "Total gain " << (int)(m_money * m_globalGainMultiplier) << std::endl;
	std::cout << std::endl << "Winning Lines :" << std::endl;
	for(int i = 0; i < m_winningLines.size(); i++)
	{
		m_winningLines[i]->DebugPrint();
		std::cout << "Line gain = " << m_lineGains[i] << std::endl;
	}
}

// Update the global gain multiplier
void Engine::ComputeGainMultiplier()
{
	// First get the line shape manager
	LineShapeManager* LSM = LineShapeManager::GetInst();

	// Get all the lines
	std::vector<LineShape*> lines = LSM->GetLineShapes();

	// Array to save the number of occurrences of each symbol in a line
	int* numOfOccurrences = new int[Config::GetInst()->GetNumOfSymbols()];
	std::memset(numOfOccurrences, 0, Config::GetInst()->GetNumOfSymbols()* sizeof(int));
	
	// Save the number of bonus
	int numberOfBonus = 0;
	// Save the number of free spins
	int numberOfFS = 0;

	// Check each line	
	std::vector<LineShape*>::iterator line;
	for(line = lines.begin(); line != lines.end(); line++)
	{	
		// Get line cells first
		std::vector<LineCell*>& lineCells = (*line)->GetLineCells();
		std::vector<LineCell*>::iterator cell;

		// Set num of occurrences
		for(cell = lineCells.begin(); cell != lineCells.end(); cell++)
		{	
			// Get Wheel
			Wheel * wheel = WheelManager::GetInst()->GetWheel((*cell)->x);
			// Get Symbol id
			int symbolId = wheel->GetSymbolId((m_wheelPositions[(*cell)->x] + (*cell)->y) % Config::GetInst()->GetNumOfSymbols());
			
			// Get the symbol
			Symbol* currentSymbol = SymbolManager::GetInst()->GetSymbol(symbolId);
			if(currentSymbol == NULL)
			{
				std::cerr << "Error in ComputeGainMultiplier. Symbol not found " << symbolId << std::endl;
				return;
			}

			// Normal type => increment the current occurrence
			if(currentSymbol->GetType() == NORMAL)
			{
				numOfOccurrences[symbolId]++;
			}
			// If it is WILD increment all symbol occurrences
			else if(currentSymbol->GetType() == WILD)
			{
				for(int i = 0; i < Config::GetInst()->GetNumOfSymbols(); i++)
				{
					numOfOccurrences[i]++;
				}
			}
		}
		
		// To add to multiplier
		int toAdd = 0;

		// Check if it is a winning line
		for(int i = 0; i < Config::GetInst()->GetNumOfSymbols(); i++)
		{	
			// Check if there is something to add
			if(numOfOccurrences[i] > 1 &&
			SymbolManager::GetInst()->GetSymbol(i) != NULL &&
			SymbolManager::GetInst()->GetSymbol(i)->GetType() == NORMAL)
			{
				toAdd += SymbolManager::GetInst()->GetSymbol(i)->GetMultiplier(numOfOccurrences[i] - 1);
			}
		}

		// If this is a winning line
		if(toAdd)
		{
			// Save the winning line
			m_winningLines.push_back(*line);
			m_globalGainMultiplier += toAdd;
			// Save the line gain
			m_lineGains.push_back(toAdd);
		}
		
		// Reset num of occurrences
		std::memset(numOfOccurrences, 0, Config::GetInst()->GetNumOfSymbols()* sizeof(int));
	}
}
