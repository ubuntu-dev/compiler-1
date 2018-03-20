/*
 * RuleExtractor.cpp
 * Created on: Mar 17, 2018
 * Author: Amr Hendy
 */

#include "RuleExtractor.h"
#include <iostream>

using namespace std;

RuleExtractor::RuleExtractor() {
	keyWordRule = KeyWordRule();
	punctuationRule = PunctuationRule();
	regularRule = RegularRule();
}

RuleExtractor::~RuleExtractor() {
	// TODO Auto-generated destructor stub
}

void RuleExtractor::extractRule(string rule){
	string rule_trimmed = removeSpaces(rule);
	if(rule_trimmed[0] == '{'){
		keyWordRule.appendkeyWords(rule);
	}
	else if(rule_trimmed[0] == '['){
		punctuationRule.appendPunctuations(rule);
	}
	else{
		int colon_index = rule_trimmed.find(':');
		int equal_index = rule_trimmed.find('=');
		if(colon_index != string::npos && equal_index != string::npos){
			if(equal_index < colon_index){
				regularRule.parseRegularDefinition(rule);
			}
			else{
				regularRule.parseRegularExpression(rule);
			}
		}
		else if(colon_index != string::npos){
			regularRule.parseRegularExpression(rule);
		}
		else if(equal_index != string::npos){
			regularRule.parseRegularDefinition(rule);
		}
	}
}


vector<Rule> RuleExtractor::getAllRules(){
	vector<Rule> all;

	/*
	vector<string> v1 = keyWordRule.keyWords;
	vector<string> v2 = punctuationRule.punctuations;
	vector<pair<string, string> > v3 = regularRule.regularExpressions;
	cout << "KEYWORDS\n";
	for(string s : v1)cout << removeSpaces(s) << endl;
	cout << "==============================================\n";

	cout << "PUNCUTATIONS\n";
	for(string s : v2)cout << removeSpaces(s) << endl;
	cout << "==============================================\n";


	cout << "REGULAR EXPRESSIONS\n";
	for(pair<string,string> p : v3)cout << removeSpaces(p.first) << "  =  " << removeSpaces(p.second) << endl;
	cout << "==============================================\n";

	*/

	for(pair<string, int> keyWord : keyWordRule.keyWords){
		keyWord.first = removeSpaces(keyWord.first);
		Rule rule("T_" + keyWord.first, keyWord.first, keyWord.second);
		all.push_back(rule);
		rule.toPostfix();
	}

	for(pair<string, int> punc : punctuationRule.punctuations){
		punc.first = removeSpaces(punc.first);
		Rule rule("T_" + punc.first, punc.first, punc.second);
		all.push_back(rule);
		rule.toPostfix();
	}

	for(pair<pair<string,string>, int> p : regularRule.regularExpressions){
		p.first.first = removeSpaces(p.first.first);
		p.first.second = removeSpaces(p.first.second);
		Rule rule(p.first.first, p.first.second, p.second);
		all.push_back(rule);
		rule.toPostfix();
	}
	return all;
}

string RuleExtractor::removeSpaces(string str){
	string trimmedStr = "";
	for(int index = 0; index < str.length(); index++){
		if(str[index] != ' '){
			trimmedStr += str[index];
		}
	}
	return trimmedStr;
}

