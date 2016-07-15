#include "Predicate.h"

class Head
{
public:
	Head(Predicate _p){
		predList.push_back(_p);
	}
	~Head();
	Head(std::vector<Predicate> _predList):predList(_predList){}

	Predicate getPredicate() {
		return predList.at(0);	
	}


	std::vector<Predicate> getPredicateList() {
		return predList;	
	}

	void addPredicate(Predicate _p) { 
		predList.push_back(_p);
	}

	std::string toString() const{
		// return predList.at(0).toString();
		return headStr;
	}

	void appendStr(std::string str, bool trim, bool disjunction, bool conjunction){

		if(disjunction){
			headStr += " v ";
		}
		else if(conjunction){
			headStr += " ^ ";
		}

		headStr += str;
		
		if(trim){
			headStr = headStr.substr(0,headStr.size()-3); 
		}
	}

	void setDisjunction(bool val){
		isDisjunction = val;
	}

	bool getDisjunction(){
		return isDisjunction;
	}

private:
	std::vector<Predicate> predList;
	bool isDisjunction = false;

	Predicate p;
	std::string headStr;
	
};