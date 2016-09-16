#pragma once
#include "Predicate.h"

class Head
{
public:
	Head(Predicate _p){
		predList.push_back(_p);
	}
	~Head();
	Head(std::vector<Predicate> _predList):predList(_predList){}

	inline Predicate getPredicate() {
		return predList.at(0);	
	}


	inline std::vector<Predicate> getPredicateList() {
		return predList;	
	}

	void addPredicate(Predicate _p) { 
		predList.push_back(_p);
	}

	inline std::string toString() const{
		// return predList.at(0).toString();
		return headStr;
	}

	void appendStr(std::string, bool, bool, bool);

	inline void setDisjunction(bool val){
		isDisjunction = val;
	}

	inline bool getDisjunction(){
		return isDisjunction;
	}

	std::set<std::string> getConstantSet(){
		std::set<std::string> intermediateSet;
		for (unsigned int i = 0; i < predList.size(); ++i){
			if(!predList.at(i).getConstants().empty()){
				for(auto it : predList.at(i).getConstants()){
					intermediateSet.insert(it);
				}		
			}
		}
		return intermediateSet;
	}

private:
	std::vector<Predicate> predList;
	bool isDisjunction = false;

	Predicate p;
	std::string headStr;
	
};