#ifndef SLEEKWINDOWCLASSSINGLETON_H
#define SLEEKWINDOWCLASSSINGLETON_H

#include "sleekwindowclass.h"

class SleekWindowClassSingleton
{
public:
    static SleekWindowClass* getInstance();

private:
    static SleekWindowClass _sleekWindowClass;
    SleekWindowClassSingleton();
    SleekWindowClassSingleton(const SleekWindowClassSingleton& src);
    SleekWindowClassSingleton& operator=(const SleekWindowClassSingleton& rhs);
};

#endif // SLEEKWINDOWCLASSSINGLETON_H
