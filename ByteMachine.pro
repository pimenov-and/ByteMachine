QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += APP_VERSION=\\\"0.015\\\" \
    APP_BUILD_DATE=\\\"13.06.2025\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    base_node.cpp \
    dialog_about_prog.cpp \
    form_designer.cpp \
    form_node_panel_item.cpp \
    form_project_settings.cpp \
    generate_node.cpp \
    main_window.cpp \
    project.cpp \
    status_bar.cpp

HEADERS += main_window.h \
    base_node.h \
    dialog_about_prog.h \
    form_designer.h \
    form_node_panel_item.h \
    form_project_settings.h \
    generate_node.h \
    i_to_str.h \
    i_xml.h \
    project.h \
    status_bar.h

FORMS += main_window.ui \
    dialog_about_prog.ui \
    form_designer.ui \
    form_project_settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc
