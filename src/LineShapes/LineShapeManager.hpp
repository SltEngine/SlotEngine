#ifndef _H_LINESHAPESMANAGER_H_
#define _H_LINESHAPESMANAGER_H_

/**
 * LineShapeManager class contains different line shapes
 * in order to know if the player has a winning combinaison
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include "LineShape.hpp"
#include "../Common.hpp"

#include <vector>
#include <iostream>

class LineShapeManager
{
private:
	// Singleton Instance
	static LineShapeManager* m_instance;
	// Number of currently used singleton ref
	int m_numOfSingletonRef;
	
	// Vector containing all the line shapes
	std::vector<LineShape*> m_lineShapes;
	
	// Error while loading of the file ?
	bool m_loadError;
	// Load line shapes from txt file
	// Returns false if load failed
	bool LoadLineShapes();
	
	// Main contructor
	LineShapeManager();
	// Main destructor
	~LineShapeManager();
public:
	// Get the instance of the singleton
	static LineShapeManager* GetInst();
	// Delete the ref of the singleton
	void DeleteRef();

	// Get the line shapes	
	const std::vector<LineShape*>& GetLineShapes();
	// Get the error flag
	const bool& GetLoadErr();

	// FOR DEBUG : DISPLAY the values of the class
	void DebugPrint();
};

#endif
