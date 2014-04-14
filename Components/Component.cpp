#include "Gate.h"

/** Create new Component. Component is pure virtual so this constructor
    should never be directly called. */
Component::Component(int nIns, int nOuts) : \
    nInputs(nIns), nOutputs(nOuts)
{
    return 0;
}
