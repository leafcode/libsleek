#include "testwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile stylesheet( ":/themes/graphite.css" );
    if ( stylesheet.open( QFile::ReadOnly ) ) {
        QString styleSheet = stylesheet.readAll();
        a.setStyleSheet( styleSheet );
    }

    TestWindow testW(&a, true);
    testW.show();

    return a.exec();
}
