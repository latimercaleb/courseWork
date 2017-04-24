/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "lineinstrument.h"
#include "../imagearea.h"
#include "../datasingleton.h"

#include <QPen>
#include <QPainter>
#include <QImage>
#include<QApplication>

LineInstrument::LineInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}
//bool LineInstrument::shiftKeyClicked(QKeyEvent *keyevent){
//	if (keyevent->key() == ){
//		return true;
//	}
//	else{
//		return false;
//	}
//}
void LineInstrument::mousePressEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        mStartPoint = mEndPoint = event->pos();
        imageArea.setIsPaint(true);
        mImageCopy = *imageArea.getImage();
        makeUndoCommand(imageArea);
    }
}

void LineInstrument::mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        mEndPoint = event->pos();
        imageArea.setImage(mImageCopy);
        if(event->buttons() & Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->buttons() & Qt::RightButton)
        {
            paint(imageArea, true);
        }
    }
}

void LineInstrument::mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea)
{
    if(imageArea.isPaint())
    {
        imageArea.setImage(mImageCopy);
        if(event->button() == Qt::LeftButton)
        {
            paint(imageArea, false);
        }
        else if(event->button() == Qt::RightButton)
        {
            paint(imageArea, true);
        }
        imageArea.setIsPaint(false);
    }
}

void LineInstrument::paint(ImageArea &imageArea, bool isSecondaryColor, bool)
{
    QPainter painter(imageArea.getImage());
    if(isSecondaryColor)
    {
        painter.setPen(QPen(DataSingleton::Instance()->getSecondaryColor(),
                            DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
    else
    {
        painter.setPen(QPen(DataSingleton::Instance()->getPrimaryColor(),
                            DataSingleton::Instance()->getPenSize() * imageArea.getZoomFactor(),
                            Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    if(mStartPoint != mEndPoint) // here is where the line is drawn 
    {
		int deltaX, deltaY;
		// my modifications start here
		if (QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier)) { // check if shift key is active
			// Compute change in x and change in y with absolute value to prevent faulty logic
			deltaX = abs(mEndPoint.x() - mStartPoint.x());
			deltaY = abs(mEndPoint.y() - mStartPoint.y());

			if (deltaX > deltaY){
				// transform to a horizontal line
				mEndPoint.setY(mStartPoint.y()); // rotate 180 making a horizontal line
			}
			else if (deltaX < deltaY){
				// transform to a vertical line 
				mEndPoint.setX(mStartPoint.x()); // rotate 90 making a vertical line
			}
			else if(deltaX == deltaY){
				// transform to a 45 degree line
				double pi = acos(-1); // Initialize pi
				double angle = 45 / 180.0 * pi; // sets angle to 45 degrees but in radians
				double LineLength = sqrt((pow(deltaX, 2) + pow(deltaY, 2))); // finds the distance of the line
				mEndPoint.setX(cos(angle)*LineLength + mStartPoint.x()); 
				mEndPoint.setY(sin(angle)*LineLength + mStartPoint.y());
			}
			else{
				// Not a special line do nothing
			}
			painter.drawLine(mStartPoint, mEndPoint); // let the line be drawn
		}// and end here
		painter.drawLine(mStartPoint, mEndPoint); // draw normal line if shift is not pressed 
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }
    imageArea.setEdited(true);
        //int rad(DataSingleton::Instance()->getPenSize() + round(sqrt((mStartPoint.x() - mEndPoint.x()) *
         //                                                            (mStartPoint.x() - mEndPoint.x()) +
          //                                                          (mStartPoint.y() - mEndPoint.y()) *
           //                                                          (mStartPoint.y() - mEndPoint.y()))));
      //mPImageArea->update(QRect(mStartPoint, mEndPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    painter.end();
    imageArea.update();
}
