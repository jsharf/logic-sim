#include "VHDLProgram.h"

VHDLProgram::compileDependencies()
{
    int len = dependencies.size();
    string nl = "\n";
    for (int i=0; i<len; i++)
    {
        string vhdl = VHDLdependencies[i].compileToEntity();
        VHDLEntities += vhdl + nl;
    }
}
