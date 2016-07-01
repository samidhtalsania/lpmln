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

private:
	Predicate p;	
};