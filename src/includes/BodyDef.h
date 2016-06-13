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

private:
	Predicate p;	
};