#define NFA_H
#ifdef NFA_H
#include <set>
#include <map>
#include <stack>
#include <string>
using std:: set;
using std:: map;

class NFA{
    public:
        NFA(set<char> a, int initial, set<int> final);
        void addTransition(int start, set<int> statesToGoTo, char symbol);
        set<int> computeEClosure(set<int> states);
        void print();
        set<char> getAlphabet();
        set<int> getFinalStates();
        int getInitialState();
        void setInitialState(int newState);
        void setAlphabet(set<char> newAlphabet);
        void incrementFinalState(int amountToUpdate);
        void updateKeysAndValues(int amount);
        map <int, map<char, set <int>> > getGraph();
        void setGraph(map <int, map<char, set <int>> > grpah);
        char getSymbol(int key);
        void setFinalState(int newFinalStates);
        void finalSet(set<int>finalStateSet);
        NFA reToNfa(std::string re);
        NFA unionFunction(NFA &nfaOne, NFA nfaTwo, std::stack<char>symbols,int &count);
        NFA concatFuntion(NFA &nfaOne, NFA nfaTwo, std::stack<char> symbols,int &count);
        NFA kleeneStarFunction(NFA &nfaOne, std::stack<char> symbols,int &count);
        int count;
        set<int> getDestinationState(int key);
        bool containsFinalState(set<int>states);

    private:
        map <int, map<char, set <int>> > graph;
        set<char> alphabet;
        int initialState;
        set<int> finalStates;
};


#endif