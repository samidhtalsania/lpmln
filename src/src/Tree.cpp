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
		ret = rules.equal_range(key.first);
		
		//Based on key, from varaibles set find out its domains.
		//Assign a variable to each of the domain of the key.
		//Use this variable in constructing strLhs and strRhs 
		std::set<Variable>::iterator itrV = variables.find(key.first);
		// std::multimap<std::string, std::pair<int, std::string> > varMap;
		std::unordered_multimap<int, std::pair<std::string, std::string> > varMap;
		std::set<std::pair<std::string,std::string>> orphanVarsSet;
		
		int count = 0;
		for(auto &var : itrV->getPosMap()){
			// std::pair<int, std::string> p(var.first,uniqueVars[count++]);
			std::pair<int, std::pair<std::string, std::string>> pa(var.first, std::pair<std::string, std::string>(var.second.getDomainVar(), uniqueVars[count++]));
			// varMap.insert(std::pair<std::string, std::pair<int, std::string>>(var.second.getDomainVar(),p));
			varMap.insert(pa);
			// varMap[var.second.getDomainVar()] = std::pair<int, std::string> (var.first,uniqueVars[count++]);
		}
		
		RuleCompletion r;
		
		
		int auxCount = 0;
		for (std::multimap<std::string,RuleCompletion>::iterator it=ret.first; it!=ret.second; ++it)
		{
			r = it->second;
			
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
			
			for(auto &pred : r.body)
			{
				strRhs.append(pred.getVar());
				strRhs.append("(");
				//If pred.getVar is the same as that of our key
				//Then in that case we make use of localPos to fill variables.
				//Otherwise we just use its own variables
				
				//std::set<std::string>::iterator itr;
				//auto itr;
				int pos = 0;
				for(auto &vars : pred.getTokens())
				{
					//auto itr = orphanVarsSet.find(vars);
					auto itr = std::find_if(orphanVarsSet.begin(), orphanVarsSet.end(), [&](const std::pair<std::string, std::string>& val) -> bool{
						return val.first == vars;
					});
					
					if(pred.getVar().compare(key.first) == 0)
					{
						if(itr != orphanVarsSet.end())
						{
							strRhs.append(vars).append(",");
						}
						
						else
						{
							for(auto &innerVar : varMap)
							{
								if(innerVar.first == pos)
								{
									strRhs.append(innerVar.second.second).append(",");
								}
							}
						}
					}
					else
					{
						if(itr != orphanVarsSet.end())
						{
							strRhs.append(vars).append(",");
						}
						else
						{
							std::set<Variable>::iterator itrInner = variables.find(Variable(pred.getVar()));
							//Finds variable with var=next
							Domain d = (*itrInner).getPosMap().at(pos);
							std::string varType(d.getDomainVar());

							 // p;
							if(isConstant(vars)){
								strRhs.append(vars).append(",");	
							}
							else{
								//find out the domain at position pos of the predicate pred
								auto pa = variables.find(pred.getVar())->getPosMap()[pos].getDomainVar();
								for(auto it3=varMap.begin(); it3!=varMap.end();++it3){
									if(it3->second.first.compare(pa) == 0)
										strRhs.append(it3->second.second).append(",");	
								}
								
							}
						}
					}
					
					pos++;
				}
				
				strRhs = strRhs.substr(0,strRhs.size()-1);
				strRhs.append(")");
				strRhs.append(" ^ ");
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

		std::cout<<strLhs<<" => "<<strRhs<<"."<<std::endl;
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
			std::vector<std::string> v = f.head.getTokens();
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
		strLhs.append("(");
		count=0;
		for(unsigned int i=0;i<f.head.getTokens().size();i++)
			strLhs.append(uniqueVars[count++]).append(",");
		strLhs = strLhs.substr(0,strLhs.size()-1);
		strLhs.append(")");
		std::cout<<strLhs<<" => "<<strRhs<<"."<<std::endl;
	}
}

