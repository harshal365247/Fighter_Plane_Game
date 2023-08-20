#include <QApplication>
#include <QFile>

#include "containerwidget.h"

containerWidget *containerWidgetObj;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    containerWidgetObj = new containerWidget() ;
    containerWidgetObj->setWindowState(Qt::WindowMaximized) ;

    QFile styleFile(":/Resources/style.qss");
    styleFile.open(QFile::ReadOnly) ;
    QString styleSheet = QLatin1String(styleFile.readAll());
    a.setStyleSheet(styleSheet);

    containerWidgetObj->show() ;

    return a.exec();
}
