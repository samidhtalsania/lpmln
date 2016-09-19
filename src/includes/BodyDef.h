#include "Predicate.h"

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
		return p.toString();
	}

	bool getHasVariables(){
		return hasVariables;
	}

	/*Special cases where BodyDef does not have variables*/
	void setHasVariables(){
		hasVariables = false;
	}

private:
	Predicate p;
	/*By default every BodyDef is assumed to have variables */
	bool hasVariables = true;	
};