#include "triangleinstrument.h"
#include "../EasyPaint/sources/imagearea.h"
#include "../EasyPaint/sources/datasingleton.h"

#include <QPen>
#include <QPainter>

TriangleInstrument::TriangleInstrument(QObject *parent) :
AbstractInstrument(parent)
{
}

void TriangleInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		mStartPoint = mEndPoint = event->pos();
		imageArea.setIsPaint(true);
		mImageCopy = *imageArea.getImage();
		makeUndoCommand(imageArea);
	}
}


void TriangleInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
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

void TriangleInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
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

void TriangleInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
	QPainter painter(imageArea.getImage());
	painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
		DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
		Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	if (isSecondaryColor)
	{
		painter.setBrush(QBrush(DataSingleton::Instance()->getSecondaryColor()));
	}
	if (mStartPoint != mEndPoint)
	{


		QPolygon triangle;
		//MODIFIED BY SAFAYETH KHAN
		triangleShapeModifier(triangle);
															//I extracted this part to a function because my current code does work, but the triangle is at a angle and
															//isn't practicle. It requires use of other tools to be practicle. From my understanding the following few
															//lines of code determine the outcome of the triangle that is drawn, hence for future improvement I made it
															//easier for people to find and modify the triangle to be more practicle.
		//triangle << QPoint(mEndPoint.y(), mStartPoint.x());
		//triangle << QPoint(mStartPoint.x(), mEndPoint.x()); 
		//triangle << QPoint(mEndPoint.x(), mStartPoint.y());
		//triangle << QPoint(mEndPoint.y(), mStartPoint.x());
	
		QPainterPath path;
		path.addPolygon(QPolygon(triangle));
		painter.drawPath(path);
		painter.strokePath(path, QPen(DataSingleton::Instance()->getPrimaryColor(),
			DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
			Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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


void TriangleInstrument:: triangleShapeModifier(QPolygon &triangle)			//new function. 
{
	triangle << QPoint(mEndPoint.y(), mStartPoint.x());						//these modify shape of triangle that is drawn.
	triangle << QPoint(mStartPoint.x(), mEndPoint.x());
	triangle << QPoint(mEndPoint.x(), mStartPoint.y());
	triangle << QPoint(mEndPoint.y(), mStartPoint.x());

}