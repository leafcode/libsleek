#ifndef SLEEKWINDOWCLASS_H
#define SLEEKWINDOWCLASS_H

#include "Windows.h"
#include <QString>

class SleekWindowClass
{
public:
    SleekWindowClass();
    ~SleekWindowClass();

    void setBackgroundBrush(HWND hWnd, QString theme);
    HINSTANCE getHInstance();

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

private:
    HBRUSH _ivoryBrush;
    HBRUSH _graphiteBrush;
    HINSTANCE _hInstance;
};

#endif // SLEEKWINDOWCLASS_H
