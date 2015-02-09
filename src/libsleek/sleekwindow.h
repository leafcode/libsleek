#ifndef SLEEKWINDOW_H
#define SLEEKWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QObject>
#include "sleekwindow_global.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#include "qwinwidget.h"
#include "sleekborderless.h"

class LIBSLEEKSHARED_EXPORT SleekWindow : public QObject
{
    Q_OBJECT

    enum class Style : DWORD
    {
      windowed = ( WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN | WS_SYSMENU  ),
      aero_borderless = ( WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN ),
      aero_borderless_no_resize = ( WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN )
    };

public:
    SleekWindow(QApplication *app, QString title, SleekWindow *parent = 0);
    ~SleekWindow();

    QWidget *getMainPanel();
    void show();
    void close();

    void initializePosition();
    void hide();
    bool isVisible();
    void toggleBorderless();
    void toggleShadow();
    void toggleResizeable();
    void toggleMinimize();
    bool isResizeable();

    void setSize(const int width, const int height);
    void setMinimumSize( const int width, const int height );
    bool isSetMinimumSize();
    void removeMinimumSize();
    int getMinimumHeight();
    int getMinimumWidth();

    void setMaximumSize( const int width, const int height );
    bool isSetMaximumSize();
    int getMaximumHeight();
    int getMaximumWidth();
    void removeMaximumSize();

    bool getBorderless();
    bool getBorderlessResizable();

    void centerPrimaryScreen();
    void centerParent();

    SleekBorderless* getSleekBorderless();
    HWND getHandle();

protected:
    QApplication* _app;

private:
    QWidget* _mainPanel;
    SleekBorderless* _sleekBorderless;

    HWND _parenthWnd;
    HWND _hWnd;
    HINSTANCE _hInstance;
    bool _closed;
    bool _visible;
    bool _borderless;
    bool _aeroShadow;
    bool _borderlessResizeable;
    bool _minimizeVisible;
    bool _isFirstTime;

    struct sizeType {
      sizeType() : required( false ), width( 0 ), height( 0 ) {}
      bool required;
      int width;
      int height;
    };

    sizeType _minimumSize;
    sizeType _maximumSize;
};

#else

class LIBSLEEKSHARED_EXPORT SleekWindow : public QObject
{
    Q_OBJECT

public:
    SleekWindow(QApplication *app, QString title, SleekWindow *parent = 0);
    ~SleekWindow();

    QWidget* getMainPanel();
    void show();
    void close();
    void toggleResizeable();
    void setMinimumSize(const int width, const int height);
    void setMaximumSize(const int width, const int height);
    void centerPrimaryScreen();
    void centerParent();

protected:
    QApplication* _app;

private:
    QWidget* _mainPanel;
};

#endif

#endif // SLEEKWINDOW_H
