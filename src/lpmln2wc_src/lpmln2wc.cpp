#include <iostream>
#include <string>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <exception>

#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;
using namespace boost;
namespace io = boost::iostreams; 

//build
//g++ -g -std=c++11 lpmln2wc.cpp -o lpmln2wc -L /usr/lib -lboost_regex


int main(int argc, char **argv){
	
	ifstream file(argv[1], ios_base::in | ios_base::binary);

	int unsatcount = 0;
	string str;

	if(file){
    
	    try{
			io::filtering_istream in;

			in.push(file);

			for(str; getline(in, str); ){

				if(str[0] == '%'){
					//ignore comments
					cout<<str+"\n";
					continue;
				}

				trim(str);
				
				vector<string> splitVec;
				

				boost::algorithm::split_regex(splitVec, str, regex(":-"));

				if(splitVec.size() == 1){
					// dont process it
					cout<<str + "\n";
				}
				else{
					vector<string> splitVecSpace;
					trim(splitVec[0]);
					split(splitVecSpace, splitVec[0], is_any_of(" "), token_compress_on);

					string newStr;

					for(unsigned int i=1;i<splitVecSpace.size();i++){
						newStr += splitVecSpace[i];
					}
					string tempstr;
					try{
						if(splitVecSpace.size() == 1){
							//W :- B
							tempstr = ":~ "+ splitVec[1] + "["+ to_string((int)(stof(splitVecSpace[0])* 10000)) +","+ to_string(unsatcount) +"]\n" ;

						}
						else{
							// W H :- B
							// if(splitVec[1][splitVec[1].length()-1] == '.')
								splitVec[1].pop_back();
							tempstr = "unsat(" + to_string(unsatcount) + ") :-" + splitVec[1] + ",not " + newStr + ".\n" + newStr + ":-" + splitVec[1] + ", " + "not unsat(" + to_string(unsatcount) + ")" + ".\n"+":~" + "unsat(" + to_string(unsatcount) + ")." + " [" + to_string((int)(stof(splitVecSpace[0])* 10000)) + ","+ to_string(unsatcount) +"]\n";
							
						}
						cout<<tempstr;
						unsatcount++;

					}
					catch(const std::invalid_argument& ia){
						cout<<str + "\n";
					}
					
				
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
}