////////////////////////////////////////////////////////////////
// ByteMachine
// Менеджер по управлению именами узлов
////////////////////////////////////////////////////////////////
#ifndef NODE_NAME_MANAGER_H
#define NODE_NAME_MANAGER_H

//==============================================================
#include <QSet>
#include <QString>

//==============================================================
// Менеджер по управлению именами узлов
//==============================================================
class NodeNameManager
{
    Q_DISABLE_COPY_MOVE(NodeNameManager)
public:
    // Получение экземпляра класса
    [[nodiscard]]
    static NodeNameManager* instance();

    // Добавление имени (возвращается скорректированный вариант)
    [[nodiscard]]
    QString addName(const QString &name);
    // Удаление имени
    bool removeName(const QString &name) { return names_.remove(name); }
    // Проверка наличия имени в списке
    [[nodiscard]]
    bool containsName(const QString &name) const { return names_.contains(name); }
    // Получение имен
    [[nodiscard]]
    QSet<QString> names() const { return names_; }
    // Получение количества имён
    [[nodiscard]]
    qint32 nameCount() const { return names_.count(); }
private:
    // Конструктор с параметром
    NodeNameManager() = default;

    // Имена
    QSet<QString> names_{};
    // Максимальная длина имени
    static constexpr qint32 maxNameLen_{32};
};

//==============================================================
// Прототипы функций
//==============================================================
// Получение менеджера по управлению именами узлов
[[nodiscard]]
NodeNameManager* nodeNameManager();

//==============================================================
#endif // NODE_NAME_MANAGER_H
