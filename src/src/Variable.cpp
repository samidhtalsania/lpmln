#include "Variable.h"

Variable::Variable()
{
}

Variable::~Variable()
{
}

std::string Variable::toString() const{
	std::string str;
	str += var;
	
	/*If singleton variable just return appended str*/
	if(pos.size() == 0) return str;

	str += "(";
	for(auto it = pos.begin();it!=pos.end();++it){
		str += it->second.toString(true);
		str += ",";
	}
	str = str.substr(0,str.size()-1);
	str += ")\n";
	return str;
}