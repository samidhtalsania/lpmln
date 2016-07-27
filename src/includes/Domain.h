#pragma once
#include <vector>
#include <string>

class Domain
{
public:
	Domain(std::string str): domainVar(str){}
	Domain();
	~Domain();
	
	void setVars(std::vector<std::string> domainVariables){
		vars = domainVariables;
	}

	void setVars(std::vector<std::string*> domainVariables){
		for(auto& v: domainVariables)
			vars.push_back(*v);

		// vars = domainVariables;
	}

	void addVars(std::string str){
		vars.push_back(str);
	}
	
	std::vector<std::string> getVars(){
		return vars;
	}
	
	void setDomainVar(std::string* domainVariable){
		domainVar = *domainVariable;
	}
	
	std::string getDomainVar() const{
		return domainVar;
	}
	
	bool operator< (const Domain& right) const{
		return domainVar < right.getDomainVar();
	}
	
	bool operator== (const Domain& right) const{
		return domainVar == right.getDomainVar();
	}

/*
source = true : Request comes from toString method of Variables
source = false : Request comes from toString method of Parser
*/
	std::string toString(bool source) const{
		if(!source){
			std::string str;
			str += domainVar;
			str += "=";
			str += "{";

			for(auto it=vars.begin();it!= vars.end();++it){
				str += *it;
				str += ",";
			}
			str = str.substr(0,str.size()-1);
			str += "}\n";
			return str;
		}
		else{
			return domainVar;
		}
	}
	
private :
	std::vector<std::string> vars;
	std::string domainVar;

};	

