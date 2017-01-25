#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <exception>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <stdexcept>      // std::invalid_argument
#include <cmath>

//For getting user home directory
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/param.h>

using namespace std;
using namespace boost;
namespace io = boost::iostreams; 

#define global 0
#define local 1

//build
//g++ -g -std=c++11 lpmln2wc.cpp -o lpmln2wc -L /usr/lib -lboost_regex

// TODO: variables in unsat

set<string> findVariables(const string&);
set<string> findFreeVariables(const string&, const string&);
void runProcess(const string&);
void printHelp();
string getcwd();

set<string> findVariables(const string& head){
	
	set<string> sGlobal;
	set<string> sLocal;
	set<string> result;

	//switch
	int area = global;

	stack<int> stack;
	for(unsigned int i=0;i<head.length();i++){
		if(head.at(i) == '('){
			stack.push(0);
		}

		else if(head.at(i) == '#' || head.at(i) == '{'){
			while(head.at(i) != '}')
				i++;
			// area = local;
			i++;
		}

		else if(head.at(i) == ':'){
			while(head.at(i) != ',' && head.at(i) != ';' && head.at(i) != '.' && head.at(i) != '-'){
				i++;
				if(i >= head.length()) break;
				// area = local;
			}
			i++;
		}

		string tempStr;
		while(!stack.empty()){
			i++;
			if(i == head.length()) break;
			
			if( (int)head.at(i) >= 65 && // A
				(int)head.at(i) <= 90 && // Z
				( 	(int)head.at(i-1) == 44 || //comma
					(int) head.at(i-1) == 40 ||  // opening paren
					(int) head.at(i-1) == 32 )
				) { //space 
				bool areaSwitch = false;
				while(true){
					
					tempStr += head.at(i);
					i++;
					
					if(i == head.length()){
						break;
					}

					if(head.at(i) == ',')
						break;
					
					if(head.at(i) == '('){
						stack.push(0);	
					}

					if(head.at(i) == ')'){
						stack.pop();
						break;	
					}
					
					if(head.at(i) == '}'){
						areaSwitch = true;
						break;
					}
				}

				if(area == global && !areaSwitch)
					sGlobal.insert(tempStr);
				else
					sLocal.insert(tempStr);
				tempStr = "";
			}

			if(!stack.empty() && head.at(i) == ')'){
				area = global;
				stack.pop();
			}
		}
	}
	set_difference(sGlobal.begin(), sGlobal.end(), sLocal.begin(), sLocal.end(),inserter(result, result.end()));
	
	

	return result;
}



set<string> findFreeVariables(const string& head,const string& body){
	set<string> s = findVariables(head);
	set<string> s1 = findVariables(body);	
	// set<string> intersect;
	// set_intersection(s.begin(), s.end(), s1.begin(), s1.end(),inserter(intersect, intersect.begin()));
	s.insert(s1.begin(), s1.end());
	// return intersect;
	s.insert(s1.begin(), s1.end());
	// cout << "global:" ;
	// for(auto iter=s.begin(); iter!=s.end();++iter) { cout << *iter << " ";}cout << endl;
	return s;
}

// To run clingo
void runProcess(const string& command){
   FILE *fpipe;
   char line[1024];

   if ( !(fpipe = (FILE*)popen(command.c_str(),"r")) )
   {  // If fpipe is NULL
      perror("Problems with pipe");
      exit(1);
   }

   while ( fgets( line, sizeof(line), fpipe) != NULL)
   {
     printf("%s", line);
   }
   pclose(fpipe);

}

// To get the current working directory
string getcwd(){
    char *buffer = new char[MAXPATHLEN];
    getcwd(buffer,MAXPATHLEN);
    if(buffer != NULL){
        string ret(buffer);
        delete[] buffer;
        return ret;
    }else{
        return string();
    }
}

void printHelp(){
	cerr << "Usage: lpmln2cl <file_name> <options>\n"
			"Options:\n"
			"	--tr-hr=false 			Hard rules are not translated\n"
			"	--tr-hr=true			Hard Rules are translated\n"
			"	--infer-type=map 		Map estimation\n"
			"	--infer-type=query		Probability Calculation\n"
			"	--h 				Print help\n"
			"For the option infer-type=query, the program will prompt you for query input. The system halts untill an input is provided. The user can choose to not provide any input by hitting return key.\n";
}


