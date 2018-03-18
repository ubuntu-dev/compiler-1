#ifndef DFA_GENERATOR_H_  /* Include guard */
#define DFA_GENERATOR_H_

/* IMPORT LIBRARIES */
/*********************************************/
#include "Machine"
#include "Transition_Table.h"

/* CLASS DEFINITIONS */
/*********************************************/
class DFA_Generator
{
	private:
	/* attributes */
	Machine nfa_machine;
		
	public:
	/* constructor */
    DFA_Generator(Machine nfa_machine);
    ~DFA_Generator(void);

    /* interface functions */
    Transition_Table generate_minimized_dfa_table(void);

};


#endif