#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql printsupport  # For PDF generation and printing support
QT       += charts                      # For adding chart functionalities in the statistics tab

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  # Includes QtWidgets if Qt version > 4

TARGET = Atelier_Connexion
TEMPLATE = app

# Enables compiler warnings for deprecated Qt features
DEFINES += QT_DEPRECATED_WARNINGS

# Optional: Uncomment to prevent usage of deprecated APIs before a specific version
# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11  # Enables C++11 standard

# Source files
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    service.cpp

# Header files
HEADERS += \
        mainwindow.h \
    connection.h \
    service.h

# UI Forms
FORMS += \
        mainwindow.ui

# Deployment rules for different platforms
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

