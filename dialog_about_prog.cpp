////////////////////////////////////////////////////////////////
// ByteMachine
// Диалоговое окно "О программе"
////////////////////////////////////////////////////////////////
#include "dialog_about_prog.h"
#include "ui_dialog_about_prog.h"

//==============================================================
// Конструктор с параметром
//==============================================================
DialogAboutProg::DialogAboutProg(QWidget *parent) : QDialog{parent},
    ui_{new Ui::DialogAboutProg{}}
{
    ui_->setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    const QSize hint = window()->sizeHint();
    setFixedSize(hint.width() * 1.1, hint.height()); // чуть увеличиваем ширину для лучшего виду диалога

    const QString version = QString{"%1 %2 %3 %4"}.
        arg("Version", APP_VERSION, "from", APP_BUILD_DATE);
    ui_->labelVersion_->setText(version);
}

//==============================================================
// Деструктор
//==============================================================
DialogAboutProg::~DialogAboutProg()
{
    delete ui_;
}
