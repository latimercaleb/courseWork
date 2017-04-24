#ifndef QTPROGRAMWIN_H
#define QTPROGRAMWIN_H

#include <QMainWindow>
#include <QObject>
namespace Ui {
class QtProgramWin;
}

class QtProgramWin : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QtProgramWin(QWidget *parent = 0);
    ~QtProgramWin();
    
private:
    Ui::QtProgramWin *ui;
	int param; // parameter 1 for calculator
	int param2; // parameter 2 for calculator
	char op; // character of operation
	
public slots:
	void setLineEditText(); // retained from previous version used to output result
	void setNewNumber(int); // new function to add number to solution
	void setOperation(char); // used to set the operation between the two numbers
	void setlineEditNum(int); // to set the line edit to display the parameters entered 

};

#endif // QTPROGRAMWIN_H
