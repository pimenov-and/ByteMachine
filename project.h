////////////////////////////////////////////////////////////////
// ByteMachine
// Класс проекта
////////////////////////////////////////////////////////////////
#ifndef PROJECT_H
#define PROJECT_H

//==============================================================
#include <QObject>
#include <QVector>
#include <QUndoStack>
#include "base_node.h"
#include "prop_value.h"

//==============================================================
// Класс проекта
//==============================================================
class Project : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Project)
    Q_PROPERTY(QString name READ name WRITE setName RESET resetName)
    Q_PROPERTY(QString comment READ comment WRITE setComment RESET resetComment)
    Q_PROPERTY(bool isUndo READ isUndo WRITE setUndo RESET resetUndo)
public:
    // Получение экземпляра
    [[nodiscard]]
    static Project* instance();

    // Создание нового проекта
    void createNew();
    // Чтение проекта из файла XML
    void loadFromXml(const QString &path);
    // Запись проекта в файл
    void saveToXml(const QString &path) const;

    // Добавление узла
    bool addNode(const ShPtrBaseNode &node);
    // Удаление узла
    bool removeNode(const ShPtrBaseNode &nodej);

    // Получение имени
    [[nodiscard]]
    QString name() const { return name_; }
    // Задание имени
    void setName(const QString &name);
    // Сброс имени
    void resetName();
    // Получение признака изменения имени
    [[nodiscard]]
    bool isNameChanged() const { return name_ != "Project"; }
    // Получение комментария
    [[nodiscard]]
    QString comment() const { return comment_; }
    // Задание комментария
    void setComment(const QString &comment);
    // Сброс комментария
    void resetComment();
    // Получение признака изменения комментария
    [[nodiscard]]
    bool isCommentChanged() const { return !comment_.isEmpty(); }

    // Получение признака режима отмены
    [[nodiscard]]
    bool isUndo() const { return isUndo_; }
    // Задание признака режима отмены
    void setUndo(bool isUndo);
    // Сброс признака режима отмены
    void resetUndo();
    // Получение признака изменения режима отмены
    [[nodiscard]]
    bool isUndoChanged() const { return isUndo_ == true; }

    // Получение выделенного узла
    [[nodiscard]]
    ShPtrBaseNode selectedNode();
    // Получение выделенного узла (константный вариант)
    [[nodiscard]]
    ShPtrConstBaseNode selectedNode() const;
    // Задание выделенного узла. Если node равно nullptr, то это
    // означает сброс выделения со всего
    void setSelectedNode(const ShPtrBaseNode &node);

    // Перенос узла наверх
    bool bringNodeToFront(ShPtrBaseNode node);

    // Получение списка узлов
    [[nodiscard]]
    const QVector<ShPtrBaseNode>& nodes() { return nodes_; }
    // Получение списка узлов (константная версия)
    [[nodiscard]]
    QVector<ShPtrConstBaseNode> nodes() const;
    // Получение количества узлов
    [[nodiscard]]
    qint32 nodeCount() const { return nodes_.count(); }

    //----------------------------------------------------------
    // Функции отмены
    //----------------------------------------------------------
    // Получение стека отмен
    [[nodiscard]]
    QUndoStack* undoStack() { return &undoStack_; }
    // Получение стека отмен (константный вариант)
    [[nodiscard]]
    const QUndoStack* undoStack() const { return &undoStack_; }
    // Создание действия Undo
    [[nodiscard]]
    QAction* createActionUndo() const;
    // Создание действия Redo
    [[nodiscard]]
    QAction* createActionRedo() const;

    //----------------------------------------------------------
    // Поиск узла по различным параметрам
    //----------------------------------------------------------
    // Поиск узла по имени
    [[nodiscard]]
    ShPtrBaseNode findNodeByName(const QString &name);
    // Поиск узал по имени (константный вариант)
    [[nodiscard]]
    ShPtrConstBaseNode findNodeByName(const QString &name) const;
    // Поиск узла по идентификатору
    [[nodiscard]]
    ShPtrBaseNode findNodeById(qint32 id);
    // Поиск узла по идентификатору (константный вариант)
    [[nodiscard]]
    ShPtrConstBaseNode findNodeById(qint32 id) const;
    // Поиск узла по указателю
    [[nodiscard]]
    ShPtrBaseNode findNodeByPtr(BaseNode *node);
    // Поиск узла по указателю (константный вариант)
    [[nodiscard]]
    ShPtrConstBaseNode findNodeByPtr(BaseNode *const node) const;
    // Поиск узла по координате
    [[nodiscard]]
    ShPtrBaseNode findNodeByPt(const QPoint &pt);
    // Поиск узла по координате (константный вариант)
    [[nodiscard]]
    ShPtrConstBaseNode findNodeByPt(const QPoint &pt) const;
    // Поиск выделенного узла
    [[nodiscard]]
    ShPtrBaseNode findSelectedNode();
    // Поиск выделенного узла (константный вариант)
    [[nodiscard]]
    ShPtrConstBaseNode findSelectedNode() const;
    // Получение узла, на области состояния которого расположена точка
    // для верхнего уровня
    ShPtrBaseNode findStateAreaNodeByPt(const QPoint &pt);
    // Получение узла, на области состояния которого расположена точка
    // для верхнего уровня (константный вариант)
    ShPtrConstBaseNode findStateAreaNodeByPt(const QPoint &pt) const;

    //----------------------------------------------------------
    // Получение узла по попаданию в маркер изменения размера
    //----------------------------------------------------------
    // Получение узла, в маркер изменения размера которого попала точка
    [[nodiscard]]
    ShPtrBaseNode findResizebleAreaNodeFromCurrentByPt(const QPoint &pt);
    // Получение узла, в маркер изменения размера которого попала точка
    // (константный вариант)
    [[nodiscard]]
    ShPtrConstBaseNode findResizebleAreaNodeFromCurrentByPt(const QPoint &pt) const;

    //----------------------------------------------------------
    // Поиск пина узла по различным параметрам
    //----------------------------------------------------------
    // Поиск входного пина узла по координате
    [[nodiscard]]
    ShPtrInputPin findNodeInputPinByPt(const QPoint &pt, int pinMargin = 0);
    // Поиск входного пина узла по координате (константный вариант)
    [[nodiscard]]
    ShPtrConstInputPin findNodeInputPinByPt(const QPoint &pt,
        int pinMargin = 0) const;
    // Поиск выходного пина узла по координате
    [[nodiscard]]
    ShPtrOutputPin findNodeOutputPinByPt(const QPoint &pt, int pinMargin = 0);
    // Поиск выходного пина узла по координате (константный вариант)
    [[nodiscard]]
    ShPtrConstOutputPin findNodeOutputPinByPt(const QPoint &pt,
        int pinMargin = 0) const;

    // Виртуальная функция получения имени свойства из графического
    // интерфейса по его системному имени
    QString getUiPropertyName(const QString &systemName);

    // Задание соедениния узлов
    void setNodeConnection(const ShPtrOutputPin &sourceOutputPin,
        const ShPtrInputPin &oldTargetInputPin, const ShPtrInputPin &newTargetInputPin);
