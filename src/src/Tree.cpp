#include "Tree.h"

Tree::Tree()
{}

Tree::~Tree()
{}

void Tree::completeRules(){

	// Rule Completion
	std::vector<std::pair<std::string,RuleCompletion>> keys_dedup2;
	std::unique_copy(std::begin(rules),
				  std::end(rules),
					std::back_inserter(keys_dedup2),
				  [](const std::pair<std::string,RuleCompletion> &entry1,
					 const std::pair<std::string,RuleCompletion> &entry2) {
					   return (entry1.first == entry2.first);
				   }
				 );
				 
				 
	std::multimap<std::string, RuleCompletion> rules2;
	rules2 = rules;

	for(auto &key : keys_dedup2)
	{
		std::string strLhs;
		std::string strRhs;
		
		std::pair<int,int> auxPos;
		
		std::pair <std::multimap<std::string,RuleCompletion>::iterator, std::multimap<std::string, RuleCompletion>::iterator> ret;

		if(key.first.empty()){
			//Key is empty. This will throw a segfault.
			throw undefined_key();
		}

		ret = rules.equal_range(key.first);
		
		//Based on key, from varaibles set find out its domains.
		//Assign a variable to each of the domain of the key.
		//Use this variable in constructing strLhs and strRhs 
		std::set<Variable>::iterator itrV = variables.find(key.first);

		if(itrV != variables.end()) itrV->setCompleted();

		std::map<std::string, int> varMapVarCount; /* Maps how many times a particular argument is occuring*/
		std::map<std::string, std::string> varMapAssociate; 
		std::unordered_multimap<int, std::pair<std::string, std::string> > varMap; /* Maps every position of argument in a predicate to the argument type and the variable to be used in its place */
		std::vector<std::string> vtemp = key.second.getHead().getTokens();

		long unsigned int count = 0;
		if(itrV->getPosMap().size() != vtemp.size()){
			throw invalid_arguments(itrV->getPosMap().size(), vtemp.size(), key.first);
		}
		for(auto &var : itrV->getPosMap()){
			varMapAssociate[vtemp.at(count)] = uniqueVars[count];
			std::pair<int, std::pair<std::string, std::string>> pa(var.first, std::pair<std::string, std::string>(var.second.getDomainVar(), uniqueVars[count]));
			varMap.insert(pa);
			varMapVarCount[pa.second.first] = varMapVarCount[pa.second.first] + 1;
			count++;
		}
		
		RuleCompletion r;

		strLhs.append(key.first).append("(");
		
		std::vector<std::string> v(varMap.size());
		long unsigned int ii;
		for(auto &vm : varMap){
			ii = static_cast<long unsigned int>(vm.first);
			v[ii] = vm.second.second;
		}
			
		for(auto &vm : v)
			strLhs.append(vm).append(",");
		
		strLhs = strLhs.substr(0,strLhs.size()-1);
		strLhs.append(")");
		
		
		int auxCount = 0;
		for (std::multimap<std::string,RuleCompletion>::iterator it=ret.first; it!=ret.second; ++it)
		{
			r = it->second;
			std::set<std::pair<std::string,std::string>> orphanVarsSet;
			strRhs.append("(");
			
			//append exist and associated variables to string.
			if(r.checkOrphan())
			{
				orphanVarsSet = r.getOrphanVars();
				strRhs.append("EXIST ");
				for(auto &orphanVars : r.getOrphanVars())
				{
					strRhs.append(orphanVars.first).append(",");
				}
				strRhs = strRhs.substr(0,strRhs.size()-1);
				strRhs.append(" (");
			}
			
			auxPos.first = strRhs.size() ;
			//std::vector<std::pair<int, std::string>> constantPos;
			//Append constants to strRhs
			for(auto &constant : r.getConstantMap())
			{
				//constantPos.push_back(std::pair<int,std::string>(constant.first, constant.second.first));
				//localPos[constant.first] = constant.second.first;
				//strRhs.append("=").append(" ^ ");
				for(auto &constantInner : varMap)
				{
					if(constantInner.first == constant.first){
						strRhs.append(constantInner.second.second).append("=").append(constant.second.second).append(" ^ ");
					}
				}
			}
			
			int bodyVecCount = 0;
			for(auto &pred : r.getBody())
			{
				/*		
					if(isEquality)
						return 1;
					else if(isInEquality)
						return 2;
					else
						return 0;
				*/
				int e = pred.checkEquality();
				if(e != 0)
				{
					/*Check if LHS is in the orphanVarsSet */
					auto itr = std::find_if(orphanVarsSet.begin(), orphanVarsSet.end(), [&](const std::pair<std::string, std::string>& val) -> bool{
						return val.first == pred.getLvar();
					});

					//If it is then simply add it
					if(itr != orphanVarsSet.end()){
						strRhs.append(pred.getLvar());
					}

					//Otherwise find out which internal variable is the LHS replaced with
					else
					{
						Predicate predicateWeWant;
						//search all predicates innerVariables to find out its domain
						int pos = 0; 
						for(auto innerPred: r.getBody()){
							int found = 0;

							if(innerPred.checkEquality()==0){
								std::vector<std::string> tok = innerPred.getTokens();
								pos = 0;
								for(auto &tokenStr:tok){
									if(tokenStr == pred.getLvar()){
										predicateWeWant = innerPred;
										found = 1;
										break;
									}
									pos++;
								}
							}
							if(found == 1) break;
						}


						int x = 10;
						x++;

						if(!predicateWeWant.getVar().empty()){
							
							std::set<Variable>::iterator itrInner = variables.find(predicateWeWant.getVar());
							//Finds variable with var=next
							Domain d = itrInner->getPosMap().at(pos);
							std::string varType(d.getDomainVar());

							auto pa = variables.find(predicateWeWant.getVar())->getPosMap()[pos].getDomainVar();
							for(auto it3=varMap.begin(); it3!=varMap.end();++it3){
								if(it3->second.first.compare(pa) == 0)
									strRhs.append(it3->second.second);	

							}
						}
						else{
							std::cout<<"Error: Cannot find predicate containing "<<pred.getLvar();
						}

					}

					if(e == 1) strRhs.append("=");
					else if(e == 2) strRhs.append("!=");

					itr = std::find_if(orphanVarsSet.begin(), orphanVarsSet.end(), [&](const std::pair<std::string, std::string>& val) -> bool{
						return val.first == pred.getRvar();
					});

					if(itr != orphanVarsSet.end())
					{
						strRhs.append(pred.getRvar());
					}
					else
					{
						//search all predicates innerVariables to find out its domain
						Predicate* predicateWeWant;
						//search all predicates innerVariables to find out its domain
						int pos = 0; 
						for(auto &innerPred: r.getBody()){
							int found = 0;

							if(innerPred.checkEquality()==0){
								std::vector<std::string> tok = innerPred.getTokens();
								pos = 0;
								for(auto &tokenStr:tok){
									if(tokenStr == pred.getRvar()){
										predicateWeWant = &innerPred;
										found = 1;
										break;
									}
									pos++;
								}
							}
							if(found == 1) break;
						}

						if(predicateWeWant == NULL){
							std::cout<<"Error: Cannot find predicate containing "<<pred.getRvar();
						}
						else{
							std::set<Variable>::iterator itrInner = variables.find(Variable(predicateWeWant->getVar()));
							//Finds variable with var=next
							Domain d = (*itrInner).getPosMap().at(pos);
							std::string varType(d.getDomainVar());

							auto pa = variables.find(predicateWeWant->getVar())->getPosMap()[pos].getDomainVar();
							for(auto it3=varMap.begin(); it3!=varMap.end();++it3){
								if(it3->second.first.compare(pa) == 0)
									strRhs.append(it3->second.second);	

							}
						}
					}
					strRhs.append(" ^ ");
					continue;
				}

				if(pred.isSingleNegated()){
					strRhs.append("!");
				}
				strRhs.append(pred.getVar());
				strRhs.append("(");
				//If pred.getVar is the same as that of our key
				//Then in that case we make use of localPos to fill variables.
				//Otherwise we just use its own variables

				//The above strat caused a bug. Now always we use its own variables.
				
				//std::set<std::string>::iterator itr;
				//auto itr;
				int pos = 0;
				//Iterate over all the tokens of the predicate
				for(auto &vars : pred.getTokens())
				{
					//auto itr = orphanVarsSet.find(vars);
					auto itr = std::find_if(orphanVarsSet.begin(), orphanVarsSet.end(), [&](const std::pair<std::string, std::string>& val) -> bool{
						return val.first == vars;
					});
					
					if(itr != orphanVarsSet.end())
					{
						strRhs.append(vars).append(",");
					}
					else
					{
						if(domainList.find(vars) != domainList.end()){
							strRhs.append(vars).append(",");
							pos++;
							continue;	
						}

						if(!varMapAssociate[vars].empty()){
							strRhs.append(varMapAssociate[vars]).append(",");	
							pos++;
							continue;
						}
						std::set<Variable>::iterator itrInner = variables.find(Variable(pred.getVar()));
						//Finds domain of the predicate at position pos
						Domain d = (*itrInner).getPosMap().at(pos);
						std::string varType(d.getDomainVar());

						//Check if the value is a constant
						if(isConstant(vars)){
							strRhs.append(vars).append(",");	
						}
						else{
							//find out the domain at position pos of the predicateq pred
							auto pa = variables.find(pred.getVar())->getPosMap()[pos].getDomainVar();
							for(auto it3=varMap.begin(); it3!=varMap.end();++it3){
								if(it3->second.first.compare(pa) == 0){


									if(varMapVarCount[pa] > 1){
										varMapVarCount[pa] = varMapVarCount[pa] - 1;
										continue;
									}
									varMapVarCount[pa] = varMapVarCount[pa] - 1;


									strRhs.append(it3->second.second).append(",");	
									break;
									
								}
							}
							
						}
					}
					pos++;
				}
				
				strRhs = strRhs.substr(0,strRhs.size()-1);
				strRhs.append(")");
				strRhs.append(" ^ ");
				
				bodyVecCount++;
			}
			

			strRhs = strRhs.substr(0,strRhs.size()-3);
			strRhs.append(")");
			if(r.checkOrphan())
			{
				auxPos.second = strRhs.size()-1;
				strRhs.append(")");
			}
			strRhs.append(" v ");
			
			//Add code for aux stuff
			//Aux variables needed only in case of orphans
			if(r.checkOrphan())
			{
				std::string auxVar;
				std::map<std::string,std::string> auxDeclMap;
				
				//First add declaration
				auxVar.append("aux_").append(key.first).append("_").append(std::to_string(auxCount++));
				std::string auxLhs(auxVar);
				std::string auxRhs(auxVar);
				std::string auxDecl(auxVar);
				
				
				//Figure out domains to be added in aux declaration
				//parse strRhs. Add all variables to auxLhs such that
				// ex: (EXIST t1 (_b=False ^ shoot(t1) ^ next(t1,_c) ^ target(_a,_b,t1)))
				// _b,t1,_c,_a should be added.
				
				auxDecl.append("(");
				auxLhs.append("(");
				
				for(auto &auxDeclVar : varMap)
				{
					auxDecl.append(auxDeclVar.second.first).append(",");
					auxLhs.append(auxDeclVar.second.second).append(",");
				}
				
				for(auto &auxDeclVar : r.getOrphanVars())
				{
					auxDecl.append(auxDeclVar.second).append(",");
					auxLhs.append(auxDeclVar.first).append(",");
				}
				
				auxDecl = auxDecl.substr(0,auxDecl.size()-1);
				auxLhs = auxLhs.substr(0,auxLhs.size()-1);
				
				auxDecl.append(")");
				auxLhs.append(")");
				
				size_t ar1 = static_cast<size_t>(auxPos.first);
				size_t ar2 = static_cast<size_t>(auxPos.second-auxPos.first);
				auxRhs = strRhs.substr(ar1, ar2);
				
				ar1 = static_cast<size_t>(auxPos.first);
				ar2 = static_cast<size_t>(auxPos.second-auxPos.first);
				strRhs.replace(ar1,ar2, auxLhs);
				
				
				std::cout << auxDecl << "\n";
				std::cout << auxLhs << " <=> " << auxRhs << ".\n";
			}
		}
		
		strRhs = strRhs.substr(0,strRhs.size()-3);
		// std::cout<<strLhs<<" => "<<strRhs<<"."<<std::endl;

		std::string completedStr = completedLiterals[strLhs];
		if(completedStr.empty())
			completedLiterals[strLhs] = strRhs;
		else
			completedLiterals[strLhs] = completedLiterals[strLhs] + " v " + strRhs;
	}

}

