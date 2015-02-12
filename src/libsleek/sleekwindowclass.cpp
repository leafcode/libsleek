#include "sleekwindowclass.h"
#include "sleekwindow.h"
#include "windowsx.h"

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QFileInfo>
#include <QDebug>

SleekWindowClass::SleekWindowClass() :
    _ivoryBrush(CreateSolidBrush(RGB(226,226,226))),
    _graphiteBrush(CreateSolidBrush(RGB(51,51,51))),
    _hInstance( GetModuleHandle( NULL ) )
{
    QSettings settings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);
    QString theme = settings.value("theme").toString();

    WNDCLASSEX wcx = { 0 };
    wcx.cbSize = sizeof( WNDCLASSEX );
    wcx.style = CS_HREDRAW | CS_VREDRAW;
    wcx.hInstance = _hInstance;
    wcx.lpfnWndProc = WndProc;
    wcx.cbClsExtra	= 0;
    wcx.cbWndExtra	= 0;
    wcx.lpszClassName = L"SleekWindowClass";

    if (theme == "graphite")
        wcx.hbrBackground = _graphiteBrush;
    else if (theme == "ivory")
        wcx.hbrBackground = _ivoryBrush;
    else
        wcx.hbrBackground = _graphiteBrush;

    wcx.hCursor = LoadCursor( _hInstance, IDC_ARROW );
    wcx.hIconSm = NULL;
    wcx.hIcon = LoadIcon(_hInstance, L"IDI_ICON1");
    RegisterClassEx( &wcx );
    if ( FAILED( RegisterClassEx( &wcx ) ) ) throw std::runtime_error( "Couldn't register window class" );
}

SleekWindowClass::~SleekWindowClass()
{
    DeleteObject(_graphiteBrush);
    DeleteObject(_ivoryBrush);
    UnregisterClass(L"SleekWindowClass", _hInstance);
}

void SleekWindowClass::setBackgroundBrush(HWND hWnd, QString theme)
{
    if (theme == "graphite")
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND , (LONG)_graphiteBrush);
    else if (theme == "ivory")
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND , (LONG)_ivoryBrush);
}

HINSTANCE SleekWindowClass::getHInstance()
{
    return _hInstance;
}

HDC hdc;
PAINTSTRUCT ps;

