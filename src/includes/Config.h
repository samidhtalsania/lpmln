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
	INVALID_OT,
	INVALID_OA,
	INVALID_OM,
	INVALID_FILE,
	INAVLID_OPTIMIZATION_LEVEL,
	NO_FILE,
	EXPECTED_FILE,
	UNREGONIZED_OPTION,
	ERROR_NONE
};


enum ParserType{
	FOL,
	ASP,
	MVSM,
	PARSER_NONE
};

enum OptimizationLevel{
	ALL_CLAUSES_AUX,
	ORPHAN_AUX,
	OPTI_NONE
};

enum OutputType{
	OUTPUT_ALCHEMY,
	OUTPUT_ASP,
	OUTPUT_TUFFY,
	OUTPUT_NONE
};

class Config
{
public:
	Config(int argc, char**argv);
	~Config();

	inline Translation getTranslation(){ return translation;}
	inline ParserType getParser() { return parserType;}
	inline OptimizationLevel getLevel() { return optimizationLevel;}
	inline OutputType getOutputType() { return outputType;}
	
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
	OptimizationLevel optimizationLevel = OptimizationLevel::ORPHAN_AUX;
	OutputType outputType = OutputType::OUTPUT_NONE;
	std::string path;
	std::string file;
	bool errors = false;
	bool help = false;
	bool debug = true;
	char** args;
};