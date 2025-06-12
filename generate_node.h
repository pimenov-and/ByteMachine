////////////////////////////////////////////////////////////////
// ByteMachine
// Узел "Generate"
////////////////////////////////////////////////////////////////
#ifndef GENERATE_NODE_H
#define GENERATE_NODE_H

//==============================================================
#include "base_node.h"

//==============================================================
// Узел "Generate"
//==============================================================
class GenerateNode : public BaseNode
{
public:
    // Конструктор с параметром
    explicit GenerateNode(QObject *parent = nullptr);
    // Деструктор
    ~GenerateNode() override;
private:
};

//==============================================================
#endif // GENERATE_NODE_H
