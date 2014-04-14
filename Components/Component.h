#include <cstdlib>
#include <cassert>
#include <vector>
#include <string>
using namespace std;

typedef char logic_t;

struct Component
{
    Component(int nIns, int nOuts);
    virtual ~Component() {}
  
    /*  Evaluates the component for a certain set of inputs.
        Returns outputs. */
    virtual vector <logic_t> \
        evaluateTo(vector<logic_t> Inputs) = 0;
    // Creates VHDL Entity representing this component
    virtual string compileToEntity() = 0;
    // Add a certain component as a VHDL compilation dependency
    
    int nInputs, nOutputs;

};
