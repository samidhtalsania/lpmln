#pragma once
#include <string>

enum Translation{
	Alchemy,
	Tuffy,
	Translation_None
};

enum Error{
	INVALID_T,
	INVALID_A,
	INVALID_M,
	INVALID_FILE,
	NO_FILE,
	EXPECTED_FILE,
	UNREGONIZED_OPTION,
	ERROR_NONE
};


enum ParserType{
	FOL,
	ASP,
	PARSER_NONE
};

class Config
{
public:
	Config(int argc, char**argv);
	~Config();

	inline Translation getTranslation(){ return translation;}
	inline ParserType getParser() { return parserType;}
	
	inline std::string getExecutablePath() { return path; };
	inline std::string getFile() { return file;}

	inline bool configFailed() { return errors;}

	inline void showError(Error,int);

	inline void showHelp();

	inline void showVersion();

	inline bool configReturn() {return help;}

	inline bool getDebug() { return debug;}


private:
	Translation translation = Translation::Translation_None;
	ParserType parserType = ParserType::PARSER_NONE;
	std::string path;
	std::string file;
	bool errors = false;
	bool help = false;
	bool debug = true;
	char** args;
};