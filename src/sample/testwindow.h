#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include "sleekwindow.h"
#include "ui_testwindow.h"

class TestWindow : public SleekWindow
{
    Q_OBJECT
public:
    TestWindow(QApplication *app, bool isMainWindow = false);
    TestWindow(QApplication *app, SleekWindow *parent = 0);
    ~TestWindow();

public slots:
    void slot_buttonPushed_clicked();
    void slot_buttonSetResult_clicked();

private:
    Ui::TestWindow ui;
    TestWindow* child;
    void connectSignals();
    bool hasParent;
};

#endif // TESTWINDOW_H
