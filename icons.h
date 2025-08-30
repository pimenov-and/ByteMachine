////////////////////////////////////////////////////////////////
// ByteMachine
// Иконки
////////////////////////////////////////////////////////////////
#ifndef ICONS_H
#define ICONS_H

//==============================================================
#include <QIcon>

//==============================================================
// Иконки
//==============================================================
class Icons
{
    Q_DISABLE_COPY_MOVE(Icons)
public:
    // Конструктор по умолчанию
    Icons() = delete;

    // Получение иконки New
    [[nodiscard]]
    static QIcon new_();
    // Получение иконки Open
    [[nodiscard]]
    static QIcon open();
    // Получение иконки Add
    [[nodiscard]]
    static QIcon add();
    // Получение иконки Save
    [[nodiscard]]
    static QIcon save();
    // Получение иконки Undo
    [[nodiscard]]
    static QIcon undo();
    // Получение иконки Redo
    [[nodiscard]]
    static QIcon redo();
    // Получение иконки Cut
    [[nodiscard]]
    static QIcon cut();
    // Получение иконки Copy
    [[nodiscard]]
    static QIcon copy();
    // Получение иконки Paste
    [[nodiscard]]
    static QIcon paste();
    // Получение иконки ResetValue
    [[nodiscard]]
    static QIcon resetValue();
    // Получение иконки Delete
    [[nodiscard]]
    static QIcon delete_();
    // Получение иконки PaintMode
    [[nodiscard]]
    static QIcon paintMode();
    // Получение иконки VisibleNodeComments
    [[nodiscard]]
    static QIcon visibleNodeComments();
    // Получение иконки VisibleNodesPanel
    [[nodiscard]]
    static QIcon visibleNodesPanel();
    // Получение иконки VisibleSettingPanel
    [[nodiscard]]
    static QIcon visibleSettingsPanel();
    // Получение иконки VisibleDesignerGrid
    [[nodiscard]]
    static QIcon visibleDesignerGrid();
    // Получение иконки Help
    [[nodiscard]]
    static QIcon help();
    // Получение иконки CollapseArrow
    [[nodiscard]]
    static QIcon collapseArrow();
    // Получение иконки ExpandArrow
    [[nodiscard]]
    static QIcon expandArrow();
    // Получение иконки StandartNode
    [[nodiscard]]
    static QIcon standartNode();
    // Получение иконки StandartNode в режиме Disable
    [[nodiscard]]
    static QIcon standartNodeDisable();
};

//==============================================================
#endif // ICONS_H
