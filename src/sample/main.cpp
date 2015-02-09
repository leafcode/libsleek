#include "testwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile stylesheet( ":/themes/graphite.css" );
    if ( stylesheet.open( QFile::ReadOnly ) ) {
        QString styleSheet = stylesheet.readAll();
        a.setStyleSheet( styleSheet );
    }

    TestWindow testW(&a);
    testW.show();

    return a.exec();
}
