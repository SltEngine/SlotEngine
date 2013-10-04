#ifndef _H_LINESHAPE_H_
#define _H_LINESHAPE_H_

/**
 * LineShape class contains a line shape which is used
 * in order to know if the player has a winning combinaison
 *
 * @author : Pascal Marechal <paskal.marechal.gmail.com>
 * 
 * @date : 04/10/2013
 */

#include <iostream>
#include <vector>

// A line is formed with several cells
typedef struct LineCell
{
	int x;
	int y;
}LineCell;

class LineShape
{
private:
	// Cells of this line
	std::vector<LineCell*> m_cells;
public:
	// Main Constructor
	LineShape();
	// Main Destructor
	~LineShape();
	// Set the cells of the line
	// Return false if input is wrong
	bool SetLineCells(std::string lineInfo);
};

#endif
