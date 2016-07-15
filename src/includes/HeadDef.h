#include "Predicate.h"

class headDef
{
	
public:
	headDef();
	~headDef();

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