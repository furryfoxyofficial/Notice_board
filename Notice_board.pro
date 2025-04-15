QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

VPATH = cpp/
INCLUDEPATH = h/

SOURCES += \
    formforexceltable.cpp \
    mainwindow.cpp \
    aboutme.cpp \
    main.cpp \
    presentationday.cpp \
    showallintable.cpp

HEADERS += \
    h/applicationitems.h \
    h/formforexceltable.h \
    h/mainwindow.h \
    h/aboutme.h \
    h/presentationday.h \
    h/showallintable.h

FORMS += \
    ui/formforexceltable.ui \
    ui/mainwindow.ui \
    ui/aboutme.ui \
    ui/presentationday.ui \
    ui/showallintable.ui

LIBS += \
    -lodbc32

RESOURCES += \
    Resources.qrc

RC_ICONS = App-Icon.ico

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
