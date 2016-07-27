#include <string>
#include "FactCompletion.h"

FactCompletion::~FactCompletion()
{
}

FactCompletion::FactCompletion()
{
}

bool FactCompletion::operator<(const FactCompletion& rhs) const
{
	std::string tokenStringLhs;
	std::string tokenStringRhs;
	
	for(unsigned int i=0;i<rhs.getHead().getTokens().size();i++)
		tokenStringRhs.append(rhs.getHead().getTokens().at(i));
		
	for(unsigned int i=0;i<this->getHead().getTokens().size();i++)
		tokenStringLhs.append(this->getHead().getTokens().at(i));
		
	return tokenStringLhs<tokenStringRhs;
	
	
}

bool FactCompletion::operator==(const FactCompletion& rhs) const
{
	std::string tokenStringLhs;
	std::string tokenStringRhs;
	
	for(unsigned int i=0;i<rhs.getHead().getTokens().size();i++)
		tokenStringRhs.append(rhs.getHead().getTokens().at(i));
		
	for(unsigned int i=0;i<this->getHead().getTokens().size();i++)
		tokenStringLhs.append(this->getHead().getTokens().at(i));
		
	return tokenStringLhs==tokenStringRhs;
}

