#include "FileConfig.h"
#include <fstream>
#include <string.h>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "exceptions/NoLanguageSelectedException.h"

using namespace std;

FileConfig::FileConfig(){
	map<string,string> options;
	ifstream configFile;

	const char *homedir;
	bool fileCouldNotBeOpened = false;

	if ((homedir = getenv("HOME")) == NULL) {
	    homedir = getpwuid(getuid())->pw_dir;
	}

	string filename = string(homedir)+"/.lpmln-config.txt";

	configFile.open(filename);

	if(!configFile.is_open()){
		#ifdef DEBUG
		cout<<"Cannot read from config file\n";
		#endif
		// ofstream file;
		// file.open(filename);
		// file.close();
		fileCouldNotBeOpened = true;
	}

	// Set defaults
	//Default for lpmln: Solver is MLN, Input is MVSM
	loptions.insert(pair<string,string>("input","mvsm"));
	//Compile for Clingo
	loptions.insert(pair<string,string>("solver","clingo"));
	//max number of solutions for clingo
	coptions.insert(pair<string,string>("solutions","0"));
	

	string line;
	int count = 0;
	while(getline(configFile, line)){
		count++;
		line = rtrim(ltrim(line));
		// Comments start with #
		// Empty lines are ignored
		if(line.empty() || line.at(0) == '#'){
			continue;
		}
		else{
			/*Check if it is a start of a region*/
			if (line.at(0) == '['){
				
				//It is a start of a region.
				//find out what region it is
				//Region can be either lpmln/clingo/alchemy
				line = line.substr(1,line.size()-2);
				string reg = rtrim(ltrim(line));
				if(equalsIgnoreCase("lpmln", reg)){
					region = Region::LPMLN;
					// options = loptions;
					
				}
				else if(equalsIgnoreCase("clingo", reg)){
					region = Region::CLINGO;
					// options = coptions;
					
				}
				else if(equalsIgnoreCase("alchemy", reg)){
					region = Region::ALCH;
					// options = aoptions;
					
				}
			}

			else{
				//It is one of the other lines
				//First check if region is none or not
				//if region is none it is incorrect.
				//Such lines with "=" have to be in a region
				if(region == Region::NONE){
					#ifdef DEBUG
					cout<<"No region specified. Incorrect configuration file.\n";
					#endif
					break;
				}
				else{
					//Correct configuration
					//based on the region MAP is already instantiated

					//split the string on first "=" sign
					std::size_t found = line.find('=');

					if(found == string::npos){
						#ifdef DEBUG
						cout<<"Incorrect configuration found at line:"<<count<<"\n";
						#endif
						break;
					}

					string lhs = line.substr(0, line.find('='));
					if(lhs.size() == line.size()-1){
						#ifdef DEBUG
						cout<<"No option specified for argument at line:"<<count<<"\n";
						#endif
						break;	
					}

					lhs = rtrim(ltrim(lhs));
					
					string rhs = line.substr(found+1);
					rhs = rtrim(ltrim(rhs));

					if(region == Region::LPMLN){
						if(equalsIgnoreCase("solver",lhs)){
							if(equalsIgnoreCase("alchemy",rhs)){
								aoptions.insert(pair<string,string>("region","alch"));
								execute_alch = true;
							}
							else if(equalsIgnoreCase("clingo",rhs)){
								execute_cli = true;	
							}

							loptions["solver"] = rhs;
						}
						else if(equalsIgnoreCase("input",lhs)){
							loptions["input"] = rhs;	
						}
						else if(equalsIgnoreCase("optimization",lhs)){
							loptions.insert(pair<string,string>("optimization",rhs));	
						}
						else{
							#ifdef DEBUG
							cout<<"Unknown argument at line:"<<count<<"\n";
							#endif
							break;		
						}
					}	

					if(region == Region::CLINGO){
						if(equalsIgnoreCase("solutions",lhs)){
							coptions["solutions"] = rhs;
						}
						else if(equalsIgnoreCase("extra",lhs)){
							coptions.insert(pair<string,string>("extra",rhs));
						}
						else{
							#ifdef DEBUG
							cout<<"Unknown argument at line:"<<count<<"\n";
							#endif
							break;		
						}
						execute_cli = true;
					}

					if(region == Region::ALCH){
						if(equalsIgnoreCase("query",lhs)){
							aoptions.insert(pair<string,string>("query",rhs));
						}
						else if(equalsIgnoreCase("evidence",lhs)){
							aoptions.insert(pair<string,string>("evidence",rhs));
						}
						else if(equalsIgnoreCase("extra",lhs)){
							aoptions.insert(pair<string,string>("extra",rhs));
						}
						else{
							#ifdef DEBUG
							cout<<"Unknown argument at line:"<<count<<"\n";
							#endif
							break;		
						}
						execute_alch = true;
						if(execute_cli == true) execute_cli = false;
					}

				}
			}
		}
	}

	if(!execute_alch && !execute_cli || fileCouldNotBeOpened){
		throw NoLanguageSelectedException("No language selected from config File. Check to see if config file has the right syntax.");
	}

	//Parsing done
	//Check validity

	if(aoptions.size() >= 1){
		auto itr = aoptions.find("query");
		if (itr == aoptions.end()){
			#ifdef DEBUG
			cout<<"Solver alchemy requires query argument.\n";
			#endif
		}
	}

	
	configFile.close();
}


string & FileConfig::ltrim(string & str)
{
  auto it2 =  find_if( str.begin() , str.end() , [](char ch){ return !isspace<char>(ch , locale::classic() ) ; } );
  str.erase( str.begin() , it2);
  return str;   
}

string & FileConfig::rtrim(string & str)
{
  auto it1 =  find_if( str.rbegin() , str.rend() , [](char ch){ return !isspace<char>(ch , locale::classic() ) ; } );
  str.erase( it1.base() , str.end() );
  return str;   
}

bool FileConfig::equalsIgnoreCase(std::string const& s1, std::string const& s2) {
    if(s1.length() != s2.length())
        return false;  // optimization since std::string holds length in variable.
    return strcasecmp(s1.c_str(), s2.c_str()) == 0;
}