signals:
    // Сигнал возникает при добавлении узла
    void sigAddNode(ShPtrBaseNode node);
    // Сигнал возникает при удалении узла
    void sigRemoveNode(ShPtrBaseNode node);
    // Сигнал возникает при изменении свойства узла
    void sigChangedNodeProp(ShPtrBaseNode node, PropValue value);
    // Сигнал возникает при изменении состояния узла
    void sigChangedNodeState(ShPtrBaseNode node, NodeStateInfo state);
    // Сигнал возникает при изменении свойства
    void sigChangedProp(PropValue value);
    // Сигнал возникает при изменении выделенного узла
    void sigChangeSelectedNode(ShPtrBaseNode node);
    // Сигнал возникает при изменении подключения узла
    void sigChangeNodeConnection();
private slots:
    // Функция вызывается при изменении свойства узла
    void slotChangedNodeProp(PropValue value);
    // Функция вызывается при изменении состояния узла
    void slotChangedNodeState(NodeStateInfo state);
    // Функция вызывается при изменении подключения узла
    void slotChangeNodeConnection();
private:
    // Конструктор с параметром
    explicit Project(QObject *parent = nullptr);

    // Задание соединений
    void setConnections();
    // Сброс выделения всех узлов
    void unselectNodes();

    //----------------------------------------------------------
    // Чтение из XML
    //----------------------------------------------------------
    // Чтение имени из XML
    [[nodiscard]]
    QString readNameFromXml(const QDomElement &elem) const;
    // Чтение комментария из XML
    [[nodiscard]]
    QString readCommentFromXml(const QDomElement &elem) const;
    // Чтение узлов из XML
    [[nodiscard]]
    QVector<ShPtrBaseNode> readNodesFromXml(const QDomElement &elem) const;

    //----------------------------------------------------------
    // Запись в XML
    //----------------------------------------------------------
    // Запись имени проекта в XML
    void writeNameToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись комментария к проекту в XML
    void writeCommentToXml(QDomDocument &doc, QDomElement &elem) const;
    // Запись узлов в XML
    void writeNodesToXml(QDomDocument &doc, QDomElement &elem) const;

    // Имя
    QString name_{"Project"};
    // Комментарий
    QString comment_{};
    // Путь к файлу проекта
    mutable QString path_{};
    // Узлы
    QVector<ShPtrBaseNode> nodes_{};
    // Стек отмен
    QUndoStack undoStack_{};
    // Признак режима отмены
    bool isUndo_{false};
};

//==============================================================
// Прототипы функций
//==============================================================
// Получение проекта
Project* project();

//==============================================================
#endif // PROJECT_H
