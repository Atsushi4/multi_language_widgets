#include "mainwindow.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto apTs = new QTranslator(&app);
    app.installTranslator(apTs);
    auto qtTs = new QTranslator(&app);
    app.installTranslator(qtTs);

    MainWindow window;
    auto menu = new QMenu{QObject::tr("&Language")};
    window.menuBar()->addMenu(menu);
    QDir dir{":/i18n/"};
    const auto &entries = dir.entryInfoList(QDir::Files);
    for (const auto &entry : entries) {
        if (entry.suffix() != "qm") continue;
        QLocale locale{entry.baseName().right(5)};
        auto action = new QAction(locale.nativeLanguageName());
        QObject::connect(action, &QAction::triggered, &app, [apTs, qtTs, locale, entry] {
            if (apTs->load(entry.absoluteFilePath())) {
                qDebug() << "qm load error:" << entry.absoluteFilePath();
            }
            const auto &qtTsDir = qgetenv("QTDIR") + QStringLiteral("/translations/");
            if (!qtTs->load(locale, "qt", "_", qtTsDir)) {
                qDebug() << "qt qm load error";
            }
        });
        menu->addAction(action);
    }
    window.show();
    return app.exec();
}
