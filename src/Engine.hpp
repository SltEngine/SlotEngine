#ifndef _H_ENGINE_H_
#define _H_ENGINE_H_

/**
 * Engine contains the engine class which is used to compute the final result
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 08/10/2013
 */

#include <vector>

#include "LineShapes/LineShape.hpp"

class Engine
{
private:
	// Money that the player played
	int m_money;
	// Wheel positions
	// The position represent the top symbol of the wheel
	// If position is 5 for exemple it means that the symbol 
	// which is at the position 5 on the wheel is at the first line
	int* m_wheelPositions;
	// Global gain multiplier
	int m_globalGainMultiplier;
	// Winning Line Shapes
	std::vector<LineShape*> m_winningLines;
	// Winning Line Gains
	std::vector<int> m_lineGains;
	// Bonus
	int m_bonus;
	// Free spins
	int m_freeSpins;

	// Set the wheel positions randomly
	void SetWheelPositions();
public:
	// Main constructor
	Engine(int moneyInput);
	// Main destructor
	~Engine();

	// FOR DEBUG : DISPLAY the values of the engine
	void DebugPrint();
	// Print the result out
	void SendResult();
	// Print the result out explanation
	void SendResultExplanation();
	// Update the global gain multiplier
	void ComputeGainMultiplier(bool saveWinningLines = false);

	// Get multiplier
	const int& GetMultiplier();
	// Get multiplier
	const int& GetBonus();
	
	// Compute RTE
	float ComputeRTE();
	
	// Compute Variance
	float ComputeVariance(float average);
};


#endif

