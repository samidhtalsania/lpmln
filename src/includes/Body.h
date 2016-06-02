#include <set>
#include "Predicate.h"

class Body
{
public:
	Body();
	~Body();

	void addPredicate(Predicate p){
		predList.push_back(p);
	}

	std::vector<Predicate> getPredicate(){ return predList; } 

private:
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList;
};