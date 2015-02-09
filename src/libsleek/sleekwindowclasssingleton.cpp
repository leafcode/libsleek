#include "sleekwindowclasssingleton.h"

SleekWindowClass* SleekWindowClassSingleton::getInstance()
{
    return &_sleekWindowClass;
}

SleekWindowClass SleekWindowClassSingleton::_sleekWindowClass;
