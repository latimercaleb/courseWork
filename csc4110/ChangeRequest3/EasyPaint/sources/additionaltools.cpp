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

#include "additionaltools.h"
#include "imagearea.h"
#include "dialogs/resizedialog.h"

#include <QImage>
#include <QPainter>
#include <QLabel>
#include <QTransform>
#include <QSize>
#include <QClipboard>
#include <QApplication>

AdditionalTools::AdditionalTools(ImageArea *pImageArea, QObject *parent) :
    QObject(parent)
{
    mPImageArea = pImageArea;
    mZoomedFactor = 1;
}

AdditionalTools::~AdditionalTools()
{

}


/*mirror Image implemented*/
void AdditionalTools::mirrorImageTop(int width, int height)
{
	QImage copy = mPImageArea->getImage()->copy(0, 0, width, height / 2);
	mPImageArea->setImage(mPImageArea->getImage()->mirrored(false, true)); // This function is key, using (false,true) is a horizontal mirror, using (true,false) is a vertical mirror and using (true, true) is both kind of? 
	QImage result(width, height, QImage::Format_RGB32);
	QPainter painter;
	painter.begin(&result);
	painter.drawImage(0, 0, mPImageArea->getImage()->copy(0, 0, width, height));
	painter.drawImage(0, 0, copy);
	painter.end();
	mPImageArea->setImage(result);
	mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6, mPImageArea->getImage()->rect().bottom() + 6);
	mPImageArea->update();
	mPImageArea->setEdited(true);
	mPImageArea->clearSelection();
}

void AdditionalTools::mirrorImageBot(int width, int height)
{
	
	QImage copy = mPImageArea->getImage()->copy(0, 0, width, height);

	mPImageArea->setImage(mPImageArea->getImage()->mirrored(false, true)); // This function is key, using (false,true) is a horizontal mirror, using (true,false) is a vertical mirror and using (true, true) is both kind of? 

	QImage result(width, height, QImage::Format_RGB32);

	QPainter painter;

	painter.drawImage(0, 0, copy);

	painter.begin(&result);

	painter.drawImage(0, 0, mPImageArea->getImage()->copy(0, 0, width, height));

	painter.end();

	mPImageArea->setImage(result);

	mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6, mPImageArea->getImage()->rect().bottom() + 6);

	mPImageArea->update();

	mPImageArea->setEdited(true);

	mPImageArea->clearSelection();

	mirrorImageTop(width, height);
	
}
/*ej1297*/


void AdditionalTools::mirrorImageL(int width, int height)
{
	QImage copy = mPImageArea->getImage()->copy(0, 0, width/2, height);

	mPImageArea->setImage(mPImageArea->getImage()->mirrored(true, false)); // This function is key, using (false,true) is a horizontal mirror, using (true,false) is a vertical mirror and using (true, true) is both kind of? 

	QImage result(width, height, QImage::Format_RGB32);

	QPainter painter;

	painter.begin(&result);

	painter.drawImage(0, 0, mPImageArea->getImage()->copy(0, 0, width, height));

	painter.drawImage(0, 0, copy);

	painter.end();

	mPImageArea->setImage(result);

	mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6, mPImageArea->getImage()->rect().bottom() + 6);

	mPImageArea->update();

	mPImageArea->setEdited(true);

	mPImageArea->clearSelection();

}

void AdditionalTools::mirrorImageR(int width, int height)
{
	QImage copy = mPImageArea->getImage()->copy(0, 0, width, height);

	mPImageArea->setImage(mPImageArea->getImage()->mirrored(true, false)); // This function is key, using (false,true) is a horizontal mirror, using (true,false) is a vertical mirror and using (true, true) is both kind of? 

	QImage result(width, height, QImage::Format_RGB32);

	QPainter painter;

	painter.drawImage(0, 0, copy);

	painter.begin(&result);

	painter.drawImage(0, 0, mPImageArea->getImage()->copy(0, 0, width, height));

	painter.end();
	
	mPImageArea->setImage(result);
	
	mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6, mPImageArea->getImage()->rect().bottom() + 6);

	mPImageArea->update();

	mPImageArea->setEdited(true);

	mPImageArea->clearSelection();

	mirrorImageL(width, height);
}

void AdditionalTools::resizeCanvas(int width, int height, bool flag)
{
    if(flag)
    {
        ResizeDialog resizeDialog(QSize(width, height));
        if(resizeDialog.exec() == QDialog::Accepted)
        {
            QSize newSize = resizeDialog.getNewSize();
            width = newSize.width();
            height = newSize.height();
        }
    }

    if(width < 1 || height < 1)
        return;
    QImage *tempImage = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(tempImage);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(QRect(0, 0, width, height));
    painter.drawImage(0, 0, *mPImageArea->getImage());
    painter.end();

    mPImageArea->setImage(*tempImage);

    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                        mPImageArea->getImage()->rect().bottom() + 6);
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
}

void AdditionalTools::resizeImage()
{
    ResizeDialog resizeDialog(mPImageArea->getImage()->size());
    if(resizeDialog.exec() == QDialog::Accepted)
    {
        mPImageArea->setImage(mPImageArea->getImage()->scaled(resizeDialog.getNewSize()));
        mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                            mPImageArea->getImage()->rect().bottom() + 6);
        mPImageArea->setEdited(true);
        mPImageArea->clearSelection();
    }
}

void AdditionalTools::rotateImage(bool flag)
{
    QTransform transform;
    if(flag)
    {
        transform.rotate(90);
    }
    else
    {
        transform.rotate(-90);
    }
    mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
    mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
                        mPImageArea->getImage()->rect().bottom() + 6);
    mPImageArea->update();
    mPImageArea->setEdited(true);
    mPImageArea->clearSelection();
}
void AdditionalTools::rotate180()
{
	QTransform transform;

	transform.rotate(180);

	mPImageArea->setImage(mPImageArea->getImage()->transformed(transform));
	mPImageArea->resize(mPImageArea->getImage()->rect().right() + 6,
		mPImageArea->getImage()->rect().bottom() + 6);
	mPImageArea->update();
	mPImageArea->setEdited(true);
	mPImageArea->clearSelection();
}

bool AdditionalTools::zoomImage(qreal factor)
{
    mZoomedFactor *= factor;
    if(mZoomedFactor < 0.25)
    {
        mZoomedFactor = 0.25;
        return false;
    }
    else if(mZoomedFactor > 4)
    {
        mZoomedFactor = 4;
        return false;
    }
    else
    {
        mPImageArea->setImage(mPImageArea->getImage()->transformed(QTransform::fromScale(factor, factor)));
        mPImageArea->resize((mPImageArea->rect().width())*factor, (mPImageArea->rect().height())*factor);
        emit sendNewImageSize(mPImageArea->size());
        mPImageArea->setEdited(true);
        mPImageArea->clearSelection();
        return true;
    }
}
