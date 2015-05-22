#include "testwindow.h"
#include <QDebug>

TestWindow::TestWindow(QApplication *app, bool isMainWindow)
    : SleekWindow(app, QString("TestWindow"), isMainWindow), hasParent(false), child(NULL)
{
    ui.setupUi(getMainPanel());
    centerPrimaryScreen();
    connectSignals();
}

TestWindow::TestWindow(QApplication *app, SleekWindow *parent)
    : SleekWindow(app, QString("TestWindow"), parent), hasParent(parent), child(NULL)
{
    ui.setupUi(getMainPanel());
    if (parent)
    {
        centerParent();
        hasParent = true;
    }
    else
        centerPrimaryScreen();
    connectSignals();
}

TestWindow::~TestWindow()
{
    qDebug() << "TestWindow: DESTRUCT";
}

void TestWindow::connectSignals()
{
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slot_buttonPushed()));
}

void TestWindow::slot_buttonPushed()
{
    child = new TestWindow(_app, this);
    qDebug() << child->exec();
    delete child;
}

