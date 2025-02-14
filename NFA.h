#define NFA_H
#ifdef NFA_H
#include <set>
#include <map>
#include <stack>
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
        void incrementFinalState(int amountToUpdate);
        void updateKeysAndValues(int amount);
        map <int, map<char, set <int>> > getGraph();
        void setGraph(map <int, map<char, set <int>> > grpah);
        char getSymbol(int key);
        void setFinalState(int newFinalState);

    private:
        map <int, map<char, set <int>> > graph;
        set<char> alphabet;
        int initialState;
        set<int> finalStates;
};

#endif