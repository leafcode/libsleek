#include "testwindow.h"
#include <QDebug>

TestWindow::TestWindow(QApplication *app, bool isMainWindow)
    : SleekWindow(app, QString("TestWindow"), isMainWindow),
    hasParent(false)
{
    ui.setupUi(this);
    ui.pushButtonSetResult->setVisible(false);
    centerPrimaryScreen();
    connectSignals();
    app->installEventFilter(this);
}

TestWindow::TestWindow(QApplication *app, SleekWindow *parent)
    : SleekWindow(app, QString("TestWindow"), parent),
    hasParent(parent)
{
    ui.setupUi(this);
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
    //qDebug() << "TestWindow: DESTRUCT";
}

bool TestWindow::eventFilter(QObject* /*object (Disable C4100 warning from VS compiler)*/, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return)
        {
            qDebug() << "Return pressed!";
            return true;
        }
    }
    return false;
}

void TestWindow::connectSignals()
{
    connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slot_buttonPushed_clicked()));
    connect(ui.pushButtonSetResult, SIGNAL(clicked()), this, SLOT(slot_buttonSetResult_clicked()));
}

void TestWindow::slot_buttonPushed_clicked()
{
    auto child = std::make_unique<TestWindow>(_app, this);
    qDebug() << child->exec();
}

void TestWindow::slot_buttonSetResult_clicked()
{
    setResult(true);
}


