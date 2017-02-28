#include "LanguageConstants.h"

OutputType LanguageConstants::TYPE = OutputType::OUTPUT_ALCHEMY;

std::string LanguageConstants::NOT = MLN_NOT;
std::string LanguageConstants::CON = MLN_CON;
std::string LanguageConstants::DIS = MLN_DIS;
std::string LanguageConstants::IMPL = MLN_IMPL;
std::string LanguageConstants::OBJ_SEP = MLN_OBJ_SEP;
std::string LanguageConstants::OBJ_EQUALS = MLN_OBJ_EQUALS;
std::string LanguageConstants::OBJ_PAREN_OPEN = MLN_OBJ_PAREN_OPEN;
std::string LanguageConstants::OBJ_PAREN_CLOSE = MLN_OBJ_PAREN_CLOSE;
std::string LanguageConstants::LINE_END = MLN_LINE_END;
std::string LanguageConstants::OBJ_LINE_END = MLN_OBJ_LINE_END;
std::string LanguageConstants::SPLIT_CON = MLN_CON;

void LanguageConstants::init(OutputType type){
	LanguageConstants::TYPE = type;	
	switch(type){
		case OutputType::OUTPUT_ALCHEMY:
			LanguageConstants::NOT = MLN_NOT;
			LanguageConstants::CON = MLN_CON;
			LanguageConstants::DIS = MLN_DIS;
			LanguageConstants::IMPL = MLN_IMPL;
			LanguageConstants::OBJ_SEP = MLN_OBJ_SEP;
			LanguageConstants::OBJ_EQUALS = MLN_OBJ_EQUALS;
			LanguageConstants::LINE_END = MLN_LINE_END;
			LanguageConstants::OBJ_PAREN_OPEN = MLN_OBJ_PAREN_OPEN;
			LanguageConstants::OBJ_PAREN_CLOSE = MLN_OBJ_PAREN_CLOSE;
			LanguageConstants::OBJ_LINE_END = MLN_OBJ_LINE_END;
			LanguageConstants::SPLIT_CON = MLN_CON;
			break;
		case OutputType::OUTPUT_ASP:
			LanguageConstants::NOT = ASP_NOT;
			LanguageConstants::CON = ASP_CON;
			LanguageConstants::DIS = ASP_DIS;
			LanguageConstants::IMPL = ASP_IMPL;
			LanguageConstants::OBJ_SEP = ASP_OBJ_SEP;
			LanguageConstants::OBJ_EQUALS = ASP_OBJ_EQUALS;
			LanguageConstants::LINE_END = ASP_LINE_END;
			LanguageConstants::OBJ_PAREN_OPEN = ASP_OBJ_PAREN_OPEN;
			LanguageConstants::OBJ_PAREN_CLOSE = ASP_OBJ_PAREN_CLOSE;
			LanguageConstants::OBJ_LINE_END = ASP_OBJ_LINE_END;
			LanguageConstants::SPLIT_CON = ASP_CON;
			break;
		case OutputType::OUTPUT_TUFFY:
			LanguageConstants::NOT = TUFFY_NOT;
			LanguageConstants::CON = TUFFY_CON;
			LanguageConstants::DIS = TUFFY_DIS;
			LanguageConstants::IMPL = TUFFY_IMPL;
			LanguageConstants::SPLIT_CON = TUFFY_SPLIT_CON;
			break;
		default:
			break;
	}
}