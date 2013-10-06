/**
 * LineShapeManager class contains different line shapes
 * in order to know if the player has a winning combinaison
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include "LineShapeManager.hpp"

#include <iostream>
#include <fstream>

// Singleton Instance set to 0 at start
LineShapeManager* LineShapeManager::m_instance = 0;

// Main contructor
LineShapeManager::LineShapeManager()
{
	// Load all the config variables
	m_loadError = !LoadLineShapes();
	// One ref is using this instance now
	m_numOfSingletonRef = 1;
}

// Main destructor
LineShapeManager::~LineShapeManager()
{
	// Delete all the lines
	for(std::vector<LineShape*>::iterator line= m_lineShapes.begin(); line != m_lineShapes.end(); line++)
	{
		delete *line;
	}
}

// Get the instance of the singleton
LineShapeManager* LineShapeManager::GetInst()
{
	// Not instancied
	if(LineShapeManager::m_instance == 0)
	{
		m_instance = new LineShapeManager();
	}
	else
	{	// Instancied => increased number of ref
		m_instance->m_numOfSingletonRef++;
	}
	return m_instance;
}

// Load line shapes from txt file
// Returns false if load failed
bool LineShapeManager::LoadLineShapes()
{
	// Open the file
	std::ifstream lineShapesFile;
	lineShapesFile.open(LINE_SHAPES_FILE, std::ios::in);
	
	// If lineShapesFile is not OK => exit
	if(!lineShapesFile.is_open() || !lineShapesFile.good())
	{
		return false;
	}
	
	// Each file line represent a Line Shape
	// Load and instanciate each shape
	while(lineShapesFile.good())
	{
		// Get Line shape info
		std::string line;
	 	std::getline(lineShapesFile, line);
		
		// Create new line shape
		LineShape* newLineShape = new LineShape();
		
		// Set cells of the shape
		if(newLineShape->SetLineCells(line) == false)
		{	
			// Error occured during the line setting
			delete newLineShape;
			return false;
		}

		// Save the line in the vector
		m_lineShapes.push_back(newLineShape);	
	}

	// Load is OK
	return true;
}

// Delete the ref of the singleton
void LineShapeManager::DeleteRef()
{
	// Decrement number of ref
	m_numOfSingletonRef--;
	// If ref is 0 => not used anymore => delete
	if(m_numOfSingletonRef == 0)
	{
		delete this;
		m_instance = 0;
	}
}

// Get the line shapes	
const std::vector<LineShape*>& LineShapeManager::GetLineShapes()
{
	return m_lineShapes;
}

// Get the error flag
const bool& LineShapeManager::GetLoadErr()
{
	return m_loadError;
}

// FOR DEBUG : DISPLAY the values of the class
void LineShapeManager::DebugPrint()
{
	std::cout << std::endl << "DISPLAYING ALL THE LINES VALUES : " << std::endl << std::endl;

	// Display all the lines
	for(std::vector<LineShape*>::iterator line= m_lineShapes.begin(); line != m_lineShapes.end(); line++)
	{
		(*line)->DebugPrint();
	}
}
