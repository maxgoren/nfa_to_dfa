#ifndef dfa_hpp
#define dfa_hpp
#include <set>
#include <map>
#include "nfa.hpp"
using namespace std;

struct DFAState {
    int label;
    bool accepts;
    set<NFAState*> positions;
    map<char, DFAState*> trans;
    DFAState() { }
};

struct DFA {
    map<int, DFAState*> states;
    int num_states;
    DFA() {
        num_states = 0;
    }
};

DFA makeDeterministic(NFA& nfa, string expr);

DFA minimize(DFA& dfa, string expr, set<char>& alphabet);


#endif