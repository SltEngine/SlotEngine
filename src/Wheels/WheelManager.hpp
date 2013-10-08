#ifndef _H_WHEELMANAGER_H_
#define _H_WHEELMANAGER_H_

/**
 * Wheel Manager is a singleton which has all the wheel saved
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 07/10/2013
 */

#include "Wheel.hpp"

#include <vector>

class WheelManager
{
private:
	// Singleton Instance
	static WheelManager* m_instance;
	// vector containing all the wheels
	std::vector<Wheel*> m_wheels;

	// Main contructor
	WheelManager();
	// Main destructor
	~WheelManager();

	// Load the wheels from file
	bool LoadWheels();
	// Error during load ?
	bool m_loadError;
public:
	// Get the instance of the singleton
	static WheelManager* GetInst();
	// Delete the singleton
	void DeleteSingleton();

	// Get the error flag
	const bool& GetLoadErr();
	// Get a wheel with its position
	// Return NULL is position is wrong
	Wheel* GetWheel(int position);
	// FOR DEBUG : DISPLAY all the wheel values
	void DebugPrint();
};


#endif

