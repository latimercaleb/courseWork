#include "qtprogramwin.h"
#include "ui_qtprogramwin.h"

QtProgramWin::QtProgramWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtProgramWin)
{
	param = 0;
	param2 = 0;
    ui->setupUi(this);
	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(setlineEditNum(param)));
	connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(setlineEditNum(1)));
	connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(setlineEditNum(2)));
	connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(setlineEditNum(3)));
	connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(setlineEditNum(4)));
	connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(setlineEditNum(5)));
	connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(setlineEditNum(6)));
	connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(setlineEditNum(7)));
	connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(setlineEditNum(8)));
	connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(setlineEditNum(9)));

	connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(setLineEditText()));
	connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(setLineEditText()));
	connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(setLineEditText()));
	connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(setLineEditText()));
	connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(setLineEditText()));
	connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(setLineEditText()));
	connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(setLineEditText()));
	//connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(setNewNumber(int)));
}

QtProgramWin::~QtProgramWin()
{
    delete ui;
}

void QtProgramWin::setlineEditNum(int buttonNum){
	QString input = QString::number(buttonNum);
	ui->lineEdit->setText(QString(input));
	setNewNumber(buttonNum);
}

void QtProgramWin::setLineEditText()
{
	ui->lineEdit->setText(QString("Result is!"));
}

void QtProgramWin::setOperation(char)
{
	ui->lineEdit->setText(QString("Result is!"));
}

void QtProgramWin::setNewNumber(int input)
{
	if (param < 0){
		param = input;
	}
	else{
		param2 = input;
	}
}