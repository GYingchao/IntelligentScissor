#include "imageDisplayer.h"

ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent){
	this->setMouseTracking(true);
}

ImageDisplayer::~ImageDisplayer(){}

void ImageDisplayer::loadImage(cv::Mat img)
{
	this->img = img;
}

void ImageDisplayer::paintEvent(QPaintEvent *event)
{
	QPainter widgetPainter;
	widgetPainter.begin(this);
	drawImage(widgetPainter);
	widgetPainter.end();
}

void ImageDisplayer::drawImage(QPainter &painter)
{
	if(img.data != NULL) {
		QRectF target(0.0f, 0.0f, this->width(), this->height());
		QRectF source(0.0f, 0.0f, this->width(), this->height());
		QImage::Format format = QImage::Format_RGB888;
		QImage temImage = QImage((const unsigned char*)img.data, img.cols, img.rows, format);
		painter.drawImage(target, temImage, source);
	}
}