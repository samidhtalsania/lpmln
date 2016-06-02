#include "Predicate.h"

class Head
{
public:
	Head();
	~Head();

	Predicate getPredicate() { return p;}

	void addPredicate(Predicate _p) { p = _p;}


private:
	Predicate p;
	
};