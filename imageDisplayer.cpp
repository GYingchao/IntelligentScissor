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
	QImage::Format format = QImage::Format_RGB888;
	qimg = QImage((const unsigned char*)img.data, img.cols, img.rows, format);
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
		//painter.drawImage(target, temImage, source);
		painter.drawImage(source, qimg);
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

void ImageDisplayer::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton && !isEmpty()) {
		// update progress bar
		mouse_x = event->x();
		mouse_y = event->y();
		cout << "x: " << event->x() << ", y: " << event->y() << endl;

		// compute the corresponding pixel index of the image
		cout << qimg.width() << ", " << qimg.height() << endl;
		cout << this->width() << ", " << this->height() << endl;

		double orig_i = event->x()*(qimg.width()-2)/this->width();
		double orig_j = event->y()*(qimg.height()-2)/this->height();
		cout << "From displayer: " << orig_i << ", " << orig_j << endl;
		// Update mouse clicked pixel pos
		img_x = static_cast<int>(orig_i);
		img_y = static_cast<int>(orig_j);
		handler->setSeed(img_x, img_y);
	}
}