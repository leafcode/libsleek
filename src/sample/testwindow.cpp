#include "testwindow.h"
#include <QDebug>

TestWindow::TestWindow(QApplication *app, bool isMainWindow)
    : SleekWindow(app, QString("TestWindow"), isMainWindow),
      hasParent(false)
{
    ui.setupUi(getMainPanel());
    ui.pushButtonSetResult->setVisible(false);
    centerPrimaryScreen();
    connectSignals();
}

TestWindow::TestWindow(QApplication *app, SleekWindow *parent)
    : SleekWindow(app, QString("TestWindow"), parent),
      hasParent(parent)
{
    ui.setupUi(getMainPanel());
    if (parent)
    {
        centerParent();
        hasParent = true;
    }
    else
    {
        centerPrimaryScreen();
    }
    connectSignals();
}

TestWindow::~TestWindow()
{
    qDebug() << "TestWindow: DESTRUCT";
}

void TestWindow::connectSignals()
{
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slot_buttonPushed_clicked()));
    connect(ui.pushButtonSetResult, SIGNAL(clicked()), this, SLOT(slot_buttonSetResult_clicked()));
}

void TestWindow::slot_buttonPushed_clicked()
{
    child = new TestWindow(_app, this);
    qDebug() << child->exec();
    delete child;
}

void TestWindow::slot_buttonSetResult_clicked()
{
    setResult(true);
}


