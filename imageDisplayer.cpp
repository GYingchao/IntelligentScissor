#include "imageDisplayer.h"
#include<iostream>
using namespace std;
ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent){
	zoomFactor = 0;
	//origSize = this->size();
	setFocusPolicy(Qt::StrongFocus);
	this->setMouseTracking(true);
}

ImageDisplayer::~ImageDisplayer(){}

void ImageDisplayer::zoomIn()
{
	if(zoomFactor < 5) {
		zoomFactor ++;
		this->resize(this->size()*1.25);
	}
	
	//cout << "Zoom in: " << zoomFactor << endl;
}

void ImageDisplayer::zoomOut()
{
	if(zoomFactor > -5) {
		zoomFactor --;
		this->resize(this->size()*0.8);
	}
	
	//cout << "Zoom out: " << zoomFactor << endl;
}


void ImageDisplayer::loadImage(cv::Mat img)
{
	this->img = img;
}

void ImageDisplayer::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter widgetPainter;
	widgetPainter.begin(this);
	drawImage(widgetPainter);
	widgetPainter.end();
}

void ImageDisplayer::drawImage(QPainter &painter)
{
	if(img.data != NULL) {
		//QRectF target(0.0f, 0.0f, this->width()*2*(1+zoomFactor/10.0), this->height()*2*(1+zoomFactor/10.0));
		//cout << painter.device()->width() << endl;
		//cout << painter.device()->height() << endl;
		QRectF source(0.0f, 0.0f, painter.device()->width(), painter.device()->height());
		QRectF target(source);
		QImage::Format format = QImage::Format_RGB888;
		QImage temImage = QImage((const unsigned char*)img.data, img.cols, img.rows, format);
		//painter.drawImage(target, temImage, source);
		painter.drawImage(source, temImage);
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