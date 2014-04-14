#include <cstdlib>
#include <cassert>
#include "Component.h"
using namespace std;

struct Register : public Component
{
    Register(char init);
    //  Evaluates the register.
    virtual vector <logic_t> \
        evaluateTo(vector<logic_t> Inputs);
    // Creates VHDL Entity representing the register
    virtual string compileToEntity() = 0;
    // I'm so tired, I'll do this another day.
    // leaving this here as motivation to look at this code later...
    // (it's an embarassing comment so I have to at least open the file to
    // remove it)
    char val;
};

