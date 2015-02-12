#ifndef SLEEKWINDOWCLASS_H
#define SLEEKWINDOWCLASS_H

#include "Windows.h"
#include <QString>

class SleekWindowClass
{
public:
    static SleekWindowClass& Instance() {
        static SleekWindowClass sleekWindowClass;
        return sleekWindowClass;
    }

    void setBackgroundBrush(HWND hWnd, QString theme);
    HINSTANCE getHInstance();

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

private:
    SleekWindowClass();
    SleekWindowClass(SleekWindowClass const&);
    SleekWindowClass& operator=(SleekWindowClass const&);
    ~SleekWindowClass();

    HBRUSH _ivoryBrush;
    HBRUSH _graphiteBrush;
    HINSTANCE _hInstance;
};

#endif // SLEEKWINDOWCLASS_H
