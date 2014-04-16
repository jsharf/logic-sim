#include "Register.h"

Register::Register(char init) : \
    Component(8, 8);
{
    val = init; 
}

Register::evaluateTo(vector<logic_t> Inputs)
{

}

Register::compileToEntity()
{
    // output register VHDL
    string nl = "\n";
    string compile =  \
    "entity register is" + nl + \
    "port(val : in std_logic_vector (7 DOWNTO 0);" + nl + \
    "     output : out std_logic_vector ( 7 DOWNTO 0));" + nl + \
    "end register;" + nl;
    cout << " 
}
