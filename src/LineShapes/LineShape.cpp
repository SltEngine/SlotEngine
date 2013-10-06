/**
 * LineShape class contains a line shape which is used
 * in order to know if the player has a winning combinaison
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include "LineShape.hpp"
#include "../Utils/Strings.hpp"
#include "../Config.hpp"

#include <stdlib.h>

// Main Constructor
LineShape::LineShape()
{
}

// Main Destructor
LineShape::~LineShape()
{
	// Delete all the cells
	for(std::vector<LineCell*>::iterator cell= m_cells.begin(); cell != m_cells.end(); cell++)
	{
		delete *cell;
	}
}

// Set the cells of the line
// Return false if input is wrong
bool LineShape::SetLineCells(std::string lineInfo)
{
	// Line already set
	if(m_cells.size() != 0)
	{
		return false;
	}
	
	// Get cell values
	std::vector<char*>* cellValues = SplitString(lineInfo, ';');
	
	// Get config pointer
	Config* config = Config::GetInst();

	// Iterate on cell values
	std::vector<char*>::iterator cellValue;
	for(cellValue = cellValues->begin(); cellValue != cellValues->end(); cellValue++)
	{
		// Split again 
		std::vector<char*>* cellInfos = SplitString(*cellValue, ',');

		// File is corrupted
		if(cellInfos->size() != 2)
		{
			DeleteVector(&cellInfos);
			DeleteVector(&cellValues);
			config->DeleteRef();
			return false;
		}

		// Get X and Y
		int x = atoi((*cellInfos)[0]);
		int y = atoi((*cellInfos)[1]);


		// Check Error with x and y values
		if(x < 0 || y < 0 || x >= config->GetNumOfWheels() || y >= config->GetNumOfLines())
		{
			DeleteVector(&cellInfos);
			DeleteVector(&cellValues);
			config->DeleteRef();
			return false;
		}

		// Save the new cell
		LineCell* newLineCell = new LineCell();
		newLineCell->x = x;
		newLineCell->y = y;
		m_cells.push_back(newLineCell);

		// Delete the vector
		DeleteVector(&cellInfos);
	}
	
	DeleteVector(&cellValues);
	return true;
}

// FOR DEBUG : DISPLAY the values of the class
void LineShape::DebugPrint()
{
	// Iterate on cell values
	for(std::vector<LineCell*>::iterator cell= m_cells.begin(); cell != m_cells.end(); cell++)
	{
		// Display cell value
		std::cout << (*cell)->x << "," << (*cell)->y << " ";
	}
	std::cout << std::endl;
}
