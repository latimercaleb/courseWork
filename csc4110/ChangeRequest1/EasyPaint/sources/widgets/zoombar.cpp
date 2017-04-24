#include "zoombar.h"

ZoomBar::ZoomBar(ToolBar *toolbar)
{
	mToolBar = toolbar;
	setMovable(false);
	initializeToolbar();
}

void ZoomBar::initializeToolbar()
{
	mSpacer = new QWidget(this);
	mSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	mSpacer->setVisible(true); 
	addWidget(mSpacer);

	mLabel = new QLabel();
	mLabel->setText(" Zoom: ");
	addWidget(mLabel);

	mZoomSlider = new QSlider(Qt::Horizontal);
	mZoomSlider->setMinimum(1);
	mZoomSlider->setMaximum(2);
	mZoomSlider->setTickInterval(1);
	mZoomSlider->setTickPosition(QSlider::TicksAbove);
	mZoomSlider->setValue(1);
	mZoomSlider->setMaximumWidth(200);
	connect(mZoomSlider, SIGNAL(valueChanged(int)), this, SLOT(onSlide(int)));
	addWidget(mZoomSlider);
}

void ZoomBar::onSlide(int factor)
{
	emit sendZoom(factor);
}