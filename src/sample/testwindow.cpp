#include "testwindow.h"

TestWindow::TestWindow(QApplication *app, SleekWindow *parent)
    : SleekWindow(app, "TestWindow", parent), hasParent(false)
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

}

void TestWindow::connectSignals()
{
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slot_buttonPushed()));
}

void TestWindow::slot_buttonPushed()
{
    if (hasParent)
    {
        close();
        return;
    }

    TestWindow* testWindow = new TestWindow(_app, this);
    testWindow->show();
}

