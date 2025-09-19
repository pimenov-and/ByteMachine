/////////////////////////////////////////////////////////////////////
// ByteMachine
// Описание состояния узла
/////////////////////////////////////////////////////////////////////
#ifndef NODE_STATE_DESCRIPT_H
#define NODE_STATE_DESCRIPT_H

//===================================================================
#include "node_states.h"
#include "i_to_str.h"
#include <QDebug>

//===================================================================
// Описание состояния узла
//===================================================================
class NodeStateInfo : IToStr
{
public:
    // Конструктор по умолчанию
    NodeStateInfo() = default;
    // Конструктор с параметрами
    NodeStateInfo(NodeStates state, const QString &descript);

    // Функция инициализации
    void init(NodeStates state, const QString &descript);
    // Получение представления в виде строки
    QString toStr() const override;
    // Получение состояния
    [[nodiscard]]
    NodeStates state() const;
    // Задание состояния
    void setState(const NodeStates &state);
    // Получение описания
    QString descript() const;
    // Задание описания
    void setDescript(const QString &descript);
    // Получение признака None состояния
    [[nodiscard]]
    bool isNone() const { return ::isUnknown(state_); }
    // Получение признака Success состояния
    [[nodiscard]]
    bool isSuccess() const { return ::isSuccess(state_); }
    // Получение признака Warning состояния
    [[nodiscard]]
    bool isWarning() const { return ::isWarning(state_); }
    // Получение признака Error состояния
    [[nodiscard]]
    bool isError() const { return ::isError(state_); }
private:
    // Состояние
    NodeStates state_{NodeStates::Success};
    // Описание состояния
    QString descript_{};
};

//===================================================================
Q_DECLARE_METATYPE(NodeStateInfo)

//===================================================================
// Прототипы функций
//===================================================================
// Оператор == для типа NodeStateInfo
bool operator ==(const NodeStateInfo &info1, const NodeStateInfo &info2);
// Оператор != для типа NodeStateInfo
bool operator !=(const NodeStateInfo &info1, const NodeStateInfo &info2);
// Оператор << для записи типа NodeStateInfo в поток QDebug
QDebug operator <<(QDebug debug, const NodeStateInfo &info);

//===================================================================
#endif // NODE_STATE_DESCRIPT_H
