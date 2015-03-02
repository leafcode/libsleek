#ifndef SLEEKWINDOWCLASS_H
#define SLEEKWINDOWCLASS_H

#include "Windows.h"
#include <QString>
#include "libsleek_global.h"

class LIBSLEEKSHARED_EXPORT SleekWindowClass
{
public:
    static SleekWindowClass& Instance() {
        static SleekWindowClass sleekWindowClass;
        return sleekWindowClass;
    }

    void setBackgroundBrush(HWND hWnd, QString theme);
    HINSTANCE getHInstance();

    static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

    SleekWindowClass();
    SleekWindowClass(SleekWindowClass const&);
    SleekWindowClass& operator=(SleekWindowClass const&);
    ~SleekWindowClass();
private:

    HBRUSH _ivoryBrush;
    HBRUSH _graphiteBrush;
    HINSTANCE _hInstance;
};

#endif // SLEEKWINDOWCLASS_H
