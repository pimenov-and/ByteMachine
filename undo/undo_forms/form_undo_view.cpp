////////////////////////////////////////////////////////////////
// ByteMachine
// Панель со списком отмен
/////////////////////////////////////////////////////////////////
#include "form_undo_view.h"
#include <QUndoView>
#include <QLayout>
// #include <QDebug>

//==============================================================
// Конструктор с параметрами
//==============================================================
FormUndoView::FormUndoView(QUndoStack *undoStack, QWidget *parent)
    : QWidget{parent, Qt::Popup | Qt::FramelessWindowHint}
{
    Q_ASSERT(undoStack != nullptr);

    setAttribute(Qt::WA_DeleteOnClose);

    const auto undoView = new QUndoView{undoStack, this};
    undoView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    const auto layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(undoView);
    setLayout(layout);
}

//==============================================================
// Деструктор
//==============================================================
FormUndoView::~FormUndoView()
{
}
