
#include "dashedLineInstrument.h"
#include"../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>
#include <QImage>

DashedLineInstrument::DashedLineInstrument(QObject *parent) :
AbstractInstrument(parent)
{

}

void DashedLineInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		mStartPoint = mEndPoint = event->pos();
		imageArea.setIsPaint(true);
		mImageCopy = *imageArea.getImage();
		makeUndoCommand(imageArea);
	}
}

void DashedLineInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		mEndPoint = event->pos();
		imageArea.setImage(mImageCopy);
		if (event->buttons() & Qt::LeftButton)
		{
			paint(imageArea, false);
		}
		else if (event->buttons() & Qt::RightButton)
		{
			paint(imageArea, true);
		}
	}
}

void DashedLineInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (imageArea.isPaint())
	{
		imageArea.setImage(mImageCopy);
		if (event->button() == Qt::LeftButton)
		{
			paint(imageArea, false);
		}
		else if (event->button() == Qt::RightButton)
		{
			paint(imageArea, true);
		}
		imageArea.setIsPaint(false);
	}
}

void DashedLineInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
	QPainter painter(imageArea.getImage());
	if (isSecondaryColor)
	{
		painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
			DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
			Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
	}
	else
	{
		painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
			DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
			Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
	}

	if (mStartPoint != mEndPoint)
	{
		painter.drawLine(mStartPoint, mEndPoint);
	}

	if (mStartPoint == mEndPoint)
	{
		painter.drawPoint(mStartPoint);
	}
	imageArea.setEdited(true);
	//    int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
	//                                                                 (mStartPoint.x() - mEndPoint.x()) +
	//                                                                 (mStartPoint.y() - mEndPoint.y()) *
	//                                                                 (mStartPoint.y() - mEndPoint.y()))));
	//    mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
	painter.end();
	imageArea.update();
}
