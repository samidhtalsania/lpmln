#include "Domain.h"
#include "LanguageConstants.h"
#include "Config.h"
#include <algorithm>

Domain::Domain()
{
}

Domain::~Domain()
{
}

/*
source = true : Request comes from toString method of Variables
source = false : Request comes from toString method of Parser
*/
std::string Domain::toString(bool source) const{
	if(!source){
		std::string str;
		str += domainVar;
		str += LanguageConstants::OBJ_EQUALS;
		str += LanguageConstants::OBJ_PAREN_OPEN;

		for(auto it=vars.begin();it!= vars.end();++it){
			std::string tempStr = *it;
			if (LanguageConstants::TYPE == OutputType::OUTPUT_ASP){
				Util::toLower(tempStr);
			}
			str += tempStr;
			str += LanguageConstants::OBJ_SEP;
		}
		str = str.substr(0,str.size()-1);
		str += LanguageConstants::OBJ_PAREN_CLOSE;
		str += LanguageConstants::OBJ_LINE_END;
		str += "\n";
		return str;
	}
	else{
		return domainVar;
	}
}