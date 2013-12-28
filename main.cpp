#include <QApplication>
#include <QTextCodec>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.h"

#if (QT_VERSION < QT_VERSION_CHECK(4, 0, 0))
#error "Qt 3 is not supported"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec * codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
#endif

    QTranslator translator;
    translator.load(QString(":/trans/%1.qm").arg(QLocale::system().name()));
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
