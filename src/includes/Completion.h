#pragma once
#include "Predicate.h"

class Completion
{
public:
	Completion();
	Completion(Predicate _head, std::vector<Predicate> _body) : head(_head), body(_body){};
	~Completion();

	inline Predicate getHead() const { return head; }

	inline std::vector<Predicate> getBody() const { return body;}

private:
	Predicate head;
	std::vector<Predicate> body;
};

