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
	int* m_wheelPositions;
	// Global gain multiplier
	int m_globalGainMultiplier;
	// Winning Line Shapes
	std::vector<LineShape*> m_winningLines;
	// Winning Line Gains
	std::vector<int> m_lineGains;

	// Set the wheel positions randomly
	void SetWheelPositions();
	// Update the global gain multiplier
	void ComputeGainMultiplier();
public:
	// Main constructor
	Engine(int moneyInput);
	// Main destructor
	~Engine();

	// FOR DEBUG : DISPLAY the values of the class of the config
	void DebugPrint();
};


#endif

