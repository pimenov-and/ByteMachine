QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += APP_VERSION=\\\"0.005\\\" \
    APP_BUILD_DATE=\\\"30.05.2025\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    dialog_about_prog.cpp \
    form_designer.cpp \
    main_window.cpp

HEADERS += main_window.h \
    dialog_about_prog.h \
    form_designer.h

FORMS += main_window.ui \
    dialog_about_prog.ui \
    form_designer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc
