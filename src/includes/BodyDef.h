#include "Predicate.h"
#include "Util.h"

class BodyDef
{
	
public:
	BodyDef();
	~BodyDef();

	void addPredicate(Predicate _p){
		p = _p;
	}

	Predicate getPredicate(){
		return p;
	}

	std::string toString(){
		if(!aggregateString){
			if(!hasVariables){
				std::string s = p.toString();
				Util::toUpper(s);
				return s;
			}
			return p.toString();
		}
		else
			return str;
	}



	bool getHasVariables(){
		return hasVariables;
	}

	/*Special cases where BodyDef does not have variables*/
	void setHasVariables(){
		hasVariables = false;
	}


	void setString(std::string s){
		str = s;
		aggregateString = true;
	}

private:
	Predicate p;
	/*By default every BodyDef is assumed to have variables */
	bool hasVariables = true;

	/*Used by aggregates to store strings*/
	std::string str;
	bool aggregateString = false;


};