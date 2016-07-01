#include <set>
#include "Predicate.h"

class Body
{
public:
	Body();
	~Body();
	Body(std::vector<Predicate> _predList):predList(_predList){}

	void addPredicate(Predicate p){
		predList.push_back(p);
	}

	std::string toString() const{
		return bodyStr;
	}

	void appendStr(std::string str, bool trim, bool disjunction, bool conjunction){

		if(disjunction){
			bodyStr += " v ";
		}
		else if(conjunction){
			bodyStr += " ^ ";
		}

		bodyStr += str;
		
		if(trim){
			bodyStr = bodyStr.substr(0,bodyStr.size()-3); 
		}
	}



	std::vector<Predicate> getPredicate(){ return predList; } 

private:
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList;
	
	std::string bodyStr;	
};