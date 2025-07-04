QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += APP_VERSION=\\\"0.031\\\" \
    APP_BUILD_DATE=\\\"04.07.2025\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    base_node.cpp \
    base_pin.cpp \
    byte_widths.cpp \
    connect_states.cpp \
    dialog_about_prog.cpp \
    form_designer.cpp \
    form_generate_node.cpp \
    form_node_panel_item.cpp \
    form_project_settings.cpp \
    generate_node.cpp \
    generate_types.cpp \
    main_window.cpp \
    node_name_manager.cpp \
    node_state_info.cpp \
    node_states.cpp \
    node_types.cpp \
    project.cpp \
    prop_value.cpp \
    qt_helper.cpp \
    status_bar.cpp \
    undo_add_node.cpp \
    undo_change_object_prop_value.cpp \
    undo_remove_node.cpp

HEADERS += main_window.h \
    base_node.h \
    base_pin.h \
    byte_widths.h \
    connect_states.h \
    dialog_about_prog.h \
    form_designer.h \
    form_generate_node.h \
    form_node_panel_item.h \
    form_project_settings.h \
    generate_node.h \
    generate_types.h \
    i_data.h \
    i_to_str.h \
    i_xml.h \
    node_name_manager.h \
    node_state_info.h \
    node_states.h \
    node_types.h \
    project.h \
    prop_value.h \
    qt_helper.h \
    status_bar.h \
    undo_add_node.h \
    undo_change_object_prop_value.h \
    undo_remove_node.h

FORMS += main_window.ui \
    dialog_about_prog.ui \
    form_designer.ui \
    form_generate_node.ui \
    form_project_settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc
