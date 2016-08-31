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

	std::string toNNFString() const{
		return NNFbodyStr;
	}


	void appendStr(Predicate pred, bool trim, bool disjunction, bool conjunction){

		if(disjunction){
			bodyStr += " v ";
			NNFbodyStr += " ^ ";
		}
		else if(conjunction){
			bodyStr += " ^ ";
			NNFbodyStr += " v ";
		}


		bodyStr += pred.toString();
		NNFbodyStr += pred.toNNFString();
		
		if(trim){
			bodyStr = bodyStr.substr(0,bodyStr.size()-3); 
			NNFbodyStr = NNFbodyStr.substr(0,bodyStr.size()-3); 
		}
	}



	std::vector<Predicate> getPredicate(){ return predList; } 

private:
	std::set<std::pair<std::string,std::string>> orphanVarsMap;
	std::set<std::pair<std::string,std::string>> orphanVarsHeadMap;
	std::vector<Predicate> predList;
	
	std::string bodyStr;	
	std::string NNFbodyStr;
};