LRESULT CALLBACK SleekWindowClass::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    SleekWindow *win = reinterpret_cast<SleekWindow*>( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
    if ( !win ) return DefWindowProc( hWnd, message, wParam, lParam );

    QWidget *window = win->getMainPanel();

    switch ( message ) {
    case WM_DESTROY: {
        win->close();
        break;
    }
    case WM_KEYDOWN: {
        switch ( wParam ) {
        case VK_F5: {
            qDebug() << window->childAt(window->mapFromGlobal(QCursor::pos()));
            break;
        }
        case VK_F6: {
            win->toggleShadow();
            win->toggleBorderless();
            SetFocus( (HWND)window->winId() );
            break;
        }
        case VK_F7: {
            win->toggleShadow();
            break;
        }
        }

        if ( wParam != VK_TAB ) return DefWindowProc( hWnd, message, wParam, lParam );

        SetFocus( (HWND)window->winId() );
        break;
    }

        // ALT + SPACE or F10 system menu
    case WM_SYSCOMMAND: {
        if ( wParam == SC_KEYMENU ) {
            RECT winrect;
            GetWindowRect( hWnd, &winrect );
            TrackPopupMenu( GetSystemMenu( hWnd, false ), TPM_TOPALIGN | TPM_LEFTALIGN, winrect.left + 5, winrect.top + 5, 0, hWnd, NULL);
            break;
        }
        else
        {
            return DefWindowProc( hWnd, message, wParam, lParam );
        }
    }

    case WM_SETFOCUS: {
        QString str( "Got focus" );
        QWidget *widget = QWidget::find( ( WId )HWND( wParam ) );
        if ( widget )
            str += QString( " from %1 (%2)" ).arg( widget->objectName() ).arg(widget->metaObject()->className() );
        str += "\n";
        OutputDebugStringA( str.toLocal8Bit().data() );
        break;
    }

    case WM_NCCALCSIZE: {
        //this kills the window frame and title bar we added with
        //WS_THICKFRAME and WS_CAPTION
        if (win->getBorderless()) {
            return 0;
        }
        break;
    }

    case WM_KILLFOCUS: {
        QString str( "Lost focus" );
        QWidget *widget = QWidget::find( (WId)HWND( wParam ) );
        if ( widget )
            str += QString( " to %1 (%2)" ).arg( widget->objectName() ).arg(widget->metaObject()->className() );
        str += "\n";

        OutputDebugStringA( str.toLocal8Bit().data() );
        break;
    }
    case WM_NCHITTEST: {
        if ( win->getBorderless() )
        {
            if ( win->getBorderlessResizable() )
            {
                const LONG borderWidth = 5; //in pixels
                RECT winrect;
                GetWindowRect(hWnd, &winrect);
                long x = GET_X_LPARAM( lParam );
                long y = GET_Y_LPARAM( lParam );

                //bottom left corner
                if ( x >= winrect.left && x < winrect.left + borderWidth + 6 &&
                     y < winrect.bottom && y >= winrect.bottom - borderWidth - 6 )
                {
                    return HTBOTTOMLEFT;
                }
                //bottom right corner
                if ( x < winrect.right && x >= winrect.right - borderWidth - 6 &&
                     y < winrect.bottom && y >= winrect.bottom - borderWidth - 6 )
                {
                    return HTBOTTOMRIGHT;
                }
                //top left corner
                if ( x >= winrect.left && x < winrect.left + borderWidth + 6 &&
                     y >= winrect.top && y < winrect.top + borderWidth + 6 )
                {
                    return HTTOPLEFT;
                }
                //top right corner
                if ( x < winrect.right && x >= winrect.right - borderWidth - 6 &&
                     y >= winrect.top && y < winrect.top + borderWidth + 6 )
                {
                    return HTTOPRIGHT;
                }
                //left border
                if ( x >= winrect.left && x < winrect.left + borderWidth )
                {
                    return HTLEFT;
                }
                //right border
                if ( x < winrect.right && x >= winrect.right - borderWidth )
                {
                    return HTRIGHT;
                }
                //bottom border
                if ( y < winrect.bottom && y >= winrect.bottom - borderWidth )
                {
                    return HTBOTTOM;
                }
                //top border
                if ( y >= winrect.top && y < winrect.top + borderWidth )
                {
                    return HTTOP;
                }
            }
        }
    }

    case WM_SIZE: {
        RECT winrect;
        GetClientRect( hWnd, &winrect );

        WINDOWPLACEMENT wp;
        wp.length = sizeof( WINDOWPLACEMENT );
        GetWindowPlacement( hWnd, &wp );
        if ( wp.showCmd == SW_MAXIMIZE ) {
            QPushButton* pushButtonMaximize = win->getSleekBorderless()->findChild<QPushButton*>( "pushButtonMaximize" );
            pushButtonMaximize->setStyleSheet( "#pushButtonMaximize {image: url(:/icons/header/Restore.png);} #pushButtonMaximize:hover { image: url(:/icons/header/RestoreHover.png); }" );
            win->getSleekBorderless()->setGeometry( 8, 8, winrect.right - 16, winrect.bottom - 16);
        } else {
            QPushButton* pushButtonMaximize = win->getSleekBorderless()->findChild<QPushButton*>( "pushButtonMaximize" );
            pushButtonMaximize->setStyleSheet( "#pushButtonMaximize {image: url(:/icons/header/Maximize.png);} #pushButtonMaximize:hover { image: url(:/icons/header/MaximizeHover.png); }" );
            win->getSleekBorderless()->setGeometry( 0, 0, winrect.right, winrect.bottom);
        }
        break;
    }

    case WM_GETMINMAXINFO: {
        MINMAXINFO* minMaxInfo = ( MINMAXINFO* )lParam;
        if ( win->isSetMinimumSize() ) {
            minMaxInfo->ptMinTrackSize.x = win->getMinimumWidth();
            minMaxInfo->ptMinTrackSize.y = win->getMinimumHeight();
        }

        if ( win->isSetMaximumSize() ) {
            minMaxInfo->ptMaxTrackSize.x = win->getMaximumWidth();
            minMaxInfo->ptMaxTrackSize.y = win->getMaximumHeight();
            minMaxInfo->ptMaxSize.x = win->getMaximumWidth();
            minMaxInfo->ptMaxSize.y = win->getMaximumHeight();
        }
        break;
    }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