void Tree::completeFacts(){
	//Fact completion
	
	/* Create vector of deduplicated entries: */
	std::vector<std::pair<std::string,FactCompletion>> keys_dedup;
	std::unique_copy(std::begin(facts),
				  std::end(facts),
					std::back_inserter(keys_dedup),
				  [](const std::pair<std::string,FactCompletion> &entry1,
					 const std::pair<std::string,FactCompletion> &entry2) {
					   return (entry1.first == entry2.first);
				   }
				 );

	// All unique keys are in keys_dedup now.
	for(auto &key : keys_dedup){
		std::string strLhs;
		std::string strRhs; 
		std::pair <std::multimap<std::string,FactCompletion>::iterator, std::multimap<std::string, FactCompletion>::iterator> ret;
		ret = facts.equal_range(key.first);
		
		int count = 0;
		FactCompletion f;
		for (std::multimap<std::string,FactCompletion>::iterator it=ret.first; it!=ret.second; ++it){
			//it.second are FactCompletions
			f = it->second;
			std::vector<std::string> v = f.getHead().getTokens();
			count = 0;
			strRhs.append("(");
			for(auto &str : v){
				if(isConstant(str)){
					strRhs.append(uniqueVars[count++]);
					strRhs.append("=");
					strRhs.append(str);
					strRhs.append(" ^ ");		
				}
				else{
					count++;
				}
			}
			strRhs = strRhs.substr(0,strRhs.size()-3);
			strRhs.append(")");
			//if strRhs = "()" it did not find anything
			if(strRhs.size() == 2){
				strRhs.clear();
			}
			else{
				strRhs.append(" v ");
			}
		}
		//if there is no strRhs the this rule was not supposed to be completed
		//Go to next rule.
		if(strRhs.size() == 0) continue;
		strRhs = strRhs.substr(0,strRhs.size()-3);
		strLhs.append(key.first);

		std::set<Variable>::iterator itrV = variables.find(key.first);
		if(itrV != variables.end()) itrV->setCompleted();

		strLhs.append("(");
		count=0;
		for(unsigned int i=0;i<f.getHead().getTokens().size();i++)
			strLhs.append(uniqueVars[count++]).append(",");
		strLhs = strLhs.substr(0,strLhs.size()-1);
		strLhs.append(")");

		std::string completedStr = completedLiterals[strLhs];
		if(completedStr.empty())
			completedLiterals[strLhs] = strRhs;
		else
			completedLiterals[strLhs] = completedLiterals[strLhs] + " v " + strRhs;
		// std::cout<<strLhs<<" => "<<strRhs<<"."<<std::endl;
	}
}

void Tree::completeDeclarations(){
	for(auto itr = completedLiterals.begin(); itr != completedLiterals.end() ; ++itr)
		std::cout << itr->first << " => " << itr->second << ".\n"; 

	for(auto itr = variables.begin(); itr != variables.end(); ++itr){

		if (!itr->isCompleted()){
			//There is a declaration that is not completed. Complete it
			std::string str;
			str += "!";
			str += itr->getVar();
			str += "(";

			for(unsigned int i=0;i<itr->getPosMap().size();++i){
				str += uniqueVars[i];
				str += ",";
			}
			str = str.substr(0, str.size()-1);
			str += ").\n";
			std::cout<<str;
		}
	}
}