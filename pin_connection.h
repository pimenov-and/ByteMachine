////////////////////////////////////////////////////////////////
// ByteMachine
// Подключение пина
////////////////////////////////////////////////////////////////
#ifndef PIN_CONNECTION_H
#define PIN_CONNECTION_H

//==============================================================
#include <QDebug>
#include "i_to_str.h"

//==============================================================
// Подключение пина
//==============================================================
struct PinConnection : IToStr
{
    // Конструктор по умолчанию
    PinConnection() = default;
    // Конструктор с параметрами
    PinConnection(int nodeId, int index);

    // Функция инициализации
    void init(int nodeId, int index);
    // Очистка (устанавливает поля в -1)
    void clear();
    // Получение признака подключения
    bool isConnect() const;
    // Получение представления в виде строки
    QString toStr() const override;

    // Идентификатор узла
    int nodeId{-1};
    // Индекс пина
    int index{-1};
};

//==============================================================
// Прототипы функций
//==============================================================
// Оператор == для типа PinConnection
bool operator ==(const PinConnection &pc1, const PinConnection &pc2);
// Оператор != для типа PinConnection
bool operator !=(const PinConnection &pc1, const PinConnection &pc2);
// Оператор << для вывода в поток QDebug типа PinConnection
QDebug operator <<(QDebug debug, const PinConnection &pc);

//==============================================================
#endif // PIN_CONNECTION_H
