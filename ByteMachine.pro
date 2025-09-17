QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -pedantic-errors -Werror

DEFINES += APP_VERSION=\\\"0.065\\\" \
    APP_BUILD_DATE=\\\"17.08.2025\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    base_exception.cpp \
    base_pin.cpp \
    byte_convert.cpp \
    byte_widths.cpp \
    connect_states.cpp \
    dialog_about_prog.cpp \
    form_adv_color.cpp \
    form_color.cpp \
    form_designer.cpp \
    form_generate_node.cpp \
    form_node_panel_item.cpp \
    form_project_settings.cpp \
    form_size_node.cpp \
    generate_types.cpp \
    icons.cpp \
    input_pin.cpp \
    main_window.cpp \
    moving_node.cpp \
    node_helper.cpp \
    node_name_manager.cpp \
    node_state_info.cpp \
    node_states.cpp \
    node_types.cpp \
    nodes/base_node.cpp \
    nodes/generate_node.cpp \
    nodes/size_node.cpp \
    output_pin.cpp \
    pin_connection.cpp \
    project.cpp \
    prop_value.cpp \
    qt_helper.cpp \
    show_node_state.cpp \
    size_units.cpp \
    status_bar.cpp \
    undo/undo_add_node.cpp \
    undo/undo_change_object_prop_value.cpp \
    undo/undo_remove_node.cpp \
    undo/undo_select_object.cpp \
    widget_undo_view.cpp \
    xml_helper.cpp

HEADERS += main_window.h \
    base_exception.h \
    base_pin.h \
    byte_convert.h \
    byte_widths.h \
    colors.h \
    connect_states.h \
    dialog_about_prog.h \
    form_adv_color.h \
    form_color.h \
    form_designer.h \
    form_generate_node.h \
    form_node_panel_item.h \
    form_project_settings.h \
    form_size_node.h \
    generate_types.h \
    i_data.h \
    i_to_str.h \
    i_xml.h \
    icons.h \
    input_pin.h \
    moving_node.h \
    node_helper.h \
    node_name_manager.h \
    node_state_info.h \
    node_states.h \
    node_types.h \
    nodes/base_node.h \
    nodes/generate_node.h \
    nodes/size_node.h \
    output_pin.h \
    pin_connection.h \
    project.h \
    prop_value.h \
    qt_helper.h \
    show_node_state.h \
    size_units.h \
    standart_colors.h \
    status_bar.h \
    undo/undo_add_node.h \
    undo/undo_change_object_prop_value.h \
    undo/undo_remove_node.h \
    undo/undo_select_object.h \
    widget_undo_view.h \
    xml_helper.h

FORMS += main_window.ui \
    dialog_about_prog.ui \
    form_adv_color.ui \
    form_color.ui \
    form_designer.ui \
    form_generate_node.ui \
    form_project_settings.ui \
    form_size_node.ui

INCLUDEPATH += nodes/ \
    undo/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc

DISTFILES += .gitignore
