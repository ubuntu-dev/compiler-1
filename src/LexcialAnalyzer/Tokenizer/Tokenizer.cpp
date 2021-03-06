/*
 * Tokenizer.cpp
 * Created on: Mar 23, 2018
 * Author: Amr Hendy
 */

#include "../../../header/LexcialAnalyzer/Tokenizer/Tokenizer.h"

/* CONSTRUCTOR */
/*********************************************/
Tokenizer::Tokenizer(TransitionTable minimized_dfa_table, string user_program_directory)
{
	/* read user file */
	user_program = FileReader::readUserProgram(user_program_directory);
	/* initialize tokenizer attributes */
	Tokenizer::minimized_dfa_table = minimized_dfa_table;
	current_index = 0;
}


Tokenizer::Tokenizer(){

}

Tokenizer::~Tokenizer() {
	// TODO Auto-generated destructor stub
}


/* INTERFACE FUNCTIONS */
/*********************************************/
Token
Tokenizer::next_token()
{
	/* ignore that chars of errors. */
	set<char> line_breaks = {' ', '\t', '\n'};

	/* initialize helpers */
	CompositeState* current_state = minimized_dfa_table.get_start_state();
	CompositeState* last_acceptance_state;
	int last_acceptance_index = -1;
	int start_index = current_index;

	while(current_index < user_program.size())
	{
		/* read new char into buffer */
		char current_char = user_program.at(current_index);

		/* transition in table according to input char */
		current_state = minimized_dfa_table.find_transition(current_state, current_char);
		/* check current state */
		if(current_state->isNull())
		{
			if(last_acceptance_index != -1){
				string lexeme;
				lexeme = user_program.substr(start_index, last_acceptance_index - start_index + 1);
				current_index = last_acceptance_index + 1;
				vector<Rule> conflicting_rules = last_acceptance_state->get_matched_rules();
				return get_correct_token(conflicting_rules, lexeme);
			}
			else{
				current_index = start_index + 1;
				start_index++;
				if(line_breaks.count(user_program[start_index - 1]) == 0){
					string error_str = "'";
					error_str += user_program[start_index - 1];
					error_str += "'\tError do not match any rules";
					FileWriter::append("output_tokens.txt", error_str);
				}
				continue;
			}
		}

		if(current_state->is_acceptance())
		{
			last_acceptance_state = current_state;
			last_acceptance_index = current_index;
		}
		current_index++;
	}


	if(last_acceptance_index != -1){
		string lexeme;
		lexeme = user_program.substr(start_index, last_acceptance_index - start_index + 1);
		current_index = last_acceptance_index + 1;
		vector<Rule> conflicting_rules = last_acceptance_state->get_matched_rules();
		last_acceptance_index = -1;
		return get_correct_token(conflicting_rules, lexeme);
	}
	else if(start_index >= user_program.size() - 1){
		return Token("INVALID","INVALID","INVALID");
	}
	else{
		current_index = start_index + 1;
		return next_token();
	}
}



Token
Tokenizer::get_correct_token(vector<Rule> conflicting_rules, string lexeme)
{
	Token result = Token("", "", "");
	/* the rule with the min priority will be the matched rule. */
	int min_priority = 1000000;
	for(Rule rule : conflicting_rules)
	{
		if(rule.getPriority() < min_priority){
			min_priority = rule.getPriority();
			result = Token(rule.getRuleName(), rule.getRulePattern(), lexeme);
		}
	}
	return result;
}
