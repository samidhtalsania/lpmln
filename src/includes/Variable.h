#pragma once
#include <string>
#include <map>
#include "Domain.h"

class Variable
{
public:
	Variable();
	Variable(std::string _var) : var(_var) {};
	~Variable();

	std::string getVar() const { return var;}
	
	void setVar(std::string* str) { var = *str;}

	void setVar(std::string str) { var = str;}
	
	void insertPos(const int i, const Domain d) { pos[i] = d ;}
	
	/*int is the position of that domain in that predicate*/
	std::map<int,Domain> getPosMap() const { return pos;}
	
	void setPosMap(std::map<int,Domain> _pos) { 
		pos = _pos;
	}

	unsigned int getSize() const {
		return pos.size();
	}

	void setRhsDomain(const Domain& domain){
		rhsVar = domain;
	}

	Domain getRhsDomain() const{
		return rhsVar;
	}
	
	bool operator< (const Variable& right) const
	{
		return var < right.getVar();
	}

	inline int isCompleted() const { return completed;}

	inline void setCompleted() const { completed = true;}

	std::string toString() const;

	inline int getArgumentSize(){
		return pos.size();
	}
	
private:
	std::string var;
	std::map<int,Domain> pos;
	mutable bool completed = false;
	Domain rhsVar; /*Required for MVSM Parsers*/
};