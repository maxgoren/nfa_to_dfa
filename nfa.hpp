#ifndef nfa_hpp
#define nfa_hpp
#include "parse/ast.hpp"
#include <vector>
#include <stack>
#include <map>
#include <set>
using namespace std;

template <class T>
struct Stack : public stack<T> {
    T pop() {
        T ret = stack<T>::top();
        stack<T>::pop();
        return ret;
    }
};

typedef int State;

struct NFAState;

struct Transition {
    char ch;
    bool is_epsilon;
    NFAState* dest;
    Transition(NFAState* d) : ch('&'), dest(d), is_epsilon(true) { }
    Transition(char c, NFAState* d) : ch(c), dest(d), is_epsilon(false) { }
    Transition() {
        is_epsilon = false;
        dest = nullptr;
    }
};

struct NFAState {
    State label;
    vector<Transition> transitions;
    NFAState(State st = -1) : label(st) { }
    ~NFAState() {    }
    bool hasTransition(Transition t) {
        for (auto e : transitions) {
            if (e.ch == t.ch && e.dest == t.dest)
                return true;
        }
        return false;
    }
    void addTransition(Transition t) {
        transitions.push_back(t);
    }
};

struct NFA {
    NFAState* start;
    NFAState* accept;
    NFA(NFAState* s = nullptr, NFAState* a = nullptr) : start(s), accept(a) {  }
};

static const int MAX_STATE = 255;
class RECompiler {
    private:
        NFAState* makeState(int label) {
            NFAState* ns = new NFAState();
            ns->label = label;
            return ns;
        }
        int nextLabel() {
            static int label = 0;
            return label++;
        }
        NFA makeAtomic(char ch) {
            NFAState* ns = makeState(nextLabel());
            NFAState* ts = makeState(nextLabel());
            ns->addTransition(Transition(ch, ts));
            return NFA(ns, ts);
        }
        void makeRangeClassTrans(NFAState*& ns, NFAState*& ts, astnode* ast, bool negate, int spos) {
            char lo = ast->children[0]->token.getString()[0], hi = ast->children[1]->token.getString()[0];
            if (negate == false) {
                cout<<"Add em, "<<lo<<" - "<<hi<<endl;
                for (char t = lo; t <= hi; t++)
                    ns->addTransition(Transition(t, ts));
            } else {
                for (char t = (char)14; t < lo; t++)
                    ns->addTransition(Transition(t, ts));
                for (char t = hi+1; t <= '~'; t++)
                    ns->addTransition(Transition(t, ts));
            }   
        }
        void makeRegClassTrans(NFAState*& ns, NFAState*& ts, string ccl, bool negate, int spos) {
            if (negate == false) {
                ns->addTransition(Transition(ccl[spos], ts));
            } else {
                for (char t = (char)14; t <= '~'; t++) {
                    if (ccl.find(t) == std::string::npos && !ns->hasTransition(Transition(t, ts))) {
                        ns->addTransition(Transition(t, ts));
                    }
                }
            }
        }
        NFA makeCharClass(astnode* node) {
            NFAState* ns = makeState(nextLabel());
            NFAState* ts = makeState(nextLabel());
            astnode* itr = node->children[0];
            bool negate = node->children[1] != nullptr && node->children[1]->token.getString() == "^";
            while (itr != nullptr) {
                if (itr->type == RANGE_EXPR) {
                    makeRangeClassTrans(ns, ts, itr, negate, 0);
                } else {
                    makeRegClassTrans(ns, ts, itr->token.getString(), negate, 0);
                }
                itr = itr->next;
            }
            return NFA(ns, ts);
        }

        NFA makeEpsilonAtomic() {
            NFAState* ns = makeState(nextLabel());
            NFAState* ts = makeState(nextLabel());
            ns->addTransition(Transition(ts));
            return NFA(ns, ts);
        }

        NFA makeConcat(NFA a, NFA b) {
            a.accept->addTransition(Transition(b.start));
            a.accept = b.accept;
            return a;
        }

        NFA makeAlternate(NFA a, NFA b) {
            NFAState* ns = makeState(nextLabel());
            NFAState* ts = makeState(nextLabel());
            ns->addTransition(Transition(a.start));
            ns->addTransition(Transition(b.start));
            a.accept->addTransition(Transition(ts));
            b.accept->addTransition(Transition(ts));
            return NFA(ns, ts);
        }
        NFA makeKleene(NFA a, bool must) {
            NFAState* ns = makeState(nextLabel());
            NFAState* ts = makeState(nextLabel());
            ns->addTransition(Transition(a.start));
            if (!must)
                ns->addTransition(Transition(ts));
            a.accept->addTransition(Transition(ts));
            a.accept->addTransition(Transition(a.start));
            return NFA(ns, ts);
        }

        NFA makeZeorOrOne(NFA a) {
            return makeAlternate(a, makeEpsilonAtomic());
        }


        Stack<NFA> st;
        void trav(astnode* node) {
            if (node != nullptr) {
                if (node->type == CONST_EXPR) {
                    //cout<<"Making Character State: "<<node->c<<endl;
                    st.push(makeAtomic(node->token.getString()[0]));
                } else {
                    //cout<<"Building Operator Machine: "<<node->c<<endl;
                    switch (node->token.getString()[0]) {
                        case '|': {
                            trav(node->children[0]);
                            trav(node->children[1]);
                            NFA rhs = st.pop();
                            NFA lhs = st.pop();
                            st.push(makeAlternate(lhs, rhs));
                        } break;
                        case '@': {
                            trav(node->children[0]);
                            trav(node->children[1]);
                            NFA rhs = st.pop();
                            NFA lhs = st.pop();
                            st.push(makeConcat(lhs, rhs));
                        } break;
                        case '*': {
                            trav(node->children[0]);
                            NFA lhs = st.pop();
                            st.push(makeKleene(lhs, false));
                        } break;
                        case '+': {
                            trav(node->children[0]);
                            NFA lhs = st.pop();
                            st.push(makeKleene(lhs, true));
                        } break;
                        case '?': {
                            trav(node->children[0]);
                            NFA lhs = st.pop();
                            st.push(makeZeorOrOne(lhs));
                        } break;
                        case '[': {
                            st.push(makeCharClass(node));
                        } break;
                        default:
                            break;
                    }
                }
            }
        }
    public:
        RECompiler() {

        }
        NFA compile(astnode* node) {
            trav(node);
            return st.pop();
        }
};

#endif