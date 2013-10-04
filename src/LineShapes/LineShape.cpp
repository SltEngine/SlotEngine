/**
 * LineShape class contains a line shape which is used
 * in order to know if the player has a winning combinaison
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include "LineShape.hpp"

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

	
	return true;
}
