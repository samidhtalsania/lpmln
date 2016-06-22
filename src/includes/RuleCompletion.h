#pragma once
#include "Completion.h"
#include "Predicate.h"
#include <set>

class RuleCompletion : public Completion
{
public:
	RuleCompletion(Predicate _head,
					std::vector<Predicate> _body,
					std::set<std::pair<std::string, std::string>> _orphanVars,
					std::map<int,std::pair<int, std::string>> _map):super(_head, _body), orphanVars(_orphanVars), varMap(_map)
					{
						_orphanVars.size()>0 ? isOrphan = true : isOrphan = false;
					};
	~RuleCompletion();
	RuleCompletion();
	
	//Map of constants in Head variable to later convert properly to CNF.
	std::map<int,std::pair<int, std::string>> getConstantMap() const {return varMap;}
	
	//Check if it is orphan
	bool checkOrphan() { return isOrphan;}
	
	std::set<std::pair<std::string, std::string>> getOrphanVars() {return orphanVars;}

	bool isHeadTop = false;
	
private:
	typedef Completion super;
	bool isOrphan = false;
	std::set<std::pair<std::string, std::string>> orphanVars; 
	std::map<int,std::pair<int, std::string>> varMap;

};

