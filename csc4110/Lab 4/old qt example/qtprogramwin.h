#ifndef QTPROGRAMWIN_H
#define QTPROGRAMWIN_H

#include <QMainWindow>

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
	
public slots:
	void setLineEditText();
};

#endif // QTPROGRAMWIN_H
