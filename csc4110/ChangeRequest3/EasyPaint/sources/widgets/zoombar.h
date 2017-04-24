#ifndef ZOOMBAR_H
#define ZOOMBAR_H

#include "toolbar.h"

#include <QToolBar>
#include <QSlider>
#include <QLabel>
#include <QtGui>

class ZoomBar : public QToolBar
{
	Q_OBJECT

public:
	ZoomBar(ToolBar *toolBar);

private:
	void initializeToolbar();
	ToolBar *mToolBar;
	QSlider *mZoomSlider;
	QLabel *mLabel;
	QWidget *mSpacer;

public slots:
	void onSlide(int factor);

signals:
	void sendZoom(int);

};

#endif