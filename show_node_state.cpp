////////////////////////////////////////////////////////////////
// ByteMachine
// Вывод состояния узла в виджет
////////////////////////////////////////////////////////////////
#include "show_node_state.h"
#include "base_node.h"
#include "node_states.h"
#include <QPlainTextEdit>

//==============================================================
// Вывод состояния узла в виджет
//==============================================================
void showNodeState(const BaseNode *node, QPlainTextEdit *textEdit)
{
    Q_ASSERT(node != nullptr);
    Q_ASSERT(textEdit != nullptr);

    const QString strState = node->stateInfo().toStr();
    textEdit->setPlainText(strState);
}

//===============================================================
// Вывод состояния узла в виджет
//===============================================================
void showNodeState(NodeStateInfo stateInfo, QPlainTextEdit *textEdit)
{
    Q_ASSERT(!::isUnknown(stateInfo.state()));
    Q_ASSERT(textEdit != nullptr);

    const QString strState = stateInfo.toStr();
    textEdit->setPlainText(strState);
}
