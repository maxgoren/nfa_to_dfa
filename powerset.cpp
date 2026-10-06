#include "powerset.hpp"

set<NFAState*> move(char ch, set<NFAState*> states) {
    set<NFAState*> next;
    for (NFAState* state : states) {
        for (Transition t : state->transitions) {
            if (t.ch == ch || t.ch == '.') {
                if (!t.is_epsilon && next.find(t.dest) == next.end()) {
                    next.insert(t.dest);
                }
            }
        }
    }
    return next;
}

set<NFAState*> e_closure(set<NFAState*> states) {
    set<NFAState*> next = states;
    Stack<NFAState*> st;
    for (auto s : states) {
        st.push(s);
    }
    while (!st.empty()) {
        NFAState* curr = st.pop();
        for (auto t : curr->transitions) {
            if (t.is_epsilon && next.find(t.dest) == next.end()) {
                next.insert(t.dest);
                st.push(t.dest);
            }
        }
    }
    return next;
}