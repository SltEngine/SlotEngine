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
	
 	ComputeGainMultiplier(true);
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

// FOR DEBUG : DISPLAY the values of the engine
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
	std::cout << "Total gain " << (int)(m_money * (m_bonus + m_globalGainMultiplier)) << std::endl;
	std::cout << std::endl << "Winning Lines :" << std::endl;
	for(int i = 0; i < (int)m_winningLines.size(); i++)
	{
		m_winningLines[i]->DebugPrint();
		std::cout << " gain = " << m_lineGains[i] << std::endl;
	}
	std::cout << "Bonus : " << m_bonus << std::endl;
	std::cout << "Free spins: " << m_freeSpins << std::endl;
}

// Update the global gain multiplier
void Engine::ComputeGainMultiplier(bool saveWinningLines)
{
	// Set up to zero at start
	m_bonus = m_freeSpins = 0;
	// Update the global gain multiplier
	m_globalGainMultiplier = 0;

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
			if(wheel == NULL)
			{
				// Free memory
				delete[] numOfOccurrences;
				std::cerr << "Error in Engine ComputeGainMultiplier, could not get correct wheel" << std::endl;
				return;
			}

			// Get Symbol id
			int symbolId = wheel->GetSymbolId((m_wheelPositions[(*cell)->x] + (*cell)->y) % Config::GetInst()->GetNumOfSymbols());
			
			// Get the symbol
			Symbol* currentSymbol = SymbolManager::GetInst()->GetSymbol(symbolId);
			if(currentSymbol == NULL)
			{
				// Free memory
				delete[] numOfOccurrences;
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
			m_globalGainMultiplier += toAdd;

			if(saveWinningLines)
			{
				// Save the line gain
				m_lineGains.push_back(toAdd);
				// Save the winning line
				m_winningLines.push_back(*line);
			}
		}
		
		// Reset num of occurrences
		std::memset(numOfOccurrences, 0, Config::GetInst()->GetNumOfSymbols()* sizeof(int));
	}

	// Set Bonus & Free Spins
	for(int k = 0; k <  Config::GetInst()->GetNumOfLines(); k++)
	{
		for(int i = 0; i < Config::GetInst()->GetNumOfWheels(); i++)
		{
			// Get Wheel
			Wheel * wheel = WheelManager::GetInst()->GetWheel(i);
			if(wheel == NULL)
			{
				std::cerr << "Error in Engine ComputeGainMultiplier, could not get correct wheel" << std::endl;
				// Free memory
				delete[] numOfOccurrences;
				return;
			}

			// Get symbol id first
			int symbolID = wheel->GetSymbolId((m_wheelPositions[i] + k) % Config::GetInst()->GetNumOfSymbols());

			// Get the symbol
			Symbol* currentSymbol = SymbolManager::GetInst()->GetSymbol(symbolID);
			if(currentSymbol == NULL)
			{
				std::cerr << "Error in ComputeGainMultiplier. Symbol not found " << symbolID << std::endl;
				// Free memory
				delete[] numOfOccurrences;
				return;
			}

			// Normal type => increment the current occurrence
			if(currentSymbol->GetType() == FREESPINS)
			{
				numberOfFS++;
				m_freeSpins = currentSymbol->GetMultiplier(numberOfFS - 1);
			}
			else if(currentSymbol->GetType() == BONUS)
			{
				numberOfBonus++;
				m_bonus = currentSymbol->GetMultiplier(numberOfBonus - 1);
			}
		}
	}

	// Free memory
	delete[] numOfOccurrences;
}

// Print the result out
void Engine::SendResult()
{
	// Write position of the wheels first
	for(int i = 0; i < Config::GetInst()->GetNumOfWheels(); i++)
	{
		Wheel * wheel = WheelManager::GetInst()->GetWheel(i);
		if(wheel == NULL)
		{
			std::cerr << "Error in Engine DebugPrint, could not get correct wheel" << std::endl;
			return;
		}
		if(i >= 1)
		{
			std::cout << ",";
		}
		std::cout << m_wheelPositions[i];
	}

	// Write multiplier
	std::cout << "|" << m_globalGainMultiplier;
	
	// Write bonus
	std::cout << "|" << m_bonus;

	// Write free spins
	std::cout << "|" << m_freeSpins;

	// Write total gain
	std::cout << "|" << (int)(m_money * (m_bonus + m_globalGainMultiplier)) << std::endl;

	// Then write winning lines + gain (one line => one winning line)
	for(int i = 0; i < (int)m_winningLines.size(); i++)
	{
		m_winningLines[i]->DebugPrint();
		std::cout << "|" << m_lineGains[i] << std::endl;
	}
}

// Print the result out explanation
void Engine::SendResultExplanation()
{
	std::cout << std::endl << "The result that you will get is organized like this : " << std::endl;
	std::cout << "<first wheel position>,<second wheel position>,....|<global multiplier>|<bonus multiplier>|<free spins>|<total gain>" << std::endl;
	std::cout << "<x,y of the first winning line> <x2,y2 of the first winning line> ... |<gain of this line>" << std::endl;
	std::cout << "<x,y of the second winning line> <x2,y2 of the first winning line> ... |<gain of this line>" << std::endl;
	std::cout << "..." << std::endl;

	std::cout << std::endl << "First wheel position is set for the first line, for exemple if a wheel has 5 as its position."
	<< "It means that its 5th symbol is at the first line, its 6th at the second line, and so on..." << std::endl;
	std::cout << "Global multiplier represents the whole result, the total gain is calculated (global multiplier * money)." << std::endl;
	std::cout << "Bonus multiplier is the bonus result." << std::endl;
	std::cout << "Free spins is the number of free spins." << std::endl;
	std::cout << "Total gain is the total amount of money that the play has won." << std::endl;
	std::cout << "x,y of a winning line represent the first coordinate of the winning line."
	<< "(0,0) is top left corner; (maxX,0) is top right corner; (0,maxY) is bottom left corner; (maxX,maxY) is bottom right corner." << std::endl;

	std::cout << std::endl << "Your current result is : " << std::endl;
}

// Get multiplier
const int& Engine::GetMultiplier()
{
	return m_globalGainMultiplier;
}

// Get multiplier
const int& Engine::GetBonus()
{
	return m_bonus;
}

// Compute RTE
float Engine::ComputeRTE()
{
	// Number of distinct wheel positions
	long int wheelPositions = 1;
	for(int i = 0; i < Config::GetInst()->GetNumOfWheels(); i++)
	{
		wheelPositions = wheelPositions * Config::GetInst()->GetNumOfSymbols();
	}
	
	// Set positions and compute result
	float totalResult = 0;
	for(long int k = 0; k < wheelPositions; k++)
	{
		int wheelPos = k;
		for(int i = 0; i < Config::GetInst()->GetNumOfWheels(); i++)
		{
			m_wheelPositions[i] = wheelPos % Config::GetInst()->GetNumOfSymbols();
			wheelPos /= Config::GetInst()->GetNumOfSymbols();
		}

		// Compute gain
		ComputeGainMultiplier();
		// Add to totalResult
		totalResult += GetMultiplier() + GetBonus();
	}

	// Return result
	return totalResult/wheelPositions;
}
