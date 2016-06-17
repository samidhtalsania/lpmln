#pragma once
#include <string>

enum Translation{
	Alchemy,
	Tuffy,
	None
};

enum Error{
	INVALID_T,
	INVALID_A,
	INVALID_FILE,
	NO_FILE,
	EXPECTED_FILE,
	NONE
};

class Config
{
public:
	Config(int argc, char**argv);
	~Config();

	inline Translation getTranslation(){ return translation;}
	inline std::string getExecutablePath() { return path; };
	inline std::string getFile() { return file;}

	inline bool configFailed() { return errors;}

	inline void showError(Error);

	inline void showHelp();

	inline void showVersion();

	inline bool configReturn() {return help;}

	inline bool getDebug() { return debug;}


private:
	Translation translation = Translation::None;
	std::string path;
	std::string file;
	bool errors = false;
	bool help = false;
	bool debug = false;
};