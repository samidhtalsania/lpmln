#pragma once 

#include <string>
#include "Config.h"

#define ASP_CON " , "
#define ASP_DIS " ; "
#define ASP_NOT "not "
#define ASP_IMPL " :- "
#define ASP_OBJ_SEP ";"
#define ASP_OBJ_EQUALS ""
#define ASP_OBJ_PAREN_OPEN "("
#define ASP_OBJ_PAREN_CLOSE ")"
#define ASP_OBJ_LINE_END "."
#define ASP_LINE_END "."

#define MLN_CON " ^ "
#define MLN_DIS " v "
#define MLN_NOT "!"
#define MLN_IMPL " => "
#define MLN_OBJ_SEP ","
#define MLN_OBJ_EQUALS "="
#define MLN_OBJ_PAREN_OPEN "{"
#define MLN_OBJ_PAREN_CLOSE "}"
#define MLN_LINE_END "."
#define MLN_OBJ_LINE_END ""

#define TUFFY_CON " , " 
#define TUFFY_DIS " v " 
#define TUFFY_NOT "!"
#define TUFFY_IMPL " => "

class LanguageConstants{

public:
	static std::string CON ;
	static std::string DIS ;
	static std::string NOT ;
	static std::string IMPL;
	static std::string OBJ_SEP;
	static std::string OBJ_EQUALS;
	static std::string OBJ_PAREN_CLOSE;
	static std::string OBJ_PAREN_OPEN;
	static std::string LINE_END;
	static std::string OBJ_LINE_END;

	static OutputType TYPE;

	static void init(OutputType);
};