#ifndef VHDLPROGRAM_H
#define VHDLPROGRAM_H
#include "Components/Component.h"
#include <vector>
#include <string>

class VHDLProgram
{
    public:
       void compileDependencies(); 
    private:
        vector <Component> dependencies;
        string VHDLEntities;
};

#endif VHDLPROGRAM_H
