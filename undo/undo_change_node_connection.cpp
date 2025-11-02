////////////////////////////////////////////////////////////////
// ByteLink
// Команда отмены для связи узла
////////////////////////////////////////////////////////////////
#include "undo_change_node_connection.h"
#include "base_node.h"

//==============================================================
// Конструктор с параметрами
//==============================================================
UndoChangeNodeConnection::UndoChangeNodeConnection(
    const ShPtrOutputPin &sourceOutputPin,
    const ShPtrInputPin &oldTargetInputPin,
    const ShPtrInputPin &newTargetInputPin)
{
    Q_ASSERT(sourceOutputPin != nullptr);

    sourceOutputPin_ = sourceOutputPin;
    oldTargetInputPin_ = oldTargetInputPin;
    newTargetInputPin_ = newTargetInputPin;

    if ((newTargetInputPin_ != nullptr) && newTargetInputPin_->isConnected())
    {
        targetOutputPin_ = newTargetInputPin_->outputPin();
    }

    setText("Change connection");
}

//==============================================================
// Деструктор
//==============================================================
UndoChangeNodeConnection::~UndoChangeNodeConnection()
{
}

//==============================================================
// Функция отмены
//==============================================================
void UndoChangeNodeConnection::undo()
{
    // Отключение от нового входного пина
    if (newTargetInputPin_ != nullptr)
    {
        disconnectPins(sourceOutputPin_, newTargetInputPin_);

        // Если пин был подключен ранее, то восстановить подключение
        if (targetOutputPin_ != nullptr)
        {
            connectPins(targetOutputPin_, newTargetInputPin_);
        }
    }

    // Подключение к старому входному пину
    if (oldTargetInputPin_ != nullptr)
    {
        connectPins(sourceOutputPin_, oldTargetInputPin_);
    }
}

//==============================================================
// Функция восстановления
//==============================================================
void UndoChangeNodeConnection::redo()
{
    // Отключение от старого входного пина
    if (oldTargetInputPin_ != nullptr)
    {
        disconnectPins(sourceOutputPin_, oldTargetInputPin_);
    }

    // Подключение к новому входному пину
    if (newTargetInputPin_ != nullptr)
    {
        // Если пин был подключен, то отключить его
        if (targetOutputPin_ != nullptr)
        {
            disconnectPins(targetOutputPin_, newTargetInputPin_);
        }

        connectPins(sourceOutputPin_, newTargetInputPin_);
    }
}
