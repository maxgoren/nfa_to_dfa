#include "dfa.hpp"
#include "powerset.hpp"
#include <queue>
#include <set>

DFAState* makeDFAState(int label, set<NFAState*>& pos) {
    DFAState* d = new DFAState();
    d->label = label;
    d->positions = pos;
    d->accepts = false;
    return d;
}

set<char> buildAlphabet(string expr) {
    set<char> aleph;
    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (isalpha(c) && !aleph.count(c)) { 
            aleph.insert(c);
        } else if (c == '.' && (i == 0 || expr[i-1] != '\\')) {
            for (int y = 20; y < 128; y++)
                aleph.insert((char)y);
        } else if (c == '[') {
            int j = i+1;
            while (expr[j] != ']') {
                if (expr[j+1] == '-') {
                    char lo = expr[j], hi = expr[j+2];
                    for (char m = lo; m <= hi; m++)
                        aleph.insert(m);
                    j+=2;
                } else {
                    aleph.insert(expr[j]);
                    j++;
                }
            }
            i = j;
        }
    }
    return aleph;
}

bool statesEqual(NFAState* lhs, NFAState* rhs) {
    return lhs->label == rhs->label;
}



DFAState* findStateByPosition(DFA& dfa, set<NFAState*>& next) {
    for (int i = 0; i < dfa.num_states; i++) {
        if (equal(dfa.states[i]->positions.begin(), dfa.states[i]->positions.end(), next.begin(), next.end(), &statesEqual)) {
            return dfa.states[i];
        }
    }
    return nullptr;
}

DFA makeDeterministic(NFA& nfa, string expr) {
    DFA dfa;
    set<NFAState*> ss;
    ss.insert(nfa.start);
    ss = e_closure(ss);
    DFAState* s = makeDFAState(dfa.num_states++, ss);
    dfa.states[s->label] = s;
    queue<DFAState*> fq;
    fq.push(s);
    set<char> aleph = buildAlphabet(expr);
    while (!fq.empty()) {
        DFAState* curr = fq.front(); fq.pop();
        for (char c : aleph) {
            set<NFAState*> next = move(c, curr->positions);
            if (!next.empty()) {
                next = e_closure(next);
                DFAState* p = findStateByPosition(dfa, next);
                if (p == nullptr) {
                    DFAState* n = makeDFAState(dfa.num_states++, next);
                    curr->trans[c] = n;
                    fq.push(n);
                    dfa.states[n->label] = n;
                    cout<<"New: "<<n->label<<"  (";
                    for (auto m : n->positions) {
                        cout<<m->label<<" ";
                    }
                    cout<<")"<<endl;
                } else {
                    curr->trans[c] = p;
                } 
            }
        }
    }
    for (int i = 0; i < dfa.num_states; i++) {
        if (dfa.states[i]->positions.find(nfa.accept) != dfa.states[i]->positions.end()) {
            dfa.states[i]->accepts = true;
            cout<<"Marked "<<i<<" as accepting for "<<nfa.accept->label<<endl;
        }
    }
    return dfa;
}