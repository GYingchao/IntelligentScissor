#include "imageDisplayer.h"
#include<iostream>
using namespace std;
ImageDisplayer::ImageDisplayer(QWidget *parent) : QWidget(parent){
	zoomFactor = 0;
	draw_seed = false;
	started_scissor = false;
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

// img pixel index is from (1, 1) to (cols, rows);
// displayer pixel index is from (0, 0) to (width-1, height-1);
int* ImageDisplayer::img2dis(int i, int j)
{
	int pos[2];
	pos[0] = static_cast<int>((i-1)*this->width()/(qimg.width()-2));
	pos[1] = static_cast<int>((j-1)*this->height()/(qimg.height()-2));
	return pos;
}

int* ImageDisplayer::dis2img(int x, int y)
{
	int pos[2];
	pos[0] = static_cast<int>(x*(qimg.width()-2)/this->width())+1;
	pos[1] = static_cast<int>(y*(qimg.height()-2)/this->height())+1;
	return pos;
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
	if(draw_seed) drawSeed(widgetPainter);
	if(isStarted() && draw_seed) drawPath(widgetPainter, path);
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

void ImageDisplayer::drawSeed(QPainter &painter)
{
	QBrush o = painter.brush();
	painter.setBrush(QColor(255, 0, 0, 255));
	int* tem = img2dis(img_x, img_y);
	painter.drawRect(tem[0]-2, tem[1]-2, 5, 5);
	painter.setBrush(o);
}

void ImageDisplayer::drawPath(QPainter &painter, vector<vec2i>& p)
{
	if(p.empty()) return;
	QPainterPath path;
	int* tem = img2dis(p[0].pos[0], p[0].pos[1]);
	path.moveTo(tem[0], tem[1]);
	for(int i=1; i<p.size(); i++) {
		tem = img2dis(p[i].pos[0], p[i].pos[1]);
		path.lineTo(tem[0], tem[1]);
	}
	/*
	 path.moveTo(20, 80);
	 path.lineTo(20, 30);
	 path.cubicTo(80, 0, 50, 50, 80, 80);
	 */
	//QBrush o = painter.brush();
	//painter.setBrush(QColor(0, 255, 0, 127));
	QPen o = painter.pen();
	QPen pen(Qt::green, 3);
	painter.setPen(pen);
	painter.drawPath(path);
	//painter.setBrush(o);
	painter.setPen(o);
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
		// if image is loaded correctly
		mouse_x = event->x();
		mouse_y = event->y();

		if(started_scissor && draw_seed) {
			// if already started iscissor
			int* t = dis2img(event->x(), event->y());
			int ti = t[0];
			int tj = t[1];
			handler->getPath(ti, tj, path);
			cout << "Computing new path..." << path.size() << endl;
			repaint();
		}
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
		//cout << qimg.width() << ", " << qimg.height() << endl;
		//cout << this->width() << ", " << this->height() << endl;
		if(started_scissor) {
			//seed_x = event->x();
			//seed_y = event->y();
			//double orig_i = seed_x*(qimg.width()-2)/this->width();
			//double orig_j = seed_y*(qimg.height()-2)/this->height();
			int* tem = dis2img(event->x(), event->y());
			// Update mouse clicked pixel pos
			img_x = tem[0];
			img_y = tem[1];
			cout << "From displayer: " << tem[0] << ", " << tem[1] << endl;
			
			// set new seed to the image matrix
			handler->setSeed(img_x, img_y);
			// Compute a new tree
			handler->LiveWireDP(img_x, img_y);

			// Paint for test
			draw_seed = true;
		}
		repaint();
	}
}