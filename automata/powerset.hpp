#ifndef powerset_hpp
#define powerset_hpp
#include <set>
#include "nfa.hpp"
using namespace std;

set<NFAState*> move(char ch, set<NFAState*> states);
set<NFAState*> e_closure(set<NFAState*> states);

#endif