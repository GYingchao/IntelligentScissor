#include "imageDisplayer.h"

ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent){
	zoomFactor = 0;
	setFocusPolicy(Qt::StrongFocus);
	this->setMouseTracking(true);
}

ImageDisplayer::~ImageDisplayer(){}

void ImageDisplayer::zoomIn()
{
	if(zoomFactor < 15) {
		zoomFactor ++;
	}
}

void ImageDisplayer::zoomOut()
{
	if(zoomFactor > 0) {
		zoomFactor --;
	}
}


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
		QRectF target(0.0f, 0.0f, this->width()*2*(1+zoomFactor/10.0), this->height()*2*(1+zoomFactor/10.0));
		QRectF source(0.0f, 0.0f, this->width(), this->height());
		QImage::Format format = QImage::Format_RGB888;
		QImage temImage = QImage((const unsigned char*)img.data, img.cols, img.rows, format);
		painter.drawImage(target, temImage, source);
	}
}

void ImageDisplayer::keyPressEvent(QKeyEvent *event)
{
	if(!isEmpty()) {
		if(event->key() == Qt::Key_I){ 
			zoomIn();
			this->repaint();
		}
		if(event->key() == Qt::Key_O) {
			zoomOut();
			this->repaint();
		}
	}
}

void ImageDisplayer::mouseMoveEvent ( QMouseEvent * event )
{
	if(!isEmpty()) {
		mouse_x = event->x();
		mouse_y = event->y();
	} else {
		mouse_x = -1;
		mouse_y = -1;
	}
}