int main(int argc, char **argv){
	
	ifstream file(argv[1], ios_base::in | ios_base::binary);

	// int mode = 0;

	// if(argc == 3)
	// 	mode = *argv[2] - '0';

	int unsatcount = 0;
	string str;

	//Default mode is 1, which translates only soft rules.
	//Mode 0 translates all rules.
	int mode = 1;

	//Type 0 is Map inference (default)
	//Type 1 is marginal inference
	int inferType = 0;

	#define YYFILL(n)	{}
	for (int i = 2; i < argc; ++i)
	{
		const char* YYCTXMARKER;

		char* original = argv[i];

		#define YYCTYPE char
		#define YYFILL(n) {}    
		#define YYCURSOR original
		#define YYLIMIT original+sizeof(original)
		#define YYMARKER YYCURSOR
		#define YYCTXMARKER YYCURSOR 

		/*!re2c


			WS						= [ \t\v\f];
			"\000"					{ continue;}
			
			"--tr-hr=false"			{
										mode = 1;
										continue;  	
									}
			"--tr-hr=true"			{
										mode = 0;
										continue;
									}
			"--infer-type=map"		{
										inferType = 0;
										continue;
									}
			"--infer-type=query" 	{
										inferType = 1;
										continue;
									}
			"--h"					{
										printHelp();
										exit(0);
									}
			



		*/
	}



    std::streambuf *psbuf, *backup;
	std::ofstream filestr;
	filestr.open (getcwd() + "/out.txt");

	cout << string(argv[0]) << endl;

	backup = std::cout.rdbuf();     // back up cout's streambuf

	psbuf = filestr.rdbuf();        // get file's streambuf
	std::cout.rdbuf(psbuf);         // assign streambuf to cout

	if(file){
    
	    try{
			io::filtering_istream in;

			in.push(file);
			bool f = false; 
			for(str; getline(in, str); ){

				if(str.length() == 0) continue;

				if(str[0] == '%'){
					//ignore comments
					cout<<str+"\n";
					continue;
				}



				
				std::size_t found;
				if(!f){
					found = str.find("python");
					if(found != std::string::npos) {
						f = true;
					}
				}
				
				
				if(f){
					cout<<str + "\n";
					found = str.find("end");
					if(found != std::string::npos)
						f = false;
					continue;
				}

				trim(str);
				//splits the rule to head and body
				vector<string> splitVec;
				

				boost::algorithm::split_regex(splitVec, str, regex(":-"));
				//splits the head into weight part and rule part
				vector<string> splitVecSpace;
				int weight = 0;


				if(splitVec.size() == 1){
					//process it if its of the form 
					// W H. or H.

					split(splitVecSpace, splitVec[0], is_any_of(" "), token_compress_on);
					//Process soft rules of form W H.
					try{
						std::string::size_type sz;
						float floatVal = stof(splitVecSpace[0],&sz); 
						if(isinf(floatVal) || isnan(floatVal) || sz != splitVecSpace[0].length()) throw std::runtime_error("inf/nan error");
						
						weight = (int)floatVal;
						
						string newStr;

						for(unsigned int i=1;i<splitVecSpace.size();i++){
							newStr += splitVecSpace[i] + " ";
						}
						string tempstr;

						set<string> s = findVariables(newStr);
						string vars;
						for(auto itr = s.begin(); itr!=s.end();++itr)
							vars += *itr + ",";
						if(vars.length() != 0){
							vars.pop_back();
							vars = "," + vars;
						}

						splitVecSpace[1].pop_back();
						trim(newStr);
						newStr.pop_back();

						string oldVars = vars;
						vars = ","+ to_string(weight) + vars ;


						tempstr = "unsat(" + to_string(unsatcount) + vars + ") :-";
						
						tempstr +=  "not " + newStr + ".\n" + newStr + ":-" ;
						
						tempstr += "not unsat(" + to_string(unsatcount) + vars + ")";
						tempstr +=  ".\n:~ unsat(" + to_string(unsatcount) + vars +"). [" + to_string(weight) + "@0,"+ to_string(unsatcount)+ oldVars +"]\n";


						cout<<tempstr;
						
						unsatcount++;
					}
					//Process hard rules of form H.
					catch(const std::exception& ex){
						// It could be of type H. Process it.
						
						if(mode == 1){
							//Hard facts are untouched in Mode 1
							cout << str + "\n";
							continue;
						}

						//Remove . at the end
						str.pop_back();

						set<string> s = findVariables(str);
						string vars;
						for(auto itr = s.begin(); itr!=s.end();++itr)
							vars += *itr + ",";
						if(vars.length() != 0){
							vars.pop_back();
							vars = "," + vars;
						}

						string oldVars = vars;
						vars = ",a" + vars ;

						string tempstr = "unsat("+to_string(unsatcount)+vars+") :- not " + str + ".\n" +
											str + " :- not unsat(" + to_string(unsatcount) +vars+ ").\n" +
											":~ unsat(" + to_string(unsatcount) +vars+"). [1@1," + to_string(unsatcount) + oldVars + "]";
								unsatcount++;
						cout << tempstr + "\n";
						
					}


					// dont process it
					// cout<<str + "\n";
				}
				else{
					
					trim(splitVec[0]);
					split(splitVecSpace, splitVec[0], is_any_of(" "), token_compress_on);

					string newStr;

					for(unsigned int i=1;i<splitVecSpace.size();i++){
						newStr += splitVecSpace[i] + " ";
					}
					string tempstr;
					string weightString;
					set<string> s;	
					bool issoft = false;	
								
					try{
						std::string::size_type sz;
						float floatVal = stof(splitVecSpace[0],&sz); 
						if(isinf(floatVal) || isnan(floatVal) || sz != splitVecSpace[0].length()) throw std::runtime_error("inf/nan error");
						weight = (int)(floatVal);
						// if(sz != splitVecSpace[0].length())
						// 	throw std::invalid_argument( "the number is not a weight" );;
						weightString = to_string(weight) + "@0";
						issoft = true;
						s = findFreeVariables(newStr, splitVec[1]);
					}
					catch (const std::invalid_argument& ia) {
						weightString = "1@1";
						s = findFreeVariables(splitVec[0], splitVec[1]);
						splitVecSpace.clear();
						newStr = splitVec[0];
					}
					catch(...){
						weightString = "1@1";
						s = findFreeVariables(splitVec[0], splitVec[1]);
						splitVecSpace.clear();
						newStr = splitVec[0];
					};

					// set<string> s = findFreeVariables(newStr, splitVec[1]);
					string vars;
					for(auto itr = s.begin(); itr!=s.end();++itr)
						vars += *itr + ",";
					if(vars.length() != 0){
						vars.pop_back();
						vars = "," + vars;
					}


					splitVec[1].pop_back();
					string probString = "";

					if(issoft) probString += ","+to_string(weight);
					else probString += ",a";

					string oldVars = vars;
					vars = probString + vars;

					//If it is a constraint newStr is empty, 
					//newStr holds value of splitVec[0] which is empty in case of a constraint.
					// if(newStr.length() != 0){
					// 	newStr = ", not " + newStr;
					// }

					if(splitVecSpace.size() == 1){
						//W :- B
						//weighted constraints
						// cout << "366\n";
						tempstr = "unsat(" + to_string(unsatcount) + vars + ") :- " + splitVec[1]+ ".\n" + 
										+ ":- " + splitVec[1] + ", not " + "unsat(" + to_string(unsatcount) + vars + ").\n"
										+ ":~ "+ "unsat(" + to_string(unsatcount) + vars + ")." + "["+ weightString +","+ to_string(unsatcount)+ vars+"]\n" ;

						// tempstr = ":~ "+ splitVec[1]+ "." + "["+ weightString +","+ to_string(unsatcount)+ oldVars +"]\n" ;

					}
					// Hard rules/constraints are ignored.
					else{
						//This is a constraint.
						if(newStr.empty()){
							//if soft rule translate it irrespective of the mode.
							if(issoft || (!issoft && mode == 0)){
								// tempstr = "unsat(" + 
								// cout << "377\n";
								tempstr = "unsat(" + to_string(unsatcount) + vars + ") :- " + splitVec[1]+ ".\n" + 
										+ ":- " + splitVec[1] + ", not " + "unsat(" + to_string(unsatcount) + vars + ").\n"
										+ ":~ "+ "unsat(" + to_string(unsatcount) + vars + ")." + "["+ weightString +","+ to_string(unsatcount)+ vars+"]\n" ;

								// "["+ weightString +","+ to_string(unsatcount)+ oldVars +"]\n" ;
								// tempstr = ":~ "+ splitVec[1]+ "." + "["+ weightString +","+ to_string(unsatcount)+ oldVars +"]\n" ;
							}
							else{
								tempstr = str + "\n";
							}
						}
						else if(issoft || (!issoft && mode == 0)){
							//Soft rules are translated irespective of the mode
							//Hard rules are translated only in mode 0
							tempstr = "unsat(" + to_string(unsatcount) + vars + ") :-" + splitVec[1] + ",not " + newStr + ".\n" + newStr + ":-" + splitVec[1] + ", " + "not unsat(" + to_string(unsatcount) + vars + ")" + ".\n"+":~" + "unsat(" + to_string(unsatcount) + vars +")." + " [" + weightString + ","+ to_string(unsatcount)+ oldVars +"]\n";
						}
						else if(!issoft && mode == 1){
							//Hard rules are translated only in mode 0
							// cout << str + "\n";
							tempstr = str + "\n";
						}
					}
					cout<<tempstr;
					
					unsatcount++;
				} 
			}
		}
		catch(const std::exception& ia) {
	    	cout<<"Error: "<<ia.what();
	    	return -1;
    	}
    }
    else{
    	if(string(argv[1]) != "--h")
    		cerr << "Some error ocurred while processing this file!\n";
    	printHelp();
    	return 0;
    }

	

    // cout.rdbuf(coutbuf);
    std::cout.rdbuf(backup);        // restore cout's original streambuf

	filestr.close();

    const char *homedir;

	if ((homedir = getenv("HOME")) == NULL) {
	    homedir = getpwuid(getuid())->pw_dir;
	}

	string clingoCommand;
    //Map inference
    if(inferType == 0){
    	clingoCommand = "clingo /tmp/out.txt ";
    	cout << "Clingo executed with command:\n" << clingoCommand << endl;
	}
    else{
    	clingoCommand = "clingo /tmp/out.txt /usr/local/share/lpmln/marginal-prob-script.py 0 --opt-mode=enum";
    	cout << "Clingo executed with command:\n" << clingoCommand << endl;
    }
    runProcess(clingoCommand);

    return 0;


}
