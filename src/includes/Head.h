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

	inline std::string getExtra(const std::set<Variable>& variable){
		std::string str;
		for (std::vector<Predicate>::iterator i = predList.begin(); i != predList.end(); ++i){
			std::string s = i->getExtra(variable);
			if(s.length() != 0){
				str += s;
				str += " , ";
			}
		}
		if(str.length() > 3)
			str = str.substr(0,str.size()-3);
		return str;
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

	std::string toNNFString(){
		std::string str;
		for (unsigned int i = 0; i < predList.size(); ++i){
			str += "not ";
			str += predList.at(i).toString();
			str += " , ";
		}
		str = str.substr(0,str.size()-3);
		return str;
	}

private:
	std::vector<Predicate> predList;
	bool isDisjunction = false;

	Predicate p;
	std::string headStr;
	
};