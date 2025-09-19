////////////////////////////////////////////////////////////////
// ByteMachine
// Менеджер по управлению именами узлов
////////////////////////////////////////////////////////////////
#include "node_name_manager.h"
// #include <QDebug>

//==============================================================
using std::numeric_limits;

////////////////////////////////////////////////////////////////
// Реализация класса NodeNameManager
////////////////////////////////////////////////////////////////

//==============================================================
// Получение экземпляра класса
//==============================================================
NodeNameManager* NodeNameManager::instance()
{
    static NodeNameManager manager{};

    return &manager;
}

//==============================================================
// Добавление имени (возвращается скорректированный вариант)
//==============================================================
QString NodeNameManager::addName(const QString &name)
{
    QString correctName = name.left(32);

    if (!containsName(name))
    {
        names_ << correctName;
        return correctName;
    }
    else
    {
        for (int i = 2; i < numeric_limits<int>::max(); ++i)
        {
            const QString strNum = QString::number(i);
            if (correctName.length() + strNum.length() > maxNameLen_)
            {
                correctName = correctName.mid(0, maxNameLen_ - strNum.length());
            }

            const QString nameWithNum = name + strNum;
            if (!containsName(nameWithNum))
            {
                names_ << nameWithNum;
                return nameWithNum;
            }
        }

        return QString{};
    }
}

////////////////////////////////////////////////////////////////
// Реализация функций
////////////////////////////////////////////////////////////////

//==============================================================
// Получение менеджера по управлению именами узлов
//==============================================================
NodeNameManager* nodeNameManager()
{
    return NodeNameManager::instance();
}
