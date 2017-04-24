#ifndef TRIANGLEINSTRUMENT_H
#define TRIANGLEINSTRUMENT_H

#include "abstractinstrument.h"
//#include "../EasyPaint/sources/imagearea.h"
#include <QtCore/QObject>


class TriangleInstrument : public AbstractInstrument
{
	Q_OBJECT
public:
	explicit TriangleInstrument(QObject *parent = 0);

	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

	void triangleShapeModifier(QPolygon &triangle);   //extracted method prototype;

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);

};

#endif// TRIANGLEINSTRUMENT_H
