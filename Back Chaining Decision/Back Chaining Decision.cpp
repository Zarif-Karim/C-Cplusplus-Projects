#include <iostream>
#include <string>
#include <unordered_map>

#define uM(n,d) unordered_map<n,d>

using namespace std;

#include "Knowledge Base.h"

/*
testcase 1:

AvB=>E
A^B=>D
D^E=>F
B^E=>F
A
B
C

Prove F? (yes) E? (yes)
D? (yes) P? (no)

testcase 2:

A^B^C^D=>F
BvEvG=>F
H^I=>A
J^K=>B
UvTvW=>J
I^J^T=>P
I^J^F=>Q
H
I
K
D
W
C

Prove F? (yes) A? (yes) B? (yes)
J? (yes) P? (no) Q? (yes)


testcase 3:

a^b=>c
cvd=>f
fvgvhvp=>x
x^y=>z
a
b
y
%


prove z? (yes)

*/

bool backChainingDecision(char g, KnowledgeBase kb) 
{
        auto r = kb.findKey(g);
        if (r == kb.end()) return false;
        if (r->second.size() == 0) return true;

        bool isAnd = r->second.begin()->second == '^' ? true : false;
        for (auto i = r->second.begin(); i != r->second.end(); ++i)
        {
                bool bcd = backChainingDecision(i->first, kb);
                if (isAnd && !bcd) return false;
                if (!isAnd && bcd) break;
        }

        return true;
}

int main()
{
        KnowledgeBase test;
        test.printKB();

        char f;
        cout << "Enter % to exit.\n\n";

        while (1)
        {
                cout << "Enter character to find: \n";
                cin >> f;

                if (f == '%') break;

                if (backChainingDecision(f, test)) cout << "(YES)";
                else cout << "(NO)";

                cout << endl << endl;
        }


        cout << "\n\nExiting Program!\n\n";

        return 0;
}