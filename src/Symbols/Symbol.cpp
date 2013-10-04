#include "Symbol.hpp"

// Main contructor
Symbol::Symbol(int id)
{
	this->m_id = id;
	this->m_multipliers = 0;
}

// Main destructor
Symbol::~Symbol()
{
	delete[] m_multipliers;
}

/**** Getters ****/
const int& Symbol::GetId()
{
	return this->m_id;
}

const bool& Symbol::RuleIsFollowingLines()
{
	return this->m_ruleFollowsLines;
}

/**** END Getters ****/
