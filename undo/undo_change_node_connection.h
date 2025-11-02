////////////////////////////////////////////////////////////////
// ByteMachine
// Команда отмены для связи узла
////////////////////////////////////////////////////////////////
#ifndef UNDO_CHANGE_NODE_CONNECTION_H
#define UNDO_CHANGE_NODE_CONNECTION_H

//==============================================================
#include <QUndoCommand>
#include "input_pin.h"
#include "output_pin.h"

//==============================================================
// Команда отмены для связи узла
//==============================================================
class UndoChangeNodeConnection : public QUndoCommand
{
public:
    // Конструктор с параметрами
    UndoChangeNodeConnection(const ShPtrOutputPin &sourceOutputPin,
        const ShPtrInputPin &oldTargetInputPin,
        const ShPtrInputPin &newTargetInputPin);
    // Деструктор
    ~UndoChangeNodeConnection() override;

    // Функция отмены
    void undo() override;
    // Функция восстановления
    void redo() override;
private:
    // Выходной пин, из которого производится подключение
    ShPtrOutputPin sourceOutputPin_{};
    // Старый входной пин, к которому было подключение
    ShPtrInputPin oldTargetInputPin_{};
    // Новый входной пин, к которому производится подключение
    ShPtrInputPin newTargetInputPin_{};
    // Выходной пин, к которому возможно был подключен newTargetInputPin_
    ShPtrOutputPin targetOutputPin_{};
};

//==============================================================
#endif // UNDO_CHANGE_NODE_CONNECTION_H
