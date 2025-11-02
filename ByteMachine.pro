QT += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += -pedantic-errors -Werror

DEFINES += APP_VERSION=\\\"0.079\\\" \
    APP_BUILD_DATE=\\\"02.11.2025\\\"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    byte_convert.cpp \
    byte_widths.cpp \
    connect_states.cpp \
    dialog_about_prog.cpp \
    exceptions/base_exception.cpp \
    form_adv_color.cpp \
    form_adv_spin_box.cpp \
    form_color.cpp \
    form_designer.cpp \
    form_project_settings.cpp \
    icons.cpp \
    main_window.cpp \
    math_helper.cpp \
    nodes/base_node.cpp \
    nodes/base_pin.cpp \
    nodes/generate_node.cpp \
    nodes/generate_types.cpp \
    nodes/input_pin.cpp \
    nodes/moving_node.cpp \
    nodes/moving_node_connection.cpp \
    nodes/node_forms/form_generate_node.cpp \
    nodes/node_forms/form_node_panel_item.cpp \
    nodes/node_forms/form_size_node.cpp \
    nodes/node_helper.cpp \
    nodes/node_name_manager.cpp \
    nodes/node_state_info.cpp \
    nodes/node_states.cpp \
    nodes/node_types.cpp \
    nodes/output_pin.cpp \
    nodes/pin_connection.cpp \
    nodes/prop_value.cpp \
    nodes/show_node_state.cpp \
    nodes/size_node.cpp \
    nodes/size_units.cpp \
    project.cpp \
    qt_helper.cpp \
    status_bar.cpp \
    undo/undo_add_node.cpp \
    undo/undo_change_node_connection.cpp \
    undo/undo_change_object_prop_value.cpp \
    undo/undo_forms/form_undo_view.cpp \
    undo/undo_remove_node.cpp \
    undo/undo_select_object.cpp \
    xml_helper.cpp

HEADERS += main_window.h \
    byte_convert.h \
    byte_widths.h \
    colors.h \
    connect_states.h \
    dialog_about_prog.h \
    exceptions/base_exception.h \
    form_adv_color.h \
    form_adv_spin_box.h \
    form_color.h \
    form_designer.h \
    form_project_settings.h \
    i_data.h \
    i_to_str.h \
    i_xml.h \
    icons.h \
    math_helper.h \
    nodes/base_node.h \
    nodes/base_pin.h \
    nodes/generate_node.h \
    nodes/generate_types.h \
    nodes/input_pin.h \
    nodes/moving_node.h \
    nodes/moving_node_connection.h \
    nodes/node_forms/form_generate_node.h \
    nodes/node_forms/form_node_panel_item.h \
    nodes/node_forms/form_size_node.h \
    nodes/node_forms/node_forms.h \
    nodes/node_helper.h \
    nodes/node_name_manager.h \
    nodes/node_state_info.h \
    nodes/node_states.h \
    nodes/node_types.h \
    nodes/output_pin.h \
    nodes/pin_connection.h \
    nodes/prop_value.h \
    nodes/show_node_state.h \
    nodes/size_node.h \
    nodes/size_units.h \
    project.h \
    qt_helper.h \
    standart_colors.h \
    status_bar.h \
    type_defs.h \
    undo/undo_add_node.h \
    undo/undo_change_node_connection.h \
    undo/undo_change_object_prop_value.h \
    undo/undo_forms/form_undo_view.h \
    undo/undo_remove_node.h \
    undo/undo_select_object.h \
    xml_helper.h

FORMS += main_window.ui \
    dialog_about_prog.ui \
    form_adv_color.ui \
    form_color.ui \
    form_designer.ui \
    form_project_settings.ui \
    nodes/node_forms/form_generate_node.ui \
    nodes/node_forms/form_size_node.ui

INCLUDEPATH += nodes/ \
    nodes/node_forms/ \
    undo/ \
    undo/undo_forms/ \
    exceptions/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += res.qrc

DISTFILES += .gitignore
