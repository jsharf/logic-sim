#include "Register.h"

Register::Register(char init) : \
    Component(8, 8);
{
    val = init; 
}
