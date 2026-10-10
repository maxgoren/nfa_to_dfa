#include "dfa.hpp"
#include "powerset.hpp"
#include <queue>
#include <set>
#include <algorithm>

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
            bool negate = false;
            string tmp = "";
            if (expr[j] == '^') {
                negate = true;
            }
            while (expr[j] != ']') {
                if (expr[j+1] == '-') {
                    char lo = expr[j], hi = expr[j+2];
                    for (char m = lo; m <= hi; m++)
                        tmp.push_back(m);
                    j+=2;
                } else {
                    tmp.push_back(expr[j]);
                    j++;
                }
            }
            if (negate) {
                for (char c = (char)15; c <= '~'; c++) {
                    if (tmp.find(c) == tmp.npos)
                        aleph.insert(c);
                }
            } else {
                for (char c : tmp)
                    aleph.insert(c);
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
    return minimize(dfa, expr, aleph);
}

int map_old_dest(vector<set<int>>& groups, int old) {
    bool breakout = false;
    for (int i = 0; i < groups.size(); i++) {
        for (auto j : groups[i]) {
            if (j == old) {
                return i;
            }
        }
    }
    return -1;
}

DFA minimize(DFA& dfa, string expr, set<char>& alphabet) {
    typedef int STATE;
    typedef set<STATE> GROUP;
    vector<GROUP> groups= {{}, {}};
    for (int i = 0; i < dfa.num_states; i++) {
        if (dfa.states[i]->accepts) {
            groups[1].insert(i);
        } else {
            groups[0].insert(i);
        }
    }
    bool didchange = false;
    do {
        didchange = false;
        for (GROUP& group : groups) {
            GROUP ng;
            auto it = group.begin();
            int first = *it++;
            int next = it != group.end() ? *it++:0;
            while (next != 0) {
                for (char c : alphabet) {
                    STATE gtf = -1, gtn = -1;
                    if (dfa.states[first]->trans.find(c) != dfa.states[first]->trans.end()) {
                        gtf = dfa.states[first]->trans[c]->label;
                    }
                    if (dfa.states[next]->trans.find(c) != dfa.states[next]->trans.end()) {
                        gtn = dfa.states[next]->trans[c]->label;
                    }
                    if (gtf != gtn) {
                        ng.insert(next);
                    }
                }
                next = it != group.end() ? *it:0;
                it++;
            }
            if (!ng.empty()) {
                for (STATE s : ng) {
                    group.erase(s);
                }
                groups.push_back(ng);
                didchange = true;
                break;
            } else {
                didchange = false;
            }
        }
    } while (didchange);
    return rebuildMinimal(dfa, groups, alphabet);
}

DFA rebuildMinimal(DFA& dfa, vector<set<int>>& groups, set<char>& alphabet) {
    DFA result;
    result.num_states = groups.size();
    for (int i = 0; i < result.num_states; i++) {
        result.states[i] = new DFAState();
        result.states[i]->label = i;
        result.states[i]->accepts = false;
    }
    for (int i = 0; i < result.num_states; i++) {
        int rep = *groups[i].begin();
        for (char c : alphabet) {
            if (dfa.states[rep]->trans.count(c)) {
                int ndst = map_old_dest(groups, dfa.states[rep]->trans[c]->label);
                if (ndst != -1) {
                    cout<<"Add transition "<<i<<" -> "<<c<<" -> "<<ndst<<endl;
                    result.states[i]->trans[c] = result.states[ndst];
                }
            }
        }
        for (int os : groups[i]) {
            if (dfa.states[os]->accepts) {
                result.states[i]->accepts = true;
                break;
            }
        }
    }
    for (int i = 0; i < dfa.num_states; i++) {
        delete dfa.states[i];
    }
    return result;
}