#include "testwindow.h"

TestWindow::TestWindow(QApplication *app, SleekWindow *parent)
    : SleekWindow(app, "TestWindow", parent)
{
    ui.setupUi(getMainPanel());
    if (parent)
        centerParent();
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
    TestWindow* testWindow = new TestWindow(_app, this);
    testWindow->show();
}

