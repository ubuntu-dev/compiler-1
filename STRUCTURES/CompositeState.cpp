#include "CompositeState.h"
#include <iostream>
#include "../GENERATORS/NumberGenerator.h"


CompositeState::CompositeState() {
	this -> id = -1 ;
}

CompositeState::CompositeState(vector<State> states) {
	for (State s : states)
		add_state(s) ;
}

CompositeState::~CompositeState() {
	this->states.clear() ;
}

int
CompositeState::get_size(){
	return this -> states.size() ;
}

bool
CompositeState::contains (State to_find) {
	return this -> states.count(to_find) ;
}

void
CompositeState::add_state(State new_state) {
	states.insert(new_state);
}

void
CompositeState::add_states(set<State> new_state){
	for(State s : new_state)
		add_state(s) ;
}

void
CompositeState::add_states(CompositeState new_state){
	for(State s : new_state.get_states())
		add_state(s) ;
}

set<State>
CompositeState::get_states(){
	return this -> states ;
}

CompositeState*
CompositeState::get_transition(char input) {
	CompositeState* result = new CompositeState() ;
	for(State s : states) {
		for(int i=0 ; i < s.size_transition(input) ; i++){
			State* to = s.get_transition(input,i) ;
			result->add_state(*to);
		}
	}
	return result ;
}

CompositeState*
CompositeState::find_equivalent_states(CompositeState start) {

	CompositeState* ret = new CompositeState() ;

	CompositeState* result = start.get_transition('\0') ;

	if(result->get_size() == 0 ){
		ret->add_states(start) ;
		return ret ;
	}

	CompositeState* epis_reach = find_equivalent_states(*result) ;
	epis_reach->add_states(start) ;

	return  epis_reach ;
}


vector<Rule>
CompositeState::get_matched_rules(){
	vector<Rule> rules ;
	for(State s : states) {
		if(s.is_acceptance())
			rules.push_back(s.get_matched_rule()) ;
	}
	return rules ;
}

void
CompositeState::set_start(){
	for(State s : states){
		s.set_start();
		return ;
	}
}

bool
CompositeState::is_acceptance()
{
	if(!rules.empty())
		return true ;
	for(State s : states){
		if(s.is_acceptance()){
			return true;
		}
	}
	return false;
}

bool
CompositeState::is_start(){
	for(State s : states){
		if(s.is_start()){
			return true;
		}
	}
	return false;
}

void
CompositeState::add_rule(Rule r){
	this->rules.push_back(r) ;
}

vector<Rule>
CompositeState::get_rules(){
	if(rules.empty()){
		for(State s : states)
			if(s.is_acceptance() )
				rules.push_back(s.get_matched_rule());
	}
	return this -> rules ;
}

bool
CompositeState::is_empty(){
	return this->get_size() == 0 ;
}

void
CompositeState::set_id(int id){
	this -> id = id ;
}

int
CompositeState::get_id(){
	return this -> id ;
}

bool
CompositeState::operator ==(CompositeState c){
	 for(State s : this -> states){
		 if(!c.contains(s))
			 return false ;
	 }
	 return true ;
}

bool
CompositeState::operator !=(CompositeState c){
	 for(State s : this -> states){
		 if(!c.contains(s))
			 return true ;
	 }
	 return false ;
}


void CompositeState::print(){
	Logger::logger.print_string("\t\tcomp_state{ \n" , Files::log_file) ;
	for(State s : states ){
		s.print() ;
	}
	Logger::logger.print_string("\n\t\t}" , Files::log_file);
}

