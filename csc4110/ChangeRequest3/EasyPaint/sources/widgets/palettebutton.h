#ifndef QPALETTEBUTTON_H
#define QPALETTEBUTTON_H

#include "../datasingleton.h"

#include <QToolButton>
#include <qlabel.h>

class PaletteButton : public QLabel
{
    Q_OBJECT

public:
    PaletteButton(const QColor &color, QWidget *parent = 0);
	void Button(QMouseEvent *event);//fc4097//

signals:
    void colorPicked();

public slots:
	void setColor(const QColor &color);

private:
    QColor mColor;
	QPainter *mPainterColor;
	QPixmap *mPixmapColor;

protected:
    void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // QPALETTEBUTTON_H
