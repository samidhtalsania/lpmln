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

	inline std::string toString() const{
		return bodyStr;
	}

	inline std::string toNNFString() const{
		return NNFbodyStr;
	}


	void appendStr(Predicate, bool, bool, bool);


	inline std::vector<Predicate> getPredicate(){ return predList; } 

private:
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList;
	
	std::string bodyStr;	
	std::string NNFbodyStr;
};