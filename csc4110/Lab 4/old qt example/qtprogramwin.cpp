#include "qtprogramwin.h"
#include "ui_qtprogramwin.h"

QtProgramWin::QtProgramWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtProgramWin)
{
    ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setLineEditText()));
}

QtProgramWin::~QtProgramWin()
{
    delete ui;
}


void QtProgramWin::setLineEditText()
{
	ui->lineEdit->setText(QString("Hello World!") );
}