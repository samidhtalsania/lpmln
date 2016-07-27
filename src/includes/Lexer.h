#pragma once
#include <iostream>

#define YYCTYPE		char
#define YYFILL(n)	{}
#define YYLIMIT		YYCURSOR+len


typedef struct lexeme_struct {
    const char *start;
    const char *current;
    const char *begin;
} lexeme_t;

class Lexer
{
public:
	void showInfo(){
		std::cout<<"Nothing to show\n";
	}

	virtual ~Lexer(){};

	virtual int Tokenize(const char *, int, lexeme_t*) = 0;
};