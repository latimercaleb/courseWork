#include "palettebutton.h"

#include <QMouseEvent>
#include <QColorDialog>
#include <qpainter.h>

PaletteButton::PaletteButton(const QColor &color, QWidget *parent) : QLabel(parent)
{
    mColor = color;
	mPixmapColor = new QPixmap(20, 20);
	mPainterColor = new QPainter(mPixmapColor);
	mPainterColor->fillRect(0, 0, 20, 20, mColor);
	mPainterColor->end();
	setMargin(3);
	setAlignment(Qt::AlignHCenter);
	setPixmap(*mPixmapColor);
}

void PaletteButton::setColor(const QColor &color)
{
	mColor = color;
	mPainterColor->begin(mPixmapColor);
	mPainterColor->fillRect(0, 0, 20, 20, mColor);
	mPainterColor->end();
	setPixmap(*mPixmapColor);
}

void PaletteButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        DataSingleton::Instance()->setPrimaryColor(mColor);
    else if(event->button() == Qt::RightButton)
        DataSingleton::Instance()->setSecondaryColor(mColor);

    emit colorPicked();
}

void PaletteButton::mouseDoubleClickEvent(QMouseEvent *event)
{
	Button(event);
	emit colorPicked();
	//QColor color = QColorDialog::getColor(mColor, this);
	//if (event->button() == Qt::LeftButton){
		//setColor(color);
		//DataSingleton::Instance()->setPrimaryColor(mColor);
	//}
		
	//else if (event->button() == Qt::RightButton){
		//setColor(color);
		//DataSingleton::Instance()->setSecondaryColor(mColor);
	//}
 
}

void PaletteButton::Button(QMouseEvent *event) //Zaid Naser fc4097//
{
	if (event->button() == Qt::LeftButton)
	{
		this->setColor(QColorDialog::getColor(this->mColor, this));
		DataSingleton::Instance()->setPrimaryColor(mColor);
	}
	if (event->button() == Qt::RightButton)
	{
		this->setColor(QColorDialog::getColor(this->mColor, this));
		DataSingleton::Instance()->setSecondaryColor(mColor);
	}
}