
#ifndef DASHEDLINEINSTRUMENT_H
#define DASHEDLINEINSTRUMENT_H

#include"abstractinstrument.h"
#include <QtCore/QObject>

class DashedLineInstrument : public AbstractInstrument{
	Q_OBJECT 

public:
	explicit DashedLineInstrument(QObject *parent = 0);
	void mousePressEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseMoveEvent(QMouseEvent *event, ImageArea &imageArea);
	void mouseReleaseEvent(QMouseEvent *event, ImageArea &imageArea);

protected:
	void paint(ImageArea &imageArea, bool isSecondaryColor = false, bool additionalFlag = false);
};
#endif 