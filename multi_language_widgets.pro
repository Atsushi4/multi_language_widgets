QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    translations/multi_language_widgets_ja_JP.ts \
    translations/multi_language_widgets_zh_CN.ts

# QM_FILES_INSTALL_PATH = $${OUT_PWD}/translations/ # no effects
CONFIG += lrelease
CONFIG += embed_translations
QM_FILES_RESOURCE_PREFIX = /i18n/
