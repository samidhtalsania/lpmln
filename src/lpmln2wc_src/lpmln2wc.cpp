/* Generated by re2c 0.15.3 on Fri Jan 20 05:21:30 2017 */
#line 1 "lpmln2wc.re"
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
void runProcess(string command){
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
	for (int i = 0; i < argc; ++i)
	{
		const char* YYCTXMARKER;

		char* original = argv[i];

		#define YYCTYPE char
		#define YYFILL(n) {}    
		#define YYCURSOR original
		#define YYLIMIT original+sizeof(original)
		#define YYMARKER YYCURSOR
		#define YYCTXMARKER YYCURSOR 

		
#line 200 "<stdout>"
{
	YYCTYPE yych;
	if ((YYLIMIT - YYCURSOR) < 21) YYFILL(21);
	yych = *YYCURSOR;
	switch (yych) {
	case 0x00:	goto yy3;
	case '-':	goto yy5;
	default:	goto yy2;
	}
yy2:
yy3:
	++YYCURSOR;
#line 201 "lpmln2wc.re"
	{ continue;}
#line 215 "<stdout>"
yy5:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy6;
	default:	goto yy2;
	}
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy8;
	case 't':	goto yy7;
	default:	goto yy2;
	}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy30;
	default:	goto yy2;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy9;
	default:	goto yy2;
	}
yy9:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'f':	goto yy10;
	default:	goto yy2;
	}
yy10:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy11;
	default:	goto yy2;
	}
yy11:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy12;
	default:	goto yy2;
	}
yy12:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy13;
	default:	goto yy2;
	}
yy13:
	yych = *++YYCURSOR;
	switch (yych) {
	case 't':	goto yy14;
	default:	goto yy2;
	}
yy14:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'y':	goto yy15;
	default:	goto yy2;
	}
yy15:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'p':	goto yy16;
	default:	goto yy2;
	}
yy16:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy17;
	default:	goto yy2;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy18;
	default:	goto yy2;
	}
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'm':	goto yy19;
	default:	goto yy2;
	}
yy19:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy20;
	default:	goto yy2;
	}
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'p':	goto yy22;
	case 'r':	goto yy21;
	default:	goto yy2;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'g':	goto yy24;
	default:	goto yy2;
	}
yy22:
	++YYCURSOR;
#line 210 "lpmln2wc.re"
	{
									inferType = 1;
									continue;
								}
#line 327 "<stdout>"
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'i':	goto yy25;
	default:	goto yy2;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'n':	goto yy26;
	default:	goto yy2;
	}
yy26:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy27;
	default:	goto yy2;
	}
yy27:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy28;
	default:	goto yy2;
	}
yy28:
	++YYCURSOR;
#line 214 "lpmln2wc.re"
	{
									inferType = 1;
									continue;
								}
#line 359 "<stdout>"
yy30:
	yych = *++YYCURSOR;
	switch (yych) {
	case '-':	goto yy31;
	default:	goto yy2;
	}
yy31:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'h':	goto yy32;
	default:	goto yy2;
	}
yy32:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy33;
	default:	goto yy2;
	}
yy33:
	yych = *++YYCURSOR;
	switch (yych) {
	case '=':	goto yy34;
	default:	goto yy2;
	}
yy34:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'f':	goto yy35;
	case 't':	goto yy36;
	default:	goto yy2;
	}
yy35:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'a':	goto yy41;
	default:	goto yy2;
	}
yy36:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'r':	goto yy37;
	default:	goto yy2;
	}
yy37:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'u':	goto yy38;
	default:	goto yy2;
	}
yy38:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy39;
	default:	goto yy2;
	}
yy39:
	++YYCURSOR;
#line 206 "lpmln2wc.re"
	{
									mode = 0;
									continue;
								}
#line 422 "<stdout>"
yy41:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'l':	goto yy42;
	default:	goto yy2;
	}
yy42:
	yych = *++YYCURSOR;
	switch (yych) {
	case 's':	goto yy43;
	default:	goto yy2;
	}
yy43:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'e':	goto yy44;
	default:	goto yy2;
	}
yy44:
	++YYCURSOR;
#line 202 "lpmln2wc.re"
	{
									mode = 1;
									continue;  	
								}
#line 448 "<stdout>"
}
#line 219 "lpmln2wc.re"

	}


	// if(argc >= 3){
	// 	std::stringstream ss(argv[2]);
	// 	ss >> mode;
	// 	if(mode != 0 && mode != 1){
	// 		cout << "Invalid 3rd argument. Can be either 0 or 1.\n";
	// 		exit(1);
	// 	}

	// }

	// cout to a file instead of cout to screen
	std::ofstream out("/tmp/out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

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
					// found = std::string::npos;
					// f = true;
					// while(found == std::string::npos){
					// 	cout<<str;
					// 	found = str.find("end");
					// }
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
						vars = ",0,"+ to_string(weight) + vars ;


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
						vars = ",1,1" + vars ;

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

					if(issoft) probString += ",0,"+to_string(weight);
					else probString += ",1,1";

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
    	cerr << "Some error ocurred while processing this file!\n";
    	return -1;
    }

    cout.rdbuf(coutbuf);

    const char *homedir;

	if ((homedir = getenv("HOME")) == NULL) {
	    homedir = getpwuid(getuid())->pw_dir;
	}

    //Map inference
    if(inferType == 0){
		runProcess("clingo /tmp/out.txt " + string(homedir) + "/usr/local/share/lpmln/prob-script.py 0 --opt-mode=enum");
    }
    else{
    	runProcess("clingo /tmp/out.txt " + string(homedir) + "/usr/local/share/lpmln/marginal-prob-script.py 0 --opt-mode=enum");	
    }


    return 0;


}
